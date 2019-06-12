<?php

$res->resetTemplates();

try {

  NetDeclarationManager::manageWebServiceAccess();

  $opts = array();

  $request = (string) $req->request;
  if (!empty($request)) {
    if (substr($req->request, -3, 3) != "END") throw new Exception("error request does not finish by 'END'");
    $request = trim(substr($request, 0, strlen($request) - 3));
    if (!empty($request)) {      
      $ref_messages = (array) explode(",", $request);
      $opts['filters']['|IN|ref_message'] = $ref_messages;
    }
  }


  $suivis = Suivi::collect($opts);

  $datas = array();
  if($suivis->count() == 0){
    return print "pas de suivis";
  }
  foreach ($suivis as $suivi) {
    $datas[$suivi->getId()][] = $suivi->asWebserviceHash();
    $destinataires = $suivi->getDestinataires();
    foreach ($destinataires as $destinataire) {
      $datas[$suivi->getId()][] = $destinataire->asWebserviceHash();
    }
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
}


try {
  $mail = new Mail();
  $mail->addRecipient('npinchon@kernix.com');
  $mail->setSubject('[' . P('app.domain') . '][NTD] webservice.get.edi');
  $mail->setBody('Utilisation du webservice get edi. ' . $content);
  $mail->send();
} catch (Exception $e) {

}
