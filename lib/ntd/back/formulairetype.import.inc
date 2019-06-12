<?php

try {

  $formulairetype = Formulairetype::getInstance((int) $req->id);
  $counts = array();

  foreach (array('ifield', 'operation', 'itemplate') as $model) {
    if (!File::exists($req->getAttribute('file_path_' . $model))) {
      continue;
    }
    if (Item::collect($model, array('filters' => array('formulairetype_id' => $formulairetype->getId())))->count() > 0) {
      throw new Exception('Error, some ' . $model . ' already exists');
    }
    $csv = CsvReader::getInstance($req->getAttribute('file_path_' . $model));
    foreach ($csv as $row) {
      foreach ($row as $key => $value) {
        $value = base64_decode($value);
        eval('$value = ' . $value . ';');
        $row[$key] = $value;
      }
      $row['formulairetype_id'] = $formulairetype->getId();
      unset($row['id']);


      if ($model == 'ifield') {
        $ifield = Ifield::getInstance();
        $ifield->commit($row);
        $counts[$model]++;
      }
      elseif ($model == 'operation') {
        $operation = Operation::getInstance();
        $operation->commit($row);
        $counts[$model]++;
      }
      elseif ($model == 'itemplate') {
        $itemplate = Itemplate::getInstance();
        $itemplate->commit($row);
        $counts[$model]++;
      }
    }
  }

  $res->sendMessage('Import terminé. ' . var_export($counts, true));

}
catch (Exception $e) {
  $err->add($e);
}
