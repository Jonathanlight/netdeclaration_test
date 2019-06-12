<?php

try {

  $ftype = Formulairetype::getInstance((int) $req->id);

  $table = new Table(T('ifield'));
  $columns = $table->getFields();
  $csv = CsvWriter::getInstance(array('filename' => str_replace('.', '-', P('app.domain')) . '-ftype-' . $ftype->getId() . '.ifields.csv',
                                      'columns' => $columns));

  foreach ($ftype->getIfields() as $ifield) {
    $attributes = $ifield->getAttributes();
    foreach ($attributes as $key => $value) {
      $attributes[$key] = base64_encode(var_export($value, true));
    }
    $csv->append($attributes);
  }

}
catch (Exception $e) {
  $err->add($e);
}