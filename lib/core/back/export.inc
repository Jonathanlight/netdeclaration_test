<?php

try {

  $params = $req->getAttributes();
  unset($params['limit']);
  unset($params['offset']);

  $finder = Finder::getInstance($params);

  Item::getInstance($finder->model)->onCollect($finder);
  Item::getInstance($finder->model)->onExport($finder);

  $items = $finder->getCollection(); 
  //$items->trace();

  $columns = array_keys($items->first()->asExportHash());

  $opts = array('filename' => $finder->model.'_export_'.Date::today(),
                'columns' => $columns);
  $csv = CsvWriter::getInstance($opts);
  foreach ($items as $item) {
    $csv->append($item->asExportHash());
  }

}
catch (Exception $e) { $err->add($e); }
