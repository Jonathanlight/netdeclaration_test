<?php

class ValidCvae {

  public static function calc_b($form_code, $opts, $data){
    foreach ($opts['results'] as $val_result){
      $result_ac = $val_result;
    }
    foreach ($opts['operands'] as $val_operands) {
      if($data[$val_operands] != 0){
        $active_operand = $val_operands;
      }
    }
    if($data[$active_operand] < 500000){
      $result = 0;
      $cible = $form_code . '_' .$result_ac;
      ValidMain::checkmatch(round($result, 2), $data[$result_ac], $cible);
    } else if($data[$active_operand] >= 500000 && $data[$active_operand] <= 3000000){
      $result = (0.5 * ($data[$active_operand] - 500000)) / 2500000;
      $cible = $form_code . '_' .$result_ac;
      ValidMain::checkmatch(round($result, 2), $data[$result_ac], $cible);
    } else if($data[$active_operand] >= 3000000 && $data[$active_operand] <= 10000000){
      $result = ((0.9 * ($data[$active_operand] - 3000000))  / 7000000)+ 0.5;
      $cible = $form_code . '_' .$result_ac;
      ValidMain::checkmatch(round($result, 2), $data[$result_ac], $cible);
    }else if($data[$active_operand] >= 10000000 && $data[$active_operand] <= 50000000){
      $result = ((0.1 * ($data[$active_operand] - 10000000)) / 40000000) + 1.4;
      $cible = $form_code . '_' .$result_ac;
      ValidMain::checkmatch(round($result, 2), $data[$result_ac], $cible);
    } else {
      $result = 1.5;
      $cible = $form_code . '_' .$result_ac;
      ValidMain::checkmatch(round($result, 2), $data[$result_ac], $cible);
    }
  }
          

  
  public static function calc_d($form_code, $opts, $data){
    foreach ($opts['results'] as $k_results => $v_results){
      $res = $v_results;
    }
    $operands = $opts['operands'];
    $checkbox = array_shift($operands); 
     foreach ($opts['operands'] as $val_operands) {
      if($data[$val_operands] != 0){
        $active_operand = $val_operands;
      }
    }
    if($data[$active_operand] <= 7600000){
      $result = $data[$active_operand] * 0.8;
    } else {
      $result = $data[$active_operand] * 0.85;
    }
    if($data[$checkbox]) {
      $result = '';
    }
    $cible = $form_code . '_' .$res;
    ValidMain::checkmatch(round($result, 2), $data[$res], $cible);
  }       

  public static function calc_e($form_code, $opts, $data){
    list($result_CA, $operandes_AC, $operandes_BA, $operandes_BB) = $opts['items'];
    if($data[$operandes_BA] <= $data[$operandes_BB]){
      $result = $data[$operandes_BA] * $data[$operandes_AC];
    } else if ($data[$operandes_BA] > $data[$operandes_BB]){
      $result = $data[$operandes_BB] * $data[$operandes_AC];
    } 
    $cible = $form_code . '_' .$result_CA;
    ValidMain::checkmatch(round($result, 2), $data[$result_CA], $cible);
  }       
  
  public static function calc_fac($form_code, $opts, $data){
    list($result_CB, $operandes_AA, $operandes_AD, $operandes_CA) = $opts['items'];
    $tab = array($operandes_AA, $operandes_AD);
    foreach ($tab as $val_operands) {
      if(!empty($data[$val_operands])){
        $active_operand = $val_operands;
      }
    }
    
    if($data[$active_operand] < 2000000){
      if($data[$operandes_CA] <= 1000){
        $result = 0;
      } else {
        $result = ($data[$operandes_CA] - 1000) * 0.5;
      }
    } else {
      $result = $data[$operandes_CA] * 0.5;
    }
    $cible = $form_code . '_' .$result_CB;
    ValidMain::checkmatch(round($result, 2), $data[$result_CB], $cible);
  }       
  
  public static function montant_cotisation($form_code, $opts, $data){
    list($operandes_AC, $operandes_BA, $operandes_BB, $operandes_BC, $result_CA) = $opts['items'];
    if($data[$operandes_BC] != 1) {      
      if($data[$operandes_BA] > $data[$operandes_BB]) {
        $result = $data[$operandes_BB] * $data[$operandes_AC] / 100;
      } else {
        $result = $data[$operandes_BA] * $data[$operandes_AC] / 100;
      }
    } else {
      $result = $data[$operandes_BA] * $data[$operandes_AC] / 100;
    }
    $cible = $form_code . '_' .$result_CA;
    //ValidMain::checkmatch(round($result, 2), $data[$result_CA], $cible);
  }   


   

  
  public static function calc_f($form_code, $opts, $data){
    list($result_CB, $operandes_AA, $operandes_CA) = $opts['items'];
    if($data[$operandes_AA] < 2000000){
      if($data[$operandes_CA] <= 1000){
        $result = 0;
      } else {
        $result = $data[$operandes_CA] - 1000;
      }
    } else {
      $result = $data[$operandes_CA];
    }
    $cible = $form_code . '_' .$result_CB;
    ValidMain::checkmatch(round($result, 2), $data[$result_CB], $cible);
  }   
  
  public static function cotisation_minimum($form_code, $opts, $data){
    list($AA, $AD, $EA, $CB, $DA, $DB) = $opts['items'];
    $total = 0;
    $value = $data[$AA] > 0 ? $data[$AA] : $data[$AD];
    if ($value > 500000) {
      $total = max(250, ($data[$CB] - $data[$DA] - $data[$DB]));
    }
    ValidMain::checkmatch(round($total, 2), $data[$EA], $form_code.'_'.$EA);
  }
  
  /*cotisationAvantReduction: function(elt, num){
    var itemsArray = $(elt).getAttribute('data-cotisation-avant-reduction-items'+num).split(',');
    var result_CB = $(itemsArray[0]);
    var AA = $(itemsArray[1]);
    var CA = $(itemsArray[2]);
    var total;
    if(parseFloat(AA.value) < 2000000 && parseFloat(CA.value) <= 1000){
      total = 0;
      NTD.Control.setValue(result_CB, parseFloat(total), true);
    } else if(parseFloat(AA.value) < 2000000 && parseFloat(CA.value) > 1000){
      total = parseFloat(CA.value) - 1000;
      NTD.Control.setValue(result_CB, parseFloat(total), true);
    } else if(parseFloat(AA.value) >= 2000000){
      total = parseFloat(CA.value);
      NTD.Control.setValue(result_CB, parseFloat(total), true);
    }
  },*/
  
  public static function cotisation_avant_reduction($form_code, $opts, $data){
    list($CB, $AA, $CA) = $opts['items'];
    if($data[$AA] < 2000000 && $data[$CA] <= 1000){
      $result = 0;
    } else if($data[$AA] < 2000000 && $data[$CA] > 1000){
      $result = $data[$CA] - 1000;
    } else if($data[$AA] >= 2000000){
      $result = $data[$CA];
    }
    $cible = $form_code . '_' .$CB;
    ValidMain::checkmatch(round($result, 2), $data[$CB], $cible);
  }
  
  public static function frais_gestion($form_code, $opts, $data){
    list($result_CI, $operandes_CH) = $opts['items'];
    $result = $data[$operandes_CH] * 0.01;
    $cible = $form_code . '_' .$result_CI;
    ValidMain::checkmatch(round($result, 2), $data[$result_CI], $cible);
  }
}

