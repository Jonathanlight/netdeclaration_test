<?php

class Form extends ActiveRecord
{
  const FLAG_ACK_SEND = 1;
  const FLAG_ACK_SHOW = 2;
  const FLAG_ALERT = 4;
  const FLAG_AUTH = 8;
  const FLAG_CAPTCHA = 16;
  const FLAG_CONVERSION = 32;

  public static $flags = array(self::FLAG_ACK_SEND => 'mail de confirmation',
                               self::FLAG_ACK_SHOW => 'message de confirmation',
                               self::FLAG_ALERT => 'avertissement',
                               self::FLAG_AUTH => 'compte obligatoire',
                               self::FLAG_CAPTCHA => 'captcha',
                               self::FLAG_CONVERSION => 'conversion');

  public function getDetails() {
    return array('nbre réponses' => $this->countSubmissions());
  }

  public function asEditHash() {
    $out = array();
    if ($this->isItem()) {
      $out['workspace'] = H::get('/back/form/field.workspace',
                                 array('form_id' => $this->getId()));
    }
    return $out;
  }

  public function getFieldCodes() {
    $fields = array();
    foreach ($this->getFields() as $field) {
      if (!$field->isOnline()) continue ;
      $fields[$field->id] = $field->code;
    }
    return $fields;
  }

  public function asHtml($bindings=null, $failures=null) {
    $req = S('req');

    $key = 'form'.$this->getId();
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
    $hidden = '<input type="hidden" name="item_key" value="'.$this->getKey().'" />'."\n";

    foreach ($this->getFields() as $field) {
      if (!$field->isOnline() || !$field->isHidden()) continue ;
      $hidden .= $field->asHtml($bindings, $failures)."\n";
    }

    foreach ($this->getFields() as $field) {
      if (!$field->isOnline() || $field->isHidden()) continue ;
      $fields .= $field->asHtml($bindings, $failures)."\n";
    }

    if ($this->hasFlag(self::FLAG_CAPTCHA)) {
      $fields .= Field::captcha($failures);
    }

    $args['action'] = '/form/submission.save';
    $args['onsubmit'] = $this->onsubmit ?: 'Kwo.Form.onSubmit(this)';
    $args['class'] = $this->class ? ' '.$this->class : '';
    $args['fields'] = $fields;
    $args['hidden'] = $hidden;
    $args['form'] = $this;

    $skeleton = $this->skeleton ?: 'form:form.skeleton';

    return Template::render($skeleton, $args);
  }

}