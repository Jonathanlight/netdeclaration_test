<?php

$res->resetTemplates();

try {

  NetDeclarationManager::manageWebServiceAccess();

  if (!$req->hasAttribute('request', true)) throw new Exception("request not found. use parameter name 'request' to send data.");
  if (substr($req->request, -3, 3) != "END") throw new Exception("error request does not finish by 'END'");

  $request = $req->request;
  $request = trim(substr($request, 0, strlen($request) - 3));

  $errors = array();
  $updated = array();

  $ids = explode(",", $request);
  foreach ($ids as $id) {
    $id = (int) $id;
    if (Declaration::exists($id)) {
      $declaration = Declaration::getInstance($id);
      if ($declaration->status == Declaration::STATUS_SENT_TO_TRADXPRESS) {
        $declaration->commit(array('status' => Declaration::STATUS_RECEIVED_BY_TRADXPRESS));
        $updated[] = $id;
      } else {
        $errors[] = $id . ", status at " . $declaration->status;
      }
    } else {
      $errors[] = $id . ", no exist";
    }
  }

  $body = "request : <br />";
  $body .= $request . "<br /><br />";
  $body .= "reussi : " . implode(",", $updated) . "<br /><br />";
  $body .= "erreurs : <br />";
  foreach ($errors as $error) {
    $body .= $error . "<br />";
  }



  $res->write('OK');
}
catch (Exception $e) {
  $log->error($e);
  $err->add($e);
  $res->write($e->getMessage());
}

try {
  $mail = new Mail();
  $mail->addRecipient("npinchon@kernix.com", "Nicolas PINCHON");
  $mail->setSubject('['.P('app.domain').'][NTD] Web Service - update declarations result');
  $mail->setBody($body);
  //$mail->send();
} catch (Exception $e) {

}
