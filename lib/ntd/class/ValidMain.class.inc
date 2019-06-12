<?php

class ValidMain {

  static $ValidClasses = array(
    __CLASS__, 'ValidCvae', 'ValidIs', 'ValidTs', 'ValidTva'
  );

  public static function checkmatch($php_result, $data_result, $cible) {
    if ($php_result < 0) {
      $php_result = 0;
    }
    if (round($php_result) != round($data_result)) {
      Formulaire::$errors[$cible] = array('status' => 'error', 'result' => $php_result);
    }
  }


  /*********************************************** GENERIC ********************************************************/

  public static function must_be_strictly_positive($form_code, $opts, $data, $params) {
    if (!($data[$params['current_field']] > 0)) {
      Formulaire::$errors[$form_code . '_' . $params['current_field']] = array('status' => 'not_positiv');
    }
  }

  public static function must_be_strictly_inferior($form_code, $opts, $data, $params) {
    if (!($data[$params['current_field']] < $data[$opts['field']])) {
      $cible = $form_code . '_' . $params['current_field'];
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior', 'field1' => $params['current_field'], 'field2' => $opts['field']);
    }
  }

  public static function must_be_inferior_or_egal($form_code, $opts, $data, $params) {
    if (!($data[$params['current_field']] <= $data[$opts['field']])) {
      $cible = $form_code . '_' . $params['current_field'];
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $params['current_field'], 'field2' => $opts['field']);
    }
  }

  public static function addition($form_code, $opts, $data) {
    $res = $opts['results'][0];
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ? $data[$v_operands][0] : $data[$v_operands];
      $result += $fieldValue;
    }

    $cible = strpos($res, '_') > 0 ? $res : $form_code . '_' . $res;
    self::checkmatch($result, $data[$res], $cible);
  }

  public static function soustraction($form_code, $opts, $data) {
    foreach ($opts['results'] as $k_results => $v_results) {
      $res = $v_results;
    }

    $value = is_array($data[$opts['value']]) ? $data[$opts['value']][0] : $data[$opts['value']];
    $min_value = is_array($opts['args']) && count($opts['args']) > 0 ? $opts['args'][0] : 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ? $data[$v_operands][0] : $data[$v_operands];
      $value -= $fieldValue;
      if ($value < $min_value) {
        $value = $min_value;
      }
    }
    $cible = $form_code . '_' . $res;
    self::checkmatch($value, $data[$res], $cible);
  }

  public static function multiplication($form_code, $opts, $data) {
    foreach ($opts['results'] as $k_results => $v_results) {
      $res = $v_results;
    }
    $result = 1;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ? $data[$v_operands][0] : $data[$v_operands];
      $result *= $fieldValue;
    }
    $cible = $form_code . '_' . $res;
    self::checkmatch($result, $data[$res], $cible);
  }

  /*public static function format_mm($form_code, $opts, $data){
    foreach ($opts['items'] as $v){
      $month = substr($data[$v], 0, 2);
      if(strlen($data[$opts['items']]) != 2) {
        $cible = $form_code . '_' .$v;
        Formulaire::$errors[$cible] = array('status' => 'error_length_date');
      }
      if($month < 1 || $month > 12){
        $cible = $form_code . '_' .$v;
        Formulaire::$errors[$cible] = array('status' => 'error_value_date');
      } else {
        if(Formulaire::$cast == true){
          $data[$v] = $month;
        }
      }
    }
  }  */

  public static function format_mmaa($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    if (empty($data[$current_field])) return;
    if (is_array($data[$current_field])) $data[$current_field] = $data[$current_field][0];


    if (strlen($data[$current_field]) != 7) return;
    $timestamp = mktime(0, 0, 1, (int) (substr($data[$current_field], 0, 2)), 15, (int) (substr($data[$current_field], 3, 4)));
    if ($timestamp > 0) {
      $date = date("Ym", $timestamp);
      //$siecle = (int) ((date("Y", $timestamp) / 100) + 1);
      //$data[$v] = $siecle . $date;
      $data[$current_field] = $date;
    }

  }

  public static function format_back_mmaa($registered_date) {
    if (empty($registered_date)) return $registered_date;
    //$year = ((int) substr($registered_date, 0, 2) - 1) . (int) substr($registered_date, 2, 2);
    $year = (int) substr($registered_date, 0, 4);
    $timestamp = mktime(0, 0, 0, (int) substr($registered_date, 4, 2), 15, $year);
    $date = date("m/Y", $timestamp);
    return $date;
  }

  public static function format_jjmmaa($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    if (empty($data[$current_field])) return;

    $date = Date::asHash($data[$current_field]);
    $timestamp = $date['ts'];
    if ($timestamp > 0 || $timestamp < 0) {
      $date = date("Ymd", $timestamp);
      //$siecle = (int) ((date("Y", $timestamp) / 100) + 1);
      //$data[$v] = $siecle . $date;
      $data[$current_field] = $date;
    } else {
      $cible = $form_code . '_' . $current_field;
      Formulaire::$errors[$cible] = array('status' => 'error_value_date');
    }

  }

  public static function format_back_jjmmaa($registered_date) {
    if (empty($registered_date)) return $registered_date;
    //$year = ((int) substr($registered_date, 0, 2) - 1) . (int) substr($registered_date, 2, 2);
    $year = (int) substr($registered_date, 0, 4);
    $timestamp = mktime(0, 0, 0, (int) substr($registered_date, 4, 2), (int) substr($registered_date, 6, 2), $year);
    $date = date("d/m/Y", $timestamp);
    return $date;
  }

  public static function format_jjmm($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    if (empty($data[$current_field])) return;

    $date = Date::asHash($data[$current_field]);
    $timestamp = $date['ts'];
    if ($timestamp > 0) {
      $date = date("Ymd", $timestamp);
      $data[$current_field] = $date;
    } else {
      $cible = $form_code . '_' . $current_field;
      Formulaire::$errors[$cible] = array('status' => 'error_value_date');
    }
  }

  public static function format_back_jjmm($registered_date) {
    if (empty($registered_date)) return $registered_date;
    $timestamp = mktime(0, 0, 0, (int) substr($registered_date, 4, 2), (int) substr($registered_date, 6, 2), date('Y'));
    $date = date("d/m/Y", $timestamp);
    return $date;
  }

  /*public static function format_jjmmaa($form_code, $opts, $data){
    foreach ($opts['items'] as $v){
      $day = substr($data[$v], 0, 2);
      $month = substr($data[$v], 2, 2);
      $year = substr($data[$v], 4, 7);
      if(strlen($data[$opts['items']]) != 6) {
        $cible = $form_code . '_' .$v;
        Formulaire::$errors[$cible] = array('status' => 'error_length_date');
      }
      if($day < 1 || $day > 31 || $month < 1 || $month > 12){
        $cible = $form_code . '_' .$v;
        Formulaire::$errors[$cible] = array('status' => 'error_value_date');
      } else {
        if(Formulaire::$cast == true){
          $siecle = substr($year, 0, 2) + 1;
          $new_year =  substr($year, 2, 2);
          $data[$v] = $siecle.$month.$new_year;
        }
      }
    }
  }*/

  public static function format_integer($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    foreach ($data as $key => $value) {
      list ($field, $index) = explode('/', $key);
      if ($field != $params['current_field']) continue ;
      $cible = $form_code . '_' . $key;
      if (is_array($value)) {
          $value = $value[0];
      }
      if ($value < 0) {
        Formulaire::$errors[$cible] = array('status' => 'not_negatif', 'field1' => $field.$index);
      }
      elseif (strpos($value, ',') > 0 || strpos($value, '.') > 0) {
        Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero_integer', 'field1' => $field.$index);
      }
    }
  }

  public static function check_positiv($form_code, $opts, $data) {
    $item1 = $opts['items'][0];
    $item2 = $opts['items'][1];

    if (($data[$item1] > 0) && (empty($data[$item2]) || $data[$item2] == 0)) {
      $cible = $form_code . '_' . $item2;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv');
    } else if (($data[$item2] > 0) && (empty($data[$item1]) || $data[$item1] == 0)) {
      $cible = $form_code . '_' . $item1;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv');
    }
  }

  public static function check_set_empty($form_code, $opts, $data) {
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] == 1) {
        foreach ($opts['results'] as $key_results => $value_results) {
          if (!empty($data[$value_results])) {
            Formulaire::$tests[$cible] = array('status' => 'not_empty_because_checked', 'operand' => $value_operands);
            Formulaire::$errors[$cible] = array('status' => 'not_empty_because_checked', 'operand' => $value_operands);
          }
        }
      }
    }
  }

  //public static function check_need_and_or($form_code, $opts, $data) {
  //public static function control_if_at_least_one_checkbox_checked_then_all_results_must_be_filled($form_code, $opts, $data) {
  public static function check_need_and_or($form_code, $opts, $data) { //control_any_operands_all_results_required
    $has_one_operands = false;
    foreach ($opts['operands'] as $operand) {
      if ($data[$operand] > 0) {
        $has_one_operands = true;
        break;
      }
    }
    if ($has_one_operands) {
      foreach ($opts['results'] as $result) {
        if (!(isset($data[$result]) && strlen($data[$result]))) {
          $cible = $form_code . '_' . $result;
          Formulaire::$errors[$cible] = array('msg' => 'Ce champ est requis.');
        }
      }
    }
  }

  public static function check_uneed_and_or($form_code, $opts, $data) {
    $checked = NULL;
    $isFilled = NULL;
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] == 1) {
        $checked = true;
      }
    }
    if ($checked) {
      $isFilled = true;
      foreach ($opts['results'] as $key_results => $value_results) {
        if (empty($data[$value_results])) {
          $isFilled = false;
        }
      }
      if ($isFilled) {
        foreach ($opts['results'] as $key_results => $value_results) {
          $cible = $form_code . '_' . $value_results;
          Formulaire::$tests[$cible] = array('status' => 'uneeded');
          Formulaire::$errors[$cible] = array('status' => 'uneeded');
        }
      }
    }
  }

  public static function check_percent($form_code, $opts, $data) {
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ? $data[$v_operands][0] : $data[$v_operands];
      if (!empty($fieldValue) && ($fieldValue <= 0) || ($fieldValue > 100)) {
        $cible = $form_code . '_' . $v_operands;
        Formulaire::$errors[$cible] = array('status' => 'not_percent');
      }
    }
  }

  public static function check_inf($form_code, $opts, $data) { // TODO : non utilisée ???
    foreach ($opts['results'] as $k_results => $v_results) {
      $res = $v_results;
    }
    list($operande1, $operande2) = $opts['operands'];
    if ($data[$operande1] >= $data[$operande2]) {
      $cible = $form_code . '_' . $res;
      Formulaire::$tests[$cible] = array('status' => 'must_be_strictly_inferior', 'field1' => $operande1, 'field2' => $operande2);
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior', 'field1' => $operande1, 'field2' => $operande2);
    }
  }

  public static function check_inf_egal($form_code, $opts, $data) {
    foreach ($opts['results'] as $k_results => $v_results) {
      $res = $v_results;
    }
    list($operande1, $operande2) = $opts['operands'];
    if ($data[$operande1] > $data[$operande2]) {
      $cible = $form_code . '_' . $res;
      Formulaire::$tests[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $operande1, 'field2' => $operande2);
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $operande1, 'field2' => $operande2);
    }
  }

  public static function check_positiv_set_empty($form_code, $opts, $data) {
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ? $data[$v_operands][0] : $data[$v_operands];
      if ($fieldValue > 0) {
        foreach ($opts['results'] as $k_results => $v_results) {
          if (!empty($data[$v_results])) {
            $cible = $form_code . '_' . $v_results;
            Formulaire::$tests[$cible] = array('status' => 'not_empty', 'operand' => $v_operands);
            Formulaire::$errors[$cible] = array('status' => 'not_empty', 'operand' => $v_operands);
          }
        }
      }
    }
  }

  public static function check_positiv_zero($form_code, $opts, $data) {
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] >= 0) {
        foreach ($opts['results'] as $key_results => $value_results) {
          if (!$data[$value_results] < 0) {
            $cible = $form_code . '_' . $value_results;
            Formulaire::$tests[$cible] = array('status' => 'not_positiv_or_zero');
            Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero');
          }
        }
      }
    }
  }


  public static function check_positiv_set_full($form_code, $opts, $data) {
    $areFilled = true;
    foreach ($opts['operands'] as $value_operands) {
      if ($data[$value_operands] > 0) {
        foreach ($opts['results'] as $key_results => $value_results) {
          if (empty($data[$value_results])) {
            $areFilled = false;
          }
        }
        if ($areFilled == false) {
          foreach ($opts['results'] as $key_results => $value_results) {
            $cible = $form_code . '_' . $value_results;
            Formulaire::$tests[$cible] = array('status' => 'has_to_be_filled', 'operand' => $value_operands, 'field1' => $value_operands, 'field2' => $value_results);
            Formulaire::$errors[$cible] = array('status' => 'has_to_be_filled', 'operand' => $value_operands, 'field1' => $value_operands, 'field2' => $value_results);
          }
        }
      }
    }
  }

  public static function check_positiv_zero_set_full($form_code, $opts, $data) {
    $areFilled = true;
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] >= 0) {
        foreach ($opts['results'] as $key_results => $value_results) {
          if (empty($data[$value_results])) {
            $areFilled = false;
          }
        }
        if ($areFilled == false) {
          foreach ($opts['results'] as $key_results => $value_results) {
            $cible = $form_code . '_' . $value_results;
            Formulaire::$tests[$cible] = array('status' => 'has_to_be_filled_zero', 'operand' => $value_operands);
            Formulaire::$errors[$cible] = array('status' => 'has_to_be_filled_zero', 'operand' => $value_operands);
          }
        }
      }
    }
  }

  public static function check_positiv_zero_set_zero($form_code, $opts, $data) {
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] >= 0) {
        foreach ($opts['results'] as $key_results => $value_results) {
          if ($data[$value_results] != 0) {
            $cible = $form_code . '_' . $value_results;
            Formulaire::$tests[$cible] = array('status' => 'must_be_zero');
            Formulaire::$errors[$cible] = array('status' => 'must_be_zero');
          }
        }
      }
    }
  }

  public static function check_full_set_zero($form_code, $opts, $data) {
    foreach ($opts['results'] as $key_results => $value_results) {
      if (!empty($data[$value_results])) {
        foreach ($opts['operands'] as $key_operands => $value_operands) {
          if ($data[$value_results] != 0) {
            $cible = $form_code . '_' . $value_operands;
            Formulaire::$tests[$cible] = array('status' => 'must_be_zero');
            Formulaire::$errors[$cible] = array('status' => 'must_be_zero');
          }
        }
      }
    }
  }

  public static function check_null_or_zero_set_zero($form_code, $opts, $data) {
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] == 0 || empty($data[$value_operands])) {
        foreach ($opts['results'] as $key_results => $value_results) {
          if ($data[$value_results] != 0) {
            $cible = $form_code . '_' . $value_results;
            Formulaire::$tests[$cible] = array('status' => 'must_be_zero');
            Formulaire::$errors[$cible] = array('status' => 'must_be_zero');
          }
        }
      }
    }
  }

  public static function check_null_or_zero_set_null_or_zero($form_code, $opts, $data) {
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] == 0 || empty($data[$value_operands])) {
        foreach ($opts['results'] as $key_results => $value_results) {
          if ($data[$value_results] != 0 || !empty($data[$value_results])) {
            $cible = $form_code . '_' . $value_results;
            Formulaire::$tests[$cible] = array('status' => 'must_be_zero_or_empty');
            Formulaire::$errors[$cible] = array('status' => 'must_be_zero_or_empty');
          }
        }
      }
    }
  }


  public static function check_full($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    if (empty($data[$current_field])) return;
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if (empty($data[$value_operands])) {
        $cible = $form_code . '_' . $value_operands;
        Formulaire::$errors[$cible] = array('status' => 'required', 'operand' => $value_operands);
      }
    }
  }

  public static function report($form_code, $opts, $data) {
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      foreach ($opts['results'] as $key_results => $value_results) {
        if ($data[$value_operands] != $data[$value_results]) {
          $cible = $form_code . '_' . $value_results;
          Formulaire::$errors[$cible] = array('status' => 'must_be_same_result', 'operand' => $value_operands);
        }
      }
    }
  }

  public static function check_sup_egal_150($form_code, $opts, $data) {
    foreach ($opts['operands'] as $key_operands => $value_operands) {
      if ($data[$value_operands] < 150) {
        foreach ($opts['results'] as $key_results => $value_results) {
          $cible = $form_code . '_' . $value_results;
          Formulaire::$tests[$cible] = array('status' => 'sup_or_egal_150', 'operand' => $value_operands);
          Formulaire::$errors[$cible] = array('status' => 'sup_or_egal_150', 'operand' => $value_operands);
        }
      }
    }
  }

  public static function check_bic($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    if (empty($data[$current_field])) return;
    $cible = $form_code . '_' . $params['current_field'];
    if (!Valid::isBicCode($data[$current_field])) {
      Formulaire::$errors[$cible] = array('status' => 'not_bic', 'field1' => $params['current_field']);
    }
  }

  public static function check_iban($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    if (empty($data[$current_field])) return;
    $cible = $form_code . '_' . $params['current_field'];
    if (!Valid::isIBan($data[$current_field], 'FR')) {
      Formulaire::$errors[$cible] = array('status' => 'not_iban', 'field1' => $params['current_field']);
    }
  }

  public static function check_email($form_code, $opts, $data, $params) {
    $current_field = $params['current_field'];
    if (empty($data[$current_field])) return;

    if (!Email::isValid($data[$current_field])) {
      $cible = $form_code . '_' . $current_field;
      Formulaire::$errors[$cible] = array('status' => 'error_value_email');
    }
  }

  /* ----- T-IDENTIF ----- */
  public static function kf_required_in_3514($form_code, $opts, $data, $params) {
    if ($params['declaration_formulairetype']->code == '3514') {
      if (empty($data[$params['current_field']])) {
        $cible = $form_code . '_' . $params['current_field'] . '-controls-container';
        Formulaire::$errors[$cible] = array('status' => 'required');
      }
    }
  }


  public static function need_iban_if_amount($form_code, $opts, $data, $params) {
    $amount_field = $opts['items'][0];
    $iban_field = $opts['items'][1];
    if ($data[$amount_field] > 0 && empty($data[$iban_field])) {
      $cible = $form_code . '_' . $iban_field;
      Formulaire::$errors[$cible] = array('status' => 'need_iban_if_amount');
    }
  }


  // don't have JS function
  public static function isFieldRequired($form_code, $opts, $data, $params) {
    $field = $params['current_field'];
    $items = $opts['items'];
    $is_required = $opts['is_required'];

    $conditions = array();
    foreach ($items as $field_code => $values) {
      $conditions[] = $field_code . " ".(!$opts['is_required'] ? 'égal à ' : 'différent de ')." : " . implode(", ", $values);
      foreach ((array) $values as $value) {
        if ($data[$field_code] == $value) {
          $is_required = !$opts['is_required'];
        }
      }
    }
    if ($is_required && empty($data[$field])) {
      Formulaire::$errors[$form_code . '_' . $field] = array('msg' => "Champ $field ".($opts['is_required'] ? 'requis' : 'non requis')." <br />SI " . implode(' OU ', $conditions));
    }
  }



}
