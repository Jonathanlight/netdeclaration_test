<?php

try {

  $filepath = $ctx->_current_adherent->getBulletinPdfPath();
  if(!file_exists($filepath)) {
  }
  $ctx->_current_adherent->generateBulletinPdf();
  $res->sendData($filepath);

}
catch (Exception $e) {
  $err->add($e);
}