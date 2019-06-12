<?php

try {

  foreach (Checksum::collect() as $checksum) {
    if (!Item::exists($checksum->model_id, $checksum->record_id)) {
      print 'Item not exists [' . $checksum->model_id . ':' . $checksum->record_id . ']';
      S('dbo')->exec('DELETE FROM #table_checksum WHERE id=:id: LIMIT 1',
                     array('#table_checksum' => T('checksum'), ':id:' => $checksum->getId()));
      print " OK\n";
    }
  }

  foreach (DecBdd::$models as $model) {
    $time = time();
    print $model . ' : ';
    foreach (Item::collect($model) as $item) {
      Checksum::store($item);
    }
    print  time() - $time . "\n";
  }


}
catch (Exception $e) {
  $err->add($e);
}