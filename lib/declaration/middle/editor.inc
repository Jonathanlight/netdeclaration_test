<?php

try {

  $itemplate = Itemplate::getInstance((int) $req->itemplate_id);
  $editor = FormEditor::getInstance($itemplate);
  $ctx->editor = $editor;
  $ctx->render = $editor->renderTemplate();
  $ctx->ftype = $itemplate->getFormulairetype();
  $ctx->itemplate = $itemplate;
  $res->resetTemplates();
  $res->useTemplate();
}
catch (Exception $e) {    
  $err->add($e);
}