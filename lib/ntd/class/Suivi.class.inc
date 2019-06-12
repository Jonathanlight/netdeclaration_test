<?php

class Suivi extends ActiveRecord {

  const FLAG_ADHERENT_EMETTEUR_CACHED = 1;
  const FLAG_ADHERENT_DECLARANT_CACHED = 2;


  public static $flags = array(
    self::FLAG_ADHERENT_EMETTEUR_CACHED => '[Cache] Adhérent émetteur',
    self::FLAG_ADHERENT_DECLARANT_CACHED => '[Cache] Adhérent déclarant',
  );

  public static $flgs = array('flg_depot' => 'Dépôt',
                              'flg_envoi' => 'Envoi',
                              'flg_ack' => 'Réception');

  /*public static function getTeletransmissionsCount($adherent_id, $date_depot) {
    $sql = 'SELECT COUNT(*) '
        . ' FROM ntd_destinataire d '
        . ' LEFT JOIN ntd_suivi s ON (d.suivi_id = s.id)  '
        . ' WHERE s.adherent_id = :adherent_id:';
    $bindings = array(':adherent_id:' => $adherent_id);
    $count = S('dbo')->query($sql, $bindings)->fetchValue();
    return $count;
  }*/

  public function asWebserviceHash() {
    $attributes = $this->getAttributes();
    $attributes['ref_envoi'] = $attributes['declaration_id'];
    unset($attributes['declaration_id']);
    return $attributes;
  }

  public function hasDeclaration() {
    return self::suiviHasDeclaration($this->declaration_id);
  }

  public static function suiviHasDeclaration($declaration_id) {
    return $declaration_id > 0 && Declaration::exists($declaration_id);
  }

  public function getDeclaration() {

    return  Declaration::exists($this->declaration_id) ? (Declaration::getInstance($this->declaration_id)) : null;
  }

  protected function onAfterCommit($attrs) {
    $this->cache();
    if ($this->declaration_id > 0) {
      if (Declaration::exists($this->declaration_id)) {
        $declaration = Declaration::getInstance($this->declaration_id);
        $declaration->setAttribute('suivi_id', $this->getId());
      }
    }

  }


  public function cache() {
    if (!$this->hasFlag(self::FLAG_ADHERENT_DECLARANT_CACHED)) {
      $this->setAttributes(array('adherent_declarant_id' => self::getAdherentId($this->siret_decl)));
      $this->setFlag(self::FLAG_ADHERENT_DECLARANT_CACHED);
    }
    if (!$this->hasFlag(self::FLAG_ADHERENT_EMETTEUR_CACHED)) {
      $this->setAttributes(array('adherent_emetteur_id' => self::getAdherentId($this->siret_emetteur)));
      $this->setFlag(self::FLAG_ADHERENT_EMETTEUR_CACHED);
    }
    foreach ($this->getDestinataires() as $destinataire) {
      $destinataire->cache();
    }
  }

  public static function getAdherentId($siret) {
    if (empty($siret)) {
      return 0;
    }
    //return Adherent::exists(array('siret' => $siret));

    $adherents = Adherent::collect(array('filters' => array('siret' => $siret,
                                                            array('OR' => array('|%%|old_sirets' => $siret))
    )));
    if ($adherents->count() == 1) {
      return $adherents->first()->getId();
    }
    elseif ($adherents->count() > 1) {
      return '99999999999999';
    }
    return 0;
  }

  public function getAdherentEmetteurName() {
    if ($this->adherent_emetteur_id > 0 && Adherent::exists($this->adherent_emetteur_id)) {
      return Adherent::getInstance($this->adherent_emetteur_id)->company;
    }
    return '';
  }

  public function getAdherentDeclarantName() {
    return $this->nom_decl;
  }


}
