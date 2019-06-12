<?php

class Souscription extends ActiveRecord {

  const STATUS_CANCELLED = -20;
  const STATUS_CANCELLING_ASKED = -10;
  const STATUS_DISABLED = 0;
  const STATUS_WAITING_PAIEMENT = 10;
  const STATUS_ACTIVE = 20;

  public static $statuses = array(
    self::STATUS_CANCELLED => '<span class="link-finder link-red"></span> Résilié',
    self::STATUS_CANCELLING_ASKED => '<span class="link-finder link-orange"></span> Résiliation demandée',
    self::STATUS_DISABLED => '<span class="link-finder link-white"></span> Désactivé',
    self::STATUS_WAITING_PAIEMENT => '<span class="link-finder link-yellow"></span> En attente de paiement',
    self::STATUS_ACTIVE => '<span class="link-finder link-green"></span> Paiement Reçu'
  );

  public static $export_statuses = array(
    self::STATUS_CANCELLED => 'Résilié',
    self::STATUS_CANCELLING_ASKED => 'Résiliation demandée',
    self::STATUS_DISABLED => 'Désactivé',
    self::STATUS_WAITING_PAIEMENT => 'En attente de paiement',
    self::STATUS_ACTIVE => 'Paiement Reçu'
  );

  const FLAG_CANCELLED_FACTURE_NON_PAYE = 1;
  const FLAG_FACTURE_ALREADY_SEND = 2;
  const FLAG_CONSUMED = 3;

  public static $flags = array(
    self::FLAG_CANCELLED_FACTURE_NON_PAYE => 'Résilié à cause de non-paiement de la facture',
    self::FLAG_FACTURE_ALREADY_SEND       => 'Facture envoyée pour renouvellement',
    self::FLAG_CONSUMED                   => 'Consommée (Service Greffe)'
  );

  public static function createSouscription(Service $service, Adherent $adherent, $record = array(), $opts = array()) {
    $record['adherent_id'] = $adherent->getId();
    if ($adherent->partenaire_id > 0 && Partenaire::exists($adherent->partenaire_id)) {
      $record['partenaire_id'] = $adherent->partenaire_id;
    }
    $record['service_id'] = $service->getId();
    $record['context'] = Souscription::getSouscriptionContext($service, $adherent, $opts);
    $record = Souscription::getDefaultValues($record);
    $souscription = Souscription::getInstance();
    $souscription->commit($record);
    return $souscription;
  }

  public static function getDefaultValues($record) {
    $record['price'] = $record['context']['price_ht'];
    if ($record['partenaire_id']) {
      $partenaire = Partenaire::getInstance($record['partenaire_id']);
      if ($partenaire->hasService($record['service_id']) && $partenaire->status == Partenaire::STATUS_ONLINE) {
        $record['commission'] = $record['price'] * $partenaire->commission / 100;
      }
    }
    $record['sign_at'] = $record['sign_at'] ? $record['sign_at'] : Date::today();
    $record['start_at'] = $record['start_at'] ? $record['start_at'] : Date::DATE_NULL;
    if (!$record['finish_at']) {
      if (!Date::isNull($record['start_at'])) {
        $record['finish_at'] = Date::toDb(strtotime('next year', strtotime(Date::toDb($record['start_at']))));
      } else {
        $record['finish_at'] = Date::DATE_NULL;
      }
    }
    $record['is_renew_auto'] = (int) $record['is_renew_auto'];
    $record['status'] = $record['status'] ? $record['status'] : Souscription::STATUS_WAITING_PAIEMENT;
    return $record;
  }

  public static function getSouscriptionContext(Service $service, Adherent $adherent, $opts = array()) {
    $quantity = (int) $opts['quantity'];

    $tarif_forfait = $service->getTarif($adherent, Tarif::PRICE_TYPE_FORFAIT);
    if ($service->hasTarif($adherent, Tarif::PRICE_TYPE_UNITAIRE)) {
      $tarif_unitaire = $service->getTarif($adherent, Tarif::PRICE_TYPE_UNITAIRE, $quantity);
    }
    elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_SIRET)) {
      $tarif_siret = $service->getTarif($adherent, Tarif::PRICE_TYPE_SIRET);
    }
    elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_SIREN)) {
      $tarif_siren = $service->getTarif($adherent, Tarif::PRICE_TYPE_SIREN);
    }
    elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_NO_FISCAL)) {
      $tarif_no_fiscal = $service->getTarif($adherent, Tarif::PRICE_TYPE_NO_FISCAL);
    }
    elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_LOYER)) {
      $tarif_loyer = $service->getTarif($adherent, Tarif::PRICE_TYPE_LOYER);
    }
    elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_GREFFE)) {
      $souscription_quantity = GreffeManager::hasCurrentDossier() ? GreffeManager::getSouscriptionQuantityForCurrentDossier() : 0;
      if ($service->service_id > 0 && GreffeManager::isFirstSouscriptionConditionForCurrentDossier()) {
        $required_service = $service->getService();
        if ($required_service->hasTarif($adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity)) {
          $tarif_forfait_greffe = $required_service->getTarif($adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity);
        }
      }
      $tarif_greffe = $service->getTarif($adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity);
    }

    $context = array();
    $price_ht = 0;

    if ($tarif_forfait) {
      $context['prix_forfait'] = $tarif_forfait->price;
      $price_ht += $tarif_forfait->price;
    }

    if ($tarif_unitaire) {
      if($service->hasFlag(Service::FLAG_TARIF_UNITAIRE_QUANTITY_CUMULATE)) {
        $quantity = 1;
      }
      $context['prix_unitaire'] = $tarif_unitaire->price;
      $context['quantity'] = $quantity;
      $context['qty_min'] = $tarif_unitaire->qty_min;
      $context['qty_max'] = $tarif_unitaire->qty_max;
      $context['price_type'] = $tarif_unitaire->price_type;
      $price_ht += $quantity * $tarif_unitaire->price;
    }
    elseif ($tarif_siret) {
      $context['prix_unitaire'] = $tarif_siret->price;
      $context['quantity'] = $quantity;
      $context['price_type'] = $tarif_siret->price_type;
      $price_ht += $quantity * $tarif_siret->price;
    }
    elseif ($tarif_siren) {
      $context['prix_unitaire'] = $tarif_siren->price;
      $context['quantity'] = $quantity;
      $context['price_type'] = $tarif_siren->price_type;
      $price_ht += $quantity * $tarif_siren->price;
    }
    elseif ($tarif_no_fiscal) {
      $context['prix_unitaire'] = $tarif_no_fiscal->price;
      $context['quantity'] = $quantity;
      $context['price_type'] = $tarif_no_fiscal->price_type;
      $price_ht += $quantity * $tarif_no_fiscal->price;
    }
    elseif ($tarif_loyer) {
      $context['prix_unitaire'] = $tarif_loyer->price;
      $context['quantity'] = $quantity;
      $context['price_type'] = $tarif_loyer->price_type;
      $price_ht += $quantity * $tarif_loyer->price;
    }
    elseif ($tarif_greffe) {
      $context['prix_unitaire'] = $tarif_greffe->price;
      $context['quantity'] = $quantity;
      $context['price_type'] = $tarif_greffe->price_type;
      $price_ht += (float)$tarif_forfait_greffe->price + (float)$tarif_greffe->price;
    }
    $context['price_ht'] = $price_ht;
    if ($adherent->partenaire_id > 0 && Partenaire::exists($adherent->partenaire_id)) {
      $partenaire = $adherent->getPartenaire();
      if ($partenaire->hasService($service->getId()) && $partenaire->status == Partenaire::STATUS_ONLINE) {
        $context['commission'] = $price_ht * (float) $partenaire->commission / 100;
      }
    }

    return $context;
  }

  /* ----- INTERFACE hooks ----- */
  protected function onBeforeCommit(&$attrs) {
    if (S('req')->isBack()) {
      if (!$this->isLoaded() && isset($attrs['opts_quantity'])) {
        $service = Service::getInstance($attrs['service_id']);
        $adherent = Adherent::getInstance($attrs['adherent_id']);
        $opts['quantity'] = $attrs['opts_quantity'];
        unset($attrs['opts_quantity']);
        if ($service->hasTarif($adherent, Tarif::PRICE_TYPE_UNITAIRE)
          && !$service->hasTarif($adherent, Tarif::PRICE_TYPE_UNITAIRE, $opts['quantity'])) {
          throw new Exception('Attention, il y a un tarif Unitaire pour ce service. Veuillez remplir le champ quantité.');
        }
        elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_SIRET)
          && !($opts['quantity'] > 0)) {
          throw new Exception('Attention, il y a un tarif par Siret pour ce service. Veuillez remplir le champ quantité.');
        }
        elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_SIREN)
          && !($opts['quantity'] > 0)) {
          throw new Exception('Attention, il y a un tarif par Siren pour ce service. Veuillez remplir le champ quantité.');
        }
        elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_NO_FISCAL)
          && !($opts['quantity'] > 0)) {
          throw new Exception('Attention, il y a un tarif par N° fiscal pour ce service. Veuillez remplir le champ quantité.');
        }


        $attrs['context'] = Souscription::getSouscriptionContext($service, $adherent, $opts);
        $attrs = Souscription::getDefaultValues($attrs);
      }
      else {
        unset($attrs['opts_quantity']);
        unset($attrs['can_cancel']);
        unset($attrs['has_contexte_forfait']);
        unset($attrs['contexte_prix_forfait']);
        unset($attrs['has_contexte_unitaire']);
        unset($attrs['contexte_prix_unitaire']);
        unset($attrs['contexte_qty_unitaire']);
        unset($attrs['contexte_price_type']);

      }
    }
  }


    protected function onAfterCreate()
    {
        if ($this->partenaire_id == 0) {
            $adherent = $this->getAdherent();
            if (Partenaire::exists(array('id' => $adherent->partenaire_id))) {
                $partenaire = Partenaire::getInstance($adherent->partenaire_id);
                $attr = array(
                    'partenaire_id' => $partenaire->getId(),
                    'commission' => $this->price * (float)$partenaire->commission / 100
                );
                $this->commit($attr);
            }

        }
    }

    protected function onAfterCommit($attrs) {
    $adherent = $this->getAdherent();
    if ($adherent->adherent_id > 0) {
      $main_adherent = Adherent::getInstance($adherent->adherent_id);
    } else {
      $main_adherent = $adherent;
    }
    $service = $this->getService();

    if ($this->status == self::STATUS_ACTIVE && $this->_changes['status'] == self::STATUS_WAITING_PAIEMENT) {
      if (!(strtotime($this->start_at) > 0)) {
        $start_at = Date::today();
        $finish_at = Date::toDb(strtotime('next year', strtotime($start_at)));
        $this->setAttribute('start_at', $start_at);
        $this->setAttribute('finish_at', $finish_at);
        if ($this->partenaire_id) {
          $partenaire = $this->getPartenaire();
          $commission = $this->price * (float) $partenaire->commission / 100;
          $this->setAttribute('commission', $commission);
        }
      }

      if ($service->getId() == NetDeclarationManager::SERVICE_ADHESION_MAIN_PROFILE) {
        //$adherent->setStatus(Adherent::STATUS_SUBSCRIPTION_VALIDE);
//        Letter::send(
//          'adherent.status.activated',
//          $adherent->getEmail(),
//          array('adherent.first_name' => $main_adherent->first_name,
//                'adherent.last_name' => $main_adherent->last_name,
//                'footer' => NetDeclaration::getMailFooter()));
      }
      elseif ($service->getId() == NetDeclarationManager::SERVICE_ADHESION_PROFILE_SECONDAIRE) {
        //$adherent->setStatus(Adherent::STATUS_SUBSCRIPTION_VALIDE);
        /*Letter::send(
          'adherent.secondary.status.activated',
          $adherent->getEmail(),
          array('adherent.first_name' => $main_adherent->first_name,
                'adherent.last_name' => $main_adherent->last_name,
                'adherent.secondary.first_name' => $adherent->first_name,
                'adherent.secondary.last_name' => $adherent->last_name,
                'footer' => NetDeclaration::getMailFooter()));*/
      }
      if (in_array($service->type, array(Service::TYPE_EDI, Service::TYPE_FORMULAIRE))) {
        Letter::send(
          'souscription.validated.user',
          $adherent->getEmail(),
          array('adherent.first_name' => $main_adherent->first_name,
                'adherent.last_name' => $main_adherent->last_name,
                'adherent.siret' => $main_adherent->siret,
                'service.name' => $service->name,
                'footer' => NetDeclaration::getMailFooter()));
      }
    }
    elseif ($this->status == self::STATUS_CANCELLING_ASKED && $this->_changes['status'] == self::STATUS_ACTIVE) {
      Letter::send(
        'ntd.souscription.cancelize',
        NetDeclaration::getMailAdmin(),
        array('id' => $adherent->getId(),
              'service' => $service->name,
              'compte' => $adherent->identity()));
    }
    elseif ($this->status == self::STATUS_CANCELLED && $this->_changes['status'] == self::STATUS_CANCELLING_ASKED) {
      if ($service->getId() == NetDeclarationManager::SERVICE_ADHESION_MAIN_PROFILE) {
        $adherents = Adherent::getAllAdherent($adherent->getUser()->getId());
        foreach ($adherents as $adherent) {
          $adherent->cancelAllServices();
        }
      }
      elseif ($service->getId() == NetDeclarationManager::SERVICE_ADHESION_PROFILE_SECONDAIRE) {
        $adherent->cancelAllServices();
      }
    }

    if ($this->service_id > 0 && $this->getService()->code == 'GREFFE') {
      $this->setAttribute('is_renewable', 0);
      $this->setAttribute('is_renew_auto', 0);
    }
  }

  protected function onAfterDestroy() {
    S('dbo')->query('DELETE FROM ntd_facture_souscription WHERE souscription_id = :souscription_id:',
                    array(':souscription_id:' => $this->getId()));

  }

  public function getName($locale = null) {
    return '[' . strtoupper(self::$statuses[$this->status]) . '] ' . $this->getService()->name . " : du " . H::datenice($this->start_at) . " au " . H::datenice($this->finish_at);
  }

  public function getAttribute($key) {
    if ($key == 'service_name') return $this->getService()->name;
    if ($key == 'adherent_name') return $this->getAdherent()->name;
    if ($key == 'adherent_siret') return $this->getAdherent()->siret;
    if ($key == 'adherent_company') return $this->getAdherent()->company;
    if ($key == 'adherent_company') return $this->getAdherent()->company;
    if ($key == 'facture_id') return S('dbo')->fetchValue('SELECT facture_id FROM ntd_facture_souscription WHERE souscription_id = ' . $this->getId());
    if ($key == 'status_label') return self::$statuses[$this->status];
    if ($key == 'user_email') {
      try {
        return $this->getAdherent()->getUser()->email;
      } catch (Exception $e) {
        return "pas d'email trouvé";
      }
    }
    return parent::getAttribute($key);
  }

  public function getSuiviCollectionOpts($regularization = false) {
    $adherent = $this->getAdherent();
    $sirets = $adherent->getAllSirets();
    $adherent_filters = array();

    $suivi_payants = $this->getService()->getSuiviPayants(array('filters' => array('status' => 1)));
    if ($suivi_payants->count() < 1) {
      return array('filters' => array('id' => -1,
                                      'origine' => 'EDI'));
    }
    // get All adherent siret
    foreach ($suivi_payants as $key => $suivi_payant) {
      $filter = array(T('suivi') . '.message' => Edimessagetype::getInstance($suivi_payant->edimessagetype_id)->name,
                      'type_dest' => $suivi_payant->destinataire,
                      '|IN|' . ($suivi_payant->sens == Suivipayant::SENS_R ? T('destinataire').'.siret' : T('suivi').'.siret_emetteur') => $sirets);
      if ($key == 0) {
        $adherent_filters[0] = $filter;
      }
      else {
        $adherent_filters[]['OR'] = $filter;
      }
    }





    // get all OGA adherents
    $ogas = Adherent::collect(array('filters' => array('|!=|id' => $adherent->getId(),
                                                       'type' => Adherent::TYPE_OGA,
                                                       'status' => Adherent::STATUS_SUBSCRIPTION_VALIDE)));
    $sirets_ogas = array();
    foreach ($ogas as $oga) {
      $sirets_ogas = array_merge($sirets_ogas, $oga->getAllSirets());
    }

    $opts = array('include' => array('destinataire'),
                  'filters' => array());
    $opts['filters']['|><|date_depot'] = $regularization ? array(date('Y-m-d', strtotime($this->start_at . ' -1 month')), $this->start_at) : array($this->start_at, $this->finish_at);
    $opts['filters']['origine'] = 'EDI';
    $opts['filters']['|!IN|siret'] = $sirets_ogas;
    $opts['filters'][] = $adherent_filters;
    return $opts;
  }

  public function getSuivisCount($regularization = false) {
    $suivis_opts = $this->getSuiviCollectionOpts();
    $suivis = Suivi::collect($suivis_opts);
    if ($regularization) {
        $suivis_opts_regularization = $this->getSuiviCollectionOpts($regularization);
        $suivis_regularization =  Suivi::collect($suivis_opts_regularization);
        $suivis_opts_to_compare = $suivis_opts_regularization;
        $suivis_opts_to_compare['filters']['|><|date_depot'] = array(date('Y-m-d', strtotime($this->start_at . ' -1 year')),
                                                                     date('Y-m-d', strtotime($this->start_at . ' -1 month')));
        $suivis_to_compare = Suivi::collect($suivis_opts_to_compare);
    }
    if ($this->context['price_type'] == Tarif::PRICE_TYPE_SIRET) {
      if ($regularization) {
          $sirets_declares_regularization = $suivis_regularization->asHash('siret_decl', 'siret_decl');
          $sirets_declares_to_compare = $suivis_to_compare->asHash('siret_decl', 'siret_decl');
          return sizeof(array_diff($sirets_declares_regularization, $sirets_declares_to_compare));
      }
      $sirets_declares = $suivis->asHash('siret_decl', 'siret_decl');
      return sizeof($sirets_declares);
    }
    if ($this->context['price_type'] == Tarif::PRICE_TYPE_SIREN) {
      if ($regularization) {
          $sirets_declares_regularization = $suivis_regularization->asHash('siret_decl', 'siret_decl');
          $sirets_declares_to_compare = $suivis_to_compare->asHash('siret_decl', 'siret_decl');
          return sizeof(array_diff($sirets_declares_regularization, $sirets_declares_to_compare));
      }
      $sirets_declares = $suivis->asHash('siret_decl', 'siret_decl');
      return sizeof($sirets_declares);
    }
    if ($this->context['price_type'] == Tarif::PRICE_TYPE_NO_FISCAL) {
      if ($regularization) {
          $sirets_declares_regularization = $suivis_regularization->asHash('no_fiscal', 'no_fiscal');
          $sirets_declares_to_compare = $suivis_to_compare->asHash('siret_decl', 'siret_decl');
          return sizeof(array_diff($sirets_declares_regularization, $sirets_declares_to_compare));
      }
      $sirets_declares = $suivis->asHash('no_fiscal', 'no_fiscal');
      return sizeof($sirets_declares);
    }
    elseif($this->context['price_type'] == Tarif::PRICE_TYPE_LOYER){
      $edimessages = Edimessage::collect(array('filters' => array('|IN|suivi_id' => $suivis->asSet('id'))));
      if ($regularization) {
          $edimessages = Edimessage::collect(array('filters' => array('|IN|suivi_id' => $suivis_regularization->asSet('id'))));
      }
      $loyers_count = $edimessages->sum('nb_donnees');
      return $loyers_count;
    }
    if ($regularization) {
        return $suivis_regularization->count();
    } else {
        return $suivis->count();
    }
  }

  public function onFind($finder) {
    if (S('req')->branch['adherent_id'] > 0) {
      unset($finder->cols['adherent_identity']);
      unset($finder->cols['siret']);
    }
  }

  public function asFinderHash($hash) {
    $adherent = $this->getAdherent();
    if (isset($hash['adherent_identity'])) $hash['adherent_identity'] = $adherent->identity();
    if (isset($hash['siret'])) $hash['siret'] = $adherent->siret;

    $hash['start_at'] = $this->start_at == '00-00-0000' ? '' : H::date($this->start_at);
    $hash['finish_at'] = $this->finish_at == '00-00-0000' ? '' : H::date($this->finish_at);
    $hash['sign_at'] = $this->sign_at == '00-00-0000' ? '' : H::date($this->sign_at);
    $hash['price'] = H::amount($this->price);
    $adherent_finder_hash = $adherent->asFinderHash(array());
    $hash['_color'] = $adherent_finder_hash['_color'];
    $hash['is_renewable'] = ($hash['is_renewable']) ? 'oui' : 'non';
    return $hash;
  }

  public function asEditHash() {
    $hash = array();


    $hash['can_cancel'] = false;
    //$hash['adherent_identity'] = $this->getAdherent()->identity();
    if ($this->isLoaded()) {
      //$hash['siret'] = $this->getAdherent()->siret;
    }
    else {
      $hash['can_cancel'] = $this->status == self::STATUS_CANCELLING_ASKED;
      $adherent = Adherent::getInstance(S('req')->branch['adherent_id']);
      $services = Service::collect(array('include' => array('tarif'),
                                         'filters' => array('|%%|' . T('tarif') . '.adherent_types' => $adherent->type,
                                                            '|%%|' . T('service') . '.adherent_types' => $adherent->type),
                                         'order' => array('name' => 'asc')));
      $service_availables = array();
      foreach ($services as $service) {
        $tarifs = $service->getTarifs();
        $tarif_types = array();
        foreach ($tarifs as $tarif) {
          $tarif_types[Tarif::$price_types[$tarif->price_type]] = true;
        }
        $service_availables[$service->getId()] = $service->name . ' - ' . implode(', ', array_keys($tarif_types));
      }
      $hash['services_availables'] = $service_availables;
    }

    $hash['has_contexte_forfait'] = $this->context['prix_forfait'] > 0;
    $hash['contexte_prix_forfait'] = $this->context['prix_forfait'];

    $hash['has_contexte_unitaire'] = $this->context['prix_unitaire'] > 0;
    $hash['contexte_prix_unitaire'] = $this->context['prix_unitaire'];
    $hash['contexte_qty_unitaire'] = $this->context['quantity'];
    $hash['contexte_price_type'] = Tarif::$price_types[$this->context['price_type']];

    return $hash;
  }

  public function asCsvHash($csv_export_columns) {
    $hash = array();
    foreach ($csv_export_columns as $column) {
      $hash[$column] = $this->getAttribute($column);
    }
    return $hash;
  }

  public function asSummaryText() {
    $textes = array("Souscription - ID " . $this->getId());
    try {
      $textes[] = "Service : \t" . $this->getService()->name;
    } catch (Exception $e) {
      $textes[] = 'Service inconnu';
    }
    $textes[] = "Prix HT : \t" . H::amount($this->context['price_ht']);
    $textes[] = "Signée le : \t" . H::date($this->sign_at);
    $textes[] = "Commence le : \t" . H::date($this->start_at);
    $textes[] = "Finie le : \t" . H::date($this->finish_at);
    $textes[] = "Etat : \t\t" . trim(strip_tags(Souscription::$statuses[$this->status]));
    if ($this->souscription_renew_id > 0) {
      $textes[] = "Cette souscription a été renouvellée, ID de la nouvelle souscription : " . $this->souscription_renew_id;
    }

    $textes[] = "\n# Tarifs ";
    if (isset($this->context['prix_forfait'])) {
      $textes[] = "Tarif Forfait : \t" . H::amount($this->context['prix_forfait']);
    }
    if (isset($this->context['price_type'])) {
      if ($this->context['price_type'] == Tarif::PRICE_TYPE_UNITAIRE) {
        $textes[] = "Tarif télétransmissions : " . H::amount($this->context['prix_unitaire']);
        $textes[] = "Quantité : " . $this->context['quantity'] . " Télétransmissions";
        $textes[] = "Tranche du tarif : " . $this->context['qty_min'] . " à " . $this->context['qty_max'];
      }
      elseif ($this->context['price_type'] == Tarif::PRICE_TYPE_SIRET) {
        $textes[] = "Tarif SIRET : \t" . H::amount($this->context['prix_unitaire']);
        $textes[] = "Quantité : \t" . $this->context['quantity'] . " SIRET";
      }
      elseif ($this->context['price_type'] == Tarif::PRICE_TYPE_SIREN) {
        $textes[] = "Tarif SIREN : \t" . H::amount($this->context['prix_unitaire']);
        $textes[] = "Quantité : \t" . $this->context['quantity'] . " SIREN";
      }
      elseif ($this->context['price_type'] == Tarif::PRICE_TYPE_NO_FISCAL) {
        $textes[] = "Tarif N° fiscal : \t" . H::amount($this->context['prix_unitaire']);
        $textes[] = "Quantité : \t" . $this->context['quantity'] . " N° fiscal";
      }
      elseif ($this->context['price_type'] == Tarif::PRICE_TYPE_LOYER) {
        $textes[] = "Tarif Loyer : \t" . H::amount($this->context['prix_unitaire']);
        $textes[] = "Quantité : \t" . $this->context['quantity'] . " Loyer";
      }
      else {
        $textes[] = "Tarif inconnu";
      }
    }


    return implode("\n", $textes);
  }
}
