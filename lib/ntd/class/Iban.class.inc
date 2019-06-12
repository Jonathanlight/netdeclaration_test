<?php

class Iban extends ActiveRecord {

  const MAX_IBAN_PER_ADHERENT = 3;

  const TYPE_PRIMARY = 1;
  const TYPE_SECONDARY = 2;

  public static $types = array(
    self::TYPE_PRIMARY => 'IBAN Primaire',
    self::TYPE_SECONDARY => 'IBAN Secondaire'
  );

  /* ----- STATIC ----- */
  public static function validateIban($hash) {
    if (!(is_numeric($hash['code_banque']) && strlen($hash['code_banque']) == 5)) {
      throw new Exception(l('iban.validation.code_banque'));
    }
    if (!(is_numeric($hash['code_guichet']) && strlen($hash['code_guichet']) == 5)) {
      throw new Exception(l('iban.validation.code_guichet'));
    }
    $hash['numero_compte'] = trim($hash['numero_compte']);
    if (!strlen($hash['numero_compte']) == 11) {
      throw new Exception(l('iban.validation.numero_compte'));
    }
    if (!(is_numeric($hash['cle_iban']) && strlen($hash['cle_iban']) == 2)) {
      throw new Exception(l('iban.validation.cle_iban'));
    }
    if (empty($hash['numero_iban'])) {
      throw new Exception(l('iban.validation.numero_iban'));
    }
    Iban::compareIban($hash['numero_iban'], array('banque' => $hash['code_banque'],
                                                  'guichet' => $hash['code_guichet'],
                                                  'compte' => $hash['numero_compte'],
                                                  'clef' => $hash['cle_iban']));
    if (strlen($hash['numero_bic']) != 8 && strlen($hash['numero_bic']) != 11) {
      throw new Exception(l('iban.validation.numero_bic'));
    }    
  }

  protected function onBeforeCommit(&$attrs) {
    if (S('req')->isBack()) {      
      //self::validateIban($attrs);
    }
  }

  public function asHtml() {
    $html = 'IBAN : '.$this->banque
        .' - '.$this->code_banque
        .' - '.$this->code_guichet
        .'	- '.$this->numero_compte
        .' - '.$this->cle_iban;
    return $html;
  }

  public function asFormulaireInputLabel() {
    return "$this->code_banque-$this->code_guichet-$this->numero_compte-$this->cle_iban";
  }

  public function asFormulaireInputValue() {
    return "$this->code_banque$this->code_guichet$this->numero_compte$this->cle_iban";
  }

  /*
  public function getAttribute($key) {
    if ($key == 'option_label') return $this->asFormulaireInputLabel();
    if ($key == 'option_value') return $this->asFormulaireInputValue();
    return parent::getAttribute($key);
  }*/

  public function formatToDb() {

  }

  public static function formatFromDb($value) {
    if (strlen($value) != 23) return $value;
    $code_banque = substr($value, 0, 5);
    $code_guichet = substr($value, 5, 5);
    $numero_compte = substr($value, 10, 11);
    $cle_iban = substr($value, 21, 2);
    return "$code_banque-$code_guichet-$numero_compte-$cle_iban";
  }

  public static function compareIban($iban, $args) {
    if (!Valid::isRib($args)) {
      throw new Exception(l('iban.validation.rib'));
    }
    $generated_iban = 'FR'.$args['banque'].$args['guichet'].$args['compte'].$args['clef'];
    $iban_tmp = substr($iban, 0, 2).substr($iban, 4);
    if ($generated_iban != $iban_tmp || !Valid::isIBan($iban, 'FR')) {
      throw new Exception(l('iban.validation.numero_iban'));
    }
  }

  public static function getHashFromNumeroIban($numero_iban) {
    return array('code_banque' => substr($numero_iban, 4, 5),
                 'code_guichet' => substr($numero_iban, 9, 5),
                 'numero_compte' => substr($numero_iban, 14, 11),
                 'cle_iban' => substr($numero_iban, 25, 2));

  }

  public function getName($locale = null) {
    return "[".$this->getType()."] ".$this->asFormulaireInputLabel();
  }

  public function getType() {
    return self::$types[$this->type];
  }

}