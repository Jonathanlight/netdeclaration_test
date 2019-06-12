<?php

try {


  foreach (Dectype::collect() as $dectype) {
    $millesimes = array();
    foreach ($dectype->getFormulairetypes() as $ftype) {
      $millesimes[$ftype->ftype_millesime_id][] = $ftype;
    }
    if (count($millesimes) > 1) {
      print $dectype->getId() . "\n";
      //var_export($millesimes);
      foreach ($millesimes as $millesime) {
        if (count($millesime) == 1) {
          print current($millesime)->getId() . ' : ' . current($millesime)->name;
          print"\n\n";
        }
      }

    }
  }

}
catch (Exception $e) {
  $err->add($e);
}
