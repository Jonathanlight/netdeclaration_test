<?php

class ValidIs {
  
  /*********************************************** IS - 2572 ********************************************************/  
  
  public static function compare($form_code, $opts, $data){
    $elt1 = is_array($opts['results']) ? $opts['results'][0] : $opts['results'];
    $elt2 = is_array($opts['operands']) ? $opts['operands'][0] : $opts['operands'];
    if(!empty($data[$elt1]) && ($data[$elt2] > 0)){
      $result = 0;
      $cible = $form_code . '_' .$elt2;
      Formulaire::$tests[$cible] = array('status' => 'not_empty_choice', 'field1' => $elt1, 'field2' => $elt2);
      Formulaire::$errors[$cible] = array('status' => 'not_empty_choice', 'field1' => $elt1, 'field2' => $elt2);
    } else if(!empty($data[$elt2]) && ($data[$elt1] > 0)){
      $result = 0;
      $cible = $form_code . '_' .$elt1;
      Formulaire::$tests[$cible] = array('status' => 'not_empty_choice', 'field1' => $elt1, 'field2' => $elt2);
      Formulaire::$errors[$cible] = array('status' => 'not_empty_choice', 'field1' => $elt1, 'field2' => $elt2);
    }
  }
  
  public static function soustraction_cada($form_code, $opts, $data){
    list($result_CA,$result_DA,$operande_AD,$operande_BD) = $opts['items'];
    if($data[$operande_AD] > $data[$operande_BD]){
      $result = $data[$operande_AD] - $data[$operande_BD];
      $cible = $form_code . '_' .$result_CA;
      ValidMain::checkmatch($result, $data[$result_CA], $cible);
      $result = 0;
      $cible = $form_code . '_' .$result_DA;
      ValidMain::checkmatch($result, $data[$result_DA], $cible);
    } else if($data[$operande_BD] > $data[$operande_AD]) {
      $result = $data[$operande_BD] - $data[$operande_AD];
      $cible = $form_code . '_' .$result_DA;
      ValidMain::checkmatch($result, $data[$result_DA], $cible);
      $result = 0;
      $cible = $form_code . '_' .$result_CA;
      ValidMain::checkmatch($result, $data[$result_CA], $cible);
    } else {
      $result = 0;
      $cible = $form_code . '_' .$result_DA;
      ValidMain::checkmatch($result, $data[$result_DA], $cible);
    }
  }
  
  public static function verification_ea($form_code, $opts, $data){
    list($operandes_ad,$operandes_bd,$operandes_da,$result_ea,$result_eb) = $opts['items'];
    $result = $data[$operandes_da] - $data[$result_ea];
    $cible = $form_code . '_' .$result_eb;
    ValidMain::checkmatch($result, $data[$result_eb], $cible);
    
    if((($data[$operandes_ad] >= $data[$operandes_bd]) || ($data[$result_ea] > $data[$operandes_da])) && $data[$operandes_da] != 0) {
      $cible = $form_code . '_' .$result_ea;
      Formulaire::$tests[$cible] = array('status' => 'integrity_ea');
      Formulaire::$errors[$cible] = array('status' => 'integrity_ea');
    }
  }
}

?>
