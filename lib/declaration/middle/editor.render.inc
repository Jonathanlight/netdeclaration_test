<?php

try {

  $itemplate = Itemplate::getInstance((int) $req->itemplate_id);
  $itemplate->setAttribute('html', $req->template);
  $itemplate->renderPsp();  
  $render = FormEditor::getInstance($itemplate)->renderTemplate();  
  $ctx->html = $render['html'];
  $ctx->code = $render['code'];

  $res->resetTemplates();
  
}
catch (Exception $e) {
  $log->debug($e);
  $err->add($e);
}