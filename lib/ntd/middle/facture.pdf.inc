<?php

try {

  $facture = Facture::getInstance((int) $req->id);
  if ($facture->getAdherent()->user_id !== $ctx->_current_adherent->user_id) {
    throw new MaliciousException();
  }

  $filepath = $facture->getPdfPath();
  if(!file_exists($filepath)) {

  }
  $facture->generatePdf();
  $res->sendData($filepath);

}
catch (Exception $e) {
  $err->add($e);
}