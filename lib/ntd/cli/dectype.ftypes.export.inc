<?php

try {

  $file = File::getInstance('doc/dectype.ftypes.export.csv', 'w');

  $csv = CsvWriter::getInstance(array('fd' => $file,
                                      'encoding' => 'UTF-8',
                                      'columns' => array('dectype', 'ftype', 'position', 'type', 'millesime_id'),
                                      'delimiter' => '"'));
  foreach (Dectype::collect(array('filters' => array(/*'millesime_id' => 5,
                                                     'document_code' => Formulairetype::DOCUMENT_CODE_TDFC,
                                                     '|!=|code' => '72'*/))) as $dectype) {
    foreach ($dectype->getFormulairetypes() as $ftype) {
      $csv->append(array('dectype' => $dectype->code,
                         'ftype' => $ftype->name,
                         'position' => $ftype->ftype_position,
                         'type' => $ftype->ftype_type,
                         'millesime_id' => $ftype->ftype_millesime_id));

    }
  }

}
catch (Exception $e) {
  $err->add($e);
}
