<?php

$res->resetTemplates();

try {

  NetDeclarationManager::manageWebServiceAccess();

  $datas = array();
  $exceptions = array();
  $opts = array('filters' => array('status' => Adherent::STATUS_SUBSCRIPTION_VALIDE));
  $adherents = Adherent::collect($opts);
  foreach ($adherents as $adherent) {
    try {
      $datas[] = $adherent->asWebServiceHash();
    } catch (Exception $e) {
      $exceptions[] = $e->getFile().":".$e->getLine()." - [".$e->getCode()."]".$e->getMessage();
    }
  }

  $csv = new CsvWriter(array('eol' => "\n", 'separator' => '|'));
  foreach ($datas as $data) {
    $row = array();
    foreach ($data as $key => $value) {
      $row[$key] = "$key=$value";
    }
    $csv->append($row);
  }
  $csv->append(array('END' => 'END'));

}
catch (Exception $e) {
  //$err->add($e);
  //$res->write($e->getMessage());
  $log->error($e);
  $mail = new Mail();
  $mail->addRecipient('npinchon@kernix.com');
  $mail->setSubject('[' . P('app.domain') . '][NTD] webservice.adherents - Exception');
  $mail->setBody($e->getMessage());
  //$mail->send();
}

if (sizeof($exceptions) > 0) {
  $mail = new Mail();
  $mail->addRecipient('npinchon@kernix.com');
  $mail->setSubject('[' . P('app.domain') . '][NTD] webservice.adherents - Exceptions');
  $body = "Exceptions : \n".implode("\n", $exceptions);  
  $mail->setBody(nl2br($body));
  //$mail->send();
}
