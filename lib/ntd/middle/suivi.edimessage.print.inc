<?php

try {

  $file_path = SuiviManager::generateEdiMessagePdf((int)$req->id);
  $res->sendData($file_path);

}
catch (Exception $e) { $err->add($e); }