<?php

class Dicoedi extends ActiveRecord {

  const OPTION_CHECKBOX = 'checkbox';

  public static function asOptions($code_table) {
    if ($code_table == 'TBX') return self::OPTION_CHECKBOX;
    $dicoedis = Dicoedi::collect(array('filters' => array('code_table' => $code_table)));
    if ($dicoedis->count() < 1) return self::OPTION_CHECKBOX;    
    return $dicoedis->asHash('value', 'name');
  }

}