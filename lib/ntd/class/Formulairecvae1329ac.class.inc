<?php

class Formulairecvae1329ac {

  const FORMULAIRE_CODE = 'cvae1329ac';

  public static function accompteAVerser($args, $data, $params) {
    list($result, $item1, $item2, $item3) = $args['items'];
    $result = $data[$item1] + $data[$item2] - $data[$item3];
    $cible = self::FORMULAIRE_CODE . '_' . $result;
    ValidMain::checkmatch(round($result, 2), $data[$result], $cible);
  }

  public static function paiement(){

  }

}

