<?php

try {



  $csv = CsvReader::getInstance('doc/dectype.ftypes.export_good.csv');
  foreach ($csv as $row) {
    if ($row['dectype'] == 'IR MS') continue;

    $dectype = Dectype::getInstance(array('code' => $row['dectype'],
                                          'millesime_id' => 5));
    $ftype = Formulairetype::getInstance(array('name' => $row['ftype']));
    /*$ftypes = $dectype->getFormulairetypes();
    if($ftypes->count() > 0) {
      print $dectype->getId() . " : " . $ftypes->count()."\n";
      continue;
    } */

    $count = $dbo->fetchValue('SELECT COUNT(*) FROM ntd_dectype_formulairetype WHERE dectype_id=' . $dectype->getId() . ' AND formulairetype_id=' . $ftype->getId());
    if ($count > 0) {
      var_export($row);
    }

    $dbo->insert('ntd_dectype_formulairetype',
                 array('position' => $row['position'],
                       'type' => $row['type'],
                       'millesime_id' => $row['millesime_id'],
                       'dectype_id' => $dectype->getId(),
                       'formulairetype_id' => $ftype->getId()));
    //print "OK\n";
  }

  print "terminé!";

}
catch (Exception $e) {

  print $e->getMessage();
}
