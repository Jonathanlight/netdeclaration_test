<?php

try {
  
  if ($req->model_id > 0) {
    $ctx->model = Imodel::getInstance($req->model_id);
    $ctx->cells = explode(";", $ctx->model->code); 
    $ctx->default_cols = count($ctx->cells);
  } 
  else {
    $ctx->default_cols = Imodel::DEFAULT_COLS;
  }
  
  $res->resetTemplates();
  $res->useTemplate();
  
}
catch (Exception $e) {
  $err->add($e);
}