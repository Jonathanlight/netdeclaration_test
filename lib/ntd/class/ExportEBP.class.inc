<?php


class ExportEBP {

  const FOLDER_PATH = 'doc/ebp';
  const CSV_COMPTES_FOLDER_NAME = 'comptes';
  const CSV_ECRITURES_FOLDER_NAME = 'ecritures';

  public static $export_ecritures_types = array('ve' => 'Ventes (VE)', 'bq' => 'Règlements (BQ)');

  public static function exportComptes($begin_at, $end_at) {
    self::checkFolders();

    if (Date::isNull($begin_at)) {
      $begin_at = Date::today();
    }
    if (Date::isNull($end_at)) {
      $end_at = Date::today();
    }

    $filename = date('Ymd', strtotime($begin_at)) . '_' . date('Ymd', strtotime($end_at)) . '_COMPTES.txt';
    if ($begin_at == $end_at) {
      $filename = date('Ymd', strtotime($begin_at)) . '_COMPTES.txt';
    }

    $columns = array('Numéro de compte',
                     'Intitulé',
                     'Raison sociale',
                     'Adresse',
                     'Code postal',
                     'Ville',
                     'Pays',
                     'Interlocuteur',
                     'Téléphone',
                     'Fax',
    );
    $filepath = self::FOLDER_PATH . '/' . self::CSV_COMPTES_FOLDER_NAME . '/' . $filename;
    $file = File::getInstance($filepath, 'w');
    $csv = CsvWriter::getInstance(array('delimiter' => '',
                                        'separator' => ',',
                                        'eol' => "\r",
                                        'columns' => $columns,
                                        'fd' => $file));
    $adherents = Adherent::collect(array('filters' => array('|><|created_at' => array($begin_at, $end_at)),
                                         'order' => array('created_at' => 'DESC'),
                                         'metas' => array('created_at')));
    foreach ($adherents as $adherent) {
      try {
        $row = array('Numéro de compte' => '411' . str_pad($adherent->getId(), 5, '0', STR_PAD_LEFT),
                     'Intitulé' => $adherent->company,
                     'Raison sociale' => $adherent->company,
                     'Adresse' => $adherent->address,
                     'Code postal' => $adherent->zipcode,
                     'Ville' => $adherent->city,
                     'Pays' => Country::getInstance($adherent->country_id)->name_fr,
                     'Interlocuteur' => $adherent->getUser()->email,
                     'Téléphone' => $adherent->phone,
                     'Fax' => $adherent->siret);
        $csv->append($row);
      }
      catch (Exception $e) {
        S('log')->error($e, __METHOD__);
      }
    }
    return $file;
  }

  public static $prestation_service = array(
    'siege' => array('metropole' => array('20.00' => '70602000',
                                          'default' => '70600000'),
                     'domtom' => array('default' => '70600100'),
                     'corse' => array('default' => '70600200'),
                     'monaco' => array('default' => '70600300'),
                     'ue' => array('default' => '70620000'),
                     'international' => array('default' => '70630000'),
                     'suspension' => array('default' => '70640000'),
    ),
    'bureau_secondaire' => array('metropole' => array('default' => '70650000'),
                                 'domtom' => array('default' => '70650100')),
  );

  public static $tva_code = array(
    'siege' => array('metropole' => array('20.00' => '44571340',
                                          '19.60' => '44571130',
                                          '5.50' => '44571140',
                                          '2.10' => '44571150',
                                          '7.00' => '44571170'),
                     'domtom' => array('8.50' => '44571220',
                                       '2.10' => '44571230'),
                     'corse' => array('20.00' => '44571340',
                                      '19.60' => '44571320',
                                      '8.00' => '44571330'),
                     'monaco' => array('19.60' => '44571430',
                                       '5.50' => '44571440',
                                       '2.10' => '44571450',
                                       '7.00' => '44571470'),
    ),
    'bureau_secondaire' => array('domtom' => array('8.50' => '44571520')),
  );
  public static $dom_coutry_ids = array('312', '474', '175', '638');
  public static $tom_coutry_ids = array('540', '254');


  public static function exportEcritures($begin_at, $end_at, $all, $export_types) {
    self::checkFolders();

    if (Date::isNull($begin_at)) {
      $begin_at = Date::today();
    }
    if (Date::isNull($end_at)) {
      $end_at = Date::today();
    }

    $filename = date('Ymd', strtotime($begin_at)) . '_' . date('Ymd', strtotime($end_at)) . '_ECRITURES.txt';
    if ($begin_at == $end_at) {
      $filename = date('Ymd', strtotime($begin_at)) . '_ECRITURES.txt';
    }



    $columns = array('Ligne',
                     'Date',
                     'Code journal',
                     'N° de compte',
                     'vide ?',
                     'Siret Adhérent',
                     'Raison sociale',
                     'Raison sociale (2)',
                     'Libellé automatique',
                     'Libellé',
                     'Pièce',
                     'Montant (associé au sens)',
                     'Sens',
                     'Date de l’échéance',
                     'Devise',
    );
    $filepath = self::FOLDER_PATH . '/' . self::CSV_ECRITURES_FOLDER_NAME . '/' . $filename;
    $file = File::getInstance($filepath, 'w');
    $csv = CsvWriter::getInstance(array('delimiter' => '',
                                        'separator' => ',',
                                        'eol' => "\r",
                                        'columns' => $columns,
                                        'fd' => $file));


    // JOURNAL DES VENTES
    if (in_array('ve', $export_types)) {

      $opts = array('filters' => array('|><|created_at' => array($begin_at, $end_at),
                                       '|>|price_ttc' => 0),
                    'metas' => array('created_at'));
      if (!$all) {
        $opts['filters']['|!&|flags'] = Facture::FLAG_EBP_EXPORTED;
      }
      $factures = Facture::collect($opts);

      $factures_exported = array();
      foreach ($factures as $facture) {

        try {

          $entite = 'siege'; // TODO : différenciation siege / bureau_secondaire à l'ouverture du 2eme site
          $region = 'international';
          $tva = (string) self::amount($facture->data_prices['percent_tva'] * 100);
          $country_id = $facture->data_address['country_id'];
          $zipcode = str_pad($facture->data_address['zipcode'], 5, '0', STR_PAD_LEFT);
          if (substr($zipcode, 0, 2) == '20') {
            $region = 'corse';
          }
          elseif ($country_id == 250) { // 250 == FRANCE
            $region = 'metropole';
          }
          elseif ($country_id == 492) { // 492 == Monaco
            $region = 'monaco';
          }
          elseif (in_array($country_id, self::$dom_coutry_ids)) {
            $region = 'domtom';
          }
          elseif (in_array($country_id, self::$tom_coutry_ids)) {
            $region = 'suspension';
          }



          $adherent = $facture->getAdherent();
          $date_echeance = $facture->is_renew_auto > 0 ? $facture->start_at : $facture->getMeta('created_at');
          $row = array('Ligne' => '',
                       'Date' => date('dmY', strtotime($facture->getMeta('created_at'))),
                       'Code journal' => 'VE',
                       'N° de compte' => '411' . str_pad($adherent->getId(), 5, '0', STR_PAD_LEFT),
                       'vide ?' => null,
                       'Siret Adhérent' => $adherent->siret,
                       'Raison sociale' => $adherent->company,
                       'Raison sociale (2)' => $adherent->company_bis,
                       'Libellé automatique' => '',
                       'Libellé' => $facture->getType() . ' N°' . $facture->getId() . ' - ' . $adherent->company,
                       'Pièce' => $facture->getType() . ' N°' . $facture->getId(),
                       'Montant (associé au sens)' => null,
                       'Sens' => null,
                       'Date de l’échéance' => date('dmY', strtotime($date_echeance)),
                       'Devise' => '');

          // TTC
          $row['vide ?'] = 'client';
          $row['Montant (associé au sens)'] = self::amount($facture->data_prices['price_ttc']);
          $row['Sens'] = $facture->type == Facture::TYPE_FACTURE ? 'D' : 'C';
          $csv->append($row);



          // TVA
          if (!($region == 'suspension' || $tva == '0.00')) {
            $row['N° de compte'] = self::$tva_code[$entite][$region][$tva];
            $row['vide ?'] = 'TVA ' . self::amount(($facture->data_prices['percent_tva'] * 100)) . '%';
            $row['Montant (associé au sens)'] = self::amount($facture->data_prices['price_tva']);
            $row['Sens'] = $facture->type == Facture::TYPE_FACTURE ? 'C' : 'D';
            $csv->append($row);
          }


          // HT
          $compte = isset(self::$prestation_service[$entite][$region][$tva])
              ? self::$prestation_service[$entite][$region][$tva]
              : self::$prestation_service[$entite][$region]['default'];
          $row['N° de compte'] = $compte;
          $row['vide ?'] = 'PRESTATIONS DE SERVICES';
          $row['Montant (associé au sens)'] = self::amount($facture->data_prices['price_ht']);
          $row['Sens'] = $facture->type == Facture::TYPE_FACTURE ? 'C' : 'D';
          $csv->append($row);
          $factures_exported[$facture->getId()] = $facture->getId();

        }
        catch (Exception $e) {
          S('log')->error($e, __METHOD__);
        }
      }
    }



    // PAIEMENTs
    $payments_exported = array();

    $opts = array();
    $opts['filters']['status'] = Payment::STATUS_RECEIVED;
    $opts['filters']['|><|paid_at'] = array($begin_at, $end_at);
    $opts['filters']['|>|method_id'] = 0;
    if (!$all) {
      $opts['filters']['|!&|flags'] = Payment::FLAG_EBP_EXPORTED;
    }
    $opts['order']['paid_at'] = 'ASC';
    $payments = Payment::collect($opts);

    $payments_by_dates = array();
    foreach ($payments as $payment) {
      $method = $payment->getMethod();
      if ($method->code == 'cb' || $method->code == 'cheque') {
        $payments_by_dates[$payment->paid_at][$payment->method_id][0][] = $payment;
      }
      elseif ($method->code == 'prelevement' || $method->code == 'virement') {
        $payments_by_dates[$payment->paid_at][$payment->method_id][][] = $payment;
      }
    }

    $payment_libelles = array('cb' => 'CB',
                              'cheque' => 'CHQ',
                              'prelevement' => 'Prélèvement',
                              'virement' => 'Virement');
    if (in_array('bq', $export_types)) {
      foreach ($payments_by_dates as $paid_at => $payments_by_method_id) {
        foreach ($payments_by_method_id as $method_id => $group_payments) {
          foreach ($group_payments as $payments) {
            try {
              $method = Method::getInstance($method_id);
              $montant_total = 0;
              foreach ($payments as $payment) {
                $montant_total += $payment->amount;
              }

              $libelle = '';
              if ($method->code == 'cb') {
                $libelle = 'CB';
              }
              elseif ($method->code == 'cheque') {
                $libelle = 'RC';
              }
              $row = array('Ligne' => '',
                           'Date' => date('dmY', strtotime($paid_at)),
                           'Code journal' => 'BQ',
                           'N° de compte' => '51210000',
                           'vide ?' => 'BANQUE',
                           'Siret Adhérent' => '',
                           'Raison sociale' => '',
                           'Raison sociale (2)' => '',
                           'Libellé automatique' => '',
                           'Libellé' => $libelle,
                           'Pièce' => $method->code,
                           'Montant (associé au sens)' => self::amount($montant_total),
                           'Sens' => 'D',
                           'Date de l’échéance' => date('dmY', strtotime($paid_at)),
                           'Devise' => '');
              $csv->append($row);

              foreach ($payments as $payment) {
                $facture = $payment->getFactures()->first();

                $adherent = $facture->getAdherent();
                $libelle = $payment_libelles[$method->code] . ' ' . $payment->name;

                $row['N° de compte'] = '411' . str_pad($adherent->getId(), 5, '0', STR_PAD_LEFT);
                $row['vide ?'] = 'client';
                $row['Siret Adhérent'] = $adherent->siret;
                $row['Raison sociale'] = $adherent->company_bis;
                $row['Raison sociale (2)'] = $adherent->company;
                $row['Libellé'] = $adherent->company . ' - ' . $libelle;
                $row['Montant (associé au sens)'] = self::amount($payment->amount);
                $row['Date de l’échéance'] = date('dmY', strtotime($paid_at));
                $row['Sens'] = 'C';

                $csv->append($row);

                $payments_exported[$payment->getId()] = $payment->getId();
              }

            }
            catch (Exception $e) {
              S('log')->error($e, __METHOD__);
            }
          }
        }
      }
    }

    if (!$all) {
      if (count($factures_exported) > 0) {
        foreach (Facture::collect(array('filters' => array('|IN|id' => $factures_exported))) as $facture) {
          $facture->setFlag(Facture::FLAG_EBP_EXPORTED);
        }
      }
      if (count($payments_exported) > 0) {
        foreach (Payment::collect(array('filters' => array('|IN|id' => $payments_exported))) as $payment) {
          $payment->setFlag(Payment::FLAG_EBP_EXPORTED);
        }
      }
    }


    return $file;
  }

  public static function amount($amount) {
    $amount = number_format($amount, 4, '.', '');
    return substr($amount, 0, -2);
  }


  public static function checkFolders() {
    if (!Folder::exists(self::FOLDER_PATH)) {
      Folder::create(self::FOLDER_PATH, true);
    }
    if (!Folder::exists(self::FOLDER_PATH . '/' . self::CSV_COMPTES_FOLDER_NAME)) {
      Folder::create(self::FOLDER_PATH . '/' . self::CSV_COMPTES_FOLDER_NAME, true);
    }
    if (!Folder::exists(self::FOLDER_PATH . '/' . self::CSV_ECRITURES_FOLDER_NAME)) {
      Folder::create(self::FOLDER_PATH . '/' . self::CSV_ECRITURES_FOLDER_NAME, true);
    }
  }

}
