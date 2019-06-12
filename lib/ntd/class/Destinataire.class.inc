<?php

class Destinataire extends ActiveRecord {

  const TYPE_DGI = 'DGI';
  const TYPE_BDF = 'BDF';
  const TYPE_OGA = 'OGA';
  const TYPE_BQE = 'BQE';
  const TYPE_CEC = 'CEC';
  const TYPE_IRC = 'IRC';
  const TYPE_OGA2 = 'OGA2';
  const TYPE_OGA3 = 'OGA3';
  const TYPE_URSSAF = 'URSSAF';
  const TYPE_XXX = 'XXX';

  const FLAG_ADHERENT_DESTINATAIRE_CACHED = 1;
  const FLAG_SOUSCRIPTIONS_CACHED = 2;

  const SENS_EMISSION = 'E';
  const SENS_RECEPTION = 'R';

  const STATUS_ACK_ANO = 'ACK ANO';
  const STATUS_ACK_DEPOT = 'ACK DEPOT';
  const STATUS_ACK_KO = 'ACK KO';
  const STATUS_ACK_OK = 'ACK OK';
  const STATUS_CONTROL = 'CONTROL';
  const STATUS_ENVOYE = 'ENVOYE';
  const STATUS_ERREUR = 'ERREUR';
  const STATUS_REJET = 'REJET';

  public static $sens = array(
    self::SENS_EMISSION => 'Émission',
    self::SENS_RECEPTION => 'Réception'
  );

  public static $types = array(
    self::TYPE_BDF => 'Banque de France',
    self::TYPE_DGI => 'DGFiP',
    self::TYPE_OGA => 'OGA',
    self::TYPE_OGA2 => 'OGA2',
    self::TYPE_OGA3 => 'OGA3',
    self::TYPE_BQE => 'BQE',
    self::TYPE_CEC => 'CEC',
    self::TYPE_IRC => 'IRC',
    self::TYPE_URSSAF => 'URSSAF',
    self::TYPE_XXX => 'XXX',
  );

  public static $types_exported = array(
    self::TYPE_BDF,
    self::TYPE_DGI,
    self::TYPE_OGA,
    self::TYPE_CEC,
  );

  public static $statuses = array(
    self::STATUS_ACK_OK => 'Acquittement OK reçu',
    self::STATUS_ACK_KO => 'Acquittement KO reçu',
    self::STATUS_ACK_ANO => 'Acquittement ANOMALIE reçu',
    self::STATUS_ENVOYE => 'Envoyé vers le destinataire',
    self::STATUS_REJET => 'Rejeté par Net Declaration',
  );

  public static $flags = array(
    self::FLAG_ADHERENT_DESTINATAIRE_CACHED => '[Cache] Adhérent destinataire',
    self::FLAG_SOUSCRIPTIONS_CACHED => '[Cache] Souscriptions',
  );


  public function getAdherentDestinataireName() {
    if ($this->type_dest == self::TYPE_OGA && Adherent::exists($this->adherent_destinataire_id)) {
      $destinataire_name = 'OGA - ' . Adherent::getInstance($this->adherent_destinataire_id)->company;
    }
    elseif (isset(self::$types[$this->type_dest])) {
      $destinataire_name = self::$types[$this->type_dest];
    }
    else {
      $destinataire_name = $this->type_dest;
    }
    if (!empty($this->siret)) {
      //$destinataire_name .= ' - ' . $this->siret;
    }
    return $destinataire_name;
  }

  public function status() {
    return self::$statuses[$this->status];
  }

  public function asWebserviceHash() {
    return $this->getAttributes();
  }

  protected function onAfterCommit($attrs) {
    $this->cache();
  }

  public function getAdherentEmetteurName() {
    if ($this->suivi_adherent_emetteur_id > 0 && Adherent::exists($this->suivi_adherent_emetteur_id)) {
      return Adherent::getInstance($this->suivi_adherent_emetteur_id)->company;
    }
    return '';
  }

  public function getAdherentDeclarantName() {
    if ($this->suivi_adherent_declarant_id > 0 && Adherent::exists($this->suivi_adherent_declarant_id)) {
      return Adherent::getInstance($this->suivi_adherent_declarant_id)->company;
    }
    return $this->getSuivi()->nom_decl;
  }

  public function cache() {
    if (!$this->hasFlag(self::FLAG_ADHERENT_DESTINATAIRE_CACHED)) {
      $this->setAttributes(array('adherent_destinataire_id' => Suivi::getAdherentId($this->siret)));
      $this->setFlag(self::FLAG_ADHERENT_DESTINATAIRE_CACHED);
    }

    $suivi = $this->getSuivi();
    if (!$this->hasFlag(self::FLAG_SOUSCRIPTIONS_CACHED)) {
      if ($suivi->adherent_emetteur_id > 0 && Adherent::exists($suivi->adherent_emetteur_id)) {
        $adherent_emetteur = Adherent::getInstance($suivi->adherent_emetteur_id);
        $opts = array(
          'include' => array('edimessagetype'),
          'filters' => array('ntd_edimessagetype.name' => $suivi->message,
                                         'destinataire' => $this->type_dest,
                                         'sens' => Suivipayant::SENS_E,
                                         'adherent_type' => $adherent_emetteur->type,
                                         'status' => 1));
        $suivi_payants = Suivipayant::collect($opts);
        foreach ($suivi_payants as $suivi_payant) {
          $opts = array('filters' => array('|IN|service_id' => $suivi_payant->getServices()->asSet('id'),
                                           '|IN|status' => array(Souscription::STATUS_ACTIVE,
                                                                 Souscription::STATUS_WAITING_PAIEMENT,
                                                                 Souscription::STATUS_CANCELLING_ASKED),
                                           '|<=|start_at' => $suivi->date_depot,
                                           '|>|finish_at' => $suivi->date_depot));
          $souscriptions = $adherent_emetteur->getSouscriptions($opts);
          foreach ($souscriptions as $souscription) {
            S('dbo')->insert('ntd_souscription_suivi',
                             array('souscription_id' => $souscription->getId(),
                                   'suivi_id' => $suivi->getId(),
                                   'destinataire_id' => $this->getId(),
                                   'suivipayant_id' => $suivi_payant->getId()),
                             array('IGNORE'));
          }
        }
      }
      if ($this->adherent_destinataire_id > 0 && Adherent::exists($this->adherent_destinataire_id)) {
        $adherent_destinataire = Adherent::getInstance($this->adherent_destinataire_id);
        $opts = array(
          'include' => array('edimessagetype'),
          'filters' => array('ntd_edimessagetype.name' => $suivi->message,
                             'destinataire' => $this->type_dest,
                             'sens' => Suivipayant::SENS_R,
                             'adherent_type' => $adherent_destinataire->type,
                             'status' => 1));
        $suivi_payants = Suivipayant::collect($opts);
        foreach ($suivi_payants as $suivi_payant) {
          $opts = array('filters' => array('|IN|service_id' => $suivi_payant->getServices()->asSet('id'),
                                           '|IN|status' => array(Souscription::STATUS_ACTIVE,
                                                                 Souscription::STATUS_WAITING_PAIEMENT,
                                                                 Souscription::STATUS_CANCELLING_ASKED),
                                           '|<=|start_at' => $suivi->date_depot,
                                           '|>|finish_at' => $suivi->date_depot));
          $souscriptions = $adherent_destinataire->getSouscriptions($opts);
          foreach ($souscriptions as $souscription) {
            S('dbo')->insert('ntd_souscription_suivi',
                             array('souscription_id' => $souscription->getId(),
                                   'suivi_id' => $suivi->getId(),
                                   'destinataire_id' => $this->getId(),
                                   'suivipayant_id' => $suivi_payant->getId()),
                             array('IGNORE'));
          }
        }
      }
      $this->setFlag(self::FLAG_SOUSCRIPTIONS_CACHED);
    }


    $this->setAttributes(array('adherent_declarant_id' => $suivi->adherent_declarant_id,
                               'suivi_date_depot' => $suivi->date_depot,
                               'adherent_emetteur_id' => $suivi->adherent_emetteur_id));


//    $suivi_payants = $this->getService()->getSuiviPayants(array('filters' => array('status' => 1)));
//    if ($suivi_payants->count() < 1) {
//      return array('filters' => array('id' => -1,
//                                      'origine' => 'EDI'));
//    }
//
//    $adherent = $this->getAdherent();
//
//    // get All adherent siret
//    $sirets = $adherent->getAllSirets();
//    $filters = array();
//    foreach ($suivi_payants as $key => $suivi_payant) {
//      $filter = array(T('suivi') . '.message' => $suivi_payant->message,
//                      'type_dest' => $suivi_payant->destinataire,
//                      '|IN|' . ($suivi_payant->sens == Suivipayant::SENS_R ? 'siret' : 'siret_emetteur') => $sirets);
//      if ($key == 0) {
//        $filters[0] = $filter;
//      }
//      else {
//        $filters[]['OR'] = $filter;
//      }
//    }
//
//    // get all OGA adherents
//    $ogas = Adherent::collect(array('filters' => array('|!=|id' => $adherent->getId(),
//                                                       'type' => Adherent::TYPE_OGA,
//                                                       'status' => Adherent::STATUS_SUBSCRIPTION_VALIDE)));
//    $sirets_ogas = array();
//    foreach ($ogas as $oga) {
//      $sirets_ogas = array_merge($sirets_ogas, $oga->getAllSirets());
//    }
//
//    $opts = array('include' => array('destinataire'),
//                  'filters' => array());
//    $opts['filters']['|><|date_depot'] = array($this->start_at, $this->finish_at);
//    $opts['filters']['origine'] = 'EDI';
//    $opts['filters']['|!IN|siret'] = $sirets_ogas;
//    $opts['filters'][] = $filters;

  }

}