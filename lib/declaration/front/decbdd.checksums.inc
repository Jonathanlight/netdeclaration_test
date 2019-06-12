<?php

try {

  $model = $req->model;

  $exports = DecBdd::getAll('decbdd.checksum.export', array('model' => $model));

  $checksums = array('name' => $model,
                     'items' => array(),
                     'count' => 0);
  foreach (DecBdd::$apps as $app => $hostname) {
    foreach ($exports[$app][$model] as $record_id => $checksum) {
      $checksums['items'][$record_id][$checksum]++;
    }
  }
  foreach ($checksums['items'] as $record_id => $item_checksums) {
    if (count($item_checksums) < 2 && array_sum($item_checksums) == count($exports)) {
      unset($checksums['items'][$record_id]);
    }
  }
  $checksums['count'] = count($checksums['items']);
  $ctx->checksums = $checksums;

  $res->setFormat(Response::FORMAT_JSON);

}
catch (Exception $e) {
  $err->add($e);
}