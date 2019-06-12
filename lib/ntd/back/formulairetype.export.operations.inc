<?php

try {

  $ftype = Formulairetype::getInstance((int) $req->id);

  $table = new Table(T('operation'));
  $columns = $table->getFields();
  $csv = CsvWriter::getInstance(array('filename' => str_replace('.', '-', P('app.domain')) . '-ftype-' . $ftype->getId() . '.operations.csv',
                                      'columns' => $columns));

  foreach ($ftype->getOperations() as $operation) {
    $attributes = $operation->getAttributes();
    foreach ($attributes as $key => $value) {
      $attributes[$key] = base64_encode(var_export($value, true));
    }
    $csv->append($attributes);
  }

}
catch (Exception $e) {
  $err->add($e);
}