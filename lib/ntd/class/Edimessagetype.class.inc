<?php

class Edimessagetype extends ActiveRecord {

  const FLAG_CREATED_AUTO = 1;

  public static $flags = array(
    self::FLAG_CREATED_AUTO => 'Créée automatiquement'
  );

  public static function generate() {
    $sql = 'SELECT DISTINCT  `message` FROM `ntd_suivi` ORDER BY `message` ASC';
    foreach (S('dbo')->query($sql) as $row) {
      $code = String::urlify($row['message']);
      if (Edimessagetype::exists(array('code' => $code))) {
        continue;
      }
      $edimessagetype = Edimessagetype::getInstance();
      $edimessagetype->commit(array('code' => $code,
                                    'name' => $row['message']));
      $edimessagetype->setFlag(self::FLAG_CREATED_AUTO);
    }
  }

  public static function associateSuiviPayant(){
    foreach(Suivipayant::collect() as $suivipayant) {
      if($suivipayant->edimessagetype_id > 0) {
        continue;
      }
      $suivipayant->commit(array('edimessagetype_id' => Edimessagetype::exists(array('name' => $suivipayant->message))));
    }
  }

  protected function onBeforeCommit(&$attrs){
    if($attrs['name']) {
      $attrs['code'] = String::urlify($attrs['name']);
    }
  }

}