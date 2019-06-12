<?php

$res->resetTemplates();

try { 
  if ($req->hasAttribute('code')) {
    $args = array('code' => $req->code,
                  'locale' => $res->getLocale());
  }
  elseif ($req->hasAttribute('id')) {
    $args = (int) $req->id;
  }
  else {
    throw new Exception(l('error.item.unknown'));
  }
  
  $form = Form::getInstance($args);

  $ctx->form = $form;

  if ($form->hasFlag(Form::FLAG_AUTH)) {
    $uid = $req->getUserId();
  }
  
  $res->useTemplate();
  
}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }
