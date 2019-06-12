<?php

class Formulairecalcul {

  public static function ifCheckboxThenMultiplyFieldByPercent($args, $data, $params) {
    if (!$data[$args['checkbox']]
        && $data[$args['result_field']] != round($data[$args['field']] * $args['percent'])) {
      Formulaire::$errors[$params['form_code'] . '_' . $args['result_field']] = array(
        'msg' => 'Si ' . $params['form_code'] . '_' . $args['checkbox'] .
            ' n\'est pas coché, alors ' . $params['form_code'] . '_' . $args['result_field'] .
            ' = ' . $params['form_code'] . '_' . $args['field'] . ' * ' . $args['percent'] . ' %');
    }
  }

  public static function itemsSumAndPercent($args, $data, $params) {
    $total = 0;
    foreach ($args['items'] as $item) {
      $total += $data[$item];
    }
    $total *= $args['percent'];
    if (round($total) != $data[$args['result_field']]) {
      Formulaire::$errors[$params['form_code'] . '_' . $args['result_field']] = array(
        'msg' => $params['form_code'] . '_' . $args['result_field'] .
            ' doit être égal à (' . implode(' + ', $args['items']) . ') * ' . $args['percent'] . ' %');
    }
  }

  public static function calcul($args, $data, $params) {
    $total = 0;
    foreach ((array) $args['items'] as $item) {
      list($operateur, $field) = explode('|', $item);
      $fieldValue = is_array($data[$field]) ? $data[$field][0] : $data[$field];
      if ($operateur == '+') $total += $fieldValue;
      if ($operateur == '-') $total -= $fieldValue;
      if ($operateur == '*') $total *= $fieldValue;
      if ($operateur == '/') $total /= $fieldValue;
    }

    $total = max(0, $total);
    if ($data[$args['field_result']] != $total) {
      Formulaire::$errors[$params['form_code'] . '_' . $args['field_result']] = array('status' => 'error', 'result' => $total . ' != ' . $data[$args['field_result']]);
    }
  }

  public static function onlyOneInputFilled($args, $data, $params) {
    $items = $args['items'];
    $inputs_filleds = 0;
    foreach ($items as $item) {
      if (!empty($data[$item])) {
        $inputs_filleds++;
      }
    }
    if ($inputs_filleds > 1) {
      foreach ($items as $item) {
        Formulaire::$errors[$params['form_code'] . '_' . $item] = array('msg' => "Un seul champ peut-être rempli : " . implode(', ', $items));
      }

    }
  }

  // lié à formulaire.calcul.js : equation
  public static function equation($args, $data, $params) {
    $left = $args['left'];
    $right = $args['right'];
    $operator = $args['operator'];
    $operator = $operator ? $operator : '=';
    $total_left = 0;
    $total_right = 0;
    foreach ($left as $field) {
        $fieldValue = is_array($data[$field]) ? $data[$field][0] : $data[$field];
        $total_left += $fieldValue;
    }
    foreach ($right as $field) {
      if (!is_numeric($field)) {
        $fieldValue = is_array($data[$field]) ? $data[$field][0] : $data[$field];
        $total_right += $fieldValue;
      }
      else {
        $total_right += $field;
      }
    }


    $isEquationOK = false;
    if (($operator == '=') && ($total_left == $total_right)) {
      $isEquationOK = true;
    }
    elseif (($operator == '<') && ($total_left < $total_right)) {
      $isEquationOK = true;
    }
    elseif (($operator == '<=') && ($total_left <= $total_right)) {
      $isEquationOK = true;
    }
    elseif (($operator == '>') && ($total_left > $total_right)) {
      $isEquationOK = true;
    }
    elseif (($operator == '>=') && ($total_left >= $total_right)) {
      $isEquationOK = true;
    }    
    if (!$isEquationOK) {
      foreach (array_merge($left, $right) as $field) {
        if (!is_numeric($field)) {
          Formulaire::$errors[$params['form_code'] . '_' . $field] = array('msg' => implode(' + ', $left) . ' doit être ' . $operator . ' à ' . implode(' + ', $right));
        }
      }
    }

  }

}
