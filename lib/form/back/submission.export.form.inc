<?php

try {

  $form = Form::getInstance((int) $req->getBranchValue('form_id'));

  $fields = array();
  foreach ($form->getFields() as $field) {
    $fields[$field->getId()] = $field->code;
  }

  $ctx->fields = $fields;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
