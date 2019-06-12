<?php

try {

  $t_identif = array('old' => 21,
                     'new' => 286);


  $dectypes_tva = array('new' => array(158, 159, 160, 161, 157, 162, 163, 164),
                        'old' => array(104, 111, 106, 109, 108, 110, 107, 105));


  foreach ($dectypes_tva['new'] as $key => $id) {
    /** update formulairetype sur Dectype **/
    $dectype = Dectype::getInstance($id);

    // $old_dectype = Dectype::getInstance($dectypes_tva['old'][$key]);
    // echo $dectype->name . ' :: ' . $old_dectype->name;


    $ftypes = $dectype->getFormulairetypes(array('filters' => array('formulairetype_id' => $t_identif['old']),
                                                 'limit'   => 1));
    if (count($ftypes) > 0) {
      $ftype = $ftypes->first();
      echo 'Update "'.$dectype->name.'" : ftype('.$ftype->getId().') => ftype('.$t_identif['new'].')' . "\n";

      $dbo->update('ntd_dectype_formulairetype',
        array(
          'formulairetype_id' => $t_identif['new']
        ),
        array(
          'filters' => array('formulairetype_id' => $ftype->getId(),
                             'dectype_id'        => $dectype->getId())
        )
      );

      echo "\n\n---\n\n";
    }


    /** update formulairetype sur Declaration **/
    $filters = array('dectype_id' => $id);
    $declarations = Declaration::collect(array('filters' => $filters));

    foreach ($declarations as $declaration) {
      echo '#' . $declaration->getId() . ' ' . $declaration->getDectype()->name . "\n";

      foreach ($declaration->getFormulaires() as $formulaire) {
        $formulaire_type = $formulaire->getFormulaireType();
        echo '> #' . $formulaire_type->getId() . ' ' . $formulaire_type->name . '('.$formulaire->getId().')' . "\n";

        if ($formulaire_type->getId() == $t_identif['old']) {
          echo '>> t_identif('.$t_identif['old'].') => ('.$t_identif['new'].')' . "\n";

          $formulaire->setAttribute('formulairetype_id', $t_identif['new']);
        }
      }
      echo "\n\n---\n\n";
    }
  }
}
catch (Exception $e) { $err->add($e); }