<?php

try {

  $csv = CsvReader::getInstance('doc/ntd_operation_millesimes.csv');

  foreach ($csv as $row) {
    $operation = Operation::getInstance(array('name' => $row['name']));
    if (strcmp($operation->name, $row['name']) !== 0) {
      print "Erreur " . $row['name'] . "\n";
      continue;
    }
    $millesimes = $operation->millesimes;
    $millesimes = explode(',', $row['millesimes']);
    $operation->setAttribute('millesimes', $millesimes);
    //var_export($millesimes);
  }

  print 'Terminé ! ';

}
catch (Exception $e) {
  print $e->getMessage();
}
