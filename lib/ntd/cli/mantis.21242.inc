<?php

return;

try {

  $declarations = Declaration::collect(array('filters' => array('dectype_id' => 6,
                                                                '|>=|created_at' => '2013-10-20'),
                                             'metas' => array('created_at')));
  $declarations->trace();
  foreach ($declarations as $declaration) {
    print $declaration->getId() . "\n";
    $fidentif = $declaration->getFormulaires(array('filters' => array('formulairetype_id' => 20)))->first();
    $data = $fidentif->data;
    unset($data['KA']);
    unset($data['KB']);
    unset($data['KC']);
    $fidentif->setAttribute('data', $data);
  }

}
catch (Exception $e) {
  print $e->getMessage();
}
