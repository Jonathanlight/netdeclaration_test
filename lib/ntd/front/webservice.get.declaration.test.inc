<?php

$res->resetTemplates();

try {

  //NetDeclarationManager::manageWebServiceAccess();

  $datas = array();
  $declaration = Declaration::getInstance((int) $req->id);
  $rows = $declaration->asWebServiceRows();
  if ($rows !== false) {
    $datas[] = $rows;
  }


  $csv = new CsvWriter(array('eol' => "\n", 'separator' => '|'));
  foreach ($datas as $rows) {
    foreach ($rows as $row) {
      $_row = array();
      foreach ($row as $key => $value) {
        $_row[$key] = "$key=$value";
      }
      $csv->append($_row);
    }
    $csv->append(array('END' => 'END'));
  }

}
catch (Exception $e) {
  $log->error($e);
  $res->write($e->getMessage());
}

