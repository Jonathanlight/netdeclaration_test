<?php

try {

  $res->setFormat(Response::FORMAT_JSON);

  $exports = DecBdd::getAll('decbdd.checksum.export');

  $models = array();
  foreach (DecBdd::$models as $model) {
    $models[$model] = array('name' => $model,
                            'items' => array(),
      'count' => 0);
    foreach (DecBdd::$apps as $app => $hostname) {
      foreach ($exports[$app][$model] as $record_id => $checksum) {
        $models[$model]['items'][$record_id][$checksum]++;
      }
    }
    foreach ($models[$model]['items'] as $record_id => $checksums) {
      if (count($checksums) < 2 && array_sum($checksums) == count($exports)) {
        unset($models[$model]['items'][$record_id]);
      }
    }
    $models[$model]['count'] = count($models[$model]['items']);
  }
  $ctx->models = $models;

}
catch (Exception $e) {
  $err->add($e);
}