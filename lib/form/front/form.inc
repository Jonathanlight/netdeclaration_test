<?php

try {

  if ($req->hasAttribute('code')) {
    $args = array('code' => $req->code,
                  'locale' => $res->getLocale());
  }
  elseif ($req->hasAttribute('id')) {
    $args = (int) $req->id;
  }
  else {
    throw new Exception('args missing');
  }
  
  $form = Form::getInstance($args);

  $form->track();

  $res->setSeo($form);
  $res->write($form->asHtml());
  
}
catch (Exception $e) { $err->add($e); }