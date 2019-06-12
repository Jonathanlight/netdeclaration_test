<?php

try {

  $model = $req->model;

  $models = DecBdd::$models;
  if (in_array($model, DecBdd::$models)) {
    $models = array($model);
  }

  $export = array();
  foreach ($models as $model) {
    $checksums = Checksum::collect(array('filters' => array('model_id' => Model::id($model))));
    $export[$model] = $checksums->asHash('record_id', 'checksum');
  }

  $res->write(var_export($export, true));
  $res->setFormat(Response::FORMAT_TEXT);
  $res->useTemplates(array(null));

}
catch (Exception $e) {
  $err->add($e);
}