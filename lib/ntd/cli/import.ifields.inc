<?php

try {

  // 'doc/kernix/imports/ifields_liasse_2016.csv'

  if (!$req->hasAttribute('filename', true)) {
    throw new Exception('filename parameter required');
  }

  if (!$req->hasAttribute('millesime_id', true)) {
    throw new Exception('millesime_id required');
  }

  if (!$req->hasAttribute('millesime_old_id', true)) {
    throw new Exception('millesime_old_id required');
  }

  $path = $req->filename;
  $csv_reader = CsvReader::getInstance($path);

  $millesime_id = (int)$req->millesime_id;
  if (!Millesime::exists($millesime_id)) {
    throw new Exception('unknown millesime #' . $millesime_id);
  }

  $millesime_old_id = (int)$req->millesime_old_id;
  if (!Millesime::exists($millesime_old_id)) {
    throw new Exception('unknown old millesime #' . $millesime_old_id);
  }

  $forms_no_exists = array();
  $fields_no_exists = array();
  $ftype_builds = array();

  $fields = array();

  foreach ($csv_reader as $row) {
    if (!Formulairetype::exists(array('code' => $row['imprime']))) {
      if (!in_array($row['imprime'], $forms_no_exists)) {
        $forms_no_exists[] = $row['imprime'];
        print "- Formulaire non existant [" . $row['imprime'] . "]\n";
        continue;
      }
    }

    // continue;

    $ftype = Formulairetype::getInstance(array('code' => $row['imprime']));
    if (!in_array($ftype->code, $ftype_builds)) {
      $millesimes = $ftype->getMillesimes()->asSet('id');
      $duplicate_template = !in_array($millesime_id, $millesimes);
      $ftype_builds[] = $ftype->code;
      $ftype->duplicateMillesime($millesime_id, $millesime_old_id, $duplicate_template);

      $sql = sprintf('SELECT formulairetype_id FROM `%s` WHERE formulairetype_id = %d AND millesime_id = %d',
        Formulairetype::TABLE_MILLESIME,
        $ftype->getId(),
        $millesime_id
      );
      $ftype_millesime_exists = S('dbo')->query($sql)->count() > 0;

      if (!$ftype_millesime_exists) {
        $record = array(
          'formulairetype_id' => $ftype->getId(),
          'millesime_id'      => (int)$millesime_id,
          'is_repetable'      => $ftype->hasFlag(Formulairetype::FLAG_REPETABLE) ? 1 : 0,
          'is_v1'             => $ftype->hasFlag(Formulairetype::FLAG_OLD_SYSTEM) ? 1 : 0
        );
        S('dbo')->insert(Formulairetype::TABLE_MILLESIME, $record);
      }

      print '- Ajout du millésime #' . $millesime_old_id . ' => #' . $millesime_id . ' [' . $ftype->code . ']' . "\n";
    }

    $field_code = $ftype->code . '_' . $row['code_edi'] . '_' . $row['simple'] . '_' . $row['donnee_simple'];
    if (!Ifield::exists(array('code' => $field_code))) {
      if (!in_array($field_code, $fields_no_exists)) {
        $fields_no_exists[] = $field_code;
        print '- IField non existant [' . $field_code . ']' . "\n";
      }

      // continue;

      $suffix = '';

      if ($row['type_segment'] == 'NAD') {
        $suffix = Ifield::$segment_indexes['NAD'][$row['simple'] . '.' . $row['donnee_simple']];
      }
      elseif ($row['type_segment'] == 'CUX') {
        $suffix = Ifield::$segment_indexes['CUX'][$row['simple'] . '.' . $row['donnee_simple']];
      }
      else {
        // $suffix = str_pad($suffix_count++, 2, '0', STR_PAD_LEFT);
      }

      $ifield_commit = array();
      $ifield_commit['formulairetype_id'] = $ftype->getId();
      $ifield_commit['type_segment'] = strtolower($row['type_segment']);
      $ifield_commit['name'] = $row['code_edi'] . $suffix;
      $ifield_commit['code_edi'] = $row['code_edi'];
      $ifield_commit['type_composite'] = str_pad($row['composite'], 4, '0', STR_PAD_LEFT);
      $ifield_commit['type_simple'] = $row['simple'];
      $ifield_commit['no_donnee_simple'] = str_pad($row['donnee_simple'], 2, '0', STR_PAD_LEFT);
      $ifield_commit['label'] = $row['libelle'];
      $ifield_commit['indice_donnee'] = str_pad($row['indice_donnee'], 4, '0', STR_PAD_LEFT); // extensible (IField)
      $ifield_commit['table_edi'] = $row['table_edi'];
      $ifield_commit['millesimes'] = array($millesime_id => $millesime_id);
      $ifield_commit['default_value'] = in_array($ifield_commit['type_segment'], array('moa', 'pcd', 'qty')) ? 0 : '';
      $ifield_commit['status'] = Ifield::STATUS_ONLINE;

      // var_export($ifield_commit);

      $ifield = Ifield::getInstance();
      $ifield->commit($ifield_commit);
      $ifield->setFlag(Ifield::FLAG_EXPORTABLE);
      print '- IField créé [' . $field_code . ']' . "\n";
    }
    else {
      // Ifields
      $ifield = Ifield::getInstance(array('code' => $field_code));

      $millesimes = (array)$ifield->getMillesimes()->asSet('id');
      if ($row['libelle_modifie'] == 'SUPPRESSION') {
        //
      }
      else {
        $sql = sprintf('SELECT ifield_id FROM `%s` WHERE ifield_id = %d AND millesime_id = %d',
          Ifield::TABLE_MILLESIME,
          $ifield->getId(),
          $millesime_id
        );
        $ifield_millesime_exists = S('dbo')->query($sql)->count() > 0;

        if (!$ifield_millesime_exists) {
          $record = array(
            'ifield_id'     => $ifield->getId(),
            'millesime_id'  => (int)$millesime_id,
            'is_extensible' => $ifield->indice_donnee == '0001'
          );
          S('dbo')->insert(Ifield::TABLE_MILLESIME, $record);
          print '- Millesime ' . $millesime_id . ' ajouté au IField [' . $field_code . ']' . "\n";
        }
      }

      // Operations
      if ($row['libelle_modifie'] == 'SUPPRESSION') {
        $operation_filters = array('filters' => array('|%%|name' => $ftype->code.'_'.$ifield->code_edi));
        $operations = $ftype->getOperations($operation_filters);

        foreach ($operations as $operation) {
          $millesimes = (array)$operation->millesimes;
          if (in_array($millesime_id, $millesimes)) {
            $key = array_search($millesime_id, $millesimes);
            unset($millesimes[$key]);
            $operation->setAttribute('millesimes', $millesimes);
            print '- Millesime ' . $millesime_id . ' supprimé de l\'Operation ' . $operation->name . "\n";
          }
        }
      }
    }
  }

}
catch (Exception $e) {
  $err->add($e);
}
