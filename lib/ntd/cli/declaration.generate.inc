<?php

try {

  $opts = array('include' => array('millesime'),
                'filters' => array(T('millesime').'.name' => '2014',
                                   '|!&|flags' => Dectype::FLAG_OLD_SYSTEM));

  $dectypes = Dectype::collect($opts);
  $adherent_id = 2;

  foreach ($dectypes as $dectype) {

    $declaration = Declaration::getInstance();

    $attrs = array('adherent_id' => $adherent_id,
                   'dectype_id' => $dectype->id,
                   'status' => Declaration::STATUS_EDITABLE);

    $declaration->commit($attrs);
    $declaration->generatePdf();

  } 

} catch (Exception $e) { $err->add($e); }
