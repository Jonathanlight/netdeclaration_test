<?php

try {

  $fidentif_type = Formulairetype::getInstance(array('code' => 'F-IDENTIF'));
  foreach (Declaration::collect(array('filters' => array('|IN|id' => array(71448, 71323, 71675)))) as $declaration) {
    print $declaration->getId() . "\n";
    $fidentif = Formulaire::getInstance(array('declaration_id' => $declaration->getId(),
                                              'formulairetype_id' => $fidentif_type->getId()));
    $fields_values = $fidentif->fields_values;
    print 'CC : ' . $fields_values['CC'][0] . "\n";
    print 'CE : ' . $fields_values['CE'][0] . "\n";

    if (strlen($fields_values['CC'][0]) > 2 && stripos($fields_values['CC'][0], 'mois') === false) {
      $fields_values['CC'][0] = '';
    }
    elseif (strlen($fields_values['CC'][0]) > 0) {
      $fields_values['CC'][0] = (int) $fields_values['CC'][0];
    }
    if (strlen($fields_values['CE'][0]) > 2 && stripos($fields_values['CE'][0], 'mois') === false) {
      $fields_values['CE'][0] = '';
    }
    elseif (strlen($fields_values['CE'][0]) > 0) {
      $fields_values['CE'][0] = (int) $fields_values['CE'][0];
    }
    print 'CC : ' . $fields_values['CC'][0] . "\n";
    print 'CE : ' . $fields_values['CE'][0] . "\n";
    //$fidentif->setAttribute('fields_values', $fields_values);
    //print $fidentif->getId();
    $declaration->generateTradeExpressData();
  }

}
catch (Exception $e) {
  print $e->getMessage();
}
