<?php

class Service extends ActiveRecord {

  // ID des services à exclure du cron 'souscriptions.renew.tomorrow'
  const ACCES_ADHERENT_ID = 5;
  const ACCES_SECONDARY_ACCOUNT_ID = 6;

  const TYPE_AUTRE = 0;
  const TYPE_ADHESION = 1;
  const TYPE_FORMULAIRE = 2;
  const TYPE_EDI = 3;

  const TYPE_DOC_EDI_LIASSE = 1;
  const TYPE_DOC_EDI_TVA = 2;
  const TYPE_DOC_EDI_PAYE = 3;
  const TYPE_DOC_EDI_SOCIAL = 4;
  const TYPE_DOC_EDI_WEB_LIASSE = 5;
  const TYPE_DOC_EDI_WEB_TVA = 6;
  const TYPE_DOC_EDI_WEB_PAYE = 7;

  const STATUS_OFFLINE = 0;
  const STATUS_ONLINE = 1;

  const FLAG_ACCES_EDI_OPTIONNAL = 1;
  const FLAG_EDI_NOT_USED_QUANTITY_ADAPTATION = 2;
  const FLAG_TARIF_UNITAIRE_QUANTITY_CUMULATE = 4;
  const FLAG_MANY_SOUSCRIPTIONS_PROCESS = 8;
  const FLAG_ONLY_ONE_BY_USER = 16;

  public static $type_doc_edis = array(
    self::TYPE_DOC_EDI_LIASSE => 'Liasse',
    self::TYPE_DOC_EDI_TVA => 'TVA',
    self::TYPE_DOC_EDI_PAYE => 'Paye',
    self::TYPE_DOC_EDI_SOCIAL => 'Social',
    self::TYPE_DOC_EDI_WEB_LIASSE => 'Web Liasse',
    self::TYPE_DOC_EDI_WEB_TVA => 'Web TVA',
    self::TYPE_DOC_EDI_WEB_PAYE => 'Web Paye',
  );

  public static $type_doc_edis_code = array(
    self::TYPE_DOC_EDI_LIASSE => 'LIASSE',
    self::TYPE_DOC_EDI_TVA => 'TVA',
    self::TYPE_DOC_EDI_PAYE => 'PAYE',
    self::TYPE_DOC_EDI_SOCIAL => 'SOCIAL',
    self::TYPE_DOC_EDI_WEB_LIASSE => 'WEBLIASSE',
    self::TYPE_DOC_EDI_WEB_TVA => 'WEBTVA',
    self::TYPE_DOC_EDI_WEB_PAYE => 'WEBPAYE',
  );

  public static $types = array(
    self::TYPE_AUTRE => 'Autre',
    self::TYPE_ADHESION => 'Adhésion',
    self::TYPE_FORMULAIRE => 'Formulaire',
    self::TYPE_EDI => 'EDI',
  );

  public static $statuses = array(
    self::STATUS_OFFLINE => 'Désactivé',
    self::STATUS_ONLINE => 'Activé'
  );

  public static $flags = array(self::FLAG_ACCES_EDI_OPTIONNAL => 'Accès EDI Optionnel',
                               self::FLAG_EDI_NOT_USED_QUANTITY_ADAPTATION => 'ne pas adapter la quantité de transmissions au renouvellement',
                               self::FLAG_TARIF_UNITAIRE_QUANTITY_CUMULATE => 'Tarif Unitaire seulement : Cumuler le nombre de souscriptions actives pour le choix de la tranche tarifaire.',
                               self::FLAG_MANY_SOUSCRIPTIONS_PROCESS => 'Processus d\'achat : plusieurs souscriptions à la fois',
                               self::FLAG_ONLY_ONE_BY_USER => 'Un seul par compte utilisateur');

  const FLAG_EXPORT_ADHERENT_EDI_TDFC = 1;
  const FLAG_EXPORT_ADHERENT_EDI_TVA = 2;
  const FLAG_EXPORT_ADHERENT_EDI_CVAE = 4;
  const FLAG_EXPORT_ADHERENT_EDI_IS = 8;
  const FLAG_EXPORT_ADHERENT_EDI_TS = 16;
  const FLAG_EXPORT_ADHERENT_EDI_IAT = 32;
  const FLAG_EXPORT_ADHERENT_EDI_CRM = 64;
  const FLAG_EXPORT_ADHERENT_EDI_DUCS = 128;
  const FLAG_EXPORT_ADHERENT_EDI_RCM = 256;
  const FLAG_EXPORT_ADHERENT_EDI_REQUETE = 512;
  const FLAG_EXPORT_ADHERENT_EDI_DSI = 1024;
  const FLAG_EXPORT_ADHERENT_EDI_IR = 2048;
  const FLAG_EXPORT_ADHERENT_EDI_TDFC_BDF = 4096;
  const FLAG_EXPORT_ADHERENT_EDI_DSN = 8192;
  const FLAG_EXPORT_ADHERENT_EDI_DECLOYER = 16384;
  const FLAG_EXPORT_ADHERENT_EDI_IFU = 32768;
  const FLAG_EXPORT_ADHERENT_EDI_HON = 65536;

  public static $flags_export_adherent = array(
    self::FLAG_EXPORT_ADHERENT_EDI_TDFC     => 'TDFC',
    self::FLAG_EXPORT_ADHERENT_EDI_TVA      => 'TVA',
    self::FLAG_EXPORT_ADHERENT_EDI_CVAE     => 'CVAE',
    self::FLAG_EXPORT_ADHERENT_EDI_IS       => 'IS',
    self::FLAG_EXPORT_ADHERENT_EDI_TS       => 'TS',
    self::FLAG_EXPORT_ADHERENT_EDI_IAT      => 'IAT',
    self::FLAG_EXPORT_ADHERENT_EDI_CRM      => 'CRM',
    self::FLAG_EXPORT_ADHERENT_EDI_DUCS     => 'DUCS',
    self::FLAG_EXPORT_ADHERENT_EDI_RCM      => 'RCM',
    self::FLAG_EXPORT_ADHERENT_EDI_REQUETE  => 'REQUETE',
    self::FLAG_EXPORT_ADHERENT_EDI_DSI      => 'DSI',
    self::FLAG_EXPORT_ADHERENT_EDI_IR       => 'IR',
    self::FLAG_EXPORT_ADHERENT_EDI_TDFC_BDF => 'TDFC_BDF',
    self::FLAG_EXPORT_ADHERENT_EDI_DSN      => 'DSN',
    self::FLAG_EXPORT_ADHERENT_EDI_DECLOYER => 'DECLOYER',
    self::FLAG_EXPORT_ADHERENT_EDI_IFU      => 'IFU',
    self::FLAG_EXPORT_ADHERENT_EDI_HON      => 'HON',
  );

  const FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC = 1;
  const FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TVA = 2;
  const FLAG_EXPORT_ADHERENT_EDI_RECEPTION_PAYE = 4;
  const FLAG_EXPORT_ADHERENT_EDI_RECEPTION_IR = 8;
  const FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC_CVAE = 16;
  const FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC_LOY = 32;
  const FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC_IAT_CRM = 64;

  public static $flags_export_adherent_reception = array(
    self::FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC         => 'REC TDFC',
    self::FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TVA          => 'REC TVA',
    self::FLAG_EXPORT_ADHERENT_EDI_RECEPTION_PAYE         => 'REC PAYE',
    self::FLAG_EXPORT_ADHERENT_EDI_RECEPTION_IR           => 'REC IR',
    self::FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC_CVAE    => 'REC TDFC CVAE',
    self::FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC_LOY     => 'REC TDFC LOY',
    self::FLAG_EXPORT_ADHERENT_EDI_RECEPTION_TDFC_IAT_CRM => 'REC TDFC IAT-CRM'
  );


  public function getTarif($adherent, $type, $quantity = null, $date = null) {
    $opts = array('order' => array('qty_min' => 'ASC'));
    if ($adherent instanceof Adherent) {
      $adherent_type = $adherent->type;
      $adherent_level = $adherent->level;
    }
    else {
      $adherent_type = $adherent['type'];
      $adherent_level = $adherent['level'];
    }
    $opts['filters']['|%%|adherent_types'] = $adherent_type;
    $opts['filters']['|IN|adherent_level'] = array(Tarif::ADHERENT_LEVEL_BOTH, $adherent_level);
    if (!is_null($type)) $opts['filters']['price_type'] = $type;
    $opts['filters']['status'] = 1;

    $_quantity = 0;
    if ($date == null) {
      $date = Date::today();
    }
    if ($this->hasFlag(self::FLAG_TARIF_UNITAIRE_QUANTITY_CUMULATE)) {
      $_quantity += $this->countUserAdherentsWithActiveSouscription($adherent, $date);
    }
    if (!is_null($quantity)) {
      $quantity += $_quantity;
      $opts['filters']['|<=|qty_min'] = $quantity;
      $opts['filters']['|>=|qty_max'] = $quantity;
    }

    if ($adherent instanceof Adherent) {
      $services = $adherent->getServicesAvailables();
      $services_id = count($services) > 0 ? $services->asSet('id') : array(0);
    }
    else {
      $services_id = array(0);
    }

    $opts['filters'][T('tarif').'.service_id'] = $this->getId();

    $opts_w_tarif_conditions = $opts;
    $opts_w_tarif_conditions['through'] = 'ntd_tarif_service';
    $opts_w_tarif_conditions['filters']['|IN|ntd_tarif_service.service_id'] = $services_id;
    $tarifs = Tarif::collect($opts_w_tarif_conditions);

    if ($tarifs->count() == 0) {
      $tarifs_id = S('dbo')->asSet('SELECT DISTINCT tarif_id FROM ntd_tarif_service WHERE 1');
      $opts_wo_tarif_conditions = $opts;
      $opts_wo_tarif_conditions['filters']['|!IN|id'] = $tarifs_id;

      $tarifs = Tarif::collect($opts_wo_tarif_conditions);
    }


    return ($tarifs->count() > 0) ? $tarifs->first() : null;
  }

  public function hasTarif($adherent, $type, $quantity = null) {
    return $this->getTarif($adherent, $type, $quantity) !== null;
  }


  // ----- others
  public function isDossier() {
    return strpos(strtolower($this->name), 'dossier') !== false;
  }

  public function countUserAdherentsWithActiveSouscription($adherent, $date) {
    if($adherent instanceof Adherent) {
      $adherent_user_id = $adherent->user_id;
      $adherent_id = $adherent->getId();
    }
    else{
      $adherent_user_id = $adherent['user_id'];
      $adherent_id = $adherent['id'];
    }
    $adherents = Adherent::getAllAdherent($adherent_user_id);
    $souscriptions = $this->getSouscriptions(array('filters' => array('|IN|adherent_id' => $adherents->asSet('id'),
                                                                      '|!=|adherent_id' => $adherent_id,
                                                                      array(
                                                                        array('|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED),
                                                                              '|<=|start_at' => $date,
                                                                              '|>=|finish_at' => $date),
                                                                        array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))
                                                                      ))));
    return count($souscriptions->asHash('adherent_id', 'adherent_id'));
  }

  /* ----- asMethods ----- */
  public function asFinderHash($hash) {
    $hash['adherent_types'] = implode(', ', array_map(function ($type) {
      return Adherent::$types[$type];
    }, $this->adherent_types));
    $hash['document_code'] = Formulairetype::$document_codes[$hash['document_code']];
    return $hash;
  }

  public function asEditHash() {
    S('ctx')->setAttribute('is_service_formulaire', $this->isLoaded() && $this->type == Service::TYPE_FORMULAIRE);
  }

  public function asUrl($locale_id = null) {
    return NetDeclarationManager::url(array('item' => $this), $locale_id);
  }
}
