<?php

try {

  $facture = Facture::getInstance((int) $req->id);

  $filepath = $facture->getPdfPath();
  if(!file_exists($filepath)) {

  }
  $facture->generatePdf();
  $res->sendData($filepath);

}
catch (Exception $e) {
  $err->add($e);
}
