<?php

class Field extends ActiveRecord {

  const FLAG_REQUIRED = 1;
  const FLAG_READONLY = 2;
  const FLAG_IN_NAME = 4;

  public static $flags = array(self::FLAG_REQUIRED => 'obligatoire',
                               self::FLAG_READONLY => 'lecture seule',
                               self::FLAG_IN_NAME => 'dans résumé');

  const TYPE_TEXT = 1;
  const TYPE_SELECT = 2;
  const TYPE_RADIO = 3;
  const TYPE_CHECKBOX = 4;
  const TYPE_YESNO = 5;
  const TYPE_HIDDEN = 6;

  public static $type_names = array(self::TYPE_TEXT => 'texte',
                                    self::TYPE_SELECT => 'menu déroulant',
                                    self::TYPE_RADIO => 'radio',
                                    self::TYPE_CHECKBOX => 'checkbox',
                                    //                                    self::TYPE_YESNO => 'yesno',
                                    self::TYPE_HIDDEN => 'caché');

  public static $type_codes = array(self::TYPE_TEXT => 'text',
                                    self::TYPE_SELECT => 'select',
                                    self::TYPE_RADIO => 'radio',
                                    self::TYPE_CHECKBOX => 'checkbox',
                                    //                                    self::TYPE_YESNO => 'yesno',
                                    self::TYPE_HIDDEN => 'hidden');

  const CONTROL_SIZE = 1;
  const CONTROL_EMAIL = 2;

  public static $control_types = array(0 => 'aucun',
                                       self::CONTROL_SIZE => 'taille',
                                       self::CONTROL_EMAIL => 'email');

  const RECORD_NAME = 'record';

  protected function onBeforeCommit(&$hash) {
    if (isset($hash['code'])) {
      if (empty($hash['code']) || is_numeric($hash['code'])) {
        throw new ActiveRecordException('champ "code" invalide');
      }
      else {
        $hash['code'] = String::slugify($hash['code']);
      }
    }
    if (isset($hash['options']) && isset($hash['type']) &&
        in_array($hash['type'],
                 array(self::TYPE_SELECT, self::TYPE_RADIO, self::TYPE_CHECKBOX)) &&
        empty($hash['options'])) {
      throw new ActiveRecordException('le champs "options" est obligatoire');
    }
  }

  public function markAsEvolved() {
    parent::markAsEvolved();
    $this->getForm()->markAsEvolved();
  }

  public function asEditHash() {
    return array('disable_home' => true);
  }

  public function isHidden() {
    return $this->type == self::TYPE_HIDDEN;
  }

  public function isRequired() {
    return $this->hasFlag(self::FLAG_REQUIRED);
  }

  public function asHtml($bindings=null, $failures=null) {
    if ($this->isHidden()) {
      $attributes = array('type' => 'hidden',
                          'name' => $this->getInputName(),
                          'value' => h($this->getDefaultValue($bindings)));
      return '<input '.Hash::asAttributes($attributes).' />';
    }
    $classes  = array('form-field',
                      'form-field-'.$this->code,
                      'form-field-'.$this->getId(),
                      'form-field-type-'.self::$type_codes[$this->type]);
    if ($this->isRequired()) {
      $classes[] = 'form-field-required';
    }
    if ($this->hasFlag(self::FLAG_READONLY)) {
      $classes[] = 'form-field-readonly';
    }
    if (in_array($this->getId(), $failures)) {
      $classes[] = 'form-field-failure';
    }
    $html  = '';
    $html .= '<div class="'.join(' ', $classes).'">'."\n";
    if ($this->type != self::TYPE_CHECKBOX) {
      if ($this->name) {
        $html .= '<label>';
        $html .= c($this->name);
        if ($this->isRequired()) {
          $html .= '<span class="form-field-asterisk">*</span>';
        }
        $html .= '</label>'."\n";
      }
    } // else render checkbox differently : check renderCheckbox(...) function

    if (!empty($this->description)) {
      $html .= '<div class="form-field-description">'.$this->description.'</div>'."\n";
    }
    if (!empty($this->help)) {
      $html .= '<div class="form-field-help">'.$this->help.'</div>'."\n";
    }
    if (!empty($this->error)) {
      $style = in_array($this->getId(), $failures) ? '' : ' style="display:none;"';
      $html .= '<div class="form-field-error"'.$style.'>'.$this->error.'</div>'."\n";
    }


    switch ($this->type) {
    case self::TYPE_CHECKBOX: $html .= $this->renderCheckbox($bindings); break;
    case self::TYPE_RADIO: $html .= $this->renderRadio($bindings); break;
    case self::TYPE_SELECT: $html .= $this->renderSelect($bindings); break;
    case self::TYPE_TEXT: $html .= $this->renderText($bindings); break;
    case self::TYPE_YESNO: $html .= $this->renderYesno($bindings); break;
    case self::TYPE_FILE: $html .= $this->renderFile($bindings); break;
    }
    $html .= "\n";
    $html .= '</div>'."\n";
    return $html;
  }

  private function getInputName() {
    return self::RECORD_NAME.'['.$this->getId().']';
  }

  private function getDefaultValue($bindings) {
    if (isset($bindings[$this->id])) {
      $value = $bindings[$this->id];
      return $value;
    }
    $value = $this->default;
    if ($value['0'] == '$') {
      $value = substr($value, 1);
      $value = $bindings[$value];
    }
    return $value;
  }

  private function renderText($bindings) {
    if ($this->size > 0) {
      return $this->renderTextarea($bindings);
    }
    $attributes = array('class' => 'text',
                        'type' => 'text',
                        'name' => $this->getInputName());
    $attributes['value'] = h($this->getDefaultValue($bindings));
    if ($this->hasFlag(self::FLAG_READONLY)) {
      $attributes['readonly'] = 'true';
    }

    if (!empty($this->placeholder)) {
      $attributes['placeholder'] = $this->placeholder;
    }

    $html .= '<input '.Hash::asAttributes($attributes).' />';
    return $html;
  }

  private function renderTextarea($bindings) {
    $attributes = array('name' => $this->getInputName(),
                        'rows' => $this->size);
    if ($this->hasFlag(self::FLAG_READONLY)) {
      $attributes['readonly'] = 'true';
    }
    if (!empty($this->placeholder)) {
      $attributes['placeholder'] = $this->placeholder;
    }
    $default = $this->getDefaultValue($bindings);
    $html = '<textarea '.Hash::asAttributes($attributes).'>'.h($default).'</textarea>';
    return $html;
  }

  private function renderSelect($bindings) {
    $attributes = array('name' => $this->getInputName());
    if ($this->size > 0) {
      $attributes['size'] = $this->size;
      $attributes['multiple'] = 'multiple';
      $attributes['name'] .= '[]';
    }
    if ($this->hasFlag(self::FLAG_READONLY)) {
      $attributes['readonly'] = 'true';
    }
    $default = $this->getDefaultValue($bindings);
    $default = String::asSet($default);
    $options = String::asSet($this->options);
    $html  = '<select '.Hash::asAttributes($attributes).'>'."\n";
    foreach ($options as $option) {
      $selected = in_array($option, $default) ? ' selected="selected"' : '';
      $html .= ' <option value="'.$option.'"'.$selected.'>'.$option.'</option>'."\n";
    }
    $html .= '</select>';
    return $html;
  }

  private function renderCheckbox($bindings) {
    $attributes = array('name' => $this->getInputName().'[]',
                        'type' => 'checkbox');
    if ($this->hasFlag(self::FLAG_READONLY)) {
      $attributes['readonly'] = 'true';
    }
    $default = $this->getDefaultValue($bindings);
    $default = String::asSet($default);
    $options = String::asSet($this->options);
    $html = '<div class="field-options">';
    foreach ($options as $option) {
      $attributes['value'] = $option;
      $checked = in_array($option, $default) ? ' checked="checked"' : '';
      $html .= ' <label>';
      $html .= '<input '.Hash::asAttributes($attributes).$checked.' />';
      // render "intitule" field
      if ($this->name) {
        $html .= c($this->name);
        if ($this->isRequired()) {
          $html .= '<span class="form-field-asterisk">*</span>';
        }
      } else { // otherwise render the checkbox options field value
        $html .= $option;
      }

      $html .= '</label>'."\n";
    }
    $html .= '</div>';
    return $html;
  }

  private function renderRadio($bindings) {
    $attributes = array('name' => $this->getInputName().'[]',
                        'type' => 'radio');
    if ($this->hasFlag(self::FLAG_READONLY)) {
      $attributes['readonly'] = 'true';
    }
    $default = $this->getDefaultValue($bindings);
    $default = String::asSet($default);
    $options = String::asSet($this->options);
    $html = '<div class="field-options">';
    foreach ($options as $option) {
      $attributes['value'] = $option;
      $checked = in_array($option, $default) ? ' checked="checked"' : '';
      $html .= ' <label>';
      $html .= '<input '.Hash::asAttributes($attributes).$checked.' />';
      $html .= $option;
      $html .= '</label>'."\n";
    }
    $html .= '</div>';
    return $html;
  }

  public static function captcha($failures) {
    $html = '';
    $classes  = array('form-field',
                      'form-field-captcha',
                      'form-field-required');
    if (in_array('captcha', $failures)) {
      $classes[] = 'form-field-failure';
    }
    $html .= '<div class="'.join(' ', $classes).'">'."\n";
    $html .= '<label>Code de sécurité</label>'."\n";
    $html .= '<div class="form-field-help" style="display:none;">Veuillez indiquez</div>'."\n";
    $html .= '<div class="form-field-error" style="display:none;">Tous les caractères doivent être indiqués</div>'."\n";
    $html .= W::captcha();
    $html .= '</div>'."\n";
    return $html;
  }

  public static function asList($form) {
    if (!$form->isItem()) return '';
    $fields = $form->getFields();
    $html = '<ul>'."\n";
    if (count($fields) < 1) {
      $html .= '<li id="element_0" data-id="0" data-position="0">';
      $html .= ' <div><a href="javascript:void(0)">DROP HERE</a></div>';
      $html .= ' <div></div>';
      $html .= '</li>'."\n";
    }
    else {
      foreach ($fields as $field) {
        $html .= '<li id="xxx_'.$field->getId().'" data-id="'.$field->id.'" data-position="'.($field->position+1).'">';
        $class = 'handle';
        $class .= $field->status < 1 ? ' offline' : '';
        $html .= '<div>';
        $html .= '<strong class="'.$class.'">=</strong>';
        $html .= ' <a href="javascript:void(0)">'.$field->code.'</a></div>';
        $html .= ' <div></div>';
        $html .= '</li>'."\n";
      }
    }
    $html .= '</ul>'."\n";
    return $html;
  }







}


