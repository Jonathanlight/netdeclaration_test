<?php

class Facture extends ActiveRecord
{

  const STATUS_RESILIE = -1;
  const STATUS_NON_PAYE = 0;
  const STATUS_PAYE = 1;
  const STATUS_PENDING = 2;

  const PAYMENT_MODE_PRELEVEMENT = 4;

  public static $statuses = array(
    self::STATUS_RESILIE => 'facture résiliée',
    self::STATUS_NON_PAYE => 'facture à payer',
    self::STATUS_PENDING => 'facture en attente de réception du paiement',
    self::STATUS_PAYE => 'facture payée',
  );

  public static $colors = array(
    self::STATUS_RESILIE => 'black',
    self::STATUS_NON_PAYE => 'blue',
    self::STATUS_PENDING => 'yellow',
    self::STATUS_PAYE => 'green',
  );


  const TYPE_FACTURE = 0;
  const TYPE_AVOIR = 1;

  public static $types = array(
    self::TYPE_FACTURE => 'Facture',
    self::TYPE_AVOIR => 'Avoir'
  );

  const FLAG_EBP_EXPORTED = 1;
  const FLAG_RESILIE_NON_PAYE = 2;
  const FLAG_RAPPEL_1 = 4;
  const FLAG_RAPPEL_2 = 8;
  const FLAG_RAPPEL_3 = 16;
  const FLAG_RAPPEL_RESILIATED = 32;

  const PATH_PDF = 'doc/factures';
  const PATH_RECOVERY_PDF = 'doc/recovery';


  public static $flags = array(
    self::FLAG_EBP_EXPORTED => 'Exporté EBP',
    self::FLAG_RESILIE_NON_PAYE => 'Résiliée à cause d\'un non-paiement',
    self::FLAG_RAPPEL_1 => 'Rappel N°1',
    self::FLAG_RAPPEL_2 => 'Rappel N°2',
    self::FLAG_RAPPEL_3 => 'Rappel N°3',
    self::FLAG_RAPPEL_RESILIATED => 'Résiliation',
  );

  public static $adherent_paymentmode_facture_methods_maps = array(
    Adherent::BILLING_PAYMENT_MODE_CHEQUE => 'cheque',
    Adherent::BILLING_PAYMENT_MODE_PREVELEMENT => 'prelevement',
    Adherent::BILLING_PAYMENT_MODE_VIREMENT => 'virement',
  );

  public static $bo_export_statuses = array(
    self::STATUS_NON_PAYE => 'Toutes',
    self::STATUS_PAYE => 'Payées',
    self::STATUS_PENDING => 'En attente de paiement'
  );

  public static function getOldMethodID($adherent)
  {
    $method_id = 0;
    $method_code = self::$adherent_paymentmode_facture_methods_maps[$adherent->billing_payment_mode];
    if (!empty($method_code) && Method::exists(array('code' => $method_code))) {
      $method_id = Method::getInstance(array('code' => $method_code))->getId();
    }
    return $method_id;
  }

  public $_commit = array();

  public function setAdherent(Adherent $adherent)
  {
    $this->_commit['adherent_id'] = $adherent->getId();
    $this->_commit['data_adherent'] = $adherent->asFactureHash();
    $this->_commit['data_address'] = $adherent->getBillingAddressHash();
  }

  public function addTarif(Tarif $tarif, $quantity = 1, $date_from = null, $date_to = null, $regularization = false, $adherent = null)
  {
    if ($adherent instanceof Adherent && in_array($adherent->type, Adherent::$typesMinimumQuantity)) {
      $quantity = $quantity > 1 ? $quantity : 1;
    }
    $quantity = $quantity; // Update 12/12/2018 => set minimum quantity to 1
    $purchase = array(
      'name' => $regularization ? 'Regularisation - ' . $tarif->name : $tarif->name,
      'price' => $tarif->price,
      'quantity' => $quantity,
      'date_from' => $date_from,
      'date_to' => $date_to
    );
    $this->addPurchase($purchase);
  }

  public function addPurchase($hash)
  {
    $data_purchases = $this->_commit['data_purchases'];
    $hash['price_total_ht'] = $hash['price'] * $hash['quantity'];
    $data_purchases[] = $hash;
    $this->_commit['data_purchases'] = $data_purchases;
  }

  public function calculate()
  {

    // PRIX HT
    $price_ht = 0;
    $price_plus_ht = 0;
    $rebate = array();
    foreach ((array)$this->_commit['data_purchases'] as $purchase) {
      $price_ht += $purchase['price_total_ht'];
      // REMBOURSEMENT
      if ($purchase['price_total_ht'] < 0) {
        $rebate[] = array(
          'label' => trim($purchase['name'], '.'),
          'price_total_ht' => $purchase['price_total_ht']
        );
      } else {
        $price_plus_ht += $purchase['price_total_ht'];
      }
    }

    // TAXES
    if ($this->_commit['data_address']['country_id'] == 0) {
      S('log')->error('country_id = 0', __METHOD__);
      return false;
    }
    $country = Country::getInstance((int)$this->_commit['data_address']['country_id']);
    $tax = $country->taxes;
    $price_tva = $price_ht * $tax;
    $price_ttc = $price_ht + $price_tva;

    $this->_commit['data_prices'] = array(
      'price_ht' => $price_ht,
      'price_plus_ht' => $price_plus_ht,
      'percent_tva' => $tax,
      'rebate' => $rebate,
      'price_tva' => $price_tva,
      'price_ttc' => $price_ttc
    );
    $this->_commit['data_reglement'] = array(
      'ref_bancaires' => l('snippet:ntd.facture.reglement.ref_bancaires'),
      'informations' => l('snippet:ntd.facture.reglement.informations')
    );
    $this->_commit['price_ttc'] = $price_ttc;

    return $this->_commit['data_prices']['price_ht'];
  }

  public function getPriceHT()
  {
    return $this->data_prices['price_ht'];
  }

  public function getStatus()
  {
    if ($this->type == Facture::TYPE_AVOIR) return 'avoir';
    return self::$statuses[$this->status];
  }

  public function getType($prefix_article = false)
  {
    if ($prefix_article) {
      $prefix = ($this->type == Facture::TYPE_AVOIR) ? "l'" : "la ";
    }
    return $prefix . self::$types[$this->type];
  }

  public function isResiliable()
  {
    if ($this->status == self::STATUS_RESILIE) return false;
    $opts = array('filters' => array(
      '|>|price' => 0,
      '|!=|status' => Souscription::STATUS_CANCELLED
    ));
    if ($this->getSouscriptions($opts)->count() > 0) return false;
    return true;
  }

  /* ----- INTERFACE hooks ----- */
  protected function onBeforeCommit(&$attrs)
  {
    if (!empty($this->_commit)) {
      foreach ($this->_commit as $key => $value) {
        $attrs[$key] = $value;
      }
    }
  }

  protected function onAfterCommit($attrs)
  {

    if ($this->status == self::STATUS_PAYE && $this->_changes['status'] != self::STATUS_PAYE) {
      $souscriptions = $this->getSouscriptions();
      foreach ($souscriptions as $souscription) {
        $souscription->commit(array('status' => Souscription::STATUS_ACTIVE));
      }
    }
    if (!(strtotime($this->start_at) > 0)) {
      $souscriptions = $this->getSouscriptions();
      if ($souscriptions->count() > 0) {
        $this->setAttribute('start_at', $souscriptions->first()->start_at);
        $this->setAttribute('finish_at', $souscriptions->first()->finish_at);
      }
    }
    if (empty($this->name)) {
      $this->setAttribute('name', Facture::$types[$this->type] . ' N°' . $this->getId());
    }

    /*if ($this->status == self::STATUS_PAYE && $this->_changes['status'] != self::STATUS_PAYE) {
      if ($this->method_id > 0 && Date::isNull($this->method_date)) {
        $method = $this->getMethod();
        if ($method->code == 'prelevement') {
          $this->setAttribute('method_date', $this->getAttribute('start_at'));
        }
        elseif ($method->code == 'virement') {
          $this->setAttribute('method_date', Date::today());
        }
        elseif ($method->code == 'cb') {
          $this->setAttribute('method_date', Date::today());
        }
      }
    }*/
  }

  public function asUrl()
  {
    return '/middle/facture/-/id/' . $this->getId();
  }

  public function send($recipient = null)
  {
    $adherent = $this->getAdherent();
    $recipient = $recipient === null ? $this->getAdherent()->getEmailFacture() : $recipient;
    $bindings = array(
      'facture_id' => $this->getId(),
      'prenom' => $adherent->first_name,
      'nom' => $adherent->last_name,
      'company_name' => $adherent->getBillingAddressHash('company'),
      'siret' => $adherent->siret,
      'facture_url' => H::url('/middle/facture', array('id' => $this->getId()))
    );
    if ($this->type == Facture::TYPE_AVOIR) {
      Letter::send('avoir.send', $recipient, $bindings);
    } else {
      Letter::send('facture.send', $recipient, $bindings);
    }
    return $recipient;
  }

  public function asFinderHash($hash)
  {
    $adherent = $this->getAdherent();
    $hash['adherent_identity'] = $adherent->identity();
    $hash['price_ttc'] = H::amount($this->data_prices['price_ttc']);
    $hash['_color'] = self::$colors[$this->status];
    $hash['method_date'] = '';
    $hash['method_details'] = '';
    if ($this->status == self::STATUS_PAYE) {
      $payments = $this->getPayments(array(
        'filters' => array('status' => Payment::STATUS_RECEIVED),
        'order' => array('paid_at' => 'ASC')
      ));
      $dates = array();
      $details = array();
      foreach ($payments as $payment) {
        $dates[] = H::date($payment->paid_at);
        $details[] = $payment->name;
      }
      $hash['method_date'] = implode(', ', $dates);
      $hash['method_details'] = implode(', ', $details);
    }
    //$hash['flag_ebp_exported'] = $this->hasFlag(self::FLAG_EBP_EXPORTED) ? 'oui' : '';
    //$hash['flag_resilie_non_paye'] = $this->hasFlag(self::FLAG_RESILIE_NON_PAYE) ? 'oui' : '';
    $hash['start_at'] = $this->start_at == '00-00-0000' ? '' : H::date($this->start_at);
    $hash['finish_at'] = $this->finish_at == '00-00-0000' ? '' : H::date($this->finish_at);
    return $hash;
  }

  public function onFind($finder)
  {
    $coll = $finder->getCollection();
    $filters = $coll->getFilters();
    if (!empty($filters['method_date_begin_at'])) {
      $filters['|>=|method_date'] = Date::toDb($filters['method_date_begin_at']) . ' 00:00:00';
      unset($filters['method_date_begin_at']);
    }
    if (!empty($filters['method_date_end_at'])) {
      $filters['|<=|method_date'] = Date::toDb($filters['method_date_end_at']) . ' 00:00:00';
      unset($filters['method_date_end_at']);
    }
    $coll->setFilters($filters);
  }

  public function asEditHash()
  {
    $hash = array();
    //$hash['data_adherent'] = $this->data_adherent;
    //$hash['data_adherent']['civility'] = Adherent::$civilities[$hash['data_adherent']['civility']];
    //$hash['data_adherent'] = implode("\r\n", $hash['data_adherent']);

    //$hash['data_address'] = $this->data_address;
    //$hash['data_address']['country_id'] = Country::getInstance($hash['data_address']['country_id'])->name_fr;
    //$hash['data_address'] = implode("\r\n", $hash['data_address']);

    $hash['price_ht'] = H::amount($this->data_prices['price_ht']);
    $hash['price_tva'] = H::amount($this->data_prices['price_tva']);
    $hash['price_ttc'] = H::amount($this->data_prices['price_ttc']);
    $hash['percent_tva'] = ($this->data_prices['percent_tva'] * 100) . '%';

    $hash['method_name'] = $this->method_id > 0 ? $this->getMethod()->getName() : 'non choisi';

    $hash['can_validate'] = $this->status != self::STATUS_PAYE;
    $hash['can_setpending'] = $this->status != self::STATUS_NON_PAYE;

    $datas_adherent = $this->data_adherent;
    $datas_adherent['civility'] = Adherent::$civilities[$datas_adherent['civility']];
    $datas_adherent['country_id'] = Country::getInstance($datas_adherent['country_id'])->name_fr;
    $datas_address = $this->data_address;
    $datas_address['country_id'] = Country::getInstance($datas_address['country_id'])->name_fr;

    S('ctx')->setAttribute('datas_adherent', $datas_adherent);
    S('ctx')->setAttribute('datas_address', $datas_address);

    return $hash;
  }

  public function getAttribute($key)
  {
    if ($key == 'adherent_siret') return $this->data_adherent['siret'];
    if ($key == 'adherent_company') return $this->data_adherent['company'];
    if ($key == 'address_company') return $this->data_address['company'];
    if ($key == 'address_address') return $this->data_address['address'];
    if ($key == 'address_zipbox') return $this->data_address['zipbox'];
    if ($key == 'address_zipcode') return $this->data_address['zipcode'];
    if ($key == 'address_city') return $this->data_address['city'];
    if ($key == 'address_country_id') return $this->data_address['country_id'];
    if ($key == 'address_mail') return $this->data_address['mail'];
    if ($key == 'prices_ht') return H::amount($this->data_prices['price_ht']);
    if ($key == 'percent_tva') return number_format($this->data_prices['percent_tva'] * 100, 2, ',', '');
    if ($key == 'prices_ttc') return H::amount($this->data_prices['price_ttc']);
    if ($key == 'prices_tva') return H::amount($this->data_prices['price_tva']);
    if ($key == 'meta_created_at') return $this->getMeta('created_at');
    if ($key == 'status_label') return $this->getStatus();
    if ($key == 'method_name') return $this->method_id > 0 ? $this->getMethod()->name : '-';
    if ($key == 'services_names') {
      $attribute = array();
      foreach ($this->getSouscriptions() as $souscription) {
        $attribute[] = $souscription->service_name;
      }
      return implode(', ', $attribute);
    }
    if ($key == 'user_email') {
      try {
        return $this->getAdherent()->getUser()->email;
      } catch (Exception $e) {
        return "pas d'email trouvé";
      }
    }
    return parent::getAttribute($key);
  }

  public function asSummaryText($as_html = false)
  {

    if (!isset($this->_commit['data_purchases'])) {
      return null;
    }

    $style = "border: 1px solid #000000; padding:2px 5px; line-height: 20px;";
    $html = '';

    if ($as_html) {
      $html .= '<table class="table-facture-summary" style="border-collapse:collapse; width:100%;">';
      $html .= '<thead>
      <tr>
      <th align="right"  style="' . $style . '">N°</th>
      <th align="left"  style="' . $style . '">Nom</th>
      <th align="center"  style="' . $style . '">Période</th>
      <th align="right"  style="' . $style . '">Prix</th>
      <th align="right"  style="' . $style . '">Quantité</th>
      <th align="right"  style="' . $style . '">Prix Total HT</th>
      </tr>

      </thead>';
    } else {
      $textes[] = "Prix TTC : \t" . H::amount($this->_commit['price_ttc']);
    }

    if ($as_html) {
      $html .= "<tbody>";
    } else {
      $textes[] = "\n# produits facturés ";
    }
    foreach ($this->_commit['data_purchases'] as $index => $purchase) {
      if (!$purchase['price'] > 0) {
        continue;
      }
      if ($as_html) {
        $html .= '<tr>';
        $html .= '<td align="right" style="' . $style . '">' . ($index + 1) . '</td>';
        $html .= '<td align="left"  style="' . $style . '">' . $purchase['name'] . '</td>';
        $html .= '<td align="center"  style="' . $style . '">' . H::date($purchase['date_from']) . ' à ' . H::date($purchase['date_to']) . '</td>';
        $html .= '<td align="right"  style="' . $style . '">' . H::amount($purchase['price']) . '</td>';
        $html .= '<td align="right"  style="' . $style . '">' . $purchase['quantity'] . '</td>';
        $html .= '<td align="right"  style="' . $style . '">' . H::amount($purchase['price_total_ht']) . '</td>';
        $html .= '</tr>';
      } else {
        $textes[] = "Produit N°" . ($index + 1);
        $textes[] = "Nom : \t\t" . $purchase['name'];
        $textes[] = "Période : \t" . H::date($purchase['date_from']) . " à " . H::date($purchase['date_to']);
        $textes[] = "Prix : \t\t" . H::amount($purchase['price']);
        $textes[] = "Quantité : \t" . $purchase['quantity'];
        $textes[] = "Prix Total HT : " . H::amount($purchase['price_total_ht']);
        $textes[] = '';
      }
    }
    if ($as_html) {
      $html .= '</tbody><tfoot><tr><th colspan="5" align="right"  style="' . $style . '">Prix TTC</th>
      <th align="right"  style="' . $style . '">' . H::amount($this->_commit['price_ttc']) . '</th></tr></tfoot>';
      $html .= "</table>";
    } else {
    }

    return $as_html ? $html : implode("\n", $textes);
  }

  public function asRelationRow($relation, $row)
  {
    if ($relation instanceof Payment) {
      return '[montant : ' . $row['amount'] . '][' . Payment::$statuses[$relation->status] . '] ' . $relation->name;
    }
    return $relation->getName();
  }

  public static function getUnpaiedFactures($opts = array())
  {
    $opts['filters']['|IN|' . T('facture') . '.status'] = array(Facture::STATUS_NON_PAYE, Facture::STATUS_PENDING);
    $opts['filters']['|>|' . T('facture') . '.price_ttc'] = 0;
    $opts['filters']['|!=|' . T('facture') . '.is_renew_auto'] = 2;
    $opts['filters']['' . T('facture') . '.type'] = Facture::TYPE_FACTURE;
    return Facture::collect($opts);
  }

  public function sendLetter($code)
  {
    $adherent = $this->getAdherent();
    $bindings = array(
      'prenom' => $adherent->first_name,
      'nom' => $adherent->last_name,
      'siret' => $adherent->siret,
      'company_name' => $adherent->getBillingAddressHash('company'),
      'id_facture' => $this->getId(),
      'signature' => l('snippet:letter.footer'),
      'link' => '<a href="' . H::url($this->asUrl()) . '">Lien vers la facture</a> '
    );
    $email = $adherent->getEmailFacture();
    if (P('app.state') == 'prod' || P('app.state') == 'dev') {
      Letter::send($code, $email, $bindings);
    }
  }

  public function getPdfPath()
  {
    return self::PATH_PDF . '/' . $this->getId() . '.pdf';
  }

  public function generatePdf()
  {

    if (!Folder::exists(self::PATH_PDF)) {
      Folder::create(self::PATH_PDF, true);
    }

    $path_target = $this->getPdfPath(); //self::PATH_PDF.'/'.$this->getId().'-'.time().'.pdf';
    $path_source = str_replace('.pdf', '.html', $path_target);


    if (S('req')->isMiddle()) {
      S('log')->debug('accout', __METHOD__);
      $content = H::get('/account/ntd/facture.print', array('id' => $this->getId()));
    } elseif (S('req')->isBack()) {
      $content = H::get('/back/ntd/facture.print.pdf', array('id' => $this->getId()));
    }

    // TODO : use H::inc
    $user = $this->getAdherent()->getUser();
    $header = H::url('/skeleton.pdf.header', array(
      'domtom' => $user->hasFlag(User::FLAG_NTD_DOMTOM),
      'head_title' => base64_encode($this->getType() . ' N°' . $this->getId())
    ));
    $footer = H::url('/skeleton.pdf.footer', array('domtom' => $user->hasFlag(User::FLAG_NTD_DOMTOM)));

    $fp = fopen($path_source, 'w');
    fwrite($fp, $content);
    fclose($fp);

    if (P('auth.login') && P('auth.password')) {
      $username = P('auth.login');
      $password = P('auth.password');
    } else {
      $username = null;
      $password = null;
    }

    $options = array(
      '--header-html' => '\'' . $header . '\'',
      '--footer-html' => '\'' . $footer . '\'',
      '--username' => $username,
      '--password' => $password,
      '--page-size' => 'A4',
      '--margin-top' => '34',
      '--margin-left' => '0',
      '--margin-right' => '0',
      '--margin-bottom ' => '20',
      '--header-spacing' => '0',
      '--footer-spacing' => '0',
      '--outline-depth' => '0'
    );

    system('/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf ' . NetDeclaration::asShellParams($options) . ' \'' . $path_source . '\' \'' . $path_target . '\'"');
    //unlink($path_source);

    return $path_target;
  }

  public function isRemindable()
  {
    foreach ($this->getSouscriptions() as $souscription) { // of suscribed services
      $opts = array(
        'filters' => array(
          'adherent_id' => $souscription->adherent_id,
          'service_id' => $souscription->service_id,
          'start_at' => date('Y-m-d', strtotime('-1 year', strtotime($souscription->start_at)))
        )
      );
      $old_souscriptions = Souscription::collect($opts);

      foreach ($old_souscriptions as $old_souscription) {
        if ($old_souscription->status == Souscription::STATUS_CANCELLED &&
          !$old_souscription->hasFlag(Souscription::FLAG_CANCELLED_FACTURE_NON_PAYE)) {
          return true;
        }
      }
    }
    return false;
  }
}
