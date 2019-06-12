<?php

try {

  $declaration = Declaration::getInstanceByKey($req->key);

  if ($req->hasAttribute('ftype_id', true)) {
    $ftype = Formulairetype::getInstance($req->ftype_id);
    $file = $ftype->generatePdf($declaration);
  }
  else {
    $file = $declaration->generatePdf();
  }

  $res->sendData($file);

} catch (Exception $e) { $err->add($e); }
