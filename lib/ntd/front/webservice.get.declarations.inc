<?php

$res->resetTemplates();

try {

  NetDeclarationManager::manageWebServiceAccess();

  $datas = array();
  $opts = array('filters' => array('|IN|status' => array(Declaration::STATUS_READY_TO_SEND,
                                                         Declaration::STATUS_SENT_TO_TRADXPRESS)),
                'limit' => 100);
  $declaration_outputeds = array();
  $declarations = Declaration::collect($opts);
  foreach ($declarations as $declaration) {
    $rows = $declaration->asWebServiceRows();
    if($rows !== false) {
      $datas[] = $rows;
      $declaration_outputeds[] = $declaration->getId();
    }
  }

  $csv = new CsvWriter(array('eol' => "\n", 'separator' => '|'));
  foreach ($datas as $rows) {
    foreach ($rows as $row) {
      $_row = array();
      foreach ($row as $key => $value) {
        if (preg_match('/^(2777_ZZ)/', $key)) {
            continue;
        }
        $_row[$key] = "$key=$value";
      }
      $csv->append($_row);
    }
    $csv->append(array('END' => 'END'));
  }

  if (count($declaration_outputeds) > 0) {
    S('dbo')->update(T('declaration'), array('status' => Declaration::STATUS_SENT_TO_TRADXPRESS), array('filters' => array('|IN|id' => $declaration_outputeds)));
  }


}
catch (Exception $e) {
  $log->error($e);
  $err->add($e);
  $res->write($e->getMessage());
}


try {
  $mail = new Mail();
  $mail->addRecipient('npinchon@kernix.com');
  $mail->setSubject('['.P('app.domain').'][NTD] webservice.get.declarations');
  $mail->setBody('Utilisation du webservice get declarations. '.implode(', ', $declarations->asHash('id', 'id')));
  //$mail->send();
} catch (Exception $e) {

}
