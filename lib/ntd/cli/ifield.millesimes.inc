<?php

try {

  $csv = CsvReader::getInstance('doc/ntd_ifield_millesimes.csv');

  foreach ($csv as $row) {
    if (!Ifield::exists(array('code' => $row['code']))) {
      print "Ifield not exists" . $row['code'] . "\n";
      continue;
    }
    $ifield = Ifield::getInstance(array('code' => $row['code']));
    if (strcmp($ifield->code, $row['code']) !== 0) {
      print "Erreur " . $row['code'] . "\n";
      continue;
    }
    $millesimes = $ifield->getMillesimes()->asSet('id');
    $millesimes = explode(',', $row['millesimes']);
    $ifield->setAttribute('millesimes', $millesimes);
    //var_export($millesimes);
  }

  print 'Terminé ! ';

}
catch (Exception $e) {
  print $e->getMessage();
}
