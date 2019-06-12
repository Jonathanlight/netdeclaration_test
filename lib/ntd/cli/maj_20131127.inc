<?php

try {

  if ($req->manual != 'yes') {
    print 'manual=yes needed';
    return;
  }
  $step = (int) $req->step;
  if ($step < 1) {
    print 'step < 1';
    return;
  }


  //$step = 4;
  /*
  if ($step == 1) {
    $ftypes = Formulairetype::collect(array('filters' => array('is_visible' => 1)));
    foreach ($ftypes as $ftype) {
      $dectype = Dectype::getInstance();
      $commit = array('document_code' => $ftype->document_code,
                      'default_params' => $ftype->default_params,
                      'name' => $ftype->title,
                      'code' => strtoupper($ftype->code),
                      'position' => $ftype->position,
                      'status' => 1,
                      'ref_paiement_type_echeance' => $ftype->ref_paiement_type_echeance,
      );
      $dectype->commit($commit);
    }
  }
  if ($step == 2) {
    $table_relation = Model::relation('dectype', 'formulairetype');
    $table_relation = $table_relation['through'];

    foreach (Dectype::collect() as $dectype) {
      $ftype = Formulairetype::getInstance(array('title' => $dectype));
      foreach ($ftype->formulairetype_annexes as $annexe_id) {
        $formulairetype = Formulairetype::getInstance($annexe_id);
        $dectype->addFormulairetype($formulairetype);
        $dbo->update($table_relation,
                     array('type' => Dectype::RELATION_TYPE_OBLIGATOIRE),
                     array('filters' => array('dectype_id' => $dectype->getId(),
                                              'formulairetype_id' => $formulairetype->getId()),
                           'limit' => 1));
        $dectype->onRelationUpdate($formulairetype);
      }
      foreach ($ftype->formulairetype_annexes_no_required as $annexe_id) {
        $formulairetype = Formulairetype::getInstance($annexe_id);
        $dectype->addFormulairetype($formulairetype);
        $dbo->update($table_relation,
                     array('type' => Dectype::RELATION_TYPE_ANNEXE),
                     array('filters' => array('dectype_id' => $dectype->getId(),
                                              'formulairetype_id' => $formulairetype->getId()),
                           'limit' => 1));
        $dectype->onRelationUpdate($formulairetype);
      }
    }
  }*/
  if ($step == 2) {
    // remplissage declaration::dectype_id (en fonction de ftype->title == dectype->name)
    $hash = array();
    foreach (Dectype::collect() as $dectype) {
      if(Formulairetype::exists(array('title' => $dectype->name))) {
        $hash[Formulairetype::getInstance(array('title' => $dectype->name))->getId()] = $dectype->getId();
      }
    }

    var_export($hash);
  }
  if ($step == 3) {
    // remplissage declaration::dectype_id (en fonction de ftype->title == dectype->name)
    $hash = array();
    foreach (Dectype::collect() as $dectype) {
      if(Formulairetype::exists(array('title' => $dectype->name))) {
        $hash[Formulairetype::getInstance(array('title' => $dectype->name))->getId()] = $dectype->getId();
      }
    }
    foreach (Declaration::collect() as $declaration) {
      if (isset($hash[$declaration->formulairetype_id])) {
        $declaration->setAttribute('dectype_id', $hash[$declaration->formulairetype_id]);
      }
    }
  }
  /*if ($step == 4) {
    // remplissage dectype::code (en fonction de ftype->title == dectype->name)
    $hash = array();
    foreach (Dectype::collect() as $dectype) {
      $dectype->setAttribute('code', strtoupper(Formulairetype::getInstance(array('title' => $dectype->name))->code));
    }
  } */
  if ($step == 5) {
    $hash = array();
    foreach (Declaration::collect() as $declaration) {
      $hash[$declaration->formulairetype_id][$declaration->dectype_id]++;
    }
    var_export($hash);
  }


}
catch (Exception $e) {
  print $e->getMessage();
  $log->error($e);
}
