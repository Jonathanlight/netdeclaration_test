<?php

try {

  $facture = Facture::getInstanceByKey($req->item);

  if ($facture->adherent_id != $ctx->_current_adherent->getId()) {
    throw new MaliciousException('bad adherent');
  }
  if ($facture->status != Facture::STATUS_PENDING) {
    throw new MaliciousException('bad facture status');
  }

  Letter::send('payment.prelevement.submit',
               P('contact.admin'),
               $ctx->_current_adherent->getAttributes());

  $res->sendRedirect('/middle/payment.response/-/item/' . $facture->getKey());

}
catch (Exception $e) {
  $err->add($e);
}
