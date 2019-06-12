<?php

try {

  $csv_export_columns = array(
    'id' => 'Facture ID',
    'adherent_siret' => 'Adhérent SIRET',
    'adherent_company' => 'Adhérent raison sociale',
    'user_email' => 'E-mail adhérent',
    'address_company' => 'Adresse raison sociale',
    'address_address' => 'Facturation : Adresse',
    'address_zipbox' => 'Facturation : Boîte postale',
    'address_zipcode' => 'Facturation : Code postal',
    'address_city' => 'Facturation : Ville',
    'address_country_id' => 'Facturation : Pays',
    'address_mail' => 'Facturation : Email',
    'prices_ht' => 'Prix HT',
    'percent_tva' => 'Taux TVA',
    'prices_tva' => 'Prix TVA',
    'prices_ttc' => 'Prix TTC',
    'start_at' => 'Début',
    'finish_at' => 'Fin',
    'meta_created_at' => 'Date de création',
    'payment_paid_at' => 'Date de paiement',
    'status_label' => 'Statut',
    'services_names' => 'Services souscrits',
    'method_name' => 'Moyen de paiement'
  );

  $opts = array('order' => array('created_at' => 'DESC'),
                'metas' => array('created_at'));

  if ($req->hasAttribute('begin_at') || $req->hasAttribute('end_at')) {
    $begin_at = Date::toDb($req->begin_at);
    $end_at = Date::toDb($req->end_at);
    if (Date::isNull($begin_at)) {
      $begin_at = Date::today();
    }
    if (Date::isNull($end_at)) {
      $end_at = Date::today();
    }
    $opts['filters']['|><|created_at'] = array($begin_at, $end_at);
  }
  elseif ($req->hasAttribute('paid_begin_at') || $req->hasAttribute('paid_end_at')) {
    $begin_at = Date::toDb($req->paid_begin_at);
    $end_at = Date::toDb($req->paid_end_at);
    if (Date::isNull($begin_at)) {
      $begin_at = Date::today();
    }
    if (Date::isNull($end_at)) {
      $end_at = Date::today();
    }
    $opts['include'] = array('payment');
    $opts['filters']['|><|' . T('payment') . '.paid_at'] = array($begin_at, $end_at);
    $opts['filters'][T('payment') . '.status'] = Payment::STATUS_RECEIVED;
    $opts['filters']['status'] = Facture::STATUS_PAYE;
  }

  $filename = date('Ymd', strtotime($begin_at)) . '_' . date('Ymd', strtotime($end_at)) . '_FACTURES.csv';
  if ($begin_at == $end_at) {
    $filename = date('Ymd', strtotime($begin_at)) . '_FACTURES.csv';
  }

  $factures = Facture::collect($opts);

  $csv = new CsvWriter(array('filename' => $filename));
  $csv->append(array_map("encodeUTF8ToWin1252", $csv_export_columns));
  foreach ($factures as $facture) {
    try {
      $hash = array();
      foreach (array_keys($csv_export_columns) as $column) {
        $hash[$column] = $facture->getAttribute($column);
      }
      if (Country::exists($hash['address_country_id'])) {
        $hash['address_country_id'] = Country::getInstance($hash['address_country_id'])->name_fr;
      }
      $csv->append(array_map("encodeUTF8ToWin1252", $hash));
    }
    catch (Exception $e) {
      $log->error($e);
    }
  }

}
catch (Exception $e) {
  $err->add($e);
}


function encodeUTF8ToWin1252($field) {
  return iconv('UTF-8', 'windows-1252', $field);
}
