<?php

try {

  $itemplate = Itemplate::getInstance($req->itemplate_id);
  $editor = FormEditor::getInstance($itemplate);

  $model = Imodel::getInstance($req->model_id);
  $opts = array();
  parse_str((string) $req->opts, $opts);

  $ctx->cols = explode(";", $model->code); 
  $ctx->fields = $editor->getFields();
  $ctx->used_field = $editor->getUsedFields();
  $ctx->model_id = $model->id;
  $ctx->data = $req->data ? explode(";", $req->data) : array();
  $ctx->opts = $opts;

  $res->resetTemplates();  
  $res->useTemplate();
  
}
catch (Exception $e) {
  $err->add($e);
}