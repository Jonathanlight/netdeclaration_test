<?php

try {

  $filters = array();
  if ($req->hasAttribute('declaration_id')) {
    $declaration_id = (int)$req->declaration_id;
    $filters['filters']['id'] = $declaration_id;
  }
  else if ($req->hasAttribute('from') || $req->hasAttribute('to')) {
    if ($req->hasAttribute('from')) {
      $filters['filters']['|>=|created_at'] = $req->from;
    }
    if ($req->hasAttribute('to')) {
      $filters['filters']['|<=|created_at'] = $req->to;
    }
    $filters['metas'] = array('created_at');
  }
  else {
    echo ('Usage: tool.formulaire.check.integrity [declaration_id=] [[from=] [to=]]');
    return ;
  }

  // ------------

  $declarations = Declaration::collect($filters);
  foreach ($declarations as $declaration) {
    $dectype = $declaration->getDectype();
    $formulaire_types_id = $dectype->getFormulairetypes()->asSet('id');

    foreach ($declaration->getFormulaires() as $formulaire) {
      $formulaire_formtype = $formulaire->getFormulairetype();

      $is_t_identif = (strtoupper($formulaire_formtype->prefix_export) == 'T-IDENTIF');
      $is_p_identif = (strtoupper($formulaire_formtype->prefix_export) == 'P-IDENTIF');

      $is_old_t_identif = $formulaire_formtype->getId() == 21;
      $is_new_t_identif = $formulaire_formtype->getId() == 286;
      $is_old_p_identif = $formulaire_formtype->getId() == 19;
      $is_new_p_identif = $formulaire_formtype->getId() == 289;


      /* TESTS */

      if (!in_array($formulaire_formtype->getId(), $formulaire_types_id)) {
        echo ':: Declaration('.$declaration->getId().') ['.$dectype->code.'] ::' . "\n";
        echo 'formulaire_type different pour le formulaire #'.$formulaire->getId() . "\n";
        echo '> Valeur trouvée : formulaire_type='.$formulaire_formtype->getId() . "\n";
        echo '> Valeurs possibles : formulaire_type=(' . implode(', ', $formulaire_types_id) . ')';
        echo "\n\n";
      }


      // Check t_identif (test on field EA from old version)
      $data_keys = array_keys($formulaire->data);
      if ($is_t_identif && $is_old_t_identif && !$is_new_t_identif && !in_array('EA', $data_keys) && !empty($data_keys)) {
        echo ':: Declaration('.$declaration->getId().') ['.$dectype->code.'] ::' . "\n";
        echo 'Le données sont potentiellements commpues sur le formulaire #' . $formulaire->getId() . "\n";
        echo '> Champs attendu "EA" et n\'est pas présent';
        echo "\n\n";
      }


      // Check p_identif (test on field EA from old version)
      $data_keys = array_keys($formulaire->data);
      if ($is_p_identif && $is_old_p_identif && !$is_new_p_identif && !in_array('EA', $data_keys) && !empty($data_keys)) {
        echo ':: Declaration('.$declaration->getId().') ['.$dectype->code.'] ::' . "\n";
        echo 'Le données sont potentiellements commpues sur le formulaire #' . $formulaire->getId() . "\n";
        echo '> Champs attendu "EA" et n\'est pas présent';
        echo "\n\n";
      }
    }
  }

}
catch (Exception $e) { $err->add($e); }