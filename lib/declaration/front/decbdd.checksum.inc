<?php

try {

  if (P('app.state') != 'dev') return;

  $exports = DecBdd::getAll('decbdd.checksum.export');

  $models = array();
  foreach (DecBdd::$models as $model) {
    foreach (DecBdd::$apps as $app => $hostname) {
      foreach ($exports[$app][$model] as $record_id => $checksum) {
        $models[$model][$record_id][$checksum] = $checksum;
      }
    }
    foreach ($models[$model] as $record_id => $checksums) {
      if(count($checksums) < 2) {
        unset($models[$model][$record_id]);
      }
    }
  }

  $ctx->models = $models;


  $res->useTemplates(array(null, 'skeleton.decbdd', true));

}
catch (Exception $e) {
  $err->add($e);
}