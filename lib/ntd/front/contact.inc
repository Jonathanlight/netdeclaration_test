<?php

try {

  $form = Form::getInstance(array('code' => 'ntd.form.contact',
                                  'locale' => $res->getLocale()));

  $form->track();


  $key = 'form' . $form->getId();
  if ($req->hasAttribute($key)) {
    $attribute = $req->getAttribute($key);
    $bindings = (array) $attribute['fields'];
    $failures = (array) $attribute['failures'];
  }
  else {
    $bindings = (array) $bindings;
    $failures = (array) $failures;
  }

  $args = array();

  $fields = '';
  $hidden = '<input type="hidden" name="item_key" value="' . $form->getKey() . '" />' . "\n";

  foreach ($form->getFields() as $field) {
    if (!$field->isOnline() || !$field->isHidden()) continue;
    $hidden .= $field->asHtml($bindings, $failures) . "\n";
  }

  foreach ($form->getFields() as $field) {
    if (!$field->isOnline() || $field->isHidden()) continue;
    $fields .= $field->asHtml($bindings, $failures) . "\n";
  }

  if ($form->hasFlag(Form::FLAG_CAPTCHA)) {
    $fields .= Field::captcha($failures);
  }

  $ctx->action = '/form/submission.save';
  $ctx->onsubmit = $form->onsubmit ? : 'Kwo.Form.onSubmit(this)';
  $ctx->class = $form->class ? ' ' . $form->class : '';
  $ctx->fields = $fields;
  $ctx->hidden = $hidden;
  $ctx->form = $form;


  $res->setBreadcrumb(array('page d\'accueil' => '/',
                            $form->title));
  $res->setSeo($form);
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
