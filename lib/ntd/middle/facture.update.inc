<?php

try {


  $facture = Facture::getInstance((int) $req->facture_id);  
  if ($facture->status == Facture::STATUS_PAYE) {
    throw new Exception('facture ('.$facture->getId().') already paid');
  }
  $facture->commit(array('method_id' => $req->method_id));

  //$res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
