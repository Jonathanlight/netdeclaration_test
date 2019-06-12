<?php

class Adherent extends ActiveRecord {

  const TYPE_CEC = 1;
  const TYPE_ENTREPRISE = 2;
  const TYPE_OGA = 3;
  const TYPE_PRO_SANTE = 4;
  const TYPE_INTERNATIONAL = 5;

  public static $typesMinimumQuantity = array(
        self::TYPE_ENTREPRISE,
        self::TYPE_PRO_SANTE,
        self::TYPE_INTERNATIONAL,
  );

  const STATUS_SUBSCRIPTION_PENDING = 1;
  const STATUS_SUBSCRIPTION_SIGNATURE = 10;
  const STATUS_SUBSCRIPTION_VALIDE = 20;

  const LEVEL_TARIF_PRIMARY = Tarif::ADHERENT_LEVEL_PRIMARY;
  const LEVEL_TARIF_SECONDARY = Tarif::ADHERENT_LEVEL_SECONDARY;

  const BILLING_PAYMENT_MODE_CHEQUE = 1;
  const BILLING_PAYMENT_MODE_PREVELEMENT = 2;
  const BILLING_PAYMENT_MODE_VIREMENT = 3;

  const FLAG_CEC_AVOCAT = 1;


  public static $types = array(
    self::TYPE_CEC => 'Cabinet Expert-Comptable & Avocat',
    self::TYPE_ENTREPRISE => 'Entreprise',
    self::TYPE_OGA => 'Organisme de Gestion Agréé',
    self::TYPE_PRO_SANTE => 'Professionnel de la santé',
    self::TYPE_INTERNATIONAL => 'International',
  );

  public static $cec_flags = array(
    self::FLAG_CEC_AVOCAT => 'adherent.cec.avocat'
  );

  public static $types_mapping = array(
    5 => Adherent::TYPE_INTERNATIONAL,
    4 => Adherent::TYPE_PRO_SANTE,
    3 => Adherent::TYPE_ENTREPRISE,
    2 => Adherent::TYPE_CEC,
    1 => Adherent::TYPE_OGA
  );

  public static $types_shorts = array(
    self::TYPE_CEC => 'CEC',
    self::TYPE_ENTREPRISE => 'Entreprise',
    self::TYPE_OGA => 'OGA',
    self::TYPE_PRO_SANTE => 'Santé',
    self::TYPE_INTERNATIONAL => 'International'
  );

  public static $statuses = array(
    self::STATUS_SUBSCRIPTION_PENDING => 'en attente',
    self::STATUS_SUBSCRIPTION_SIGNATURE => 'à signer',
    self::STATUS_SUBSCRIPTION_VALIDE => 'validé',
  );

  public static $levels = array(
    self::LEVEL_TARIF_PRIMARY => 'Tarif Niveau Primaire',
    self::LEVEL_TARIF_SECONDARY => 'Tarif Niveau Secondaire'
  );

  public static $civilities = array(
    0 => 'Monsieur',
    1 => 'Madame',
    2 => 'Mademoiselle');

  public static $civilities_abreges = array(
    0 => 'Mr',
    1 => 'Mme',
    2 => 'Mlle');


  public static $export_civilities = array(
    0 => 'M',
    1 => 'Mme',
    2 => 'Mle');

  public static $export_types = array(
    self::TYPE_CEC => 'CAB',
    self::TYPE_ENTREPRISE => 'ENT',
    self::TYPE_OGA => 'OGA',
    self::TYPE_PRO_SANTE => 'ENT',
    self::TYPE_INTERNATIONAL => 'ENT'
  );

  public static $billing_payment_modes = array(
    self::BILLING_PAYMENT_MODE_CHEQUE => 'Chèque',
    self::BILLING_PAYMENT_MODE_PREVELEMENT => 'Prélèvement',
    self::BILLING_PAYMENT_MODE_VIREMENT => 'Virement'
  );

  public static $newsletter_bases = array(
    self::TYPE_CEC           => NetDeclaration::NEWSLETTER_BASE_CEC,
    self::TYPE_ENTREPRISE    => NetDeclaration::NEWSLETTER_BASE_ENTREPRISE,
    self::TYPE_OGA           => NetDeclaration::NEWSLETTER_BASE_OGA,
    self::TYPE_PRO_SANTE     => NetDeclaration::NEWSLETTER_BASE_PRO_SANTE,
    self::TYPE_INTERNATIONAL => NetDeclaration::NEWSLETTER_BASE_INTERNATIONNAL
  );


  public function isMainAdherent() {
    return $this->adherent_id == 0;
  }

  public function cancelAllServices() {
    $souscriptions = $this->getAllSouscriptionsActive();
    foreach ($souscriptions as $souscription) {
      $context = $souscription->context;
      $context['cancel_at'] = Date::now();
      $commit = array('context' => $context,
                      'status' => Souscription::STATUS_CANCELLED,
                      'is_renewable' => 0);
      $souscription->commit($commit);
    }
  }

  public function identity($compte_level_info = false) {
    $identity = Adherent::$civilities_abreges[$this->civility] . ' ' . $this->first_name . ' ' . $this->last_name;
    if ($compte_level_info) $identity .= ' (Cpt ' . ($this->adherent_id > 0 ? '2nd' : '1er') . ') ';
    return $identity;
  }

  public function getAttribute($key) {
    if ($key == 'identity') return $this->identity();
    if ($key == 'name') return $this->identity();
    if ($key == 'siret_option') return $this->siret . ' -' . $this->identity();
    if ($key == 'country_id_label') return $this->country_id > 0 ? Country::getInstance($this->country_id) : '';
    if ($key == 'adherent_id_label') return $this->adherent_id > 0 ? 'primaire' : 'secondaire';
    if ($key == 'type_label') return self::$types[$this->type];
    if ($key == 'civility_label') return self::$civilities[$this->civility];
    if ($key == 'billing_country_id_label') {
      $billing_hash = $this->getBillingAddressHash();
      return $billing_hash['country_id'] > 0 ? Country::getInstance($billing_hash['country_id']) : '';
    }
    if ($key == 'billing_payment_mode_label') {
      $billing_hash = $this->getBillingAddressHash();
      return self::$billing_payment_modes[$billing_hash['payment_mode']];
    }
    return parent::getAttribute($key);
  }

  public function hasAccesEDI() {
    $opts = array('filters' => array('service_id' => NetDeclarationManager::SERVICE_ACCES_EDI,
                                     'adherent_id' => $this->getId(),
                                     array(
                                       array('|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED),
                                             '|<=|start_at' => Date::today(),
                                             '|>=|finish_at' => Date::today()),
                                       array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))
                                     )));
    $souscriptions = Souscription::collect($opts);
    return $souscriptions->count() > 0;
  }

  public function isAvocat() {
    return $this->type == self::TYPE_CEC && $this->hasFlag(self::FLAG_CEC_AVOCAT, 'cec_flags');
  }

  /* ----- INTERFACE hooks ----- */
  protected function onBeforeUpdate(&$attrs)
  {
      if (isset($attrs['partenaire_id']) && $attrs['partenaire_id']) {
          $oldPartenaire = null;
          if ($this->partenaire_id) {
              $oldPartenaire = $this->getPartenaire();
          }
          $newPartenaire = Partenaire::getInstance($attrs['partenaire_id']);

          if ($oldPartenaire != $newPartenaire) {
              $souscriptions = Souscription::collect(array('filters' => array('adherent_id' => $this->getId())));
              foreach ($souscriptions as $souscription) {
                  if ($newPartenaire->hasService($souscription->service_id) && $newPartenaire->status == Partenaire::STATUS_ONLINE) {
                      $attr = array(
                          'partenaire_id' => $newPartenaire->getId(),
                          'commission' => $souscription->price * (float)$newPartenaire->commission / 100
                      );
                      $souscription->commit($attr);
                  }
              }
          }
      }
  }

  protected function onBeforeCommit(&$attrs) {
    if (S('req')->isBack()) {
      if (isset($attrs['type'])) {
        Adherent::validateAdherent($attrs);
      }
    }
    if ($this->isLoaded()
      && isset($attrs['siret'])
      && !empty($this->siret)
      && $this->siret != $attrs['siret']
    ) {
      $attrs['old_sirets'] = $this->old_sirets;
      $attrs['old_sirets'][] = $this->siret;
    }
  }

  protected function onAfterCommit($attrs) {
    if ($this->has_email_declaration == 1
      && ($this->_is_new || $this->_changes['has_email_declaration'] == 0)
    ) {
      Letter::send('ntd.email.creation.asked', NetDeclaration::getMailAdmin(), array('id' => $this->getUser()->getId()));
    }
    $this->updateSiren();
  }

  protected function onAfterCreate() {
    if ($this->adherent_id > 0 && !($this->ntd_bdd_id > 0)) {

      $adherent = Adherent::getInstance($this->adherent_id);
      //$iban = $adherent->getPrimaryIban();

      $service_adhesion = Service::getInstance(NetDeclarationManager::SERVICE_ADHESION_PROFILE_SECONDAIRE);
      $tarif = $service_adhesion->getTarifs(array('filters' => array('adherent_types' => $adherent->type)))->first();

      // Souscription au service d'adhésion
      $attributes = array(
        'adherent_id' => $this->getId(),
        'service_id' => $service_adhesion->getId(),
        //'iban_id' => $iban->getId(),
        'price' => $tarif->price,
        'context' => array('prix_forfait' => $tarif->price), // TODO : vérifier le fonctionnement
        'sign_at' => Date::today(),
        'status' => Souscription::STATUS_WAITING_PAIEMENT
      );
      $souscription = Souscription::getInstance();
      $souscription->commit($attributes);

      // Facture
      $facture = Facture::getInstance();
      $facture->setAdherent($this);
      $facture->addTarif($tarif, 1);
      if ($facture->calculate() > 0) {
        $facture->commit(array('status' => Facture::STATUS_NON_PAYE));
        $facture->addSouscription($souscription);
      }
      else {
        $souscription->setStatus(Souscription::STATUS_ACTIVE);
      }
    }
  }

  public function isStatusValide() {
    return $this->status == self::STATUS_SUBSCRIPTION_VALIDE;
  }

  public function asRelationEditHash($elts, $relation) {
    //$elts['start_at']['type'] = 'date';
    $elts['status']['type'] = 'select';
    $elts['status']['options'] = Adherent::$statuses;
    return $elts;
  }

  public function asEditHash() {
    $hash['can_validate'] = !$this->isStatusValide();
    $hash['is_cec'] = $this->type == Adherent::TYPE_CEC;
    $hash['is_entreprise'] = $this->type == Adherent::TYPE_ENTREPRISE;
    $hash['is_oga'] = $this->type == Adherent::TYPE_OGA;
    $hash['is_sante'] = $this->type == Adherent::TYPE_PRO_SANTE;
    $hash['is_international'] = $this->type == Adherent::TYPE_INTERNATIONAL;
    $hash['can_change_user'] = $this->adherent_id == 0;
    $hash['can_change_to_primary'] = $this->adherent_id > 0;
    $hash['can_become_adherent_primary_for_user'] = $this->adherent_id > 0;
    return $hash;
  }

  public function asFinderHash($hash) {
    if ($this->status == self::STATUS_SUBSCRIPTION_PENDING) $hash['_color'] = 'yellow';
    elseif ($this->status == self::STATUS_SUBSCRIPTION_VALIDE) {
      if ($this->adherent_id == 0) $hash['_color'] = 'green';
      else $hash['_color'] = 'blue';
    }
    else $hash['_color'] = 'red';

    return $hash;
  }

  public function onFind($finder) {
    $coll = $finder->getCollection();
    $filters = $coll->getFilters();
    if (isset($filters['cec_flags_avocat']) && $filters['cec_flags_avocat'] > 0) {
      $filters['|&|cec_flags'] = self::FLAG_CEC_AVOCAT;
    }
    elseif (isset($filters['cec_flags_avocat']) && $filters['cec_flags_avocat'] == 0) {
      $filters['|!&|cec_flags'] = self::FLAG_CEC_AVOCAT;
    }
    unset($filters['cec_flags_avocat']);

    $coll->setFilters($filters);
  }

  public function validate() { }

  public function updateSiren() {
    $siret = str_replace(' ', '', $this->siret);
    $this->setAttribute('siren', substr($siret, 0, 9));
  }

  public function getAllSirets() {
    $sirets = (array) $this->old_sirets;
    $sirets[] = $this->siret;
    return $sirets;
  }

  public function getAdherentsSecondaries() {
    $opts = array('filters' => array('adherent_id' => $this->getId()));
    return Adherent::collect($opts);
  }

  public function getProfileSecondary($profile_id) {
    $opts = array('adherent_id' => $this->getId(), 'id' => $profile_id);
    return Adherent::getInstance($opts);
  }

  public function getDecTypes($millesime_id = null) {
    $dectypes_opts = array('filters' => array('|IN|service_id' => $this->getAvailableServiceFormulaireIDs()),
                           'order' => array('document_code' => 'ASC',
                                            'position' => 'ASC',
                                            'name' => 'ASC'));
    if ($millesime_id !== null) {
      $dectypes_opts['filters']['millesime_id'] = (int) $millesime_id;
    }
    $dectypes = Dectype::collect($dectypes_opts);
    return $dectypes;
  }

  public function getAllSouscriptionsActive($opts = array()) {
    $opts['filters'] = array_merge((array) $opts['filters'],
                                   self::getSouscriptionsActiveFilters());
    $souscriptions = $this->getSouscriptions($opts);
    return $souscriptions;
  }

  public static function getSouscriptionsActiveFilters() {
    $filters = array();
    $filters['|<=|start_at'] = Date::today();
    $filters['|>=|finish_at'] = Date::today();
    $filters['|IN|status'] = array(Souscription::STATUS_ACTIVE,
                                   Souscription::STATUS_CANCELLING_ASKED,
                                   Souscription::STATUS_WAITING_PAIEMENT);
    return $filters;
  }

  public function getAvailableServiceFormulaireIDs() {
    $opts = array('type' => Service::TYPE_FORMULAIRE,
                  '|>|document_code' => 0);
    $serviceIDs = array();

    foreach ($this->getServicesAvailables($opts) as $service) {
      if ($service->service_id > 0) {
        $service_required = $service->getService();
        $adherent = ($this->adherent_id > 0) ? $this->getAdherent() : $this;
        if ($adherent->getSouscriptions(array('filters' => array('service_id' => $service_required->getId(),
                                                                 '|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_WAITING_PAIEMENT),
                                                                 '|<=|start_at' => Date::today(),
                                                                 '|>=|finish_at' => Date::today())))->count() < 1
        ) {
          continue;
        }
        $serviceIDs[] = $service->getId();
      }
      else {

        $serviceIDs[] = $service->getId();
      }
    }

    return $serviceIDs;
  }

  public function getServicesAvailables($opts_services = array()) {
    $souscriptions = $this->getAllSouscriptionsActive();

    $services_id = array(-1);
    if ($souscriptions->count() > 0) {
      $services_id = $souscriptions->asHash('id', 'service_id');
    }
    $opts_services['filters']['|IN|id'] = $services_id;
    $services = Service::collect($opts_services);
    //$services->trace();
    return $services;
  }

  public function getIban($id) {
    return Iban::getInstance(array('adherent_id' => $this->getId(), 'id' => $id));
  }

  public function asIbansHash() {
    return $this->getIbans(array('cols' => array('CONCAT_WS(" ", numero_iban, numero_bic)' => 'option_value',
                                                 'CONCAT_WS("-", numero_iban, numero_bic)' => 'option_label'),
                                 'filters' => array('type' => Iban::TYPE_SECONDARY)))->asHash('option_value', 'option_label');
  }

  public function getPrimaryIban() {
    if (Iban::exists(array('adherent_id' => $this->getId(), 'type' => Iban::TYPE_PRIMARY))) {
      return Iban::getInstance(array('adherent_id' => $this->getId(), 'type' => Iban::TYPE_PRIMARY));
    }
    return Iban::getInstance();
  }

  public function getSecondariesIbans() {
    return Iban::collect(array('filters' => array('adherent_id' => $this->getId(), 'type' => Iban::TYPE_SECONDARY)));
  }

  public function getCurrentSouscription($service_id, $opts = null) {
    $souscription_opts = array('filters' => array('adherent_id' => $this->getId(),
                                                  'service_id' => $service_id,
                                                  '|<=|start_at' => Date::today(),
                                                  '|>=|finish_at' => Date::today(),
                                                  'status' => Souscription::STATUS_ACTIVE
    ));
    if (is_array($opts['filters'])) {
      $souscription_opts['filters'] = array_merge($souscription_opts['filters'], $opts['filters']);
    }
    $souscriptions = Souscription::collect($souscription_opts);
    return $souscriptions->first();
  }

  public function hasCurrentSouscription($service_id, $opts = null) {
    $souscription_opts = array('filters' => array(array('adherent_id' => $this->getId(),
                                                        'service_id' => $service_id,
                                                        '|<=|start_at' => Date::today(),
                                                        '|>=|finish_at' => Date::today(),
                                                        '|IN|status' => Souscription::STATUS_ACTIVE)));
    if (is_array($opts['filters'])) {
      $souscription_opts['filters'] = array_merge($souscription_opts['filters'], $opts['filters']);
    }
    $souscriptions = Souscription::collect($souscription_opts);
    return $souscriptions->count() > 0;
  }

  public function getBillingAddressHash($attr = null) {
    $hash = array();
    if ($this->is_main_adherent_billing_address == 0 || $this->adherent_id == 0) {
      if ($this->has_no_billing_address == 0) {
        $hash = array(
          'company' => $this->billing_company,
          'address' => $this->billing_address,
          'zipbox' => $this->billing_zipbox,
          'zipcode' => $this->billing_zipcode,
          'city' => $this->billing_city,
          'country_id' => $this->billing_country_id,
          'mail' => $this->billing_mail,
          //'payment_mode' => $this->billing_payment_mode,
        );
      }
      else {
        $hash = array(
          'company' => $this->company,
          'address' => $this->address,
          'zipbox' => $this->zipbox,
          'zipcode' => $this->zipcode,
          'city' => $this->city,
          'country_id' => $this->country_id,
          'mail' => $this->mail,
          //'payment_mode' => $this->billing_payment_mode,
        );
      }
    }
    else {
      $adherent = Adherent::getAdherent(array('id' => $this->adherent_id));
      $hash = $adherent->getBillingAddressHash();
    }
    if ($attr !== null) {
      return $hash[$attr];
    }
    return $hash;
  }

  public function asFactureHash() {
    $hash = array(
      'civility' => $this->civility,
      'first_name' => $this->first_name,
      'last_name' => $this->last_name,
      'function' => $this->function,
      'company' => $this->company,
      'siret' => $this->siret,
      'address' => $this->address,
      'address_1' => $this->address_1,
      'address_2' => $this->address_2,
      'zipcode' => $this->zipcode,
      'city' => $this->city,
      'country_id' => $this->country_id,
    );

    return $hash;
  }

  public function asWebServiceHash() {
    $user = $this->getUser();
    $hash = array(
      'Siret adherent'   => $this->siret,
      'Type'             => self::$export_types[$this->type],
      'Nom1'             => trim($this->company, ', '),
      'Nom2'             => '',
      'Contact_Civilite' => self::$export_civilities[$this->civility],
      'Contact_Nom'      => $this->last_name,
      'Contact_Prenom'   => $this->first_name,
      'Mail'             => $user->email,
      'mail EDI'         => $this->email_edi,
      'mail EDI Message' => $this->email_edimessage,
      'No OGA'           => $this->oga_agrement,
      'Adresse1'         => $this->address,
      'Adresse2'         => '',
      'Adresse3'         => '',
      'PO'               => $this->zipcode,
      'Ville'            => $this->city,
      'IdDSN'            => implode(';', array($this->netentreprise_siret, $this->netentreprise_last_name, $this->netentreprise_first_name)),
    );

    $hash['gestion'] = "";
    foreach (array('gestion_tva',
                   'gestion_tdfc',
                   'gestion_paiement',
                   'gestion_social',
                   'gestion_requete',
                   'gestion_dsi',
                   'gestion_ir',
                   'gestion_dsn',
                   'gestion_decloyer',
                   'gestion_part') as $gestion) {
      $hash['gestion'] .= $this->getAttribute($gestion) > 0 ? 1 : 0;
    }

    $hash['services'] = "";
    $services_availables_edi = $this->getServicesAvailables(array('filters' => array('type' => Service::TYPE_EDI)))->asHash('id', 'flags_export_adherent');

    foreach (Service::$flags_export_adherent as $flag_export_adherent => $flag_export_adherent_label) {
      $has_service = false;
      foreach ($services_availables_edi as $service_edi_flags) {
        $has_service = (($service_edi_flags & $flag_export_adherent) == $flag_export_adherent);
        if ($has_service) break;
      }
      $hash['services'] .= $has_service === true ? '1' : '0';
    }

    $hash['reception'] = "";
    $services_availables_edi = $this->getServicesAvailables(array('filters' => array('type' => Service::TYPE_EDI)))->asHash('id', 'flags_export_adherent_reception');

    foreach (Service::$flags_export_adherent_reception as $flag_export_adherent_reception => $flag_export_adherent_reception_label) {
      $has_service = false;
      foreach ($services_availables_edi as $service_edi_flags) {
        $has_service = (($service_edi_flags & $flag_export_adherent_reception) == $flag_export_adherent_reception);
        if ($has_service) break;
      }
      $hash['reception'] .= $has_service === true ? '1' : '0';
    }

    array_walk_recursive($hash, "Declaration::cleanWebserviceValue");
    return $hash;
  }

  public function getEmailFacture() {
    $email = $this->getBillingAddressHash('mail');
    if (empty($email)) {
      $email = $this->getEmail();
    }
    return (P('app.state') == 'prod') ? $email : P('contact.devel');
  }

  public function getEmail() {
    return (P('app.state') == 'prod') ? $this->getUser()->email : P('contact.devel');
  }

  public function getSiren() {
    return substr($this->siret, 0, 9);
  }

  public function asCsvHash($csv_export_columns) {
    $hash = array();
    $billing_hash = $this->getBillingAddressHash();

    foreach ($csv_export_columns as $column) {
      if (strpos($column, 'billing') !== false) {
        $billing_key = substr($column, strlen('billing'));
        if (isset($billing_hash[$billing_key])) $hash[$column] = $billing_hash[$billing_key];
        else $hash[$column] = $this->getAttribute($column);
      }
      elseif ($column == 'user_email') {
        try {
          $hash[$column] = $this->getUser()->email;
        }
        catch (Exception $e) {
          $hash[$column] = "pas d'email trouvé";
        }
      }
      elseif ($column == 'partenaire_id') {
        if ($this->getAttribute($column) > 0 && Partenaire::exists($this->getAttribute($column))) {
          $partenaire = Partenaire::getInstance($this->getAttribute($column));
          $hash[$column] = $partenaire->name;
        }
        else {
          $hash[$column] = null;
        }
      }
      elseif ($column == 'cec_flags_avocat') {
        $hash[$column] = ($this->type == self::TYPE_CEC) ? ($this->isAvocat() ? 'Oui' : 'Non') : '';
      }
      else {
        $hash[$column] = $this->getAttribute($column);
      }
    }
    return $hash;
  }

  public function getRenewableSouscriptions() { }

  public function renewSouscriptions($date_today,
                                     $view_only = false,
                                     $send_facture = true,
                                     $include_forfait = true,
                                     $check_souscription_already_created = true,
                                     $resend_facture_renew_reminder = true) {
    if (!$check_souscription_already_created) {
      $send_facture = false;
      $view_only = true;
    }
    $rapport = array();
    $rapport['adherent'] = $this->siret; // DEBUG


    $souscription_finish_before = $date_today;

    // * get all souscriptions which start after limit date
    $souscriptions_already_renewed = $this->getSouscriptions(array('filters' => array('|>=|start_at' => $date_today,
                                                                                      '|IN|status' => array(Souscription::STATUS_ACTIVE,
                                                                                                            Souscription::STATUS_WAITING_PAIEMENT,
                                                                                                            Souscription::STATUS_CANCELLING_ASKED))));
    $opts = array('filters' => array('|<=|finish_at' => $souscription_finish_before,
                                     '|>=|finish_at' => $date_today,
                                     '|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED)));
    if ($check_souscription_already_created && $souscriptions_already_renewed->count() > 0) {
      $opts['filters']['|!IN|service_id'] = $souscriptions_already_renewed->asHash('service_id', 'service_id');
      $rapport['souscription_already_renewed'] = '$souscriptions_already_renewed : ' . $souscriptions_already_renewed->count();
    }
    $souscriptions = $this->getSouscriptions($opts);
    $rapport['souscriptions_count'] = $souscriptions->count(); // DEBUG

    if ($souscriptions->count() == 0) {
      $rapport['error'] = '$souscriptions->count() == 0 ';
      return $rapport;
    }

    // * get all souscriptions which start after limit date
    $group_souscriptions_by_day = array();
    $payment_method = 0;
    foreach ($souscriptions as $souscription) {
      $last_factures = $souscription->getFactures();
      if (count($last_factures)) {
          $payment_method = $last_factures->first()->method_id;
      }
      if (!$view_only) {
        if (!$resend_facture_renew_reminder && $souscription->hasFlag(Souscription::FLAG_FACTURE_ALREADY_SEND)) { // fix : souscriptions.renew CLI
          // S('log')->trace('Souscription #'.$souscription->getId().': La facture à déja été envoyée pour renouvellement');
          continue;
        }
        else {
          $souscription->setFlag(Souscription::FLAG_FACTURE_ALREADY_SEND);
        }
      } else {
          if (!$resend_facture_renew_reminder && $souscription->hasFlag(Souscription::FLAG_FACTURE_ALREADY_SEND)) { // fix : souscriptions.renew.tomorrow CLI : 22/03/2018
              continue;
          }
      }
      $group_souscriptions_by_day[$souscription->finish_at][] = $souscription;
    }
    if (count($group_souscriptions_by_day) == 0) {
        $rapport['souscriptions_count'] = 0;
    }
    // Pour chaque jour
    foreach ($group_souscriptions_by_day as $start_day => $souscriptions) {
      $previous_start_day = Date::toDb(strtotime('previous year', strtotime($start_day)), false);
      $rapport['days'][$start_day]['souscriptions_count'] = count($souscriptions); // DEBUG

      // 1. Établissement de la facture de l'année N-1
      $facture = Facture::getInstance();
      $facture->setAdherent($this);
      $data_suivis = array();
      foreach ($souscriptions as $_souscription) {
        $rapport['days'][$start_day]['souscription'][$_souscription->getId()]['summary'] = $_souscription->asSummaryText(); // DEBUG
        if (!Service::exists($_souscription->service_id)) {
          $rapport['days'][$start_day]['souscription'][$_souscription->getId()]['fatal'] = "Service [" . $_souscription->service_id . "] n'existe plus"; // DEBUG
          continue;
        }
        $service = $_souscription->getService();

        // Si ce service n'est pas EDI, on ne compte pas les suivis associés
        if (!(
          $service->type == Service::TYPE_EDI
          || ($service->type == Service::TYPE_FORMULAIRE
            && $service->hasTarif($this, Tarif::PRICE_TYPE_LOYER))
        )
        ) {
          continue;
        }

        $data_suivis[$service->getId()]['quantity'] = $_souscription->context['quantity'];
        $data_suivis[$service->getId()]['count'] = $_souscription->getSuivisCount() - $_souscription->context['quantity'];
        $data_suivis[$service->getId()]['used'] = $_souscription->getSuivisCount();
        $data_suivis[$service->getId()]['price'] = $_souscription->context['prix_unitaire'];
        $data_suivis[$service->getId()]['service'] = $service;
      }
      // 1.2 Inclusion des Forfaits
      $data_suivis_facture = $data_suivis;
      if ($include_forfait && $this->type == self::TYPE_OGA) {
        $forfaits = Forfait::collect(array('status' => 1, 'order' => array('position' => 'asc')));
        $factures_purchases = array();
        foreach ($forfaits as $forfait) {
          $forfait_services = S('dbo')->asHash('SELECT service_id, quantity FROM ntd_forfait_service WHERE forfait_id=:forfait_id:',
                                               array(':forfait_id:' => $forfait->getId()),
                                               'service_id',
                                               'quantity');
          $forfait_count = self::countDossier($forfait_services, $data_suivis_facture);
          if ($forfait_count > 0) {
            $factures_purchases[$forfait->name]['price'] = $forfait->price;
            $factures_purchases[$forfait->name]['quantity'] += $forfait_count;
          }
        }

        foreach ($factures_purchases as $forfait_name => $factures_purchase) {
          $factures_purchase['name'] = l('souscriptions.payback.forfait.dossier',
                                         array('count' => $factures_purchase['quantity'],
                                               'service_name' => $forfait_name));
          $factures_purchase['date_from'] = $previous_start_day;
          $factures_purchase['date_to'] = $start_day;
          $facture->addPurchase($factures_purchase);
        }
      }
      // 1.3 Inclusion des suivis restants
      foreach ($data_suivis_facture as $service_id => $data_suivi) {
        if ($data_suivi['count'] > 0) {
          $label = 'souscriptions.renew.quantity.payback';
          if ($data_suivi['service']->hasTarif($this, Tarif::PRICE_TYPE_LOYER)) {
            $label = 'souscriptions.renew.quantity.payback.loyer';
          }
          $facture->addPurchase(array('name' => l($label,
                                                  array('count' => $data_suivi['count'],
                                                        'service_name' => $data_suivi['service']->getName())),
                                      'price' => $data_suivi['price'],
                                      'quantity' => $data_suivi['count'],
                                      'date_from' => $previous_start_day,
                                      'date_to' => $start_day));
        }
      }


      // 2. Renouvellement des souscriptions pour l'année N
      $facture_soucriptions = array();
      $souscription_finish_at = Date::toDb(strtotime('next year', strtotime($start_day)), false);
      $soucriptions_created = 0;


      // offer E-CVAE Service if souscriptions contains E-liasse (ID = 38) && E-CVAE Service
      $service_eliasse_id = 38;
      $services_id_offer = array(13, 48);
      $has_eliasse_subscription_active = $this->getSouscriptions(array('filters' => array('service_id' => $service_eliasse_id,
                                                                                          '|IN|status' => array(Souscription::STATUS_ACTIVE,
                                                                                                                Souscription::STATUS_WAITING_PAIEMENT,
                                                                                                                Souscription::STATUS_CANCELLING_ASKED)),
                                                                       'order'   => array('finish_at' => 'DESC'),
                                                                       'limit'   => 1))->count() > 0;
      foreach ($souscriptions as $_souscription) {
        $rapport['days'][$start_day]['souscription'][$_souscription->getId()]['summary'] = $_souscription->asSummaryText(); // DEBUG

        // La souscription est-elle renouvelable ?
        if (!$_souscription->is_renewable) {
           if ($view_only) {
              $rapport['souscriptions_count']--;
           }
          $rapport['days'][$start_day]['souscription'][$_souscription->getId()]['fatal'] = "Service [" . $_souscription->service_id . "] : Souscription à ne pas renouveler"; // DEBUG
          continue;
        }

        // Le service existe-t-il encore ?
        if (!Service::exists($_souscription->service_id)) {
          if ($view_only) {
              $rapport['souscriptions_count']--;
          }
          $rapport['days'][$start_day]['souscription'][$_souscription->getId()]['fatal'] = "Service [" . $_souscription->service_id . "] n'existe plus"; // DEBUG
          continue;
        }
        // Services gratuits à exclure également du rapport
        if ($_souscription->service_id == Service::ACCES_ADHERENT_ID || $_souscription->service_id == Service::ACCES_SECONDARY_ACCOUNT_ID) {
            $rapport['souscriptions_count']--;
        }

        $service = $_souscription->getService();
        $quantity_used = $data_suivis[$service->getId()]['used'];
        $can_offer_service = false;
        if ($has_eliasse_subscription_active && in_array($service->getId(), $services_id_offer)) {
          $can_offer_service = true;
          if ($view_only) {
              $rapport['souscriptions_count']--;
          }
        }

        if (!$can_offer_service) {

          // Ajout du tarif forfait si existant
          $tarif_forfait = $service->getTarif($this, Tarif::PRICE_TYPE_FORFAIT);

            if ($tarif_forfait !== null) {
            $facture->addTarif($tarif_forfait, 1, $start_day, $souscription_finish_at, false, $this);
          }

            // Si c'est un service EDI, y-a-t-il eu des transmissions ?
          if ($service->type == Service::TYPE_EDI) {

            if ($service->hasFlag(Service::FLAG_EDI_NOT_USED_QUANTITY_ADAPTATION)) {
              $quantity_used = $data_suivis[$service->getId()]['quantity'];
            }
            elseif ($this->type == Adherent::TYPE_OGA) {
              $quantity_used = 0;
            }

            if ($this->type == self::TYPE_ENTREPRISE) {
                $regularization = $_souscription->getSuivisCount(true);
                $regularizationDate = date('Y-m-d', strtotime($_souscription->start_at . ' -1 month'));
            }

            // Ajout du tarif unitaire si existant
            if ($service->hasTarif($this, Tarif::PRICE_TYPE_UNITAIRE, $quantity_used)) {
              $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_UNITAIRE, $quantity_used, $start_day), $quantity_used, $start_day, $souscription_finish_at, false, $this);
              if ($regularization > 0) {
                  $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_UNITAIRE, $regularization, $start_day), $regularization, $regularizationDate, $_souscription->start_at, true, $this);
              }
            }
            elseif ($service->hasTarif($this, Tarif::PRICE_TYPE_SIRET)) {
              $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_SIRET), $quantity_used, $start_day, $souscription_finish_at, false, $this);
              if ($regularization > 0) {
                  $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_SIRET), $regularization, $regularizationDate, $_souscription->start_at, true, $this);
              }
            }
            elseif ($service->hasTarif($this, Tarif::PRICE_TYPE_SIREN)) {
              $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_SIREN), $quantity_used, $start_day, $souscription_finish_at, false, $this);
              if ($regularization > 0) {
                  $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_SIREN), $regularization, $regularizationDate, $_souscription->start_at, true, $this);
              }
            }
            elseif ($service->hasTarif($this, Tarif::PRICE_TYPE_NO_FISCAL)) {
              $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_NO_FISCAL), $quantity_used, $start_day, $souscription_finish_at, false, $this);
              if ($regularization > 0) {
                  $facture->addTarif($service->getTarif($this, Tarif::PRICE_TYPE_NO_FISCAL), $regularization, $regularizationDate, $_souscription->start_at, false, $this);
              }
            }
          }
          elseif ($service->type == Service::TYPE_FORMULAIRE
            && $service->hasFlag(Service::FLAG_TARIF_UNITAIRE_QUANTITY_CUMULATE)
          ) {

            $main_adherent = Adherent::getInstance(array('user_id' => $this->user_id,
                                                         'adherent_id' => 0));
            $tarif_unitaire = $service->getTarif($main_adherent, Tarif::PRICE_TYPE_UNITAIRE, 1, $start_day);
            $facture->addTarif($tarif_unitaire, 1, $start_day, $souscription_finish_at, false, $this);
          }
          if ($service->type == Service::TYPE_FORMULAIRE) {
            if ($service->hasTarif($this, Tarif::PRICE_TYPE_LOYER)) {

              $tarif = $service->getTarif($this, Tarif::PRICE_TYPE_LOYER);
              $facture->addTarif($tarif,
                                 $data_suivis[$service->getId()]['used'],
                                 $start_day,
                                 $souscription_finish_at,
                                 false,
                                 $this);
            }
          }
        }


        // Si on ne veux que le rapport, on continue à la prochaine souscription
        $soucriptions_created++;
        if ($view_only) {
          continue;
        }

        // Update 12/12/2018 => set minimum quantity to 1
        // Update 28/01/2019 => add rule to set minimum only for some adherent types

        $quantity = $quantity_used;
        if (in_array($this->type, self::$typesMinimumQuantity)) {
            $quantity = $quantity > 1 ? $quantity : 1;
        }

        $record = array('sign_at' => $date_today,
                        'start_at' => $start_day,
                        'is_renew_auto' => 1,
                        'adherent_id' => $this->getId(),
                        'service_id' => $service->getId(),
                        'context' => Souscription::getSouscriptionContext($service,
                                                                          $this,
                                                                          array('quantity' => $quantity)));
        if ($can_offer_service) {
          $record['context']['prix_forfait'] = 0;
          $record['context']['price_ht'] = 0;
          $record['price'] = 0;
          $facture->addPurchase(array(
                                  'name' => '(Service offert) '.$service->name,
                                  'price' => 0,
                                  'quantity' => 1,
                                  'date_from' => $start_day,
                                  'date_to' => Date::toDb(strtotime('next year', strtotime($start_day))),
                                  'force_display' => 1,
                                ));
        }

        if ($this->partenaire_id > 0 && Partenaire::exists($this->partenaire_id)) {
          $record['partenaire_id'] = $this->partenaire_id;
        }
        $record = Souscription::getDefaultValues($record);
        $souscription = Souscription::getInstance();
        $souscription->commit($record);


        $rapport['days'][$start_day]['souscription'][$_souscription->getId()]['renew_summary'] = $souscription->asSummaryText();
        $facture_soucriptions[] = $souscription;
      }


      // 3. Traitement de la facture
      if (!($facture->calculate() > 0)) {
        if ($soucriptions_created > 0) {
          $rapport['days'][$start_day]['facture'] = $facture->asSummaryText(true);
        }
        if (!$view_only) {
          foreach ($facture_soucriptions as $facture_souscription) {
            $facture_souscription->setStatus(Souscription::STATUS_ACTIVE);
          }
        }
        continue;
      }
      $rapport['days'][$start_day]['facture'] = $facture->asSummaryText(true);
      if (!$view_only) {
        $facture->commit(array('status' => Facture::STATUS_NON_PAYE,
                               'is_renew_auto' => 1,
                               'start_at' => $start_day,
                               'finish_at' => Date::toDb(strtotime('next year', strtotime($start_day))),
                               'method_id' => $payment_method == Facture::PAYMENT_MODE_PRELEVEMENT ? $payment_method : 0));
        foreach ($facture_soucriptions as $facture_souscription) {
          $facture->addSouscription($facture_souscription);
        }
        if ($send_facture && P('app.domain') == 'www.netdeclaration.net') $facture->send();

      }


    }

    return $rapport;
  }

  public function getSubscribedNewsletterBases() {
    $adherent = self::getCurrentPrimaryAdherent();
    $user = $adherent->getUser();
    $recipient_id = $user->getInformation('recipient_id');

    if ($recipient_id < 1) {
      $recipient_id = Email::asId($user->email);
      $user->setInformation('recipient_id', $recipient_id);
    }

    return S('dbo')->query(sprintf('SELECT b.* FROM %s b JOIN %s be ON b.id = be.base_id WHERE email_id = %d AND be.status = 1',
      T('base'),
      Base::TABLE_EMAIL,
      $recipient_id
    ))->asCollection('base');
  }

  public static function countDossier($dossier_services, &$data_suivis) {
    $dossier_services_counts = array();
    foreach ($dossier_services as $dossier_service_id => $dossier_service_count) {
      $dossier_services_counts[$dossier_service_id] = floor($data_suivis[$dossier_service_id]['count'] / $dossier_service_count);
    }
    $dossiers_count = min($dossier_services_counts);

    foreach ($dossier_services as $dossier_service_id => $dossier_service_count) {
      $data_suivis[$dossier_service_id]['count'] -= $dossiers_count * $dossier_service_count;
    }
    return $dossiers_count;
  }

  /* ----- INTERFACE hooks ----- */
  public static function validateAdherent($hash) {

    if (!isset(Adherent::$types[$hash['type']])) {
      throw new Exception(l('adherent.validation.type.required'));
    }
    if (!isset(Adherent::$civilities[$hash['civility']])) {
      throw new Exception(l('adherent.validation.civility.required'));
    }

    foreach (array('last_name', 'first_name', 'company') as $field) {
      if (empty($hash[$field])) {
        throw new Exception(l("adherent.validation.$field.required"));
      }
    }

    if (empty($hash['siret'])) {
      throw new Exception(l("adherent.validation.siret.required"));
    }
    if (!Valid::isSiret($hash['siret'])) {
      throw new Exception(l('adherent.validation.bad.siret'));
    }
    $sql = "SELECT count(siret) FROM ntd_adherent WHERE siret = '" . $hash['siret'] . "'";
    if ($hash['id'] > 0) {
      $sql .= " AND id != " . $hash['id'];
    }
    if (S('dbo')->query($sql)->fetchValue() > 0) {
      throw new Exception(l('adherent.validation.siret.already.exits'));
    }

    $hash['cec_flags'] = array_sum( (array)$hash['cec_flags'] );
    if ($hash['type'] == Adherent::TYPE_CEC && (self::FLAG_CEC_AVOCAT & $hash['cec_flags'] == 0)) {
      if (empty($hash['cec_ordre'])) {
        throw new Exception(l('adherent.validation.cec_ordre.required'));
      }
    }
    elseif ($hash['type'] == Adherent::TYPE_OGA) {
      if (empty($hash['oga_agrement'])) {
        throw new Exception(l('adherent.validation.oga_agrement.required'));
      }
      if (!empty($hash['email_edi'])) {
        //throw new Exception(l('adherent.validation.email_edi.required'));
        $email_edis = String::asSet($hash['email_edi'], ',');
        foreach ($email_edis as $email_edi) {
          if (!Email::isValid($email_edi)) {
            throw new Exception(l('adherent.validation.email_edi.incorrect'));
          }
        }
      }
    }

    foreach (array('phone', 'address', 'zipcode', 'city', 'country_id') as $field) {
      if (empty($hash[$field])) {
        throw new Exception(l("adherent.validation.$field.required"));
      }
    }

    if (!isset($hash['has_no_billing_address'])) {
      throw new Exception(l('adherent.validation.has_no_billing_address.required'));
    }
    if ($hash['has_no_billing_address'] == 0) {
      if (!isset($hash['is_main_adherent_billing_address'])) {
        throw new Exception(l('adherent.validation.is_main_adherent_billing_address.required'));
      }
      if ($hash['is_main_adherent_billing_address'] == 0) {
        foreach (array('company', 'address', 'zipcode', 'city', 'mail', 'country_id') as $field) {
          if (empty($hash['billing_' . $field])) {
            throw new Exception(l("adherent.validation.billing_$field.required"));
          }
          if ($field == 'mail') {
            if (!Email::isValid($hash['billing_mail'])) {
              throw new Exception(l('adherent.validation.billing_mail.incorrect'));
            }
          }
        }
      }
    }

    foreach (array('technician_last_name', 'technician_first_name', 'technician_phone', 'technician_mail') as $field) {
      if (empty($hash[$field])) {
        throw new Exception(l("adherent.validation.$field.required"));
      }
    }
    if (!Email::isValid($hash['technician_mail'])) {
      throw new Exception(l('adherent.validation.technician_mail.incorrect'));
    }
    if (!empty($hash['partenaire_code'])) {
      if (!Partenaire::exists(array('code' => $hash['partenaire_code']))) {
        throw new Exception(l('adherent.validation.partenaire_code.incorrect'));
      }
    }

    foreach (array('netentreprise_siret', 'netentreprise_first_name', 'netentreprise_last_name') as $field) {
      if (empty($hash[$field]) && $hash['gestion_dsn']) {
        throw new Exception(l("adherent.validation.$field.required"));
      }
    }
  }

  public static function generateKey($h = array()) {
    $str = implode('-', $h);
    //$str = md5($str);
    return $str;
  }

  public static function getAllAdherent($user_id, $opts = array()) {
    $opts['filters']['user_id'] = $user_id;
    $opts['order']['adherent_id'] = 'asc';
    return Adherent::collect($opts);
  }

  public static function getCurrentPrimaryAdherent() {
    return self::getInstance(array('user_id' => S('req')->getUserId(), 'adherent_id' => 0));
  }

  public static function cleanWebserviceValue(&$value, $key) {
    $value = str_replace(array("\r\n", "\r", "\n"), array(" ", " ", " "), $value);
  }

  public static function getInstanceBySiret($siret) {
    $opts = array('siret' => $siret);
    return Adherent::getInstance($opts);
  }

  public static function getTypesAvailables($type_adherent_principal) {
    $type_keys = array();
    if ($type_adherent_principal == self::TYPE_ENTREPRISE) {
      $type_keys = array(self::TYPE_ENTREPRISE);
    }
    elseif ($type_adherent_principal == self::TYPE_PRO_SANTE) {
      $type_keys = array(self::TYPE_PRO_SANTE);
    }
    elseif ($type_adherent_principal == self::TYPE_INTERNATIONAL) {
      $type_keys = array(self::TYPE_INTERNATIONAL);
    }
    elseif ($type_adherent_principal == self::TYPE_OGA) {
      $type_keys = array(self::TYPE_OGA, self::TYPE_ENTREPRISE);
    }
    elseif ($type_adherent_principal == self::TYPE_CEC) {
      $type_keys = array(self::TYPE_CEC, self::TYPE_ENTREPRISE);
    }

    $types = array();
    foreach ($type_keys as $key) {
      $types[$key] = self::$types[$key];
    }
    return $types;
  }

  public static function collectByType($type = self::TYPE_OGA) {
    return self::collect(array('filters' => array('status' => self::STATUS_SUBSCRIPTION_VALIDE,
                                                  'type' => $type,
                                                  'adherent_id' => 0),
                               'order' => array('company' => 'ASC')))->asHash('siret', 'company');
  }

  public static function getCecFlags() {
    $flags = self::$cec_flags;
    foreach ($flags as &$flag) {
      $flag = l($flag);
    }
    return $flags;
  }

  // --- bulletin
  const BULLETIN_PDF_PATH = 'doc/factures';

  public function getBulletinPdfPath() {
    return self::BULLETIN_PDF_PATH . '/bulletin-' . $this->getId() . '.pdf';
  }

  public function generateBulletinPdf() {

    if (!Folder::exists(self::BULLETIN_PDF_PATH)) {
      Folder::create(self::BULLETIN_PDF_PATH, true);
    }

    $path_target = $this->getBulletinPdfPath();
    $path_source = str_replace('.pdf', '.html', $path_target);

    $content = H::get('/bulletin.print', array('id' => $this->getId()));
    $header = H::url('/skeleton.pdf.header', array('domtom' => $this->getUser()->hasFlag(User::FLAG_NTD_DOMTOM),
                                                   'head_title' => base64_encode('Bulletin d\'adhésion')));
    $footer = H::url('/skeleton.pdf.footer', array('domtom' => $this->getUser()->hasFlag(User::FLAG_NTD_DOMTOM)));

    $fp = fopen($path_source, 'w');
    fwrite($fp, $content);
    fclose($fp);

    if (P('auth.login') && P('auth.password')) {
      $username = P('auth.login');
      $password = P('auth.password');
    }
    else {
      $username = null;
      $password = null;
    }

    $options = array('--header-html' => '\'' . $header . '\'',
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
}
