<?php

class ValidTva {

  /***********************  TVA3310A  *************************/

  public static function calcul_090($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.009;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_210($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.021;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_550($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.055;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_800($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.08;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_850($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.085;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_1300($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.13;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_1960($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.196;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_105($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.0105;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_175($form_code, $opts, $data) {
    $res = $opts['results'][0];
    $result = 0;
    foreach ($opts['operands'] as $k_operands => $v_operands) {
      $fieldValue = is_array($data[$v_operands]) ?  $data[$v_operands][0] :  $data[$v_operands];
      $result = $fieldValue * 0.0175;
    }
    $cible = $form_code.'_'.$res;
    ValidMain::checkmatch($result, $data[$res], $cible);
  }

  public static function calcul_percent($form_code, $opts, $data, $params) {
    $result = $opts['results'][0];
    $percent = $opts['percent'];

    $total = round($data[$params['current_field']] * ($percent / 100));

    $cible = $form_code.'_'.$result;
    ValidMain::checkmatch($total, $data[$result], $cible);
  }

  /************************ 3515sd ***********************************/

  public static function integrity_ca_3515sd($form_code, $opts, $data) {
    list($CA, $BD) = $opts['items'];
    $cible = $form_code.'_'.$CA;
    if ($data[$CA] < $data[$BD]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_superior_or_egal', 'field1' => $CA, 'field2' => $BD); // TODO : $cible n'existe pas
    }
  }

  public static function report_BC_BD($form_code, $opts, $data) {
    list($CB, $CA, $BC, $BD) = $opts['items'];
    $cible = $form_code.'_'.$CB;
    if ($data[$BC] < $data[$BD]) {
      ValidMain::checkmatch($data[$BD], $data[$CA], $cible);
    } else if ($data[$BC] > $data[$BD]) {
      ValidMain::checkmatch($data[$BC], $data[$CB], $cible);
    } else {
      Formulaire::$errors[$cible] = array('status' => 'report_BC_BD');
    }
  }

  public static function soustraction_da_db_3515sd($form_code, $opts, $data) {
    list($DC, $DD, $DA, $DB) = $opts['items'];
    $cible_DC = $form_code.'_'.$DC;
    $cible_DD = $form_code.'_'.$DD;
    $result = $data[$DA]-$data[$DB];
    if ($result < 0) {
      $result_2 = 0;
      ValidMain::checkmatch(abs($result), $data[$DD], $cible_DD);
      ValidMain::checkmatch($result_2, $data[$DC], $cible_DC);
    } else if ($result > 0) {
      ValidMain::checkmatch(abs($result), $data[$DC], $cible_DC);
      ValidMain::checkmatch($result_2, $data[$DD], $cible_DD);
    } else {
      ValidMain::checkmatch($result_2, $data[$DC], $cible_DC);
      ValidMain::checkmatch($result_2, $data[$DD], $cible_DD);
    }
  }

  /************************ 3519 ***********************************/

  public static function integrity_fg($form_code, $opts, $data) {
    if ($data['DN'] > 0) return; // mantis 22708
    list($FG, $FC, $FE, $FF, $DH) = $opts['items'];
    $active_operand = ($data[$FE] >= $data[$FF]) ? $FE : $FF;

    if ($data[$FC] > $data[$active_operand]) {
      $cible = $form_code.'_'.$FC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior', 'field1' => $FC, 'field2' => $active_operand);
    }
    if ($data[$FG] == $data[$FF] && !($data[$FG] < $data[$FE])) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior', 'field1' => $FG, 'field2' => $FE);
    }
    if ($data[$FG] == $data[$FE] && !($data[$FG] < $data[$FF])) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior', 'field1' => $FG, 'field2' => $FF);
    }
    if (!empty($data[$FG]) && $data[$FG] != min($data[$FE], $data[$FF])) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'integrity_3519_fg_1');
    }
    if ($data[$FG] >= 0 && $data[$FG] != $data[$DH]) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'integrity_3519_fg_2');
    }
  }

  public static function integrity_3519($form_code, $opts, $data) {
    if (empty($data['DD']) && empty($data['DE']) && empty($data['DF'])) {
      $cible = $form_code.'_DD';
      Formulaire::$errors[$cible] = array('status' => 'must_be_checked');
    }
    if (empty($data['DI']) && empty($data['DJ']) && empty($data['DK'])) {
      $cible = $form_code.'_DK';
      Formulaire::$errors[$cible] = array('status' => 'must_be_checked');
    }
  }

  public static function integrity_3519_20140101($form_code, $opts, $data) {
    if (empty($data['DD']) && empty($data['DE']) && empty($data['DF'])) {
      $cible = $form_code.'_DD';
      Formulaire::$errors[$cible] = array('status' => 'must_be_checked');
    }
    if (empty($data['DI']) && empty($data['DJ']) && empty($data['DK'])) {
      $cible = $form_code.'_DK';
      Formulaire::$errors[$cible] = array('status' => 'must_be_checked');
    }
    if ($data['DH'] != $data['DN']) {
      $cible = $form_code.'_DN';
      Formulaire::$errors[$cible] = array('status' => 'integrity_3519');
    }
  }

  /************************ 3525bis ***********************************/

  public static function integrity_bc_3525bis($form_code, $opts, $data) {
    list($BC, $BB) = $opts['items'];
    if (!empty($data[$BB]) && !empty($data[$BC])) {
      if ($data[$BC] > $data[$BB]) {
        $cible = $form_code.'_'.$BC;
        Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $BC, 'field2' => $BB);
      }
    }
  }

  public static function disable_all_3525bis($form_code, $opts, $data) {
    $BE = array_shift($opts['items']);
    if ($data[$BE] == 1) {
      foreach ($opts['items'] as $value) {
        if (!empty($data[$value])) {
          $cible = $form_code.'_'.$value;
          Formulaire::$errors[$cible] = array('status' => 'not_empty_because_checked', 'operand' => $BE);
        }
      }
    }
  }

  /*************************** ter **********************************/

  public static function calcul_qm($form_code, $opts, $data) {
    list($QM, $QL, $SL, $RL) = $opts['items'];
    $cible = $form_code.'_'.$QM;
    /*if(empty($data[$QL]) || empty($data[$SL]) || empty($data[$RL])) {
      $result = 0;
      ValidMain::checkmatch($result, $data[$QM], $cible);
    } else {*/
    $result = $data[$QL]+$data[$SL]-$data[$RL];
    //ValidMain::checkmatch($result, $data[$QM], $cible);
    if ($result < 0) {
      $result = 0;
      ValidMain::checkmatch($result, $data[$QM], $cible);
    } else {
      ValidMain::checkmatch($result, $data[$QM], $cible);
    }
    //}
  }

  public static function calcul_rm($form_code, $opts, $data) {
    list($RM, $RL, $QL, $SL) = $opts['items'];
    $cible = $form_code.'_'.$RM;

    /*if(empty($data[$RL]) || empty($data[$QL]) || empty($data[$SL])) {
    $result = 0;
    ValidMain::checkmatch($result, $data[$RM], $cible);
  } else {*/
    $result = $data[$RL]-($data[$QL]+$data[$SL]);
    //ValidMain::checkmatch($result, $data[$RM], $cible);
    if ($result < 0) {
      $result = 0;
      ValidMain::checkmatch($result, $data[$RM], $cible);
    } else {
      ValidMain::checkmatch($result, $data[$RM], $cible);
    }
    //}
  }

  /*************************** 3310CA3 **********************************/

  public static function integrity_cc($form_code, $opts, $data) {
    list($CC, $GJ) = $opts['items'];
    if ($data[$CC] < $data[$GJ]) {
      $cible = $form_code.'_'.$CC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_superior_or_egal', 'field1' => $CC, 'field2' => $GJ);
    }
    if ($data[$CC] > 0) {
      if (!($data[$GJ] > 0)) {
        Formulaire::$errors['tva3310ca3_GJ'] = array('msg' => 'si 3310CA3_CC > 0 alors 3310CA3_GJ > 0 ');
        Formulaire::$errors['tva3310ca3_CC'] = array('msg' => 'si 3310CA3_CC > 0 alors 3310CA3_GJ > 0 ');
      }
    }
  }

  public static function integrity_cd($form_code, $opts, $data) {
    list($CD, $CC) = $opts['items'];
    if ($data[$CD] > 0 && $data[$CD] > $data[$CC]) {
      $cible = $form_code.'_'.$CD;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $CD, 'field2' => $CC);
    }
  }

  public static function integrity_ce($form_code, $opts, $data) {
    list($CE, $HH) = $opts['items'];
    if ($data[$HH] > 0 && $data[$CE] <= 0) {
      $cible = $form_code.'_'.$CE;
      Formulaire::$errors[$cible] = array('status' => 'has_to_be_filled_zero', 'field1' => $HH, 'field2' => $CE);
    }
  }

  public static function integrity_gh_gj($form_code, $opts, $data) {
    list($GH, $GJ) = $opts['items'];
    if ($data[$HH] > 0 && $data[$CE] <= 0) {
      $cible = $form_code.'_'.$CE;
      Formulaire::$errors[$cible] = array('status' => 'has_to_be_filled_zero', 'field1' => $CE, 'field2' => $HH);
    }
  }

  public static function integrity_gc($form_code, $opts, $data) {
    list($GC, $FC) = $opts['items'];
    if (empty($data[$GC]) && empty($data[$FC])) return;
    if ($data[$GC] > $data[$FC]) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GC, 'field2' => $FC);
    } else if ($data[$GC] < 0) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero', 'field1' => $GC);
    } else if (($data[$GC] < round($data[$FC] * 0.021)) && !empty($data[$FC])) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_superior_210', 'field1' => $GC, 'field2' => $FC);
    } else if (($data[$GC] > round($data[$FC] * 0.196)) && !empty($data[$FC])) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior_1960', 'field1' => $GC, 'field2' => $FC);
    }
  }

  public static function integrity_gc_2014($form_code, $opts, $data) {
    list($GC, $FC) = $opts['items'];
    if (empty($data[$GC]) && empty($data[$FC])) return;
    if ($data[$GC] > $data[$FC]) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GC, 'field2' => $FC);
    } else if ($data[$GC] < 0) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero', 'field1' => $GC);
    } else if (($data[$GC] < round($data[$FC] * 0.021)) && !empty($data[$FC])) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_superior_210', 'field1' => $GC, 'field2' => $FC);
    } else if (($data[$GC] > round($data[$FC] * 0.2)) && !empty($data[$FC])) {
      $cible = $form_code.'_'.$GC;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior_20', 'field1' => $GC, 'field2' => $FC);
    }
  }

  public static function integrity_gj($form_code, $opts, $data) {
    list($GJ, $CC, $GH, $GK) = $opts['items'];
    $cible = $form_code.'_'.$GJ;

    if ($data[$GJ] > $data[$CC]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GJ, 'field2' => $CC);
    }
    else if ($data[$GJ] > $data[$GH]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GJ, 'field2' => $GH);
    }
    else if (($data[$GH] == 0) && ($data[$GJ] != 0)) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_zero', 'field1' => $GJ);
    }
    else if (($data[$GJ]+$data[$GK]) > $data[$GH]) {
      Formulaire::$errors[$cible] = array('status' => 'result_must_be_superior', 'field1' => $GJ, 'field2' => $GK, 'field2' => $GH);
    }
    else if (($data[$GH] == 0) && ($data[$CC] != 0)) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_zero', 'field1' => $CC);
    }

    if (!(($data[$GJ] <= round($data[$CC] * 0.196)) || ($data[$GJ] <= round($data[$CC] * 0.021)) || ($data[$GJ] <= round($data[$CC] * 0.055)))) {
      Formulaire::$errors['tva3310ca3_GJ'] = array('msg' => '3310CA3_GJ <= arrondi[(3310CA3_CC x 19,6 %)] ou arrondi[(3310CA3_CC x 2,1 %)] ou arrondi[(3310CA3_CC x 5,5 %)]');
      Formulaire::$errors['tva3310ca3_CC'] = array('msg' => '3310CA3_GJ <= arrondi[(3310CA3_CC x 19,6 %)] ou arrondi[(3310CA3_CC x 2,1 %)] ou arrondi[(3310CA3_CC x 5,5 %)]');
    }
  }

  public static function integrity_gj_2014($form_code, $opts, $data) {
    list($GJ, $CC, $GH, $GK) = $opts['items'];
    $cible = $form_code.'_'.$GJ;

    if ($data[$GJ] > $data[$CC]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GJ, 'field2' => $CC);
    }
    else if ($data[$GJ] > $data[$GH]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GJ, 'field2' => $GH);
    }
    else if (($data[$GH] == 0) && ($data[$GJ] != 0)) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_zero', 'field1' => $GJ);
    }
    else if (($data[$GJ]+$data[$GK]) > $data[$GH]) {
      Formulaire::$errors[$cible] = array('status' => 'result_must_be_superior', 'field1' => $GJ, 'field2' => $GK, 'field2' => $GH);
    }
    else if (($data[$GH] == 0) && ($data[$CC] != 0)) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_zero', 'field1' => $CC);
    }

    if (!(($data[$GJ] <= round($data[$CC] * 0.200)) || ($data[$GJ] <= round($data[$CC] * 0.021)) || ($data[$GJ] <= round($data[$CC] * 0.055)))) {
      Formulaire::$errors['tva3310ca3_GJ'] = array('msg' => '3310CA3_GJ <= arrondi[(3310CA3_CC x 20 %)] ou arrondi[(3310CA3_CC x 2,1 %)] ou arrondi[(3310CA3_CC x 5,5 %)]');
      Formulaire::$errors['tva3310ca3_CC'] = array('msg' => '3310CA3_GJ <= arrondi[(3310CA3_CC x 20 %)] ou arrondi[(3310CA3_CC x 2,1 %)] ou arrondi[(3310CA3_CC x 5,5 %)]');
    }
  }

  public static function integrity_gj_2015($form_code, $opts, $data) {
    list($GJ, $CC, $GH, $GK) = $opts['items'];
    $cible = $form_code.'_'.$GJ;

    if ($data[$GJ] > $data[$CC]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GJ, 'field2' => $CC);
    }
    else if ($data[$GJ] > $data[$GH]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $GJ, 'field2' => $GH);
    }
    else if (($data[$GH] == 0) && ($data[$GJ] != 0)) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_zero', 'field1' => $GJ);
    }
    else if (($data[$GJ]+$data[$GK]) > $data[$GH]) {
      Formulaire::$errors[$cible] = array('status' => 'result_must_be_superior', 'field1' => $GJ, 'field2' => $GK, 'field2' => $GH);
    }
    else if (($data[$GH] == 0) && ($data[$CC] != 0)) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_zero', 'field1' => $CC);
    }

    if (!(($data[$GJ] <= round($data[$CC] * 0.200)) || ($data[$GJ] <= round($data[$CC] * 0.021)) || ($data[$GJ] <= round($data[$CC] * 0.055)))) {
      Formulaire::$errors['tva3310ca3_GJ'] = array('msg' => '3310CA3_GJ <= arrondi[(3310CA3_CC x 20 %)] ou arrondi[(3310CA3_CC x 2,1 %)] ou arrondi[(3310CA3_CC x 5,5 %)]');
      Formulaire::$errors['tva3310ca3_CC'] = array('msg' => '3310CA3_GJ <= arrondi[(3310CA3_CC x 20 %)] ou arrondi[(3310CA3_CC x 2,1 %)] ou arrondi[(3310CA3_CC x 5,5 %)]');
    }
  }

  public static function integrity_kc($form_code, $opts, $data) {
    list($KC, $KA, $KB, $KD) = $opts['items'];
    if (empty($data[$KC]) && empty($data[$KA]) && empty($data[$KB]) && empty($data[$KD])) return;
    $cible = $form_code.'_'.$KC;
    if(!empty($data[$KB]) || !empty($data[$KD])){
      if ($data[$KC] > $data[$KA]+$data[$KB]+$data[$KD]) {
        Formulaire::$errors[$cible] = array('status' => 'result_must_be_inferior', 'field1' => $KC, 'field2' => $KA, 'field3' => $KB, 'field4' => $KD);
      }
    }
    else {
      if (($data[$KC] > $data[$KA]) && !empty($data[$KC])) {
        Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $KC, 'field2' => $KA);
      }
    }
  }

  public static function integrity_hh($form_code, $opts, $data) {
    list($HH, $HC) = $opts['items'];
    $cible = $form_code.'_'.$HH;
    if ($data[$HH] > $data[$HC]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $HH, 'field2' => $HC);
    }
  }

  public static function integrity_kg($form_code, $opts, $data) {
    list($KG, $HG) = $opts['items'];
    $cible = $form_code.'_'.$HH; // TODO : erreur $HH n'existe pas
    if ($data[$KG] > $data[$HG]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $KG, 'field2' => $HG);
    }
  }

  public static function integrity_jb($form_code, $opts, $data) {
    list($JB, $JA, $KJ) = $opts['items'];
    $cible = $form_code.'_'.$JB;
    $valueJb = is_array($data[$JB]) ? $data[$JB][0] : $data[$JB];
    $valueJa = is_array($data[$JA]) ? $data[$JA][0] : $data[$JA];
    $valueKj = is_array($data[$KJ]) ? $data[$KJ][0] : $data[$KJ];
    if (!($valueJb <= $valueJa-$valueKj)) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $JB, 'field2' => $JA.' - '.$KJ);
    }
  }

  public static function integrity_gh($form_code, $opts, $data, $params) {        
    if ($data[$params['current_field']] <= 0) return;
    self::integrity_equation($form_code, $opts, $data);
  }

  public static function integrity_kt($form_code, $opts, $data, $params) {
    list($KT, $KR) = $opts['items'];
    if (!(($data[$KT] >= ($data[$KR] * 0.021)) && ($data[$KT] <= ($data[$KR]* 0.2)))) {
      Formulaire::$errors[$form_code . '_' . $KT] = array('msg' => 'Erreur : <br />ligne 7C >= ligne 2B x 2,1%<br />ligne 7C <= ligne 2B x 20%');
    }
  }

  // lié à formulaire.generic.js : integrity_equation
  public static function integrity_equation($form_code, $opts, $data, $params = array()) {
    $left = $opts['left'];
    $right = $opts['right'];
    $operator = $opts['operator'];
    $operator = $operator ? $operator : '=';
    $total_left = 0;
    $total_right = 0;
    foreach ($left as $field) $total_left += $data[$field];
    foreach ($right as $field) $total_right += $data[$field];


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
        Formulaire::$errors[$form_code . '_' . $field] = array('status' => 'integrity_equation_error',
                                                               'left' => implode(', ', $left),
                                                               'right' => implode(', ', $right),
                                                               'operator' => $operator);
      }
    }

  }

  public static function integrity_3310ter_20140101($form_code, $opts, $data, $params) {
    if ($data['QM'] > 0 || $data['RM'] > 0) {
      if ($data['AB'] < 1) {
        $cible = $form_code.'_AB';
        Formulaire::$errors[$cible] = array('status' => 'not_percent');
      }
    }
  }

  /*************************** 3517sca12 **********************************/

  public static function calcul_na($form_code, $opts, $data) {
    list($NA, $LA, $MC, $LB, $MA, $MB) = $opts['items'];
    $cible = $form_code.'_'.$NA;
    $result = ($data[$LA]+$data[$MC])-($data[$LB]+$data[$MA]+$data[$MB]);
    if ($result < 0) {
      if (!empty($data[$NA])) {
        Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
      }
    } else if ($result >= 0) {
      ValidMain::checkmatch($result, $data[$NA], $cible);
    }
  }

  public static function calcul_nb($form_code, $opts, $data) {
    list($NB, $MA, $MB, $LA, $MC) = $opts['items'];
    $cible = $form_code.'_'.$NB;
    $result = ($data[$MA]+$data[$MB])-($data[$LA]+$data[$MC]);
    if ($result < 0) {
      if (!empty($data[$NB])) {
        Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
      }
    } else if ($result >= 0) {
      ValidMain::checkmatch($result, $data[$NB], $cible);
    }
  }

  public static function calcul_nc($form_code, $opts, $data) {
    list($NC, $LB, $NB, $MA, $MB, $MC) = $opts['items'];
    $cible = $form_code.'_'.$NC;
    if (empty($data[$NB])) {
      $result = $data[$LB]+$data[$NB];
    } else {
      $result = $data[$LB]+$data[$MA]+$data[$MB]-$data[$MC];
    }
    ValidMain::checkmatch($result, $data[$NC], $cible);
  }

  public static function calcul_na_2015($form_code, $opts, $data) {
    list($NA, $LA, $LB, $MA) = $opts['items'];
    $cible = $form_code . '_' . $NA;
    $result = ($data[$LA]) - ($data[$LB] + $data[$MA]);
    if ($result < 0) {
      if (!empty($data[$NA])) {
        Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
      }
    }
    else if ($result >= 0) {
      ValidMain::checkmatch($result, $data[$NA], $cible);
    }
  }

  public static function calcul_nb_2015($form_code, $opts, $data) {
    list($NB, $MA, $LA) = $opts['items'];
    $cible = $form_code . '_' . $NB;
    $result = $data[$MA] - $data[$LA];
    if ($result < 0) {
      if (!empty($data[$NB])) {
        Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
      }
    }
    else if ($result >= 0) {
      ValidMain::checkmatch($result, $data[$NB], $cible);
    }
  }

  public static function calcul_nc_2015($form_code, $opts, $data) {
    list($NC, $LB, $NB, $MA) = $opts['items'];
    $cible = $form_code . '_' . $NC;
    if (empty($data[$NB])) {
      $result = $data[$LB] + $data[$NB];
    }
    else {
      $result = $data[$LB] + $data[$MA];
    }
    ValidMain::checkmatch($result, $data[$NC], $cible);
  }

  public static function calcul_rd($form_code, $opts, $data) {
    $RD = $opts['results'][0];
    $QN = array_shift($opts['operands']);
    $cible = $form_code.'_'.$RD;
    $result_addition = 0;
    foreach ($opts['operands'] as $value) {
      $result_addition += $data[$value];
    }
    $result = $data[$QN]-$result_addition;
    ValidMain::checkmatch($result, $data[$RD], $cible);
  }

  public static function calcul_sb($form_code, $opts, $data) {
    $SB = $opts['results'][0];
    $QN = array_shift($opts['operands']);
    $cible = $form_code.'_'.$SB;
    $result_addition = 0;
    foreach ($opts['operands'] as $value) {
      $result_addition += $data[$value];
    }
    $result = $result_addition-$data[$QN];
    ValidMain::checkmatch($result, $data[$SB], $cible);
  }

  public static function calcul_sb_2015($form_code, $opts, $data) {
    $SB = $opts['results'][0];
    $cible = $form_code . '_' . $SB;
    $result = 0;
    foreach ($opts['operands'] as $value) {
      $result += $data[$value];
    }
    ValidMain::checkmatch($result, $data[$SB], $cible);
  }

  public static function integrity_fg_3517($form_code, $opts, $data) {
    list($FG, $EG) = $opts['items'];
    if (empty($data[$FG]) && empty($data[$EG])) return;
    if ($data[$FG] > $data[$EG]) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $FG, 'field2' => $EG);    } else if ($data[$FG] < 0) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero', 'field1' => $FG);
    } else if (($data[$FG] < round($data[$EG] * 0.021)) && !empty($data[$EG])) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_superior_210', 'field1' => $FG, 'field2' => $EG);
    } else if (($data[$FG] > round($data[$EG] * 0.2)) && !empty($data[$EG])) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior_20', 'field1' => $FG, 'field2' => $EG);
    }
  }

  public static function integrity_fp($form_code, $opts, $data) {
    list($FP, $EP) = $opts['items'];
    if (empty($data[$FP]) && empty($data[$EP])) return;
    if ($data[$FP] > $data[$EP]) {
      $cible = $form_code.'_'.$FP;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $FP, 'field2' => $EP);    } else if ($data[$FP] < 0) {
      $cible = $form_code.'_'.$FP;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero', 'field1' => $FP);
    } else if (($data[$FP] < round($data[$EP] * 0.021)) && !empty($data[$EP])) {
      $cible = $form_code.'_'.$FP;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_superior_210', 'field1' => $FP, 'field2' => $EP);
    } else if (($data[$FP] > round($data[$EP] * 0.2)) && !empty($data[$EP])) {
      $cible = $form_code.'_'.$FP;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior_20', 'field1' => $FP, 'field2' => $EP);
    }
  }

  public static function integrity_eq($form_code, $opts, $data) {
    list($EQ, $FP) = $opts['items'];
    $cible = $form_code.'_'.$EQ;
    if ($data[$EQ] > $data[$FP]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $EQ, 'field2' => $FP);
    }
  }

  public static function integrity_fe($form_code, $opts, $data) {
    list($FE, $KD) = $opts['items'];
    $cible = $form_code.'_'.$FE;
    if ($data[$FE] >= $data[$KD]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior', 'field1' => $FE, 'field2' => $KD);
    }
  }

  public static function calcul_la_or_lb($form_code, $opts, $data) {
    list($LA, $LB, $GC, $KD) = $opts['items'];
    if ($data[$GC] > $data[$KD]) {
      $result = $data[$GC]-$data[$KD];
      $cible = $form_code.'_'.$LA;
      ValidMain::checkmatch($result, $data[$LA], $cible);
      if (!empty($data[$LB])) {
        Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
      }
    } else {
      $result = $data[$KD]-$data[$GC];
      $cible = $form_code.'_'.$LB;
      ValidMain::checkmatch($result, $data[$LB], $cible);
      if (!empty($data[$LA])) {
        Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
      }
    }
  }

  public static function integrity_rb($form_code, $opts, $data) {
    list($RB, $RA) = $opts['items'];
    $cible = $form_code.'_'.$RB;
    if ($data[$RB] > $data[$RA]) {
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $RB, 'field2' => $RA);
    }
  }

  public static function calcul_va($form_code, $opts, $data) {
    $VA = $opts['results'][0];
    list($FR, $FL, $FM, $EQ, $HC) = $opts['operands'];
    $cible = $form_code.'_'.$VA;
    $result_addition = $data[$FL]+$data[$FM]+$data[$EQ]+$data[$HC];
    $result = $data[$FR]-$result_addition;
    ValidMain::checkmatch($result, $data[$VA], $cible);
  }

  public static function calcul_nj($form_code, $opts, $data) {
    $NJ = $opts['results'][0];
    list($NG, $NH, $LB) = $opts['operands'];
    $cible = $form_code.'_'.$NJ;
    if ($data[$LB] < 150) {
      $result = $data[$NG]+$data[$NH]-$data[$LB];
    } else {
      $result = $data[$NG]+$data[$NH];
    }
    ValidMain::checkmatch($result, $data[$NJ], $cible);
  }

  public static function disable_all($form_code, $opts, $data) {
    $SD = array_pop($opts['items']);
    if ($data[$SD] == 1) {
      foreach ($opts['items'] as $value) {
        if (!empty($data[$value])) {
          $cible = $form_code.'_'.$value;
          Formulaire::$errors[$cible] = array('status' => 'not_empty_because_checked', 'operand' => $SD);
        }
      }
    }
  }

  /*************************** Bisca **********************************/

  public static function calcul_es($form_code, $opts, $data) {
    $ES = array_shift($opts['items']);
    $FF = array_shift($opts['items']);
    $GA = array_shift($opts['items']);
    $GB = array_shift($opts['items']);
    foreach ($opts['items'] as $value) {
      $result_ES += $data[$value];
    }
    $cible = $form_code.'_'.$ES;
    ValidMain::checkmatch($result_ES, $data[$ES], $cible);
    if ($data[$FF] > $data[$ES]) {
      $result_GB = $data[$FF]-$data[$ES];
      $cible = $form_code.'_'.$GB;
      ValidMain::checkmatch($result_GB, $data[$GB], $cible);
      $result_GA = 0;
      $cible = $form_code.'_'.$GA;
      ValidMain::checkmatch($result_GA, $data[$GA], $cible);
    }
  }

  public static function integrity_fg_bisca12($form_code, $opts, $data) {
    $FG = $opts['items'][0];
    if ($data[$FG] < 0 || $data[$FG] > 100) {
      $cible = $form_code.'_'.$FG;
      Formulaire::$errors[$cible] = array('status' => 'not_percent');
    }
  }

  public static function calcul_ff_bisca12($form_code, $opts, $data) {
    $FF = array_shift($opts['items']);
    $KH = array_shift($opts['items']);
    foreach ($opts['items'] as $value) {
      $result_FF += $data[$value];
    }
    $cible = $form_code.'_'.$FF;
    ValidMain::checkmatch($result_FF, $data[$FF], $cible);
    if ($data[$FF] <= $data[$KH]) {
      $cible = $form_code.'_'.$FF;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $FF, 'field2' => $KH);
    }
  }

  public static function calcul_ff_bisca12_2015($form_code, $opts, $data) {
    $FF = array_shift($opts['items']);
    $KH = array_shift($opts['items']);
    $result_FF = 0;
    foreach ($opts['items'] as $value) {
      $result_FF += $data[$value];
    }
    $cible = $form_code.'_'.$FF;
    ValidMain::checkmatch($result_FF, $data[$FF], $cible);
    if ($data[$KH] > $data[$FF]) {
      $cible = $form_code.'_'.$FF;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $FF, 'field2' => $KH);
    }
  }

  public static function calcul_ga_gb_bisca12($form_code, $opts, $data) {
    list($ES, $KH, $GA, $GB) = $opts['items'];
    if ($data[$ES] >= $data[$KH]) {
      $result_GA = $data[$ES]-$data[$KH];
      $cible = $form_code.'_'.$GA;
      ValidMain::checkmatch($result_GA, $data[$GA], $cible);
      $result_GB = 0;
      $cible = $form_code.'_'.$GB;
      ValidMain::checkmatch($result_GB, $data[$GB], $cible);
    } else {
      $result_GB = $data[$KH]-$data[$ES];
      $cible = $form_code.'_'.$GB;
      ValidMain::checkmatch($result_GB, $data[$GB], $cible);
      $result_GA = 0;
      $cible = $form_code.'_'.$GA;
      ValidMain::checkmatch($result_GA, $data[$GA], $cible);
    }
  }

  public static function integrity_eh_bisca($form_code, $opts, $data) {
    list($EH, $DH) = $opts['items'];
    if (empty($data[$EH]) && empty($data[$DH])) return;
    if ($data[$EH] > $data[$DH]) {
      $cible = $form_code.'_'.$EH;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $EH, 'field2' => $DH);    } else if ($data[$EH] < 0) {
      $cible = $form_code.'_'.$EH;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero', 'field1' => $EH);
    } else if (($data[$EH] < round($data[$DH] * 0.021)) && !empty($data[$DH])) {
      $cible = $form_code.'_'.$EH;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_superior_210', 'field1' => $EH, 'field2' => $DH);
    } else if (($data[$EH] > round($data[$DH] * 0.2)) && !empty($data[$DH])) {
      $cible = $form_code.'_'.$EH;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior_20', 'field1' => $EH, 'field2' => $DH);
    }
  }

  public static function integrity_ep_bisca($form_code, $opts, $data) {
    list($EP, $DP) = $opts['items'];
    if (empty($data[$EP]) && empty($data[$DP])) return;
    if ($data[$EP] > $data[$DP]) {
      $cible = $form_code.'_'.$EP;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $EP, 'field2' => $DP);    } else if ($data[$EP] < 0) {
      $cible = $form_code.'_'.$EP;
      Formulaire::$errors[$cible] = array('status' => 'not_positiv_or_zero', 'field1' => $EP);
    } else if (($data[$EP] < round($data[$DP] * 0.021)) && !empty($data[$DP])) {
      $cible = $form_code.'_'.$EP;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_superior_210', 'field1' => $EP, 'field2' => $DP);
    } else if (($data[$EP] > round($data[$DP] * 0.2)) && !empty($data[$DP])) {
      $cible = $form_code.'_'.$EP;
      Formulaire::$errors[$cible] = array('status' => 'must_be_strictly_inferior_20', 'field1' => $EP, 'field2' => $DP);
    }
  }

  public static function calcul_ja_jb_jc_bisca12($form_code, $opts, $data) {
    list($JA, $JB, $JC, $GA, $GB, $HA, $HB, $HC) = $opts['items'];
    $result_JA = ($data[$GA]+$data[$HC])-($data[$GB]+$data[$HA]+$data[$HB]);
    $result_JB = ($data[$HA]+$data[$HB])-($data[$HC]+$data[$GA]);
    if ($result_JA > 0) {
      $cible = $form_code.'_'.$JA;
      ValidMain::checkmatch($result_JA, $data[$JA], $cible);
      $result_JB = 0;
      $cible = $form_code.'_'.$JB;
      ValidMain::checkmatch($result_JB, $data[$JB], $cible);
    } else if ($result_JA == 0) {
      $result_JA = 0;
      $cible = $form_code.'_'.$JA;
      ValidMain::checkmatch($result_JA, $data[$JA], $cible);
    } else if ($result_JB > 0) {
      $cible = $form_code.'_'.$JB;
      ValidMain::checkmatch($result_JB, $data[$JB], $cible);
      $result_JA = 0;
      $cible = $form_code.'_'.$JA;
      ValidMain::checkmatch($result_JA, $data[$JA], $cible);
    } else if ($result_JB == 0) {
      $result_JB = 0;
      $cible = $form_code.'_'.$JB;
      ValidMain::checkmatch($result_JB, $data[$JB], $cible);
    }
/*
    if ($result_JB > 0) {
      $result_JC = $data[$GB]+$data[$JB];
      $cible = $form_code.'_'.$JC;
      ValidMain::checkmatch($result_JC, $data[$JC], $cible);
    } else {
      $result_JC = $data[$GB]+$data[$HA]+$data[$HB]-$data[$HC];
      $cible = $form_code.'_'.$JC;
      ValidMain::checkmatch($result_JC, $data[$JC], $cible);

    }
*/
  }

  public static function report_if_150($form_code, $opts, $data) {
    $operande = $opts['operands'][0];
    if ($data[$operande] >= 150) {
      foreach ($data['results'] as $value) {
        $cible = $form_code.'_'.$value;
        ValidMain::checkmatch($data[$operande], $data[$value], $cible);
      }
    } else {
      foreach ($data['results'] as $value) {
        $result = 0;
        $cible = $form_code.'_'.$value;
        ValidMain::checkmatch($result, $data[$value], $cible);
      }
    }
  }

  public static function calcul_nj_bisca12($form_code, $opts, $data) {
    list($NJ, $GB, $NG, $NH) = $opts['items'];
    if ($data[$GB] >= 150) {
      $result_NJ = $data[$NJ]-$data[$NH];
      $cible = $form_code.'_'.$NJ;
      ValidMain::checkmatch($result_NJ, $data[$NJ], $cible);
    } else {
      $result_NJ = $data[$GB]+$data[$NJ]-$data[$NH];
      $cible = $form_code.'_'.$NJ;
      ValidMain::checkmatch($result_NJ, $data[$NJ], $cible);
    }
  }

  public static function integrity_mb_bisca12($form_code, $opts, $data) {
    list($MB, $MA) = $opts['items'];
    if ($data[$MB] > $data[$MA]) {
      $cible = $form_code.'_'.$MB;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $MB, 'field2' => $MA);
    }
  }

  public static function disable_all_bisca12($form_code, $opts, $data) {
    $ND = array_pop($opts['items']);
    if ($data[$ND] == 1) {
      foreach ($opts['items'] as $value) {
        if (!empty($data[$value])) {
          $cible = $form_code.'_'.$value;
          Formulaire::$errors[$cible] = array('status' => 'not_empty_because_checked', 'operand' => $ND);
        }
      }
    }
  }

  /////////////////////////////////////////////////////////////////

  /*public static function calcul_ja($form_code, $opts, $data){
    list($result_JA) = $opts['results'];
    list($GA, $HC, $GB, $HA, $HB) = $opts['operands'];
    $result = ($data[$GA] + $data[$HC]) - ($data[$GB] + $data[$HA] + $data[$HB]);
    if($result < 0){
      $cible = $form_code . '_' .$result_JA;
      Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
    }
  }
  
  public static function calcul_jb($form_code, $opts, $data){
    list($result_JB) = $opts['results'];
    list($HA, $HB, $HC, $GA) = $opts['operands'];
    $result = ($data[$HA] + $data[$HB]) - ($data[$HB] + $data[$GA]);
    if($result < 0){
      $cible = $form_code . '_' .$result_JB;
      Formulaire::$errors[$cible] = array('status' => 'not_empty_no_reason');
    }
  }*/

  /*************************** 3514 **********************************/

  public static function disable_on_da($form_code, $opts, $data) {
    $DA = array_shift($opts['items']);
    if (!empty($data[$DA])) {
      foreach ($opts['items'] as $v) {
        if (!empty($data[$v])) {
          $cible = $form_code.'_'.$v;
          Formulaire::$errors[$cible] = array('status' => 'not_empty', 'field1' => $DA, 'field2' => $v);
        }
      }
    }
  }

  public static function disable_on_db($form_code, $opts, $data) {
    $DB = array_shift($opts['items']);
    $DC = array_shift($opts['items']);
    if (!empty($data[$DB])) {
      foreach ($opts['items'] as $v) {
        if (!empty($data[$v])) {
          $cible = $form_code.'_'.$v;
          Formulaire::$errors[$cible] = array('status' => 'not_empty', 'field1' => $DB, 'field2' => $v);
        }
      }
    }
    if (!empty($data[$DB]) && empty($data[$DC])) {
      $cible = $form_code.'_'.$DC;
      Formulaire::$errors[$cible] = array('status' => 'has_to_be_filled', 'field1' => $DB, 'field2' => $DC);
    }
  }

  public static function disable_on_dc($form_code, $opts, $data) {
    $DC = array_shift($opts['items']);
    $DB = array_shift($opts['items']);
    if (!empty($data[$DC])) {
      foreach ($opts['items'] as $v) {
        if (!empty($data[$v])) {
          $cible = $form_code.'_'.$v;
          Formulaire::$errors[$cible] = array('status' => 'not_empty', 'field1' => $DC, 'field2' => $v);
        }
      }
    }
  }

  public static function disable_if_dd_checked($form_code, $opts, $data) {
    list($DD, $DF, $DA, $DC) = $opts['items'];
    if ($data[$DD] == 1) {
      if (!empty($data[$DA])) {
        $cible = $form_code.'_'.$DA;
        Formulaire::$errors[$cible] = array('status' => 'not_empty', 'field1' => $DC, 'field2' => $DA);
      }
      if (empty($data[$DF]) || $data[$DF] == 0) {
        $cible = $form_code.'_'.$DF;
        Formulaire::$errors[$cible] = array('status' => 'integrity_dd_3514');
      }
    } else {
      if (!empty($data[$DF])) {
        $cible = $form_code.'_'.$DD;
        Formulaire::$errors[$cible] = array('status' => 'should_be_checked', 'field1' => $DF, 'field2' => $DD);
      }
    }
  }

  /*var DD = $(itemsArray[0]);
var DF = $(itemsArray[1]);
if(parseFloat(DF.value) <= 0 || DF.value == ""){
    //NTD.Debug.trace('integrity_de_checked -> erreur, si DD est cochée, alors DF doit être supérieur à 0');
    NTD.Generic.negativ(DF);
  } else {
    //NTD.Debug.trace('fonction integrity_de_checked -> Les conditions liées à DD cochée sont correctes');
    NTD.Generic.positiv(DF);
  }*/

  public static function integrity_dd($form_code, $opts, $data) {
    $DD = $opts['items'][0];
    $DF = $opts['items'][1];
    if ($data[$DD] == 1) {
      if (empty($data[$DF]) || $data[$DF] == 0) {
        $cible = $form_code.'_'.$DF;
        Formulaire::$errors[$cible] = array('status' => 'integrity_dd_3514');
      }
    }
  }

  public static function disable_if_de_checked($form_code, $opts, $data) {
    $DE = array_shift($opts['items']);
    if ($data[$DE] == 1) {
      foreach ($opts['items'] as $v) {
        if (!empty($data[$v])) {
          $cible = $form_code.'_'.$v;
          Formulaire::$errors[$cible] = array('status' => 'not_empty', 'field1' => $DE, 'field2' => $v);
        }
      }
    }
  }

  public static function calcul_ga_gb($form_code, $opts, $data) {
    list($GA, $GB, $ES, $FD, $GC, $GD, $GF, $GH, $GK) = $opts['items'];

    if ($data[$ES] > $data[$FD]) {
      $result = $data[$ES]-$data[$FD];
      $cible = $form_code.'_'.$GA;
      ValidMain::checkmatch($result, $data[$GA], $cible);
      $result2 = 0;
      ValidMain::checkmatch($result2, $data[$GB], $cible);
      $operandes = array($GC, $GD, $GF, $GH, $GK);
      foreach ($operandes as $v) {
        if ($data[$v] != 0) {
          Formulaire::$errors[$cible] = array('status' => 'must_be_zero');
        }
      }
    } else if ($data[$ES] < $data[$FD]) {
      $result = $data[$FD]-$data[$ES];
      $cible = $form_code.'_'.$GB;
      ValidMain::checkmatch($result, $data[$GB], $cible);
      $result2 = 0;
      $cible = $form_code.'_'.$GA;
      ValidMain::checkmatch($result2, $data[$GA], $cible);
    } else {
      $result = 0;
      $cible = $form_code.'_'.$GA;
      ValidMain::checkmatch($result, $data[$GA], $cible);
      $result2 = 0;
      $cible = $form_code.'_'.$GB;
      ValidMain::checkmatch($result, $data[$GB], $cible);
    }
  }

  public static function disable_on_dg($form_code, $opts, $data) {
    $DG = array_shift($opts['items']);
    if (!empty($data[$DG])) {
      foreach ($opts['items'] as $v) {
        if (!empty($data[$v])) {
          $cible = $form_code.'_'.$v;
          Formulaire::$errors[$cible] = array('status' => 'not_empty', 'field1' => $DG, 'field2' => $v);
        }
      }
    }
  }

  public static function integrity_gc_3514($form_code, $opts, $data) {
    list($GC, $FA, $GB) = $opts['items'];
    if ($data[$GC] > 0) {
      if (($data[$GC] > $data[$FA]) || ($data[$GC] > $data[$GB])) {
        Formulaire::$errors[$cible] = array('integrity_gc_3514' => 'si GC est supérieur à 0, alors GC doit être inférieur ou égal à FA ET GC doit être inférieur ou égal à GB'); // TODO : erreur $cible n'existe pas
      }
    }
  }

  public static function calcul_gg_3514($form_code, $opts, $data) {
    list($GG, $GA, $GE) = $opts['items'];
    if ($data[$GA] < $data[$GE]) {
      $result = 0;
      $cible = $form_code.'_'.$GG;
      ValidMain::checkmatch($result, $data[$GG], $cible);
    } else {
      $result = $data[$GA]-$data[$GE];
      $cible = $form_code.'_'.$GG;
      ValidMain::checkmatch($result, $data[$GG], $cible);
    }
  }

  public static function integrity_id($form_code, $opts, $data) {
    list($ID, $IC) = $opts['items'];
    if (empty($data[$ID]) && empty($data[$IC])) return;
    if ($data[$ID] > $data[$IC]) {
      $cible = $form_code.'_'.$ID;
      Formulaire::$errors[$cible] = array('status' => 'must_be_inferior_or_egal', 'field1' => $ID, 'field2' => $IC);
    } else if ($data[$ID] < 760) {
      $cible = $form_code.'_'.$ID;
      Formulaire::$errors[$cible] = array('status' => 'must_be_superior_or_egal', 'field1' => $ID, 'field2' => 760);
    }
  }

  public static function check_dw_dg($form_code, $opts, $data) {
    if ($data['DW'] > 0) {
      if (empty($data['DG'])) {
        $cible = $form_code.'_DG';
        Formulaire::$errors[$cible] = array('status' => 'integrity_dg_3514');
      }
    }
  }

  public static function check_need_and_or_input($form_code, $opts, $data) {
    $DW = $opts['operands'][0];
    $DG = $opts['operands'][1];
    if (!empty($data[$DW]) && !empty($DG)) {
      foreach ($opts['results'] as $value) {
        if (empty($data[$value])) {
          $cible = $form_code.'_'.$value;
          Formulaire::$errors[$cible] = array('status' => 'has_to_be_filled', 'field1' => $DW, 'field2' => $value);
        }
      }
    }
  }

  public static function integrity_3514($form_code, $opts, $data, $params) {
    $fields_1 = explode(',', 'AA, AB, AC');
    $fields_2 = explode(',', 'DA, DB, DC, DD, DE, DF, DG, EA, EB, EC, ED, EE, EF, EG, EH, EJ, EK, EL, EM, EN, EP, EQ, ER, ES, FA, FB, FC, FD, GA, GB, GC, GD, GE, GF, GG, BA, BB, BC, BD, BE, BF, BG, BH, BJ, BP, BQ, BK, BL, BM, BN, BO, GH, GJ, GK, GL');
    $total_1 = 0;
    $total_2 = 0;
    foreach ($fields_1 as $field) $total_1 += $data[trim($field)];
    foreach ($fields_2 as $field) $total_2 += $data[trim($field)];
    if ($total_1 > 0 && $total_2 > 0) {
      foreach ($fields_2 as $field) {
        $cible = $form_code.'_'.$field;
        Formulaire::$errors[$cible] = array('status' => 'integrity_3514', 'fields_1' => $fields_1, 'fields_2' => $fields_2);
      }
    }

  }

  public static function integrity_3514_20140101($form_code, $opts, $data, $params) {
    $fields_1 = explode(',', 'HA, HB, HC');
    $fields_2 = explode(',', 'IA, IB, IC, ID');
    $total_1 = 0;
    $total_2 = 0;
    foreach ($fields_1 as $field) $total_1 += $data[trim($field)];
    foreach ($fields_2 as $field) $total_2 += $data[trim($field)];
    if ($total_1 > 0 && $total_2 > 0) {
      foreach ($fields_2 as $field) {
        $cible = $form_code.'_'.$field;
        Formulaire::$errors[$cible] = array('status' => 'integrity_3514', 'fields_1' => $fields_1, 'fields_2' => $fields_2);
      }
    }
  }



  public static $tva3514_20150101 = null;
  public static function general_tva3514_20150101 ($form_code, $opts, $data, $params) {
    self::$tva3514_20150101 = $data;
    $value = function ($fieldName) use ($data) {
      return $data[$fieldName];
    };
     $float = function ($fieldName) use($value) {
       $_value = ($value($fieldName));
       return is_numeric($_value) ? (float) $_value : false;
    };
    $fieldLabels = array(
      'HA'=> 'Ligne 01',
      'HB'=> 'Ligne 02',
      'HC'=> 'Ligne 03',
      'DE'=> 'Ligne 04',
      'IA'=> 'Ligne 05',
      'IB'=> 'Ligne 06',
      'IC'=> 'Ligne 07',
      'ID'=> 'Ligne 08',
      'CC'=> 'Mention express',
      '<' =>'doit être strictement inférieur à',
      '<='=> 'doit être inférieur ou égal à',
      '>' =>'doit être strictement supérieur à',
      '>='=> 'doit être supérieur ou égal à',
      '='=> 'doit être égal à'
    );
    $_l = function($fieldName) use ($fieldLabels) {
        if(isset($fieldLabels[$fieldName])) {
          return $fieldLabels[$fieldName];
        }
        return $fieldName;
    };
    $_l = function($fieldName) use ($_l) {
      if (func_num_args() == 1) {
        return $_l($fieldName);
      }
      $labels = array();
      for ($i =0; $i< func_num_args(); $i++) {
        $labels[] = $_l(func_get_arg($i));
      }
      return implode(" ", $labels);
    };
    $_error = function($field, $msg, $code) use ($form_code){
      Formulaire::$errors[$form_code.'_'.$field] = array('code' => $code,
                                                    'name' => 'error-required',
                                                    'msg' => $msg);
    };



    // --- IA <= IB
    if ($float('IA') > 0) {
      if (!($float('IA') <= $float('IB'))) {
        $_error('IA', $_l('IA', '<=', 'IB'), 'IA <= IB');
      }
    }
    // --- HB <= HA
    if ($float('HB') > 0) {
      if (!($float('HB') <= $float('HA'))) {
        $_error('HB', $_l('HB', '<=', 'HA'), 'HB <= HA');
      }
    }
    // --- 760 <= ID <= IC
    if ($float('ID') > 0) {
      if ($float('ID') < 760) {
        $_error('ID', $_l('ID', '>=', '760'), 'ID Control');
      }
      else if ($float('ID') > $float('IC')) {
        $_error('ID', $_l('ID', '<=', 'IC'), 'ID Control');
      }
    }
    // --- DE need HA
    if ($value('DE') > 0) {
      if(!($float('HA') !== false && $float('HA') >= 0)) {
        $_error('HA', $_l('HA', '>=', '0'), 'DE need HA');
      }
    }
    // --- CB need CC
    if (strlen($value('CB')) > 0 && !($value('CC') > 0)) {
      $_error('CB', $_l('CC', 'doit être coché'), 'CB need CC');
    }
  }

  /* ----- TVA 3517 DDR----- */
  public static function integrity_3517ddr_ae($form_code, $opts, $data, $params) {
    if ($data['AE'] != ($data['AC']-$data['AD'])) {
      $cible = $form_code.'_AE';
      Formulaire::$errors[$cible] = array('status' => 'integrity_3517ddr_ae');
    }
    if (!($data['AA'] > 0)) {
      if (!(($data['AE']+$data['AD']-$data['AC']) < 150)) {
        $cible = $form_code.'_AE';
        Formulaire::$errors[$cible] = array('status' => 'integrity_3517ddr_ae');
      }
    }
  }

  public static function integrity_3517ddr_ah_aj($form_code, $opts, $data, $params) {
    if (!($data['AH'] > 0) && !($data['AJ'] > 0)) {
      $cible = $form_code.'_AH';
      Formulaire::$errors[$cible] = array('status' => 'integrity_3517ddr_ah_aj');
    }
  }




}  
