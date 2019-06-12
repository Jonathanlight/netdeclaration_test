<?php

try {

  $facture = Facture::getInstanceByKey($req->item);

  if ($facture->status == Facture::STATUS_PENDING) {
    $facture->setAttribute('status', Facture::STATUS_NON_PAYE);
  }

  $res->sendRedirect('/middle/payment/-/facture_id/'.$facture->getId());

}
catch (Exception $e) { $err->add($e); }