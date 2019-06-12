<?php

class ValidTs {

  public static function calcul_425($form_code, $opts, $data){
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands){
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.0425;
    }
    $cible = $form_code . '_' .$res;
    ValidMain::checkmatch(round($result), $data[$res], $cible);
  }

  public static function calcul_935($form_code, $opts, $data){
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands){
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.0935;
    }
    $cible = $form_code . '_' .$res;
    ValidMain::checkmatch(round($result), $data[$res], $cible);
  }

  public static function calcul_295($form_code, $opts, $data){
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands){
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.0295;
    }
    $cible = $form_code . '_' .$res;
    ValidMain::checkmatch(round($result), $data[$res], $cible);
  }

  public static function calcul_255($form_code, $opts, $data){
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands){
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.0255;
    }
    $cible = $form_code . '_' .$res;
    ValidMain::checkmatch(round($result), $data[$res], $cible);
  }

  public static function calcul_1575($form_code, $opts, $data){
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands){
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.1575;
    }
    $cible = $form_code . '_' .$res;
    ValidMain::checkmatch(round($result), $data[$res], $cible);
  }

  public static function multpercent($form_code, $opts, $data){
      if (count($opts['results'])  == 1) {
          $res = $opts['results'][0];
      } else {
          foreach ($opts['results'] as $k_results => $v_results){
              $res = $v_results;
          }
      }

    $toOperate = $opts['value'];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands){
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $operandValue = is_array($data[$toOperate]) ?  $data[$toOperate][0] :  $data[$toOperate];
      $result = $operandValue * $fieldValue;
    }
    $result = $result / 100;
    $cible = $form_code . '_' .$res;
    ValidMain::checkmatch(round($result, 2), $data[$res], $cible);
  }


  public static function franchise_decote($form_code, $opts, $data){
    list($result_FA, $result_FB, $operandes_EM) = $opts['items'];
    $cible_FA = $form_code . '_' .$result_FA;
    $cible_FB = $form_code . '_' .$result_FB;
    if($data[$operandes_EM] < 840){
      $total_FA = $data[$operandes_EM];
      ValidMain::checkmatch($total_FA, $data[$result_FA], $cible_FA);
      $total_FB = 0;
      ValidMain::checkmatch($total_FB, $data[$result_FB], $cible_FB);
    } else if($data[$operandes_EM] > 840 && $data[$operandes_EM] <= 1680){
      $total_FA = 0;
      ValidMain::checkmatch($total_FA, $data[$result_FA], $cible_FA);
      $total_FB = ((1680 - $data[$operandes_EM]) * 3) / 4;
      ValidMain::checkmatch($total_FB, $data[$result_FB], $cible_FB);
    } else {
      $total_FA = 0;
      ValidMain::checkmatch($total_FA, $data[$result_FA], $cible_FA);
      $total_FB = 0;
      ValidMain::checkmatch($total_FB, $data[$result_FB], $cible_FB);
    }
  }

  public static function franchise_decote_201412($form_code, $opts, $data){
    list($result_FA, $result_FB, $operandes_EM) = $opts['items'];
    $cible_FA = $form_code . '_' .$result_FA;
    $cible_FB = $form_code . '_' .$result_FB;
    if($data[$operandes_EM] < 1200){
      $total_FA = $data[$operandes_EM];
      ValidMain::checkmatch($total_FA, $data[$result_FA], $cible_FA);
      $total_FB = 0;
      ValidMain::checkmatch($total_FB, $data[$result_FB], $cible_FB);
    } else if($data[$operandes_EM] > 1200 && $data[$operandes_EM] <= 2040){
      $total_FA = 0;
      ValidMain::checkmatch($total_FA, $data[$result_FA], $cible_FA);
      $total_FB = ((2040 - $data[$operandes_EM]) * 3) / 4;
      ValidMain::checkmatch($total_FB, $data[$result_FB], $cible_FB);
    } else {
      $total_FA = 0;
      ValidMain::checkmatch($total_FA, $data[$result_FA], $cible_FA);
      $total_FB = 0;
      ValidMain::checkmatch($total_FB, $data[$result_FB], $cible_FB);
    }
  }

  public static function abattement($form_code, $opts, $data){
    list($result_FC, $operandes_EM, $operandes_FA,  $operandes_FB) = $opts['items'];
    $operande_array = array($operandes_FA,  $operandes_FB);
    $cible = $form_code . '_' .$result_FC;
    foreach ($operande_array as $val_operands) {
      if($data[$val_operands] != 0){
        $active_operand = $val_operands;
      }
    }
    if(($data[$operandes_EM] - $data[$active_operand]) < 5453){
      $result = $data[$operandes_EM] - $data[$active_operand];
      ValidMain::checkmatch($result, $data[$result_FC], $cible);
    } else {
      $result = 5453;
      ValidMain::checkmatch($result, $data[$result_FC], $cible);
    }
    if($data[$result_FC] == 6002){
      $result = 0;
      ValidMain::checkmatch($result, $data[$result_FC], $cible);
    }
  }

  public static function abattement_201412($form_code, $opts, $data){
    list($result_FC, $operandes_EM, $operandes_FA,  $operandes_FB) = $opts['items'];
    $operande_array = array($operandes_FA,  $operandes_FB);
    $cible = $form_code . '_' .$result_FC;
    foreach ($operande_array as $val_operands) {
      if($data[$val_operands] != 0){
        $active_operand = $val_operands;
      }
    }
    if(($data[$operandes_EM] - $data[$active_operand]) < 20161){
      $result = $data[$operandes_EM] - $data[$active_operand];
      ValidMain::checkmatch($result, $data[$result_FC], $cible);
    } else {
      $result = 20161;
      ValidMain::checkmatch($result, $data[$result_FC], $cible);
    }
    if($data[$result_FC] == 20161){
      $result = 0;
      ValidMain::checkmatch($result, $data[$result_FC], $cible);
    }
  }

  public static function taxe_nette_due($form_code, $opts, $data){
    list($result_FD, $operandes_EM, $operandes_FA,  $operandes_FB, $operandes_FC) = $opts['items'];
    $operande_array = array($operandes_FA,  $operandes_FB);
    $cible = $form_code . '_' .$result_FD;
    foreach ($operande_array as $val_operands) {
      if($data[$val_operands] != 0){
        $active_operand = $val_operands;
      }
    }

    $operandeEm = is_array($data[$operandes_EM]) ? $data[$operandes_EM][0] : $data[$operandes_EM];
    $activeOperande = is_array($data[$active_operand]) ? $data[$active_operand][0] : $data[$active_operand];
    $operandeFc = is_array($data[$operandes_FC]) ? $data[$operandes_FC][0] : $data[$operandes_FC];

    $result = ($operandeEm - ($activeOperande + $operandeFc));
    ValidMain::checkmatch($result, $data[$result_FD], $cible);
  }

  public static function ts_value_percent($form_code, $opts, $data){
    list($item1, $item2) = $opts['items'];
    $fieldValue = is_array($data[$item2]) ? $data[$item2][0] : $data[$item2];

    if($fieldValue < 0 || $fieldValue > 100) {
      $cible = $form_code . '_' .$item2;
      Formulaire::$errors[$cible] = array('status' => 'not_percent');
    }
  }
}
