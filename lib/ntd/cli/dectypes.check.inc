<?php

try {

  foreach (Dectype::collect(array('filters' => array('|!&|flags' => Dectype::FLAG_OLD_SYSTEM))) as $dectype) {
    //print '[' . $dectype->getId() . '] ' . $dectype->name . "\n";
    foreach ($dectype->getFormulairetypes() as $ftype) {
      //print '[' . $ftype->getId() . '] ' . $ftype->name . "";
      $itemplates = $ftype->getItemplates(array('filters' => array('millesime_id' => $ftype->ftype_millesime_id,
                                                                   'status' => 1)));
      //print $itemplates->count() . "\n";
      if ($itemplates->count() < 1) {
        print 'Dectype [' . $dectype->getId() . '] ' . $dectype->name . "\n";
        print 'Ftype [' . $ftype->getId() . '] ' . $ftype->name . "\n";
        print "Missing Template" . "\n" . "\n";
      }
    }
  }

}
catch (Exception $e) {
  print $e->getMessage();
}
