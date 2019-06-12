<?php

class Formulaire extends ActiveRecord {

  const STATUS_REMOVED = -10;
  const STATUS_ACTIF = 0;

  public static $statuses = array(
    self::STATUS_REMOVED => 'supprimé',
    self::STATUS_ACTIF => 'rempli',
  );


  protected function onBeforeCommit(&$attrs) {
    if ($this->isLoaded()) {
      $formulairetype = Formulairetype::getInstance($this->formulairetype_id);
      $declaration = Declaration::getInstance($this->declaration_id);
    }
    else {
      $formulairetype = Formulairetype::getInstance($attrs['formulairetype_id']);
      $declaration = Declaration::getInstance($attrs['declaration_id']);
    }
    $dectype = $declaration->getDectype();
    if ($formulairetype->document_code == Formulairetype::DOCUMENT_CODE_IDENTIF
      && $formulairetype->code != 'f_' && $formulairetype->code != 'F-IDENTIF'
    ) {
      $adherent = $declaration->getAdherent();
      if ($dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
        $attrs['data'] = Formulaire::calculate_reference_paiment($attrs['data'], $declaration, $adherent);
      }
    }
  }

  protected function onAfterUpdate(&$attrs) {
    if (!isset($this->_changes['fields_values'])) return;
    $declaration = $this->getDeclaration();
    $dectype = $declaration->getDectype();
    $ftype = $this->getFormulairetype();
    if ($ftype->document_code == Formulairetype::DOCUMENT_CODE_IDENTIF
      && $ftype->code != 'f_' && $ftype->code != 'F-IDENTIF'
      && $ftype->code != 'r_' && $ftype->code != 'R-IDENTIF'
      && $ftype->code != 'a_' && $ftype->code != 'A-IDENTIFIFU'
      && $ftype->code != 'a_' && $ftype->code != 'A-IDENTIFHON'
    ) {
      $adherent = $declaration->getAdherent();
      if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
        $fields_values = $this->fields_values;
        $imprime = new Imprime();
        $imprime->setFormulaire($this, $dectype->getFtypeMillesime($ftype));
        $data = array('KD' => $imprime->getField('KD')->asTradeXpressExportHash(0),
                      'KF' => $imprime->getField('KF')->asTradeXpressExportHash(0),
                      'HA' => $imprime->getField('HA')->asTradeXpressExportHash(0),
                      'HB' => $imprime->getField('HB')->asTradeXpressExportHash(0),
                      'HC' => $imprime->getField('HC')->asTradeXpressExportHash(0),
        );

        $result = Formulaire::calculate_reference_paiment_is_ts_cvae($data,
                                                                     $declaration,
                                                                     $adherent);
        $fields_values['KA'] = array($result['KA']);
        $fields_values['KB'] = array($result['KB']);
        $fields_values['KC'] = array($result['KC']);
        $this->setAttribute('fields_values', $fields_values);

      }
    }
  }


  /* ----- STATIC ----- */
  public static $form = array();
  public static $errors = array();
  public static $tests = array();
  public static $cast;

  public static function initData($formulaire_code) {
    if (self::$form[$formulaire_code]) {
      return self::$form[$formulaire_code];
    }
    $form = array();
    include LIB_PATH . '/ntd/data/form.' . $formulaire_code . '.data.inc';
    self::$form = array_merge(self::$form, $form);
    return self::$form[$formulaire_code];
  }

  public static function getDataFields($formulaire_code) {
    $formulaire_data = self::initData($formulaire_code);
    return array_keys($formulaire_data);
  }

  public static function caster($form_code, $data) {
    $form = self::$form[$form_code];
    foreach ($form as $key => $opts) {
      //if ($opts['type'] == 'checkbox') {
      $data[$key] = (int) $data[$key];
      //}
    }
    foreach ($data as $values) {
      return;
    }
    return $data;
  }

  public static function validForm($form_code, $data, $params) {
    $form = self::$form[$form_code];
    $params['form_code'] = $form_code;
    $millesime = $params['declaration_formulairetype']->getMillesime();

    foreach ($data as $key => $value) {

      list ($field, $index) = explode('/', $key);
      $params['current_field'] = $field;

      if ($form[$field]['required'] && empty($value) && strlen($value) == 0) {
        if ($form[$field]['type'] == 'date-ssaamm') {
          self::$errors[$form_code . '_' . $key . '-controls-container'] = array('status' => 'required');
        }
        else {
          self::$errors[$form_code . '_' . $key] = array('status' => 'required');
        }
      }

      // check field format
      switch ($form[$field]['type']) {
        case 'date-mmjj':
          ValidMain::format_jjmm($form_code, array(), $data, $params);
          break;
        case 'date-ssaammjj':
          ValidMain::format_jjmmaa($form_code, array(), $data, $params);
          break;
        case 'date-ssaamm':
          ValidMain::format_mmaa($form_code, array(), $data, $params);
          break;
        case 'number':
          ValidMain::format_integer($form_code, array(), $data, $params);
          break;
        case 'email':
          ValidMain::check_email($form_code, array(), $data, $params);
          break;
      }

      foreach ((array) $form[$field]['operations'] as $operation) {

        if ($operation['function']) {

          $class_name = 'Formulaire' . $form_code;
          if (!class_exists($class_name, false)) {
            $class_name = 'Formulairecalcul';
          }
          if (method_exists($class_name, $operation['function'])) {
            call_user_func_array($class_name . '::' . $operation['function'], array($operation['args'], $data, $params));
          }
        }

        if (is_array($operation['opt']['results']) && count($operation['opt']['results']) > 0
          && strpos($operation['opt']['results'][0], '_') > 0 && !array_key_exists($operation['opt']['results'][0], $data)
        ) {
          continue;
        }

        if ($operation['func'] && strpos('data-', $operation['func']) != 0) continue;
        $fonction_name = str_replace(array('data-', '-'), array('', '_'), $operation['func']);
        foreach (ValidMain::$ValidClasses as $values) {
          if (method_exists($values, $fonction_name)) {
            call_user_func_array($values . '::' . $fonction_name, array($form_code, (array) $operation['opt'], $data, $params));
            break;
          }
        }
        if ($operation['assert']) {
          DeclarationAsserter::assert($operation['assert'], $params['declaration_data'], $millesime);
        }
      }
    }

    if (DeclarationAsserter::exists($form_code, $millesime)) {
      DeclarationAsserter::assert($form_code, $params['declaration_data'], $millesime);
    }
    //S('log')->debug(self::$errors);
    return self::$errors;
  }


  public static function getHTMLField($form_code, $args = array()) {
    $field_name = $args['field_name'];
    $field_code = $args['field_code'] ? $args['field_code'] : $args['field_name'];
    $elt_conf = self::$form[$form_code][$field_code];

    $elt = array();
    $elt['name'] = $elt_conf['no_recording'] ? '' : $form_code . '[' . $field_name . ']';

    if (isset($args['index'])) {
        $elt['name'] .= '[' . $args['index'] . ']';
    } elseif (!$elt_conf['no_recording']) {
        $elt['name'] .= '[]';
    }

    $elt['id'] = $form_code . '_' . $field_name;
    $elt['class'] = array_merge((array)$args['class'], array('field', 'field-type-' . $elt_conf['type'], $form_code.'_'.$field_name));
    $elt['value'] = $args['value'];
    //$elt['placeholder'] = isset($elt_conf['placeholder']) ? $elt_conf['placeholder'] : strtoupper($field_name); // MANTIS 12554
    $elt['onchange'] = array('NTD.Control.checkValue(this);');
    $elt['onmouseout'] = 'NTD.Control.hideError(this);';
    $elt['onmouseover'] = 'NTD.Control.displayError(this);';

    if (isset($args['data-value'])) {
      $elt['data-value'] = $args['data-value'];
      $elt['value'] = $args['data-value'];
    }

    // input type
    if ($elt_conf['type'] == 'checkbox') {
      $elt['type'] = 'checkbox';
      $elt['value'] = 1;
      if (($args['value']) == '1') $elt['checked'] = 'checked';
      $elt['class'][] = 'checked-true';
    }
    elseif ($elt_conf['type'] == 'radio') {
      $elt['type'] = 'radio';
    }
    elseif ($elt_conf['type'] == 'pourcentage') {
      $elt['type'] = 'text';
      $elt['class'][] = 'pourcentage';
    }
    elseif ($elt_conf['type'] == 'alphabetic') {
      $elt['type'] = 'text';
      $elt['class'][] = 'alpha';
    }
    elseif ($elt_conf['type'] == 'date-ssaammjj') {
      if (strpos($elt['value'], '/') === false) {
        $elt['value'] = ValidMain::format_back_jjmmaa($elt['value']);
      }
      $elt['type'] = 'text';
      $elt['onclick'] = 'NTD.Control.hideError(this); new Kwo.Datepicker($(this));';
      $elt['class'][] = 'input-date';
    }
    elseif ($elt_conf['type'] == 'date-ssaamm') {
      $elt['type'] = 'hidden';
      $elt['class'][] = 'input-date';
      $value_month = substr($elt['value'], 4, 2);
      $value_year = substr($elt['value'], 0, 4);
      $elt['value'] = $value_month && $value_year ? $value_month . '/' . $value_year : '';
      $current_year = date('Y');
      $years = range($current_year - ($elt_conf['range'] ? (int)$elt_conf['range'] : 10), $current_year + 1, 1);
      $years = array_combine($years, $years);
      $html_controls = Template::render('ntd:_formulaire.elt.date.ssaamm', array('elt' => $elt, 'years' => $years, 'value_month' => $value_month, 'value_year' => $value_year));
    }
    elseif ($elt_conf['type'] == 'date-ssaa') {
      $elt['type'] = 'select';
      $elt['class'][] = 'input-date';
      $current_year = date('Y');
      $years = range($current_year - ($elt_conf['range'] ? (int)$elt_conf['range'] : 10), $current_year + 1, 1);
      $years = array_combine($years, $years);
      $elt['options'] = array('' => '-') + $years;
    }
    elseif ($elt_conf['type'] == 'date-ssmmjj') {
      $elt['type'] = 'hidden';
      $elt['class'][] = 'input-date';
      $value_day = substr($elt['value'], 2, 2);
      $value_month= substr($elt['value'], 0, 2);
      $elt['value'] = $value_day && $value_month ? $value_day . '/' .  $value_month : '';

      // render two selects (day and month)
      $html_controls = Template::render('ntd:_formulaire.elt.date.ssmmjj', array('elt' => $elt, 'value_month' => $value_month, 'value_day' => $value_day));
    }
    elseif ($elt_conf['type'] == 'data-select') {
      $elt['type'] = 'select';
      $elt['options'] = array_key_exists($elt_conf['options'], FormulaireData::$data) ? FormulaireData::$data[$elt_conf['options']] : array();
    }
    elseif ($elt_conf['type'] == 'counter-select') {
      $elt['type'] = 'select';
      $elt['options'][''] = '----';
      for ($i = 1; $i < $elt_conf['max']; $i++) {
        $value = str_pad($i, (strlen($elt_conf['max']) - 1), "0", STR_PAD_LEFT);
        $elt['options'][$value] = $value;
      }
    }
    elseif ($elt_conf['type'] == 'date-mm') {
      $elt['type'] = 'select';
      $elt['class'][] = 'input-date';
      $elt['options'] = array('' => '-') + I18n::$months[S('req')->getLocale()]['long'];
    }
    elseif ($elt_conf['type'] == 'comments') {
      $elt['type'] = 'textarea';
      $elt['rows'] = $elt_conf['rows'] ? $elt_conf['rows'] : 10;
      $elt['class'][] = 'textarea-split-comments';
      $elt['onchange'][] = 'NTD.Control.splitComments(this);';
      $elt['value'] = str_replace("^^^", "\n", $elt['value']);
    }
    elseif ($elt_conf['type'] == 'comments-part') {
      $elt['type'] = 'hidden';
      $elt['value'] = str_replace("^^^", "\n", $elt['value']);
    }
    elseif ($elt_conf['type'] == 'number') {
    }
    elseif ($elt_conf['type'] == 'hidden') {
      $elt['type'] = 'hidden';
    }
    elseif ($elt_conf['type'] == 'textarea') {
      $elt['type'] = 'textarea';
    }
    elseif ($elt_conf['type'] == 'select') {
      $elt['type'] = 'select';
      $elt['options'] = $elt_conf['options'];
    }
    else {
      $elt['type'] = 'text';
    }

    if ($args['style']) {
      $elt['style'] = $args['style'];
    }

    // others options
    if ($elt_conf['readonly'] === true) {
      $elt['readonly'] = 'readonly';
      $elt['class'][] = 'result';
    }

    if ($elt_conf['display'] == 'none') {
      $elt['class'][] = 'hidden';
    }
    if ($elt_conf['value']) {
      $elt['value'] = $elt_conf['value'];
    }

    if ($elt_conf['length']) {
      $elt['maxlength'] = $elt_conf['length'];
      $elt['value'] = substr($elt['value'], 0, $elt_conf['length']);
    }

    $elt_conf['operations'] = (array) $elt_conf['operations'];

    foreach ($elt_conf['operations'] as $num => $operation) {
      if ($operation['assert']) {
        $elt['onchange'][] = 'asserts.run(\'' . $operation['assert'] . '\');';
      }
      if ($operation['function']) {

        $function_name = FormulaireFunctions::$funcs[$operation['function']];
        if (empty($function_name)) {
          $function_name = 'Formulaire.' . $form_code . '.' . $operation['function'];
          $class_name = 'Formulaire' . $form_code;
          if (!file_exists('lib/ntd/class/' . $class_name . '.class.inc') || !method_exists($class_name, $operation['function'])) {
            $function_name = 'Formulaire.calcul.' . $operation['function'];
          }
          //continue;
        }

        $args = (is_array($operation['args'])) ? str_replace('"', "'", json_encode($operation['args'])) : '{}';
        $params = str_replace('"', "'", json_encode(array('formulaire_code' => $form_code)));
        $elt['onchange'][] = $function_name . '(this, ' . $args . ', ' . $params . ');';


      }
      else {
        $function_name = $operation['func'];

        $opt = $operation['opt'];
        if ($opt['percent']) {
          $elt[$function_name . '-percent-' . $num] = $opt['percent'];
        }

        if ($opt['items']) {
          $ids = array();
          foreach ($opt['items'] as $id) {
            $ids[] = strpos($id, '_') > 0 ? $id : $form_code . '_' . $id;
          }
          $elt[$function_name . '-items' . $num] = implode(',', $ids);
          if ($function_name == 'data-compare') {
            $elt[$function_name . '-type'] = $opt['type'];
          }
          if (!empty(FormulaireFunctions::$funcs[$function_name])) {
            $elt['onchange'][] = FormulaireFunctions::$funcs[$function_name] . '(this, ' . $num . ');';
          }
        }
        else {
          $ids = array();
          foreach ($opt['operands'] as $id) {
            $ids[] = strpos($id, '_') > 0 ? $id : $form_code . '_' . $id;
          }
          $elt[$function_name . '-operands' . $num] = implode(',', $ids);

          $ids = array();
          foreach ($opt['left'] as $id) {
            $ids[] = strpos($id, '_') > 0 ? $id : $form_code . '_' . $id;
          }
          if (sizeof($ids) > 0) $elt[$function_name . '-lefts' . $num] = implode(',', $ids);

          $ids = array();
          foreach ($opt['right'] as $id) {
            $ids[] = strpos($id, '_') > 0 ? $id : $form_code . '_' . $id;
          }
          if (sizeof($ids) > 0) $elt[$function_name . '-rights' . $num] = implode(',', $ids);


          if ($opt['value']) {
            $id = $form_code . '_' . $opt['value'];
            $elt[$function_name . '-value' . $num] = $id;
          }

          $elt[$function_name . '-args' . $num] = implode(',', (array) $opt['args']);
          $ids = array();
          foreach ($opt['results'] as $id) {
            $ids[] = strpos($id, '_') > 0 ? $id : $form_code . '_' . $id;
          }
          $elt[$function_name . '-results' . $num] = implode(',', $ids);
          if (!empty(FormulaireFunctions::$funcs[$function_name])) {
            $elt['onchange'][] = FormulaireFunctions::$funcs[$function_name] . '(this, ' . $num . ');';
          }
        }
      }

    }


    $elt['onchange'] = implode(' ', $elt['onchange']);
    $elt['class'] = implode(' ', $elt['class']);


    if (substr($form_code, 0, 9) == 'f_identif') {
      if (in_array($args['field_name'], array('BA', 'BB', 'BC'))) {
        $hidden = '<input type="hidden" value="' . $elt['value'] . '" name="' . $elt['name'] . '" />';
        $elt['disabled'] = true;
      }
    }

    foreach ($elt as $name => $value) {
      if (empty($elt['type'])) {
        $attributes['type'] = 'type="text"';
      }
      if ($name != 'options' && ($elt['type'] != 'select' || $name != 'value')) $attributes[$name] = "$name=\"$value\"";
    }

    $attributes = implode(' ', $attributes);

    if ($elt['type'] == 'textarea') {
      $elt_html = '<textarea ' . $attributes . '>' . $elt['value'] . '</textarea>';
    }
    elseif ($elt['type'] == 'select') {
      $elt_html = '<select ' . $attributes . '>';
      foreach ($elt['options'] as $key => $value) {
        $elt_html .= '<option value="' . $key . '" ' . ($elt['value'] == $key ? ' selected="selected"' : '') . '>' . c($value) . '</option>';
      }
      $elt_html .= '</select>';
    }
    elseif ($elt['type'] == 'radio') {
      $elt_html = '<div class="input-container" id="' . $elt['id'] . '" onmouseover="' . $elt['onmouseover'] . '" onmouseout="' . $elt['onmouseout'] . '">' .
        Elt::radio(array('options' => $elt_conf['options'],
                         'value' => $elt['value'],
                         'name' => $elt['name'],
                         'events' => array('change' => $elt['onchange']))) . '</div>';
    }
    else {
      $elt_html = '<input ' . $attributes . ' />';
      if (!isset($args['removeClear']) || !$args['removeClear']) {
        $elt_html .= '<div class="clear"></div>';
      }
    }

    $helper = '<span class="field--code" style="display: ' . ((P('app.domain') == 'dev.ntd-dev.li.kernix.net') ? 'block' : 'none') . ';">' . $field_name . '</span>';

    if (array_key_exists('annotate', $args) && !empty($args['annotate'])) {
      $elt_html = '<div style="text-align: center; font-size:10px;">'.$args['annotate'].'</div>' . $elt_html;
    }

    // Render HTML
    $html = $helper;
    $html .= $hidden . $elt_html . $html_controls . Tooltip::getTooltipError();


    return $html;
  }

  public static function asValidationData($form_code, $attributes = array()) {
    $data = (array) $attributes[$form_code];
    foreach ($attributes as $key => $value) {
      if ($key == $form_code || !is_array($value)) continue;
      foreach ($value as $_key => $_value) {
        $data[$key . '_' . $_key] = $_value;
      }
    }
    return $data;
  }

  public static function asFormulairePreFilledHash(Formulairetype $formulaire_type, Adherent $adherent) {
    $hash = array();

    $formulaire_code = $formulaire_type->name;
    if ($formulaire_code == 'p_identif_20151020') {
      $hash['AA1'] = substr($adherent->siret, 0, 9);
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->function;
      $hash['AA5'] = $adherent->forme_juridique;
      $hash['AA6'] = $adherent->address;
      $hash['AA7'] = $adherent->zipbox;
      $hash['AA8'] = $adherent->city;
      $hash['AA9'] = $adherent->zipcode;
      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);
    }
    elseif (substr($formulaire_code, 0, 9) == 'p_identif') {
      $hash['AA1'] = $adherent->siret;
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->function;
      $hash['AA5'] = $adherent->forme_juridique;
      $hash['AA6'] = $adherent->address;
      $hash['AA7'] = $adherent->zipbox;
      $hash['AA8'] = $adherent->city;
      $hash['AA9'] = $adherent->zipcode;
      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);
    }
    elseif ($formulaire_code == 't_identif_20160101') {
      $hash['OGA'] = '';
      $hash['IDOGA'] = '';
      $hash['AA1'] = substr($adherent->siret, 0, 9);
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->forme_juridique;

      $hash['AA5'] = $adherent->address;
      $hash['AA6'] = $adherent->zipbox;
      $hash['AA7'] = $adherent->city;
      $hash['AA8'] = $adherent->zipcode;
      $hash['AA9'] = Country::getInstance($adherent->country_id)->code;

      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);
    }
    elseif ($formulaire_code == 't_identif_20170101') {
      $hash['OGA'] = '';
      $hash['IDOGA'] = '';
      $hash['AA1'] = substr($adherent->siret, 0, 9);
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->forme_juridique;

      $hash['AA5'] = $adherent->address;
      $hash['AA6'] = $adherent->zipbox;
      $hash['AA7'] = $adherent->city;
      $hash['AA8'] = $adherent->zipcode;
      $hash['AA9'] = Country::getInstance($adherent->country_id)->code;

      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);
    }
    elseif ($formulaire_code == 't_identif_20151020') {
      $hash['FRP'] = $adherent->frp;
      $hash['OGA'] = '';
      $hash['IDOGA'] = '';
      $hash['AA1'] = $adherent->siret;
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->forme_juridique;

      $hash['AA5'] = $adherent->address;
      $hash['AA6'] = $adherent->zipbox;
      $hash['AA7'] = $adherent->city;
      $hash['AA8'] = $adherent->zipcode;
      $hash['AA9'] = Country::getInstance($adherent->country_id)->code;

      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);
    }
    elseif ($formulaire_code == 't_identif') {
      $hash['FRP'] = $adherent->frp;
      $hash['OGA'] = '';
      $hash['IDOGA'] = '';
      $hash['AA1'] = $adherent->siret;
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->forme_juridique;

      $hash['AA5'] = $adherent->address;
      $hash['AA6'] = $adherent->zipbox;
      $hash['AA7'] = $adherent->city;
      $hash['AA8'] = $adherent->zipcode;
      $hash['AA9'] = Country::getInstance($adherent->country_id)->code;

      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);

      $hash['EA'] = 1;
    }
    elseif ($formulaire_code == 'f_identif' || $formulaire_code == 'f_identif_20140320') {
      $hash['AA'] = $adherent->siret;

      $hash['AA1'] = $adherent->identity();
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->address;
      $hash['AA6'] = $adherent->city;
      $hash['AA7'] = $adherent->zipcode;
      $hash['AA8'] = Country::getInstance($adherent->country_id)->code;
      $hash['AA13'] = $adherent->email;

      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);

      $hash['BA'] = 'FL';
      $hash['BB'] = 'CV';
    }
    elseif (substr($formulaire_code, 0, 9) == 'f_identif') {
      $hash['AA'] = $adherent->siren;

      $hash['AA1'] = $adherent->identity();
      $hash['AA2'] = $adherent->company;
      $hash['AA3'] = $adherent->company_bis;
      $hash['AA4'] = $adherent->address;
      $hash['AA6'] = $adherent->city;
      $hash['AA7'] = $adherent->zipcode;
      $hash['AA8'] = Country::getInstance($adherent->country_id)->code;
      $hash['AA13'] = $adherent->email;

      $date_now = time();
      $previous_month = strtotime('previous month', $date_now);
      $previous_month_hash = Date::asHash($previous_month);

      $start_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-01');
      $end_month = strtotime($previous_month_hash['year'] . '-' . $previous_month_hash['month'] . '-' . date('t', $previous_month));
      $hash['CA'] = date("Ymd", $start_month);
      $hash['CB'] = date("Ymd", $end_month);

      $hash['BA'] = 'FL';
      $hash['BB'] = 'CV';
      $hash['BF'] = 'NOR';
    }
    elseif (strpos($formulaire_code, 'tva3517ddr') !== false) {
      $hash['AH'] = 1;
      $hash['AA'] = 0;
      $hash['AB'] = 0;
      $hash['AC'] = 0;
      $hash['AD'] = 0;
      $hash['AE'] = 0;
    }
    elseif (strpos($formulaire_code, 'tva3519') !== false) {
      $hash['DD'] = 1;
      $hash['FK'] = 1;
      $hash['DK'] = 1;
      $hash['DC8'] = 'FR';
    }
    elseif ($formulaire_code == 'tva3310ter_20150101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DG'] = 0;
      $hash['DH'] = 0;
      $hash['DJ'] = 0;
      $hash['DK'] = 0;
      $hash['DL'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['EE'] = 0;
      $hash['EF'] = 0;
      $hash['EG'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EK'] = 0;
      $hash['EL'] = 0;

      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GD'] = 0;
      $hash['GE'] = 0;
      $hash['GF'] = 0;
      $hash['GG'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GL'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['HD'] = 0;
      $hash['HE'] = 0;
      $hash['HF'] = 0;
      $hash['HG'] = 0;
      $hash['HH'] = 0;

      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KC'] = 0;
      $hash['KD'] = 0;
      $hash['KE'] = 0;
      $hash['KF'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KK'] = 0;
      $hash['KL'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LE'] = 0;
      $hash['LF'] = 0;
      $hash['LG'] = 0;
      $hash['LH'] = 0;
      $hash['LH'] = 0;
      $hash['LJ'] = 0;
      $hash['LK'] = 0;
      $hash['LL'] = 0;

      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['ND'] = 0;
      $hash['NE'] = 0;
      $hash['NF'] = 0;
      $hash['NG'] = 0;
      $hash['NH'] = 0;
      $hash['NJ'] = 0;
      $hash['NK'] = 0;
      $hash['NL'] = 0;


    }
    elseif ($formulaire_code == 'tva3310ca3_20150101') {
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['CC'] = 0;
      $hash['CD'] = 0;
      $hash['CE'] = 0;
      $hash['CF'] = 0;
      $hash['CG'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DG'] = 0;

      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;

      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GG'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GM'] = 0;
      $hash['GN'] = 0;
      $hash['GP'] = 0;
      $hash['GR'] = 0;

      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['HD'] = 0;
      $hash['HG'] = 0;
      $hash['HH'] = 0;
      $hash['HJ'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KE'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KR'] = 0;
      $hash['KS'] = 0;
      $hash['KT'] = 0;
      $hash['KU'] = 0;
      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;
    }
    elseif ($formulaire_code == 'tva3517sca12_20150101') {

      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['EF'] = 0;
      $hash['EG'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EL'] = 0;
      $hash['EM'] = 0;
      $hash['EN'] = 0;
      $hash['EP'] = 0;
      $hash['EQ'] = 0;
      $hash['EU'] = 0;
      $hash['EV'] = 0;
      $hash['EW'] = 0;
      $hash['EX'] = 0;
      $hash['EY'] = 0;
      $hash['EZ'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FF'] = 0;
      $hash['FG'] = 0;
      $hash['FJ'] = 0;
      $hash['FL'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;
      $hash['FU'] = 0;
      $hash['FV'] = 0;
      $hash['FW'] = 0;
      $hash['FY'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GF'] = 0;
      $hash['GH'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['JA'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KD'] = 0;
      $hash['KL'] = 0;
      $hash['KM'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['MA'] = 0;
      $hash['MM'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['QA'] = 0;
      $hash['QD'] = 0;
      $hash['QE'] = 0;
      $hash['QF'] = 0;
      $hash['QH'] = 0;
      $hash['QJ'] = 0;
      $hash['QS'] = 0;
      $hash['RA'] = 0;
      $hash['RB'] = 0;
      $hash['RC'] = 0;
      $hash['RE'] = 0;
      $hash['RF'] = 0;
      $hash['RG'] = 0;
      $hash['RH'] = 0;
      $hash['RK'] = 0;
      $hash['RL'] = 0;
      $hash['RM'] = 0;
      $hash['RN'] = 0;
      $hash['SA'] = 0;
      $hash['SB'] = 0;
      $hash['SC'] = 0;
      $hash['VA'] = 0;
      $hash['VC'] = 0;
      $hash['VE'] = 0;
      $hash['VF'] = 0;
      $hash['VJ'] = 0;
      $hash['VM'] = 0;
      $hash['VN'] = 0;
      $hash['VP'] = 0;
      $hash['VQ'] = 0;
      $hash['VS'] = 0;
      $hash['VT'] = 0;
      $hash['VV'] = 0;
      $hash['VW'] = 0;
      $hash['VX'] = 0;
      $hash['VY'] = 0;
      $hash['VZ'] = 0;
      $hash['WA'] = 0;


    }
    elseif ($formulaire_code == 'tva3517bisca12_20150101') {

      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DH'] = 0;
      $hash['DJ'] = 0;
      $hash['DK'] = 0;
      $hash['DL'] = 0;
      $hash['DM'] = 0;
      $hash['DN'] = 0;
      $hash['DP'] = 0;
      $hash['DQ'] = 0;
      $hash['DR'] = 0;
      $hash['DS'] = 0;
      $hash['DU'] = 0;
      $hash['DV'] = 0;
      $hash['DY'] = 0;
      $hash['DZ'] = 0;
      $hash['EE'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EK'] = 0;
      $hash['EL'] = 0;
      $hash['EM'] = 0;
      $hash['EN'] = 0;
      $hash['EP'] = 0;
      $hash['EQ'] = 0;
      $hash['ER'] = 0;
      $hash['ES'] = 0;
      $hash['EU'] = 0;
      $hash['EV'] = 0;
      $hash['EZ'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FF'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['HA'] = 0;
      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KC'] = 0;
      $hash['KD'] = 0;
      $hash['KF'] = 0;
      $hash['KH'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LF'] = 0;
      $hash['LH'] = 0;
      $hash['LK'] = 0;
      $hash['LM'] = 0;
      $hash['MA'] = 0;
      $hash['MB'] = 0;
      $hash['MC'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['RC'] = 0;
      $hash['RD'] = 0;
      $hash['RF'] = 0;
      $hash['RG'] = 0;
      $hash['RH'] = 0;
      $hash['RJ'] = 0;
      $hash['RK'] = 0;
      $hash['RL'] = 0;
    }
    elseif ($formulaire_code == 'is2572_2015') {
      $hash['PN'] = 0;
      $hash['PT'] = 0;
      $hash['PV'] = 0;
      $hash['AD'] = 0;
      $hash['PR'] = 0;
      $hash['PQ'] = 0;
      $hash['PU'] = 0;
      $hash['PW'] = 0;
      $hash['BD'] = 0;
      $hash['PS'] = 0;
      $hash['CA'] = 0;
      $hash['DA'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['TA'] = 0;
      $hash['TB'] = 0;
      $hash['GC'] = 0;
      $hash['GD'] = 0;
      $hash['GE'] = 0;
      $hash['PM'] = 0;
      $hash['IA'] = 0;
      $hash['JA'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KC'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LE'] = 0;
      $hash['LF'] = 0;
      $hash['MA'] = 0;
      $hash['MB'] = 0;
      $hash['MC'] = 0;
      $hash['MD'] = 0;
      $hash['ME'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['ND'] = 0;
      $hash['NE'] = 0;
      $hash['NF'] = 0;
      $hash['NG'] = 0;
      $hash['NH'] = 0;
      $hash['NJ'] = 0;
      $hash['NK'] = 0;
      $hash['NL'] = 0;
      $hash['NM'] = 0;
      $hash['NN'] = 0;
      $hash['NO'] = 0;
      $hash['OA'] = 0;
      $hash['OB'] = 0;
      $hash['OC'] = 0;
      $hash['OD'] = 0;
      $hash['RE'] = 0;
      $hash['RF'] = 0;
      $hash['RA'] = 0;
      $hash['RB'] = 0;
      $hash['RC'] = 0;
      $hash['RG'] = 0;
      $hash['RH'] = 0;
      $hash['RJ'] = 0;
      $hash['RK'] = 0;
      $hash['RL'] = 0;
      $hash['RM'] = 0;
      $hash['RN'] = 0;
      $hash['RP'] = 0;
      $hash['RS'] = 0;
      $hash['RT'] = 0;
      $hash['RU'] = 0;
      $hash['RV'] = 0;
      $hash['RX'] = 0;
      $hash['RY'] = 0;
      $hash['RW'] = 0;
      $hash['RZ'] = 0;
      $hash['PA'] = 0;
      $hash['PB'] = 0;
      $hash['PC'] = 0;
      $hash['PD'] = 0;
      $hash['PH'] = 0;
      $hash['PL'] = 0;
    }
    elseif ($formulaire_code == 'is2572_2018') {
        $hash['QA'] = 0;
        $hash['QB'] = 0;
    }
    elseif ($formulaire_code == 'is2571_2015') {
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FE'] = 0;
      $hash['FF'] = 0;
      $hash['FG'] = 0;
      $hash['CA'] = 0;
      $hash['CF'] = 0;
      $hash['CC'] = 0;
      $hash['CD'] = 0;
      $hash['CE'] = 0;
      $hash['CG'] = 0;
      $hash['CH'] = 0;
      $hash['FN'] = 0;
    }
    elseif ($formulaire_code == 'cvae1329ac_20150101' || $formulaire_code == 'cvae1329ac_20160101'
            || $formulaire_code == 'cvae1329ac_20170101' || $formulaire_code == 'cvae1329ac_20180101'
            || $formulaire_code == 'cvae1329ac_20190101') {
      $hash['AC'] = 0;
      $hash['BA'] = 0;
      $hash['BB'] = 0;
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['GB'] = 0;
      $hash['HA'] = 0;
      $hash['KA'] = 0;
    }
    elseif ($formulaire_code == 'cvae1329def_20150101' || $formulaire_code == 'cvae1329def_20160101' || $formulaire_code == 'cvae1329def_20170101'
            || $formulaire_code == 'cvae1329def_20190101') {
      $hash['AC'] = 0;
      $hash['BA'] = 0;
      $hash['BB'] = 0;
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['JA'] = 0;
    }

    // Millesime 2016
    elseif ($formulaire_code == 'tva3310ca3_20160101') {
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['CC'] = 0;
      $hash['CD'] = 0;
      $hash['CE'] = 0;
      $hash['CF'] = 0;
      $hash['CG'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DG'] = 0;

      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;

      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GG'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GM'] = 0;
      $hash['GN'] = 0;
      $hash['GP'] = 0;
      $hash['GR'] = 0;

      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['HD'] = 0;
      $hash['HG'] = 0;
      $hash['HH'] = 0;
      $hash['HJ'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KE'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KR'] = 0;
      $hash['KS'] = 0;
      $hash['KT'] = 0;
      $hash['KU'] = 0;
      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;
    }
    elseif ($formulaire_code == 'tva3310ter_20160101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DG'] = 0;
      $hash['DH'] = 0;
      $hash['DJ'] = 0;
      $hash['DK'] = 0;
      $hash['DL'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['EE'] = 0;
      $hash['EF'] = 0;
      $hash['EG'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EK'] = 0;
      $hash['EL'] = 0;

      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GD'] = 0;
      $hash['GE'] = 0;
      $hash['GF'] = 0;
      $hash['GG'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GL'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['HD'] = 0;
      $hash['HE'] = 0;
      $hash['HF'] = 0;
      $hash['HG'] = 0;
      $hash['HH'] = 0;

      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KC'] = 0;
      $hash['KD'] = 0;
      $hash['KE'] = 0;
      $hash['KF'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KK'] = 0;
      $hash['KL'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LE'] = 0;
      $hash['LF'] = 0;
      $hash['LG'] = 0;
      $hash['LH'] = 0;
      $hash['LH'] = 0;
      $hash['LJ'] = 0;
      $hash['LK'] = 0;
      $hash['LL'] = 0;

      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['ND'] = 0;
      $hash['NE'] = 0;
      $hash['NF'] = 0;
      $hash['NG'] = 0;
      $hash['NH'] = 0;
      $hash['NJ'] = 0;
      $hash['NK'] = 0;
      $hash['NL'] = 0;
    }
    elseif ($formulaire_code == 'tva3515sd_20160101') {
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['BE'] = 0;
      $hash['BF'] = 0;
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BD'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
    }
    elseif ($formulaire_code == 'tva3517bisca12_20160101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DH'] = 0;
      $hash['DJ'] = 0;
      $hash['DK'] = 0;
      $hash['DL'] = 0;
      $hash['DM'] = 0;
      $hash['DN'] = 0;
      $hash['DP'] = 0;
      $hash['DQ'] = 0;
      $hash['DR'] = 0;
      $hash['DS'] = 0;
      $hash['DU'] = 0;
      $hash['DV'] = 0;
      $hash['DY'] = 0;
      $hash['DZ'] = 0;
      $hash['EE'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EK'] = 0;
      $hash['EL'] = 0;
      $hash['EM'] = 0;
      $hash['EN'] = 0;
      $hash['EP'] = 0;
      $hash['EQ'] = 0;
      $hash['ER'] = 0;
      $hash['ES'] = 0;
      $hash['EU'] = 0;
      $hash['EV'] = 0;
      $hash['EZ'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FF'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['HA'] = 0;
      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KC'] = 0;
      $hash['KD'] = 0;
      $hash['KF'] = 0;
      $hash['KH'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LF'] = 0;
      $hash['LH'] = 0;
      $hash['LK'] = 0;
      $hash['LM'] = 0;
      $hash['MA'] = 0;
      $hash['MB'] = 0;
      $hash['MC'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['RC'] = 0;
      $hash['RD'] = 0;
      $hash['RG'] = 0;
      $hash['RH'] = 0;
      $hash['RJ'] = 0;
      $hash['RK'] = 0;
      $hash['RM'] = 0;
      $hash['RN'] = 0;
      $hash['RP'] = 0;
      $hash['RQ'] = 0;
      $hash['RR'] = 0;
      $hash['RS'] = 0;
      $hash['RT'] = 0;
      $hash['RU'] = 0;
      $hash['RV'] = 0;
      $hash['RW'] = 0;
      $hash['RX'] = 0;
      $hash['RY'] = 0;
      $hash['RZ'] = 0;
      $hash['SA'] = 0;
      $hash['SB'] = 0;
      $hash['SC'] = 0;
      $hash['SD'] = 0;
    }
    elseif ($formulaire_code == 'tva3517sca12_20160101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['EF'] = 0;
      $hash['EG'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EL'] = 0;
      $hash['EM'] = 0;
      $hash['EN'] = 0;
      $hash['EP'] = 0;
      $hash['EQ'] = 0;
      $hash['EU'] = 0;
      $hash['EV'] = 0;
      $hash['EW'] = 0;
      $hash['EX'] = 0;
      $hash['EY'] = 0;
      $hash['EZ'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FF'] = 0;
      $hash['FG'] = 0;
      $hash['FJ'] = 0;
      $hash['FL'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;
      $hash['FU'] = 0;
      $hash['FV'] = 0;
      $hash['FW'] = 0;
      $hash['FY'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GF'] = 0;
      $hash['GH'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['JA'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KD'] = 0;
      $hash['KL'] = 0;
      $hash['KM'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['MA'] = 0;
      $hash['MM'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['QA'] = 0;
      $hash['QD'] = 0;
      $hash['QE'] = 0;
      $hash['QF'] = 0;
      $hash['QH'] = 0;
      $hash['QJ'] = 0;
      $hash['QS'] = 0;
      $hash['RA'] = 0;
      $hash['RB'] = 0;
      $hash['RC'] = 0;
      $hash['RE'] = 0;
      $hash['RF'] = 0;
      $hash['RG'] = 0;
      $hash['RH'] = 0;
      $hash['RL'] = 0;
      $hash['RN'] = 0;
      $hash['SA'] = 0;
      $hash['SB'] = 0;
      $hash['SC'] = 0;
      $hash['VA'] = 0;
      $hash['VC'] = 0;
      $hash['VE'] = 0;
      $hash['VF'] = 0;
      $hash['VJ'] = 0;
      $hash['VM'] = 0;
      $hash['VN'] = 0;
      $hash['VP'] = 0;
      $hash['VS'] = 0;
      $hash['VT'] = 0;
      $hash['VW'] = 0;
      $hash['VX'] = 0;
      $hash['VY'] = 0;
      $hash['VZ'] = 0;
      $hash['WB'] = 0;
      $hash['WC'] = 0;
      $hash['WD'] = 0;
      $hash['WE'] = 0;
      $hash['WF'] = 0;
      $hash['WG'] = 0;
      $hash['WH'] = 0;
      $hash['WJ'] = 0;
      $hash['WK'] = 0;
      $hash['WL'] = 0;
      $hash['WM'] = 0;
      $hash['WN'] = 0;
      $hash['WP'] = 0;
      $hash['WQ'] = 0;
      $hash['WR'] = 0;
      $hash['WS'] = 0;
      $hash['WT'] = 0;
      $hash['WU'] = 0;
      $hash['WV'] = 0;
      $hash['WX'] = 0;
      $hash['WY'] = 0;
      $hash['WZ'] = 0;
      $hash['ZA'] = 0;
      $hash['ZB'] = 0;
    }
    elseif ($formulaire_code == 'tva3525bis_20160101') {
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BD'] = 0;
    }

    // Millesime 2017
    elseif ($formulaire_code == 'tva3310ca3_20170101') {
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['CC'] = 0;
      $hash['CD'] = 0;
      $hash['CE'] = 0;
      $hash['CF'] = 0;
      $hash['CG'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DG'] = 0;

      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;

      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GG'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GM'] = 0;
      $hash['GN'] = 0;
      $hash['GP'] = 0;
      $hash['GR'] = 0;

      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['HD'] = 0;
      $hash['HG'] = 0;
      $hash['HH'] = 0;
      $hash['HJ'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KE'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KR'] = 0;
      $hash['KS'] = 0;
      $hash['KT'] = 0;
      $hash['KU'] = 0;
      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;
    }
    elseif ($formulaire_code == 'tva3310ter_20170101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DG'] = 0;
      $hash['DH'] = 0;
      $hash['DJ'] = 0;
      $hash['DK'] = 0;
      $hash['DL'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['EE'] = 0;
      $hash['EF'] = 0;
      $hash['EG'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EK'] = 0;
      $hash['EL'] = 0;

      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GD'] = 0;
      $hash['GE'] = 0;
      $hash['GF'] = 0;
      $hash['GG'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GL'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['HD'] = 0;
      $hash['HE'] = 0;
      $hash['HF'] = 0;
      $hash['HG'] = 0;
      $hash['HH'] = 0;

      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KC'] = 0;
      $hash['KD'] = 0;
      $hash['KE'] = 0;
      $hash['KF'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KK'] = 0;
      $hash['KL'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LE'] = 0;
      $hash['LF'] = 0;
      $hash['LG'] = 0;
      $hash['LH'] = 0;
      $hash['LH'] = 0;
      $hash['LJ'] = 0;
      $hash['LK'] = 0;
      $hash['LL'] = 0;

      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['ND'] = 0;
      $hash['NE'] = 0;
      $hash['NF'] = 0;
      $hash['NG'] = 0;
      $hash['NH'] = 0;
      $hash['NJ'] = 0;
      $hash['NK'] = 0;
      $hash['NL'] = 0;
    }
    elseif ($formulaire_code == 'tva3515sd_20170101') {
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['BE'] = 0;
      $hash['BF'] = 0;
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BD'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
    }
    elseif ($formulaire_code == 'tva3517bisca12_20170101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DH'] = 0;
      $hash['DJ'] = 0;
      $hash['DK'] = 0;
      $hash['DL'] = 0;
      $hash['DM'] = 0;
      $hash['DN'] = 0;
      $hash['DP'] = 0;
      $hash['DQ'] = 0;
      $hash['DR'] = 0;
      $hash['DS'] = 0;
      $hash['DU'] = 0;
      $hash['DV'] = 0;
      $hash['DY'] = 0;
      $hash['DZ'] = 0;
      $hash['EE'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EK'] = 0;
      $hash['EL'] = 0;
      $hash['EM'] = 0;
      $hash['EN'] = 0;
      $hash['EP'] = 0;
      $hash['EQ'] = 0;
      $hash['ER'] = 0;
      $hash['ES'] = 0;
      $hash['EU'] = 0;
      $hash['EV'] = 0;
      $hash['EZ'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FF'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['HA'] = 0;
      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KC'] = 0;
      $hash['KD'] = 0;
      $hash['KF'] = 0;
      $hash['KH'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LF'] = 0;
      $hash['LH'] = 0;
      $hash['LK'] = 0;
      $hash['LM'] = 0;
      $hash['MA'] = 0;
      $hash['MB'] = 0;
      $hash['MC'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['RC'] = 0;
      $hash['RD'] = 0;
      $hash['RG'] = 0;
      $hash['RH'] = 0;
      $hash['RJ'] = 0;
      $hash['RK'] = 0;
      $hash['RM'] = 0;
      $hash['RN'] = 0;
      $hash['RP'] = 0;
      $hash['RQ'] = 0;
      $hash['RR'] = 0;
      $hash['RS'] = 0;
      $hash['RT'] = 0;
      $hash['RU'] = 0;
      $hash['RV'] = 0;
      $hash['RW'] = 0;
      $hash['RX'] = 0;
      $hash['RY'] = 0;
      $hash['RZ'] = 0;
      $hash['SA'] = 0;
      $hash['SB'] = 0;
      $hash['SC'] = 0;
      $hash['SD'] = 0;
      $hash['SE'] = 0;
      $hash['SF'] = 0;
      $hash['SG'] = 0;
    }
    elseif ($formulaire_code == 'tva3517sca12_20170101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['EE'] = 0;
      $hash['EF'] = 0;
      $hash['EG'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EL'] = 0;
      $hash['EM'] = 0;
      $hash['EN'] = 0;
      $hash['EP'] = 0;
      $hash['EQ'] = 0;
      $hash['EU'] = 0;
      $hash['EV'] = 0;
      $hash['EW'] = 0;
      $hash['EX'] = 0;
      $hash['EY'] = 0;
      $hash['EZ'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FF'] = 0;
      $hash['FG'] = 0;
      $hash['FJ'] = 0;
      $hash['FL'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;
      $hash['FU'] = 0;
      $hash['FV'] = 0;
      $hash['FW'] = 0;
      $hash['FY'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GF'] = 0;
      $hash['GH'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['JA'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KD'] = 0;
      $hash['KL'] = 0;
      $hash['KM'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['MA'] = 0;
      $hash['MM'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['QA'] = 0;
      $hash['QD'] = 0;
      $hash['QE'] = 0;
      $hash['QF'] = 0;
      $hash['QH'] = 0;
      $hash['QJ'] = 0;
      $hash['QS'] = 0;
      $hash['RA'] = 0;
      $hash['RB'] = 0;
      $hash['RC'] = 0;
      $hash['RE'] = 0;
      $hash['RF'] = 0;
      $hash['RG'] = 0;
      $hash['RH'] = 0;
      $hash['RL'] = 0;
      $hash['RN'] = 0;
      $hash['SA'] = 0;
      $hash['SB'] = 0;
      $hash['SC'] = 0;
      $hash['VA'] = 0;
      $hash['VC'] = 0;
      $hash['VE'] = 0;
      $hash['VF'] = 0;
      $hash['VJ'] = 0;
      $hash['VM'] = 0;
      $hash['VN'] = 0;
      $hash['VP'] = 0;
      $hash['VS'] = 0;
      $hash['VT'] = 0;
      $hash['VW'] = 0;
      $hash['VX'] = 0;
      $hash['VY'] = 0;
      $hash['VZ'] = 0;
      $hash['WB'] = 0;
      $hash['WC'] = 0;
      $hash['WD'] = 0;
      $hash['WE'] = 0;
      $hash['WF'] = 0;
      $hash['WG'] = 0;
      $hash['WH'] = 0;
      $hash['WJ'] = 0;
      $hash['WK'] = 0;
      $hash['WL'] = 0;
      $hash['WM'] = 0;
      $hash['WN'] = 0;
      $hash['WP'] = 0;
      $hash['WQ'] = 0;
      $hash['WR'] = 0;
      $hash['WS'] = 0;
      $hash['WT'] = 0;
      $hash['WU'] = 0;
      $hash['WV'] = 0;
      $hash['WX'] = 0;
      $hash['WY'] = 0;
      $hash['WZ'] = 0;
      $hash['ZA'] = 0;
      $hash['ZB'] = 0;
      $hash['ZE'] = 0;
      $hash['ZF'] = 0;
      $hash['ZG'] = 0;
      $hash['ZH'] = 0;
      $hash['ZJ'] = 0;
      $hash['ZK'] = 0;
      $hash['ZL'] = 0;
    }
    elseif ($formulaire_code == 'tva3525bis_20170101') {
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BD'] = 0;
    }
    elseif ($formulaire_code == 'tva3525bis_20180101') {
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BD'] = 0;
    } elseif ($formulaire_code == 'tva3310ter_20180101') {
        $hash['DA'] = 0;
        $hash['DB'] = 0;
        $hash['DC'] = 0;
        $hash['DD'] = 0;
        $hash['DE'] = 0;
        $hash['DF'] = 0;
        $hash['DG'] = 0;
        $hash['DH'] = 0;
        $hash['DJ'] = 0;
        $hash['DK'] = 0;
        $hash['DL'] = 0;
        $hash['EA'] = 0;
        $hash['EB'] = 0;
        $hash['EC'] = 0;
        $hash['ED'] = 0;
        $hash['EE'] = 0;
        $hash['EF'] = 0;
        $hash['EG'] = 0;
        $hash['EH'] = 0;
        $hash['EJ'] = 0;
        $hash['EK'] = 0;
        $hash['EL'] = 0;

        $hash['GA'] = 0;
        $hash['GB'] = 0;
        $hash['GC'] = 0;
        $hash['GD'] = 0;
        $hash['GE'] = 0;
        $hash['GF'] = 0;
        $hash['GG'] = 0;
        $hash['GH'] = 0;
        $hash['GJ'] = 0;
        $hash['GK'] = 0;
        $hash['GL'] = 0;
        $hash['HA'] = 0;
        $hash['HB'] = 0;
        $hash['HC'] = 0;
        $hash['HD'] = 0;
        $hash['HE'] = 0;
        $hash['HF'] = 0;
        $hash['HG'] = 0;
        $hash['HH'] = 0;

        $hash['KA'] = 0;
        $hash['KB'] = 0;
        $hash['KC'] = 0;
        $hash['KD'] = 0;
        $hash['KE'] = 0;
        $hash['KF'] = 0;
        $hash['KG'] = 0;
        $hash['KH'] = 0;
        $hash['KJ'] = 0;
        $hash['KK'] = 0;
        $hash['KL'] = 0;
        $hash['LA'] = 0;
        $hash['LB'] = 0;
        $hash['LC'] = 0;
        $hash['LD'] = 0;
        $hash['LE'] = 0;
        $hash['LF'] = 0;
        $hash['LG'] = 0;
        $hash['LH'] = 0;
        $hash['LH'] = 0;
        $hash['LJ'] = 0;
        $hash['LK'] = 0;
        $hash['LL'] = 0;

        $hash['NA'] = 0;
        $hash['NB'] = 0;
        $hash['NC'] = 0;
        $hash['ND'] = 0;
        $hash['NE'] = 0;
        $hash['NF'] = 0;
        $hash['NG'] = 0;
        $hash['NH'] = 0;
        $hash['NJ'] = 0;
        $hash['NK'] = 0;
        $hash['NL'] = 0;
    } elseif ($formulaire_code == 'tva3515sd_20180101') {
        $hash['CA'] = 0;
        $hash['CB'] = 0;
        $hash['BE'] = 0;
        $hash['BF'] = 0;
        $hash['BB'] = 0;
        $hash['BC'] = 0;
        $hash['BD'] = 0;
        $hash['DA'] = 0;
        $hash['DB'] = 0;
        $hash['DC'] = 0;
        $hash['DD'] = 0;
    } elseif ($formulaire_code == 'tva3310a_20180101') {
        $hash['BA'] = 0;
        $hash['BB'] = 0;
        $hash['BC'] = 0;
        $hash['BE'] = 0;
        $hash['BF'] = 0;
        $hash['BK'] = 0;
        $hash['BM'] = 0;
        $hash['BN'] = 0;
        $hash['BP'] = 0;
        $hash['BQ'] = 0;
        $hash['BR'] = 0;
        $hash['BS'] = 0;
        $hash['CA'] = 0;
        $hash['CB'] = 0;
        $hash['CC'] = 0;
        $hash['CE'] = 0;
        $hash['CF'] = 0;
        $hash['CK'] = 0;
        $hash['CM'] = 0;
        $hash['CN'] = 0;
        $hash['CP'] = 0;
        $hash['CQ'] = 0;
        $hash['CR'] = 0;
        $hash['CS'] = 0;
        $hash['FA'] = 0;
        $hash['FB'] = 0;
        $hash['FE'] = 0;
        $hash['FF'] = 0;
        $hash['FG'] = 0;
        $hash['FJ'] = 0;
        $hash['FR'] = 0;
        $hash['FT'] = 0;
        $hash['FV'] = 0;
        $hash['HB'] = 0;
        $hash['HE'] = 0;
        $hash['HF'] = 0;
        $hash['HI'] = 0;
        $hash['JB'] = 0;
        $hash['JC'] = 0;
        $hash['JD'] = 0;
        $hash['JE'] = 0;
        $hash['JF'] = 0;
        $hash['JG'] = 0;
        $hash['JH'] = 0;
        $hash['JJ'] = 0;
        $hash['JK'] = 0;
        $hash['JL'] = 0;
        $hash['JM'] = 0;
        $hash['JN'] = 0;
        $hash['JP'] = 0;
        $hash['JQ'] = 0;
        $hash['JR'] = 0;
        $hash['KF'] = 0;
        $hash['KG'] = 0;
        $hash['KJ'] = 0;
        $hash['KL'] = 0;
        $hash['KT'] = 0;
        $hash['KU'] = 0;
        $hash['KX'] = 0;
        $hash['KY'] = 0;
        $hash['KZ'] = 0;
        $hash['LA'] = 0;
        $hash['LC'] = 0;
        $hash['LD'] = 0;
        $hash['LE'] = 0;
        $hash['LF'] = 0;
        $hash['LG'] = 0;
        $hash['LH'] = 0;
        $hash['LJ'] = 0;
        $hash['LK'] = 0;
        $hash['LL'] = 0;
        $hash['LM'] = 0;
        $hash['LN'] = 0;
        $hash['LP'] = 0;
        $hash['LQ'] = 0;
        $hash['LR'] = 0;
        $hash['LS'] = 0;
        $hash['LT'] = 0;
        $hash['LU'] = 0;
        $hash['LV'] = 0;
        $hash['LW'] = 0;
        $hash['LX'] = 0;
        $hash['LZ'] = 0;
        $hash['MA'] = 0;
        $hash['MB'] = 0;
        $hash['MC'] = 0;
        $hash['MD'] = 0;
        $hash['ME'] = 0;
        $hash['MF'] = 0;
        $hash['MG'] = 0;
        $hash['MH'] = 0;
        $hash['MJ'] = 0;
        $hash['MK'] = 0;
        $hash['ML'] = 0;
        $hash['MM'] = 0;
        $hash['MN'] = 0;
        $hash['MP'] = 0;
        $hash['MQ'] = 0;
        $hash['MR'] = 0;
        $hash['MS'] = 0;
        $hash['MU'] = 0;
        $hash['MV'] = 0;
        $hash['MW'] = 0;
        $hash['MX'] = 0;
        $hash['MY'] = 0;
        $hash['MZ'] = 0;
        $hash['NA'] = 0;
        $hash['NB'] = 0;
        $hash['NC'] = 0;
        $hash['ND'] = 0;
        $hash['NE'] = 0;
        $hash['NF'] = 0;
        $hash['NG'] = 0;
        $hash['NH'] = 0;
        $hash['NJ'] = 0;
        $hash['NK'] = 0;
        $hash['NL'] = 0;
        $hash['NM'] = 0;
        $hash['NN'] = 0;
        $hash['NP'] = 0;
        $hash['NQ'] = 0;
        $hash['NR'] = 0;
        $hash['NS'] = 0;
        $hash['NT'] = 0;
        $hash['NU'] = 0;
        $hash['NV'] = 0;
        $hash['NW'] = 0;
        $hash['NX'] = 0;
        $hash['NY'] = 0;
        $hash['NZ'] = 0;
        $hash['PA'] = 0;
        $hash['PB'] = 0;
        $hash['PC'] = 0;
        $hash['PD'] = 0;
        $hash['PE'] = 0;
        $hash['PF'] = 0;
        $hash['PG'] = 0;
        $hash['PH'] = 0;
        $hash['PK'] = 0;
        $hash['PL'] = 0;
        $hash['PN'] = 0;
    } elseif ($formulaire_code == 'tva3310ca3_20180101') {
        $hash['CA'] = 0;
        $hash['CB'] = 0;
        $hash['CC'] = 0;
        $hash['CD'] = 0;
        $hash['CE'] = 0;
        $hash['CF'] = 0;
        $hash['CG'] = 0;
        $hash['DA'] = 0;
        $hash['DB'] = 0;
        $hash['DC'] = 0;
        $hash['DD'] = 0;
        $hash['DE'] = 0;
        $hash['DF'] = 0;
        $hash['DG'] = 0;
        $hash['DH'] = 0;

        $hash['FB'] = 0;
        $hash['FC'] = 0;
        $hash['FG'] = 0;
        $hash['FH'] = 0;
        $hash['FJ'] = 0;
        $hash['FK'] = 0;
        $hash['FM'] = 0;
        $hash['FN'] = 0;
        $hash['FP'] = 0;
        $hash['FR'] = 0;

        $hash['GB'] = 0;
        $hash['GC'] = 0;
        $hash['GG'] = 0;
        $hash['GH'] = 0;
        $hash['GJ'] = 0;
        $hash['GK'] = 0;
        $hash['GM'] = 0;
        $hash['GN'] = 0;
        $hash['GP'] = 0;
        $hash['GR'] = 0;

        $hash['HA'] = 0;
        $hash['HB'] = 0;
        $hash['HC'] = 0;
        $hash['HD'] = 0;
        $hash['HG'] = 0;
        $hash['HH'] = 0;

        $hash['JA'] = 0;
        $hash['JB'] = 0;
        $hash['JC'] = 0;

        $hash['KA'] = 0;
        $hash['KB'] = 0;
        $hash['KE'] = 0;
        $hash['KG'] = 0;
        $hash['KH'] = 0;
        $hash['KJ'] = 0;
        $hash['KL'] = 0;
        $hash['KR'] = 0;
        $hash['KS'] = 0;
        $hash['KT'] = 0;
        $hash['KU'] = 0;

      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;

      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KE'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KR'] = 0;
      $hash['KS'] = 0;
      $hash['KT'] = 0;
      $hash['KU'] = 0;
    }
    elseif ($formulaire_code == 'tva3310ca3g_20180101') {
        $hash['DA'] = 0;
        $hash['DB'] = 0;
        $hash['DC'] = 0;
        $hash['DD'] = 0;
        $hash['EA'] = 0;
        $hash['EB'] = 0;
        $hash['EC'] = 0;
        $hash['FA'] = 0;
        $hash['FB'] = 0;
        $hash['FE'] = 0;
        $hash['GA'] = 0;
        $hash['GB'] = 0;
        $hash['GD'] = 0;
        $hash['GE'] = 0;
        $hash['GF'] = 0;
        $hash['GH'] = 0;
        $hash['GJ'] = 0;
        $hash['GK'] = 0;
        $hash['GL'] = 0;
        $hash['GM'] = 0;
        $hash['GO'] = 0;
        $hash['GP'] = 0;
        $hash['GQ'] = 0;
        $hash['GR'] = 0;
        $hash['GS'] = 0;
        $hash['GT'] = 0;
        $hash['GU'] = 0;
        $hash['GV'] = 0;
        $hash['GX'] = 0;
        $hash['GZ'] = 0;
        $hash['HK'] = 0;
        $hash['HL'] = 0;
        $hash['HM'] = 0;
        $hash['HN'] = 0;
        $hash['HO'] = 0;
        $hash['HP'] = 0;
        $hash['HQ'] = 0;
        $hash['HR'] = 0;
        $hash['HS'] = 0;
        $hash['HT'] = 0;
        $hash['HU'] = 0;
        $hash['KJ'] = 0;
        $hash['KK'] = 0;
        $hash['KL'] = 0;
        $hash['KM'] = 0;
        $hash['KR'] = 0;
        $hash['KS'] = 0;
        $hash['KT'] = 0;
        $hash['KU'] = 0;
        $hash['KV'] = 0;
        $hash['KW'] = 0;
        $hash['KX'] = 0;
        $hash['KY'] = 0;
        $hash['KZ'] = 0;
        $hash['LA'] = 0;
        $hash['LB'] = 0;
        $hash['LC'] = 0;
        $hash['LD'] = 0;
        $hash['LF'] = 0;
        $hash['LG'] = 0;
        $hash['MA'] = 0;
        $hash['MB'] = 0;
        $hash['MC'] = 0;
        $hash['MD'] = 0;
        $hash['ME'] = 0;
        $hash['MF'] = 0;
        $hash['MG'] = 0;
        $hash['MH'] = 0;
        $hash['MJ'] = 0;
        $hash['MK'] = 0;
        $hash['ML'] = 0;
        $hash['MM'] = 0;
        $hash['MN'] = 0;
        $hash['MP'] = 0;
        $hash['MR'] = 0;
        $hash['MS'] = 0;
        $hash['NA'] = 0;
        $hash['NB'] = 0;
        $hash['NC'] = 0;
        $hash['ND'] = 0;
        $hash['NE'] = 0;
        $hash['NF'] = 0;
        $hash['NG'] = 0;
        $hash['NH'] = 0;
        $hash['NK'] = 0;
        $hash['NL'] = 0;
        $hash['NM'] = 0;
        $hash['NN'] = 0;
        $hash['NP'] = 0;
        $hash['NQ'] = 0;
        $hash['NR'] = 0;
        $hash['NS'] = 0;
        $hash['NT'] = 0;
    } elseif ($formulaire_code == 'tva3517sca12_20180101') {
        $hash['DA'] = 0;
        $hash['DB'] = 0;
        $hash['DC'] = 0;
        $hash['EA'] = 0;
        $hash['EB'] = 0;
        $hash['EC'] = 0;
        $hash['ED'] = 0;
        $hash['EE'] = 0;
        $hash['EF'] = 0;
        $hash['EG'] = 0;
        $hash['EH'] = 0;
        $hash['EJ'] = 0;
        $hash['EL'] = 0;
        $hash['EM'] = 0;
        $hash['EN'] = 0;
        $hash['EP'] = 0;
        $hash['EQ'] = 0;
        $hash['EU'] = 0;
        $hash['EV'] = 0;
        $hash['EW'] = 0;
        $hash['EX'] = 0;
        $hash['EY'] = 0;
        $hash['EZ'] = 0;
        $hash['FA'] = 0;
        $hash['FB'] = 0;
        $hash['FC'] = 0;
        $hash['FD'] = 0;
        $hash['FF'] = 0;
        $hash['FG'] = 0;
        $hash['FJ'] = 0;
        $hash['FL'] = 0;
        $hash['FM'] = 0;
        $hash['FN'] = 0;
        $hash['FP'] = 0;
        $hash['FR'] = 0;
        $hash['FU'] = 0;
        $hash['FV'] = 0;
        $hash['FW'] = 0;
        $hash['FY'] = 0;
        $hash['GA'] = 0;
        $hash['GB'] = 0;
        $hash['GC'] = 0;
        $hash['GF'] = 0;
        $hash['GH'] = 0;
        $hash['HA'] = 0;
        $hash['HB'] = 0;
        $hash['HC'] = 0;
        $hash['JA'] = 0;
        $hash['KA'] = 0;
        $hash['KB'] = 0;
        $hash['KD'] = 0;
        $hash['KE'] = 0;
        $hash['KF'] = 0;
        $hash['KG'] = 0;
        $hash['KH'] = 0;
        $hash['KJ'] = 0;
        $hash['KL'] = 0;
        $hash['KM'] = 0;
        $hash['LA'] = 0;
        $hash['LB'] = 0;
        $hash['MA'] = 0;
        $hash['MM'] = 0;
        $hash['MN'] = 0;
        $hash['NA'] = 0;
        $hash['NB'] = 0;
        $hash['NC'] = 0;
        $hash['QA'] = 0;
        $hash['QD'] = 0;
        $hash['QE'] = 0;
        $hash['QF'] = 0;
        $hash['QH'] = 0;
        $hash['QJ'] = 0;
        $hash['QS'] = 0;
        $hash['RA'] = 0;
        $hash['RB'] = 0;
        $hash['RC'] = 0;
        $hash['RE'] = 0;
        $hash['RF'] = 0;
        $hash['RG'] = 0;
        $hash['RN'] = 0;
        $hash['SA'] = 0;
        $hash['SB'] = 0;
        $hash['SC'] = 0;
        $hash['SE'] = 0;
        $hash['SF'] = 0;
        $hash['SH'] = 0;
        $hash['SJ'] = 0;
        $hash['SK'] = 0;
        $hash['SL'] = 0;
        $hash['SM'] = 0;
        $hash['SN'] = 0;
        $hash['SP'] = 0;
        $hash['VA'] = 0;
        $hash['VC'] = 0;
        $hash['VE'] = 0;
        $hash['VF'] = 0;
        $hash['VJ'] = 0;
        $hash['VM'] = 0;
        $hash['VN'] = 0;
        $hash['VP'] = 0;
        $hash['VS'] = 0;
        $hash['VT'] = 0;
        $hash['VW'] = 0;
        $hash['VX'] = 0;
        $hash['VY'] = 0;
        $hash['VZ'] = 0;
        $hash['WB'] = 0;
        $hash['WC'] = 0;
        $hash['WD'] = 0;
        $hash['WE'] = 0;
        $hash['WF'] = 0;
        $hash['WG'] = 0;
        $hash['WH'] = 0;
        $hash['WJ'] = 0;
        $hash['WK'] = 0;
        $hash['WL'] = 0;
        $hash['WM'] = 0;
        $hash['WN'] = 0;
        $hash['WP'] = 0;
        $hash['WQ'] = 0;
        $hash['WR'] = 0;
        $hash['WS'] = 0;
        $hash['WT'] = 0;
        $hash['WU'] = 0;
        $hash['WV'] = 0;
        $hash['WX'] = 0;
        $hash['WY'] = 0;
        $hash['WZ'] = 0;
        $hash['YA'] = 0;
        $hash['YB'] = 0;
        $hash['YC'] = 0;
        $hash['YK'] = 0;
        $hash['YL'] = 0;
        $hash['ZA'] = 0;
        $hash['ZB'] = 0;
        $hash['ZE'] = 0;
        $hash['ZF'] = 0;
        $hash['ZG'] = 0;
        $hash['ZH'] = 0;
        $hash['ZJ'] = 0;
        $hash['ZK'] = 0;
        $hash['ZL'] = 0;
        $hash['ZM'] = 0;
        $hash['ZN'] = 0;
        $hash['ZP'] = 0;
        $hash['ZR'] = 0;
        $hash['ZS'] = 0;
        $hash['ZT'] = 0;
        $hash['ZU'] = 0;
        $hash['ZV'] = 0;
        $hash['ZW'] = 0;
        $hash['ZX'] = 0;
        $hash['ZY'] = 0;
        $hash['ZZ'] = 0;
    } elseif ($formulaire_code == 'rcm2777_20180101') {
        $hash['AA'] = 0;
        $hash['AB'] = 0;
        $hash['AK'] = 0;
        $hash['AL'] = 0;
        $hash['AM'] = 0;
        $hash['AN'] = 0;
        $hash['AO'] = 0;
        $hash['AP'] = 0;
        $hash['AQ'] = 0;
        $hash['AR'] = 0;
        $hash['AS'] = 0;
        $hash['AT'] = 0;
        $hash['AU'] = 0;
        $hash['AV'] = 0;

        $hash['CA'] = 0;
        $hash['CC'] = 0;
        $hash['CE'] = 0;
        $hash['CG'] = 0;
        $hash['CI'] = 0;
        $hash['CJ'] = 0;
        $hash['CK'] = 0;
        $hash['CL'] = 0;
        $hash['CN'] = 0;
        $hash['CO'] = 0;
        $hash['CP'] = 0;
        $hash['CQ'] = 0;
        $hash['CS'] = 0;
        $hash['CU'] = 0;
        $hash['CV'] = 0;
        $hash['CW'] = 0;
        $hash['CX'] = 0;
        $hash['CY'] = 0;
        $hash['CZ'] = 0;

        $hash['EA'] = 0;
        $hash['EB'] = 0;
        $hash['ED'] = 0;
        $hash['EE'] = 0;
        $hash['EI'] = 0;
        $hash['EJ'] = 0;

        $hash['FH'] = 0;
        $hash['FI'] = 0;
        $hash['FJ'] = 0;
        $hash['FK'] = 0;
        $hash['FL'] = 0;
        $hash['FM'] = 0;
        $hash['FN'] = 0;
        $hash['FP'] = 0;
        $hash['FQ'] = 0;
        $hash['FR'] = 0;
        $hash['FS'] = 0;
        $hash['FT'] = 0;
        $hash['FU'] = 0;
        $hash['FV'] = 0;
        $hash['FX'] = 0;
        $hash['FY'] = 0;
        $hash['FZ'] = 0;

        $hash['GA'] = 0;
        $hash['GE'] = 0;
        $hash['GH'] = 0;
        $hash['GI'] = 0;
        $hash['GJ'] = 0;
        $hash['GK'] = 0;
        $hash['GL'] = 0;
        $hash['GM'] = 0;
        $hash['GN'] = 0;
        $hash['GP'] = 0;
        $hash['GQ'] = 0;
        $hash['GR'] = 0;
        $hash['GS'] = 0;
        $hash['GT'] = 0;
        $hash['GU'] = 0;
        $hash['GV'] = 0;
        $hash['GX'] = 0;
        $hash['GY'] = 0;
        $hash['GZ'] = 0;

        $hash['IA'] = 0;
        $hash['II'] = 0;
        $hash['IJ'] = 0;

        $hash['JA'] = 0;
        $hash['JE'] = 0;

        $hash['KA'] = 0;
        $hash['KE'] = 0;

        $hash['LA'] = 0;
        $hash['LE'] = 0;

        $hash['MA'] = 0;
        $hash['ME'] = 0;

        $hash['NA'] = 0;
        $hash['NB'] = 0;

        $hash['OA'] = 0;

        $hash['PA'] = 0;
        $hash['PB'] = 0;

        $hash['RA'] = 0;
        $hash['RB'] = 0;
        $hash['RC'] = 0;
        $hash['RF'] = 0;
        $hash['RG'] = 0;
        $hash['RH'] = 0;
        $hash['RI'] = 0;
        $hash['RJ'] = 0;
        $hash['RK'] = 0;
        $hash['RL'] = 0;
        $hash['RM'] = 0;
        $hash['RN'] = 0;
        $hash['RO'] = 0;
        $hash['RP'] = 0;
        $hash['RQ'] = 0;
        $hash['RR'] = 0;
        $hash['RS'] = 0;
        $hash['RT'] = 0;
        $hash['RU'] = 0;
        $hash['RV'] = 0;
    }

    // Millesime 2019
    elseif ($formulaire_code == 'rcm2777_20190101') {
        $hash['AA'] = 0;
        $hash['AB'] = 0;
        $hash['AG'] = 0;
        $hash['AH'] = 0;
        $hash['AK'] = 0;
        $hash['AL'] = 0;
        $hash['AM'] = 0;
        $hash['AN'] = 0;
        $hash['AO'] = 0;
        $hash['AP'] = 0;
        $hash['AQ'] = 0;
        $hash['AR'] = 0;
        $hash['AS'] = 0;
        $hash['AT'] = 0;
        $hash['AU'] = 0;
        $hash['AV'] = 0;

        $hash['BA'] = 0;
        $hash['BB'] = 0;
        $hash['BG'] = 0;
        $hash['BH'] = 0;
        $hash['BK'] = 0;
        $hash['BL'] = 0;
        $hash['BM'] = 0;
        $hash['BN'] = 0;
        $hash['BO'] = 0;
        $hash['BP'] = 0;
        $hash['BQ'] = 0;
        $hash['BR'] = 0;
        $hash['BS'] = 0;
        $hash['BT'] = 0;
        $hash['BU'] = 0;
        $hash['BV'] = 0;

        $hash['CA'] = 0;
        $hash['CC'] = 0;
        $hash['CE'] = 0;
        $hash['CG'] = 0;
        $hash['CI'] = 0;
        $hash['CJ'] = 0;
        $hash['CK'] = 0;
        $hash['CL'] = 0;
        $hash['CM'] = 0;
        $hash['CN'] = 0;
        $hash['CO'] = 0;
        $hash['CP'] = 0;
        $hash['CQ'] = 0;
        $hash['CR'] = 0;
        $hash['CS'] = 0;
        $hash['CT'] = 0;
        $hash['CU'] = 0;
        $hash['CV'] = 0;
        $hash['CW'] = 0;
        $hash['CX'] = 0;
        $hash['CY'] = 0;
        $hash['CZ'] = 0;

        $hash['DA'] = 0;
        $hash['DC'] = 0;
        $hash['DE'] = 0;
        $hash['DG'] = 0;
        $hash['DI'] = 0;
        $hash['DJ'] = 0;
        $hash['DK'] = 0;
        $hash['DM'] = 0;
        $hash['DM'] = 0;
        $hash['DN'] = 0;
        $hash['DO'] = 0;
        $hash['DP'] = 0;
        $hash['DQ'] = 0;
        $hash['DR'] = 0;
        $hash['DS'] = 0;
        $hash['DT'] = 0;
        $hash['DU'] = 0;
        $hash['DV'] = 0;
        $hash['DW'] = 0;
        $hash['DX'] = 0;
        $hash['DY'] = 0;
        $hash['DZ'] = 0;

        $hash['EA'] = 0;
        $hash['EB'] = 0;
        $hash['ED'] = 0;
        $hash['EE'] = 0;
        $hash['EG'] = 0;
        $hash['EH'] = 0;
        $hash['EI'] = 0;
        $hash['EJ'] = 0;

        $hash['FA'] = 0;
        $hash['FB'] = 0;
        $hash['FC'] = 0;
        $hash['FE'] = 0;
        $hash['FF'] = 0;
        $hash['FG'] = 0;
        $hash['FH'] = 0;
        $hash['FI'] = 0;
        $hash['FJ'] = 0;
        $hash['FK'] = 0;
        $hash['FL'] = 0;
        $hash['FM'] = 0;
        $hash['FN'] = 0;
        $hash['FO'] = 0;
        $hash['FP'] = 0;
        $hash['FQ'] = 0;
        $hash['FR'] = 0;
        $hash['FS'] = 0;
        $hash['FT'] = 0;
        $hash['FU'] = 0;
        $hash['FV'] = 0;
        $hash['FX'] = 0;
        $hash['FY'] = 0;
        $hash['FZ'] = 0;

        $hash['GA'] = 0;
        $hash['GB'] = 0;
        $hash['GC'] = 0;
        $hash['GD'] = 0;
        $hash['GE'] = 0;
        $hash['GF'] = 0;
        $hash['GG'] = 0;
        $hash['GH'] = 0;
        $hash['GI'] = 0;
        $hash['GJ'] = 0;
        $hash['GK'] = 0;
        $hash['GL'] = 0;
        $hash['GM'] = 0;
        $hash['GN'] = 0;
        $hash['GO'] = 0;
        $hash['GP'] = 0;
        $hash['GQ'] = 0;
        $hash['GR'] = 0;
        $hash['GS'] = 0;
        $hash['GT'] = 0;
        $hash['GU'] = 0;
        $hash['GV'] = 0;
        $hash['GW'] = 0;
        $hash['GX'] = 0;
        $hash['GY'] = 0;
        $hash['GZ'] = 0;

        $hash['IA'] = 0;
        $hash['IC'] = 0;
        $hash['ID'] = 0;
        $hash['IE'] = 0;
        $hash['IF'] = 0;
        $hash['IG'] = 0;
        $hash['IH'] = 0;
        $hash['II'] = 0;
        $hash['IJ'] = 0;
        $hash['IK'] = 0;

        $hash['JA'] = 0;
        $hash['JB'] = 0;
        $hash['JE'] = 0;
        $hash['JF'] = 0;

        $hash['KA'] = 0;
        $hash['KB'] = 0;
        $hash['KE'] = 0;
        $hash['KF'] = 0;

        $hash['LA'] = 0;
        $hash['LB'] = 0;
        $hash['LE'] = 0;
        $hash['LF'] = 0;

        $hash['MA'] = 0;
        $hash['MB'] = 0;
        $hash['ME'] = 0;
        $hash['MF'] = 0;

        $hash['NA'] = 0;
        $hash['NB'] = 0;

        $hash['OA'] = 0;

        $hash['PA'] = 0;
        $hash['PB'] = 0;
        $hash['PC'] = 0;
        $hash['PD'] = 0;
        $hash['PE'] = 0;

        $hash['QA'] = 0;
        $hash['QB'] = 0;
        $hash['QC'] = 0;
        $hash['QD'] = 0;
        $hash['QE'] = 0;

        $hash['RA'] = 0;
        $hash['RB'] = 0;
        $hash['RC'] = 0;
        $hash['RF'] = 0;
        $hash['RG'] = 0;
        $hash['RH'] = 0;
        $hash['RI'] = 0;
        $hash['RJ'] = 0;
        $hash['RK'] = 0;
        $hash['RL'] = 0;
        $hash['RM'] = 0;
        $hash['RN'] = 0;
        $hash['RO'] = 0;
        $hash['RP'] = 0;
        $hash['RQ'] = 0;
        $hash['RR'] = 0;
        $hash['RS'] = 0;
        $hash['RT'] = 0;
        $hash['RU'] = 0;
        $hash['RV'] = 0;
    }
    elseif ($formulaire_code == 'a_identif_hon_20190101' || $formulaire_code == 'a_identif_ifu_20190101') {
        $hash['AA01'] = $adherent->siret;
        $hash['AA02'] = $adherent->company;
        $hash['AA03'] = $adherent->company_bis;
        $hash['AB01'] = $adherent->siret;
    }
    elseif ($formulaire_code == 'das2tv_20190101') {
        $hash['ZZ1'] = 1;
    }
    elseif ($formulaire_code == 'ifu2561_20190101') {
        $hash['ZZ1'] = 1;
        $hash['ZZ2'] = 1;
    } elseif ($formulaire_code == 'tva3517sca12_20190101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['ED'] = 0;
      $hash['EE'] = 0;
      $hash['EF'] = 0;
      $hash['EG'] = 0;
      $hash['EH'] = 0;
      $hash['EJ'] = 0;
      $hash['EL'] = 0;
      $hash['EM'] = 0;
      $hash['EN'] = 0;
      $hash['EP'] = 0;
      $hash['EQ'] = 0;
      $hash['EU'] = 0;
      $hash['EV'] = 0;
      $hash['EW'] = 0;
      $hash['EX'] = 0;
      $hash['EY'] = 0;
      $hash['EZ'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FD'] = 0;
      $hash['FF'] = 0;
      $hash['FG'] = 0;
      $hash['FJ'] = 0;
      $hash['FL'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;
      $hash['FU'] = 0;
      $hash['FV'] = 0;
      $hash['FW'] = 0;
      $hash['FY'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GF'] = 0;
      $hash['GH'] = 0;
      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['JA'] = 0;
      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KD'] = 0;
      $hash['KE'] = 0;
      $hash['KF'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KM'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['MA'] = 0;
      $hash['MM'] = 0;
      $hash['MN'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['QA'] = 0;
      $hash['QD'] = 0;
      $hash['QE'] = 0;
      $hash['QF'] = 0;
      $hash['QH'] = 0;
      $hash['QJ'] = 0;
      $hash['QS'] = 0;
      $hash['RA'] = 0;
      $hash['RB'] = 0;
      $hash['RC'] = 0;
      $hash['RE'] = 0;
      $hash['RF'] = 0;
      $hash['RG'] = 0;
      $hash['RN'] = 0;
      $hash['SA'] = 0;
      $hash['SB'] = 0;
      $hash['SC'] = 0;
      $hash['SE'] = 0;
      $hash['SF'] = 0;
      $hash['SH'] = 0;
      $hash['SJ'] = 0;
      $hash['SK'] = 0;
      $hash['SL'] = 0;
      $hash['SM'] = 0;
      $hash['SN'] = 0;
      $hash['SP'] = 0;
      $hash['VA'] = 0;
      $hash['VC'] = 0;
      $hash['VE'] = 0;
      $hash['VF'] = 0;
      $hash['VJ'] = 0;
      $hash['VM'] = 0;
      $hash['VN'] = 0;
      $hash['VP'] = 0;
      $hash['VS'] = 0;
      $hash['VT'] = 0;
      $hash['VW'] = 0;
      $hash['VX'] = 0;
      $hash['VY'] = 0;
      $hash['VZ'] = 0;
      $hash['WB'] = 0;
      $hash['WC'] = 0;
      $hash['WD'] = 0;
      $hash['WE'] = 0;
      $hash['WF'] = 0;
      $hash['WG'] = 0;
      $hash['WH'] = 0;
      $hash['WJ'] = 0;
      $hash['WK'] = 0;
      $hash['WL'] = 0;
      $hash['WM'] = 0;
      $hash['WN'] = 0;
      $hash['WP'] = 0;
      $hash['WQ'] = 0;
      $hash['WR'] = 0;
      $hash['WS'] = 0;
      $hash['WT'] = 0;
      $hash['WU'] = 0;
      $hash['WV'] = 0;
      $hash['WZ'] = 0;
      $hash['YA'] = 0;
      $hash['YB'] = 0;
      $hash['YC'] = 0;
      $hash['YK'] = 0;
      $hash['YL'] = 0;
      $hash['ZA'] = 0;
      $hash['ZB'] = 0;
      $hash['ZE'] = 0;
      $hash['ZF'] = 0;
      $hash['ZG'] = 0;
      $hash['ZH'] = 0;
      $hash['ZJ'] = 0;
      $hash['ZK'] = 0;
      $hash['ZL'] = 0;
      $hash['ZM'] = 0;
      $hash['ZN'] = 0;
      $hash['ZP'] = 0;
      $hash['ZR'] = 0;
      $hash['ZS'] = 0;
      $hash['ZT'] = 0;
      $hash['ZU'] = 0;
      $hash['ZW'] = 0;
      $hash['ZX'] = 0;
      $hash['ZZ'] = 0;
    } elseif ($formulaire_code == 'tva3310ca3g_20190101') {
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['EA'] = 0;
      $hash['EB'] = 0;
      $hash['EC'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FE'] = 0;
      $hash['GA'] = 0;
      $hash['GB'] = 0;
      $hash['GD'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GL'] = 0;
      $hash['GM'] = 0;
      $hash['GO'] = 0;
      $hash['GP'] = 0;
      $hash['GQ'] = 0;
      $hash['GU'] = 0;
      $hash['GV'] = 0;
      $hash['GX'] = 0;
      $hash['GZ'] = 0;
      $hash['HK'] = 0;
      $hash['HL'] = 0;
      $hash['HN'] = 0;
      $hash['HO'] = 0;
      $hash['HP'] = 0;
      $hash['HQ'] = 0;
      $hash['HR'] = 0;
      $hash['HS'] = 0;
      $hash['HT'] = 0;
      $hash['HU'] = 0;
      $hash['KJ'] = 0;
      $hash['KK'] = 0;
      $hash['KL'] = 0;
      $hash['KM'] = 0;
      $hash['KR'] = 0;
      $hash['KS'] = 0;
      $hash['KT'] = 0;
      $hash['KU'] = 0;
      $hash['KV'] = 0;
      $hash['KW'] = 0;
      $hash['KX'] = 0;
      $hash['KY'] = 0;
      $hash['KZ'] = 0;
      $hash['LA'] = 0;
      $hash['LB'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LF'] = 0;
      $hash['LG'] = 0;
      $hash['MA'] = 0;
      $hash['MB'] = 0;
      $hash['MC'] = 0;
      $hash['MD'] = 0;
      $hash['ME'] = 0;
      $hash['MF'] = 0;
      $hash['MG'] = 0;
      $hash['MH'] = 0;
      $hash['MJ'] = 0;
      $hash['MK'] = 0;
      $hash['ML'] = 0;
      $hash['MN'] = 0;
      $hash['MP'] = 0;
      $hash['MR'] = 0;
      $hash['MS'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['ND'] = 0;
      $hash['NE'] = 0;
      $hash['NF'] = 0;
      $hash['NG'] = 0;
      $hash['NH'] = 0;
      $hash['NK'] = 0;
      $hash['NL'] = 0;
      $hash['NM'] = 0;
      $hash['NN'] = 0;
      $hash['NP'] = 0;
      $hash['NQ'] = 0;
      $hash['NR'] = 0;
      $hash['NS'] = 0;
      $hash['NT'] = 0;
      $hash['NU'] = 0;
      $hash['NV'] = 0;
      $hash['NW'] = 0;
      $hash['NX'] = 0;
      $hash['NY'] = 0;
      $hash['NZ'] = 0;
      $hash['PC'] = 0;
    } elseif ($formulaire_code == 'tva3310ca3_20190101') {
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['CC'] = 0;
      $hash['CD'] = 0;
      $hash['CE'] = 0;
      $hash['CF'] = 0;
      $hash['CG'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
      $hash['DE'] = 0;
      $hash['DF'] = 0;
      $hash['DG'] = 0;
      $hash['DH'] = 0;

      $hash['FB'] = 0;
      $hash['FC'] = 0;
      $hash['FG'] = 0;
      $hash['FH'] = 0;
      $hash['FJ'] = 0;
      $hash['FK'] = 0;
      $hash['FM'] = 0;
      $hash['FN'] = 0;
      $hash['FP'] = 0;
      $hash['FR'] = 0;

      $hash['GB'] = 0;
      $hash['GC'] = 0;
      $hash['GG'] = 0;
      $hash['GH'] = 0;
      $hash['GJ'] = 0;
      $hash['GK'] = 0;
      $hash['GM'] = 0;
      $hash['GN'] = 0;
      $hash['GP'] = 0;
      $hash['GR'] = 0;

      $hash['HA'] = 0;
      $hash['HB'] = 0;
      $hash['HC'] = 0;
      $hash['HD'] = 0;
      $hash['HG'] = 0;
      $hash['HH'] = 0;

      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;

      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KE'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KR'] = 0;
      $hash['KS'] = 0;
      $hash['KT'] = 0;
      $hash['KU'] = 0;

      $hash['JA'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;

      $hash['KA'] = 0;
      $hash['KB'] = 0;
      $hash['KE'] = 0;
      $hash['KG'] = 0;
      $hash['KH'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KR'] = 0;
      $hash['KS'] = 0;
      $hash['KT'] = 0;
      $hash['KU'] = 0;
    } elseif ($formulaire_code == 'tva3310a_20190101') {
      $hash['BA'] = 0;
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BE'] = 0;
      $hash['BF'] = 0;
      $hash['BK'] = 0;
      $hash['BM'] = 0;
      $hash['BN'] = 0;
      $hash['BP'] = 0;
      $hash['BQ'] = 0;
      $hash['BR'] = 0;
      $hash['BS'] = 0;
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['CC'] = 0;
      $hash['CE'] = 0;
      $hash['CF'] = 0;
      $hash['CK'] = 0;
      $hash['CM'] = 0;
      $hash['CN'] = 0;
      $hash['CP'] = 0;
      $hash['CQ'] = 0;
      $hash['CR'] = 0;
      $hash['CS'] = 0;
      $hash['FA'] = 0;
      $hash['FB'] = 0;
      $hash['FG'] = 0;
      $hash['FJ'] = 0;
      $hash['FR'] = 0;
      $hash['FT'] = 0;
      $hash['FV'] = 0;
      $hash['HB'] = 0;
      $hash['HE'] = 0;
      $hash['HF'] = 0;
      $hash['HI'] = 0;
      $hash['JB'] = 0;
      $hash['JC'] = 0;
      $hash['JD'] = 0;
      $hash['JE'] = 0;
      $hash['JF'] = 0;
      $hash['JG'] = 0;
      $hash['JH'] = 0;
      $hash['JJ'] = 0;
      $hash['JK'] = 0;
      $hash['JL'] = 0;
      $hash['JM'] = 0;
      $hash['JN'] = 0;
      $hash['JP'] = 0;
      $hash['JQ'] = 0;
      $hash['JR'] = 0;
      $hash['KF'] = 0;
      $hash['KG'] = 0;
      $hash['KJ'] = 0;
      $hash['KL'] = 0;
      $hash['KT'] = 0;
      $hash['KX'] = 0;
      $hash['KY'] = 0;
      $hash['KZ'] = 0;
      $hash['LA'] = 0;
      $hash['LC'] = 0;
      $hash['LD'] = 0;
      $hash['LE'] = 0;
      $hash['LF'] = 0;
      $hash['LG'] = 0;
      $hash['LH'] = 0;
      $hash['LJ'] = 0;
      $hash['LK'] = 0;
      $hash['LL'] = 0;
      $hash['LM'] = 0;
      $hash['LN'] = 0;
      $hash['LP'] = 0;
      $hash['LQ'] = 0;
      $hash['LR'] = 0;
      $hash['LS'] = 0;
      $hash['LT'] = 0;
      $hash['LU'] = 0;
      $hash['LW'] = 0;
      $hash['LX'] = 0;
      $hash['MA'] = 0;
      $hash['MB'] = 0;
      $hash['MC'] = 0;
      $hash['MD'] = 0;
      $hash['ME'] = 0;
      $hash['MF'] = 0;
      $hash['MG'] = 0;
      $hash['MH'] = 0;
      $hash['MJ'] = 0;
      $hash['MK'] = 0;
      $hash['ML'] = 0;
      $hash['MM'] = 0;
      $hash['MN'] = 0;
      $hash['MP'] = 0;
      $hash['MQ'] = 0;
      $hash['MR'] = 0;
      $hash['MS'] = 0;
      $hash['MU'] = 0;
      $hash['MV'] = 0;
      $hash['MW'] = 0;
      $hash['MX'] = 0;
      $hash['MY'] = 0;
      $hash['MZ'] = 0;
      $hash['NA'] = 0;
      $hash['NB'] = 0;
      $hash['NC'] = 0;
      $hash['ND'] = 0;
      $hash['NE'] = 0;
      $hash['NF'] = 0;
      $hash['NG'] = 0;
      $hash['NH'] = 0;
      $hash['NJ'] = 0;
      $hash['NK'] = 0;
      $hash['NL'] = 0;
      $hash['NM'] = 0;
      $hash['NN'] = 0;
      $hash['NP'] = 0;
      $hash['NQ'] = 0;
      $hash['NR'] = 0;
      $hash['NS'] = 0;
      $hash['NT'] = 0;
      $hash['NU'] = 0;
      $hash['NV'] = 0;
      $hash['NW'] = 0;
      $hash['NX'] = 0;
      $hash['NY'] = 0;
      $hash['NZ'] = 0;
      $hash['PA'] = 0;
      $hash['PB'] = 0;
      $hash['PC'] = 0;
      $hash['PD'] = 0;
      $hash['PE'] = 0;
      $hash['PF'] = 0;
      $hash['PG'] = 0;
      $hash['PH'] = 0;
      $hash['PK'] = 0;
      $hash['PP'] = 0;
      $hash['PR'] = 0;
    } elseif ($formulaire_code == 'tva3525bis_20190101') {
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BD'] = 0;
    } elseif ($formulaire_code == 'tva3515sd_20190101') {
      $hash['CA'] = 0;
      $hash['CB'] = 0;
      $hash['BE'] = 0;
      $hash['BF'] = 0;
      $hash['BB'] = 0;
      $hash['BC'] = 0;
      $hash['BD'] = 0;
      $hash['DA'] = 0;
      $hash['DB'] = 0;
      $hash['DC'] = 0;
      $hash['DD'] = 0;
    }


    array_walk_recursive($hash, "Formulaire::cleanFormulaireValue");
    return $hash;
  }

  public static function cleanFormulaireValue(&$value, $key) {
    $value = str_replace(array("\r\n", "\r", "\n", '"'), array(" ", " ", " ", "'"), $value);
  }



  /******************************************************/
  /* formatage de données pour l'enregistrement         */
  /******************************************************/
  public static function formatData($form_code, &$data, $params) {
    $form = self::$form[$form_code];
    /*
        foreach ($form as $current_field => $opts) {
          if ($opts['type'] == 'date-ssaammjj' && !empty($data[$current_field])) {
            $date = Date::asHash($data[$current_field]);
            $timestamp = $date['ts'];
            $date = date("Ymd", $timestamp);
            $data[$current_field] = $date;
          }
          if ($opts['type'] == 'date-ssaamm' && !empty($data[$current_field])) {
            $timestamp = mktime(0, 0, 1, (int) (substr($data[$current_field], 0, 2)), 15, (int) (substr($data[$current_field], 3, 4)));
            $date = date("Ym", $timestamp);
            $data[$current_field] = $date;
          }
          if ($opts['type'] == 'comments') {
            for ($i = 1; $i <= 5; $i++) {
              $data[$current_field . $i] = str_replace("\n", "^^^", $data[$current_field . $i]);
            }
            unset($data[$current_field]);
          }
        }
    */
    foreach ($data as $key => $value) {
      list ($field, $index) = explode('/', $key);
      if ($form[$field]['type'] == 'date-ssaammjj' && !empty($value)) {
        $date = Date::asHash($value);
        $timestamp = $date['ts'];
        $date = date("Ymd", $timestamp);
        $data[$key] = $date;
      }
      if ($form[$field]['type'] == 'date-ssaamm' && !empty($value)) {
        $timestamp = mktime(0, 0, 1, (int) (substr($value, 0, 2)), 15, (int) (substr($value, 3, 4)));
        $date = date("Ym", $timestamp);
        $data[$key] = $date;
      }
      if ($form[$field]['type'] == 'date-ssmmjj' && !empty($value)) {
          $date = explode('/' , $value);
          $dateFormatted = $date[1] . $date[0];
          $data[$key] = $dateFormatted;
      }
      if ($form[$field]['type'] == 'comments') {
        for ($i = 1; $i <= 5; $i++) {
          $data[$key . $i] = str_replace("\n", "^^^", $data[$key . $i]);
        }
        unset($data[$key]);
      }
    }

    return $data;
  }


  public static function calculate_reference_paiment($data, Declaration $declaration, Adherent $adherent) {
    $declaration_dectype = $declaration->getDectype();
    if ($declaration_dectype->document_code == Formulairetype::DOCUMENT_CODE_TVA) {
      return Formulaire::calculate_reference_paiment_tva($data, $declaration, $adherent);
    }
    elseif (in_array($declaration_dectype->document_code, array(Formulairetype::DOCUMENT_CODE_IS,
                                                                Formulairetype::DOCUMENT_CODE_TS,
                                                                Formulairetype::DOCUMENT_CODE_CVAE,
                                                                Formulairetype::DOCUMENT_CODE_RCM))) {
      return Formulaire::calculate_reference_paiment_is_ts_cvae($data, $declaration, $adherent);
    }
    return $data;
  }


  // - Identification Fiscale (7 c)
  // Si le code OBF=ISGROUPE, alors
  //	 Identification Fiscale = « ISGR » suivi du numéro d’ordre de la ROF,
  //	 complétée par des caractères « espace »
  // Sinon
  // 	 Identification Fiscale = ROF déclarée complétée par des caractères « espace »
  // Finsi
  // - Echéance (7 c)
  // SSAA = année d’échéance déclarée
  // MM = mois d’échéance déclarée
  // X = type échéance A : Acompte 2571 / S : Solde 2572
  // - n° séquentiel (1 c) numéro d’ordre du télé paiement (n = 1 à 3)
  // - n° SIREN ou IDSP (9 caractères)
  public static function calculate_reference_paiment_is_ts_cvae($data, Declaration $declaration, Adherent $adherent) {
    $declaration_dectype = $declaration->getDectype();

    $rof = $data['KD'];
    if (substr($rof, 0, strlen('ISGROUPE')) == 'ISGROUPE') {
      $identification_fiscale = 'ISGR' . trim(substr($rof, strlen('ISGROUPE')));
    }
    else {
      $identification_fiscale = $rof;
    }
    // $identification_fiscale = str_pad($identification_fiscale, 7, ' ', STR_PAD_RIGHT);

    $echeance = $data['KF'];
    $echeance .= $declaration_dectype->ref_paiement_type_echeance;

    $siren = $adherent->getSiren();

    $fields = array(1 => 'A', 2 => 'B', 3 => 'C');
    for ($n = 1; $n <= 3; $n++) {
      $field_amount = 'H' . $fields[$n];
      $field_ref = 'K' . $fields[$n];
      $data[$field_ref] = '';

      if (empty($data[$field_amount])) continue;
      // $ref_paiement = $identification_fiscale . $echeance . $n . $siren;
      $ref_paiement = self::tfGenRefGlobal($data, $declaration, $identification_fiscale);
      $data[$field_ref] = $ref_paiement;
    }
    return $data;
  }


  /*
     Generation des references de paiement pour les TVA.

     entree :  taLig         = tableau des valeurs recues du site

               tTypeDecl     = type de declaration
               tDateDeb      = date debut (dd/mm/yyyy)
               tDateFin      = date fin (dd/mm/yyyy)

               bREG          = TRUE si tele-reglement
               bBQ1          = TRUE si reglement 1 rempli
               bBQ2          = TRUE si reglement 2 rempli
               bBQ3          = TRUE si reglement 3 rempli

               bVIV          = TRUE si virement
               bCHQ          = TRUE si cheque
               bESP          = TRUE si espece

     sortie :
               nPeriodes     = nb periodes -1
               nCtpRef       = nb references generees
               tC_REF1       = reference reglement 1
               tC_REF2       = reference reglement 2
               tC_REF3       = reference reglement 3
               tC_REF4       = reference virement
               tC_REF5       = reference cheque
               tC_REF6       = reference espece
  */

  public static function calculate_reference_paiment_tva($data, Declaration $declaration, Adherent $adherent) {
    $declaration_dectype = $declaration->getDectype();

    if ($declaration_dectype->name == "TVA 3519") {
      return $data; /* pas de paiement dans une demande de remboursement */
    }

    $tDateDeb = ValidMain::format_back_jjmmaa($data['CA']);
    $tDateFin = ValidMain::format_back_jjmmaa($data['CB']);

    /* Nb mois dans la declaration */
    /* (anne_fin - annee_dev)*12 + (mois_fin - mois_deb) */
    $nPeriodes = (substr($tDateFin, 6, 4) - substr($tDateDeb, 6, 4)) * 12 + substr($tDateFin, 3, 2) - substr($tDateDeb, 3, 2);

    $bREG = (int) $data['EA'];
    $bVIR = (int) $data['EB'];
    $bCHQ = (int) $data['EC'];
    $bESP = (int) $data['ED'];
    $bBQ1 = !empty($data['GA']);
    $bBQ2 = !empty($data['GB']);
    $bBQ3 = !empty($data['GC']);

    $rof = $data['KD']; // KD = Référence Obligation Fiscale (T-IDENTIF)

    //if ($bREG) {
    $data['KA'] = ($bBQ1) ? self::tfGenRefGlobal($data, $declaration, $rof) : '';
    $data['KB'] = ($bBQ2) ? self::tfGenRefGlobal($data, $declaration, $rof) : '';
    $data['KC'] = ($bBQ3) ? self::tfGenRefGlobal($data, $declaration, $rof) : '';
    // $data['FB'] = ($bVIR) ? self::tfGenRefGlobal($data, $declaration, $rof) : '';
    // $data['FC'] = ($bCHQ) ? self::tfGenRefGlobal($data, $declaration, $rof) : '';
    // $data['FD'] = ($bESP) ? self::tfGenRefGlobal($data, $declaration, $rof) : '';

    //}
    return $data;
  }


  /*
     Genere une reference pour un cheque,espece ou telereglement.

     entree :
               nPeriodes     = nb periodes -1
               nCptRef       = No ref en cours
               tDateFin      = date fin (dd/mm/yyyy)
               tSIRET_Decl   = SIRET declarant

     sortie :   fonction      = reference : TVA YYYY M/T/A mm cpt:02 SIREN 0000
  */
  public static function tfGenRefTele($nCptRef, $nPeriodes, $tDateFin, $tSIREN_Decl, Declaration $declaration, $rof) {
    if ($nPeriodes == 0) {
      $tlP = "M";
    }
    elseif ($nPeriodes <= 2) {
      $tlP = "T";
    }
    else {
      $tlP = "A";
    }

    $declaration_dectype = $declaration->getDectype();
    if ($declaration_dectype->name == "TVA 3517 SCA12") {
      $tlP = "S";
    }

    return str_pad($rof, 6, " ", STR_PAD_RIGHT)
    . substr($tDateFin, 6, 4)
    . $tlP
    . substr($tDateFin, 3, 2)
    . str_pad($nCptRef, 2, '0', STR_PAD_LEFT)
    . substr($tSIREN_Decl, 0, 9);
  }


  /*
     Genere une reference pour un virement.

     entree :
               tTypeDecl     = type de declaration
               nPeriodes     = nb periodes -1
               nCptRef       = No ref en cours
               tDateFin      = date fin (dd/mm/yyyy)
               tSIRET_Decl   = SIRET declarant

     sortie :   fonction      = reference : No_formulaire mm/3trimestre/20 YY SIREN
  */
  public static function tfGenRefVir($tDateFin, $nPeriodes, $tTypeDecl, $tSIREN_Decl, Declaration $declaration) {
    $nMois = substr($tDateFin, 3, 2); /* mois fin periode */
    if ($nPeriodes == 0) {
      $tlMM = str_pad($nMois, 2, '0', STR_PAD_LEFT);
    }
    elseif ($nPeriodes <= 2) {
      $trimestre = 1 + floor($nMois / 3);
      $tlMM = "3" . $trimestre; // TODO : a vérifier
    }
    else {
      $tlMM = "20";
    }
    return substr($tTypeDecl, 0, 4) . $tlMM . substr($tDateFin, 8, 2) . substr($tSIREN_Decl, 0, 9);

  }

  /*
    Generation d'une réference de paiement global (TVA, TS, ...)
  */
  public static function tfGenRefGlobal($data, Declaration $declaration, $rof) {
    $dectype = $declaration->getDectype();
    $code_form = $dectype->code;
    $format_date = date('mY', strtotime($data['CB'].' +1 month'));

    $code = $rof
          . '-' . $format_date
          . '-' . $code_form;

    return substr($code, 0 , 32);
  }

  public function asEditHash(){
    if($this->isLoaded()) {
      S('ctx')->data = $this->data;
      S('ctx')->fields_values = $this->fields_values;
      S('ctx')->opts = $this->opts;
    }
  }

}
