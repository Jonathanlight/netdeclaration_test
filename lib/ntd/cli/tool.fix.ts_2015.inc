<?php

try {

  $p_identif = array('old' => 19,
                     'new' => 289);


  $dectypes_ts = array('new' => array(165, 166, 167, 168, 169, 170, 171, 172),
                       'old' => array(119, 120, 121, 112, 113, 114, 155, 156));

  $prod_date = '2015-10-27 09:30:00';

  foreach ($dectypes_ts['new'] as $key => $id) {
    /** update formulairetype sur Dectype **/
    $dectype = Dectype::getInstance($id);

    // $old_dectype = Dectype::getInstance($dectypes_ts['old'][$key]);
    // echo $dectype->name . ' :: ' . $old_dectype->name;

    $ftypes = $dectype->getFormulairetypes(array('filters' => array('formulairetype_id' => $p_identif['old']),
                                                 'limit'   => 1));
    if (count($ftypes) > 0) {
      $ftype = $ftypes->first();
      echo 'Update "'.$dectype->name.'" : ftype('.$ftype->getId().') => ftype('.$p_identif['new'].')' . "\n";

      $dbo->update('ntd_dectype_formulairetype',
        array(
          'formulairetype_id' => $p_identif['new']
        ),
        array(
          'filters' => array('formulairetype_id' => $ftype->getId(),
                             'dectype_id'        => $dectype->getId())
        )
      );

      echo "\n\n---\n\n";
    }


    /** update formulairetype sur Declaration **/
    $filters = array('dectype_id'     => $dectypes_ts['old'][$key],
                     '|>=|created_at' => $prod_date);
    $declarations = Declaration::collect(array('filters' => $filters,
                                               'metas'   => array('created_at', 'updated_at')));

    foreach ($declarations as $declaration) {
      echo '#' . $declaration->getId() . ' ' . $declaration->getDectype()->name . "\n";

      $declaration->setAttribute('dectype_id', $id);
      foreach ($declaration->getFormulaires() as $formulaire) {
        $formulaire_type = $formulaire->getFormulaireType();
        echo '> #' . $formulaire_type->getId() . ' ' . $formulaire_type->name . '('.$formulaire->getId().')' . "\n";

        if ($formulaire_type->getId() == $p_identif['old']) {
          echo '>> p_identif('.$p_identif['old'].') => ('.$p_identif['new'].')' . "\n";

          $formulaire->setAttribute('formulairetype_id', $p_identif['new']);
        }
      }
      echo "\n\n---\n\n";
    }
  }

}
catch (Exception $e) { $err->add($e); }