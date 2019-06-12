<?php

try {

  $imprime_document_code = Formulairetype::DOCUMENT_CODE_TDFC;
  $millesime_2014 = 5;

  $field_csv = CsvReader::getInstance('doc/ntd/liasses/dico_tdfc_2014_v07.csv');
  foreach ($field_csv as $row) {

    if (Formulairetype::exists(array('code' => $row['Imprimé']))) {
      //continue;
    }
    else {
      print "nouveau formulaire [" . $row['Imprimé'] . "]\n";
      $formulairetype = Formulairetype::getInstance();
      $commit = array('code' => $row['Imprimé'],
                      'document_code' => $imprime_document_code,
                      'title' => $row['Imprimé'],
                      'title_code' => $row['Imprimé'],
                      'prefix_export' => $row['Imprimé']
      );
      $formulairetype->commit($commit);
      $formulairetype->setAttribute('name', $formulairetype->getFormulaireCode());
    }
    
    $ftype = Formulairetype::getInstance(array('code' => $row['Imprimé']));

    $field_args = array('code' => Ifield::getIfieldCode($row['Imprimé'],
                                                        $row['Code EDI'],
                                                        $row['Simple'],
                                                        $row['N°donnée simple']));
    if (Ifield::exists($field_args)) {
      $ifield = Ifield::getInstance($field_args);
      $millesimes = $ifield->millesimes;
      if (!in_array($millesime_2014, $millesimes)) {
        $millesimes[] = $millesime_2014;
        $ifield->setAttribute('millesimes', $millesimes);
      }
      continue;
    }

    print "Nouveau Field [" . implode(', ', $field_args) . "]\n";

    $ifield = Ifield::getInstance();
    $ifield_commit = $field_args;
    $ifield_commit['formulairetype_id'] = $ftype->getId();



    $suffix = '';
    if ($add_suffix) {
      if ($row['Type segment'] == 'NAD') {
        $suffix = Ifield::$segment_indexes['NAD'][$row['Simple'] . '.' . $row['N°donnée simple']];
      }
      elseif ($row['Type segment'] == 'CUX') {
        $suffix = Ifield::$segment_indexes['CUX'][$row['Simple'] . '.' . $row['N°donnée simple']];
      }
      else {
        $suffix = str_pad($suffix_count++, 2, '0', STR_PAD_LEFT);
      }
    }


    $ifield_commit['type_segment'] = strtolower($row['Type segment']);
    $ifield_commit['name'] = $row['Code EDI'] . $suffix;
    $ifield_commit['code_edi'] = $row['Code EDI'];
    $ifield_commit['type_composite'] = $row['Composite'];
    $ifield_commit['type_simple'] = $row['Simple'];
    $ifield_commit['no_donnee_simple'] = $row['N°donnée simple'];
    $ifield_commit['label'] = $row['Libellé'];
    $ifield_commit['indice_donnee'] = $row['Indice donnée'];
    $ifield_commit['table_edi'] = $row['Table EDI'];
    $ifield_commit['millesimes'] = array($millesime_2014);
    $ifield_commit['default_value'] = in_array($ifield_commit['type_segment'], array('moa', 'pcd', 'qty')) ? 0 : '';
    $ifield->commit($ifield_commit);
    $ifield->setFlag(Ifield::FLAG_EXPORTABLE);
  }


}
catch (Exception $e) {
  print $e->getMessage();
  $log->error($e);
}
