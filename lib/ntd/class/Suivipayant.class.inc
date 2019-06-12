<?php

class Suivipayant extends ActiveRecord {

  const SENS_E = 1;
  const SENS_R = 2;

  public static $sens = array(self::SENS_E => 'E',
                              self::SENS_R => 'R');

  // cf https://mantis.kernix.com/view.php?id=13994
  public static $destinataires = array('DGI' => 'DGFiP',
                                       'OGA' => 'OGA',
                                       'BDF' => 'Banque de france (BDF)',
                                       'URSSAF' => 'URSSAF',
                                       'IRC' => 'Caisse de retraite (IRC)',
                                       'CEC' => 'CEC',
                                       'DSI' => 'DSI',
                                       'RSI' => 'RSI',
                                       'DSN' => 'DSN',
                                       'ENT' => 'ENT',
                                       'BQE' => 'BQE');

  public static $types_doc = array('LIASSE' => 'LIASSE',
                                   'TVA' => 'TVA',
                                   'PAYE' => 'PAYE',
                                   'SOCIAL' => 'SOCIAL',
                                   'DSI' => 'DSI',
                                   'WEBREQ' => 'WEBREQ');

  public function asFinderHash(&$hash) {
    $hash['adherent_type'] = Adherent::$types[$this->adherent_type];
    $hash['edimessagetype_name'] = Edimessagetype::exists($this->edimessagetype_id) ? Edimessagetype::getInstance($this->edimessagetype_id)->name : '-';
    $hash['sens'] = self::$sens[$this->sens];
    return $hash;
  }

  public static function collectByAdherentType($adherent_type) {
    return self::collect(array('filters' => array('adherent_type' => $adherent_type,
                                                  'status' => 1)))->asArray();
  }

  protected function onAfterCommit($attrs) {
    $this->setAttribute('name',
                        '[' . Adherent::$types_shorts[$this->adherent_type] . ']'
                            . ' [' . self::$sens[$this->sens] . ']'
                            . ' ' . $this->type_doc
                            . ' ' . (Edimessagetype::exists($this->edimessagetype_id) ? Edimessagetype::getInstance($this->edimessagetype_id)->name : '-')
                            . ' => ' . $this->destinataire);
  }

}
