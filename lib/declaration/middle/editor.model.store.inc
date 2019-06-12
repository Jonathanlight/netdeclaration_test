<?php

try {

  $model_records = $req->record;
  $cols = array();
  
  foreach ($model_records as $record) {
    if (empty($record['type'])) continue;
    $options = array();
    if (count($record['options']) > 0) {
      foreach ($record['options'] as $name => $value) {
        if (empty($value)) continue;
        $options[] = $name.'='.$value;
      }
    }   
    $cols[] = $record['type'].(count($options) > 0 ? '&'.implode('&', $options) : '');    
  }
  
  if (count($cols) <= 0) {
     throw new Exception('Aucune colonne !');
  }
  
  $code = implode(';', $cols);
  
  if ($req->model_id > 0 && Imodel::exists($req->model_id)) {
    $model = Imodel::getInstance($req->model_id);
  }
  elseif (Imodel::exists(array('code' => $code))) {
    $model = Imodel::getInstance(array('code' => $code));
  }
  else {
    $model = Imodel::getInstance();
  }
  
  $model->commit(array('code' => $code));
  
  $ctx->model_id = $model->id;

}
catch (Exception $e) {
  $err->add($e);
}