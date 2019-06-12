<?php

try {

  $csv = CsvReader::getInstance('doc/ntd_itemplate.csv');
  foreach ($csv as $row) {
    $ftype = Formulairetype::getInstance(array('name' => $row['f_name']));
    $commit = array('formulairetype_id' => $ftype->getId(),
                    'version' => $row['version'],
                    'millesime_id' => $row['millesime_id']);
    if (Itemplate::exists($commit)) {
      print 'Itemplate déjà existant : ' . "\n" . var_export($row, true);
      continue;
    }
    $itemplate = Itemplate::getInstance();
    $commit['name'] = $row['name'];
    $commit['html'] = $row['html'];
    $commit['psp'] = $row['psp'];
    $commit['status'] = 0;
    $itemplate->commit($commit);
  }

  print "Terminé !";

}
catch (Exception $e) {
  print $e->getMessage();
}
