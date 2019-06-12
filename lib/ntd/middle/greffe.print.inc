<?php

try {

  if (!$req->hasAttribute('id', true)) {
    throw new Exception(l('error'));
  }

  $greffe = Greffe::getInstance((int)$req->id);
  $filepath = GreffeManager::generatePdfGreffe($greffe);

  $res->sendData(File::getInstance($filepath, 'r'));

}
catch (Exception $e) { $err->add($e); }
