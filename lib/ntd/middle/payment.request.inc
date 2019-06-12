<?php

try {

  $facture = Facture::getInstance((int) $req->facture_id);

  if ($facture->status == Facture::STATUS_PAYE) {
    throw new Exception('facture ('.$facture->getId().') already paid');
  }

  $facture->setStatus(Facture::STATUS_PENDING);
  $facture->setVisit($req);
  $method = Method::getInstance($facture->method_id);

  $out = $method->request($facture);

  $log->trace($out, __FILE__);

  $ctx->_keep_templates = true;
  $res->reset();
  $res->write($out);  

}
catch (AuthException $e) {
  $err->add(l('error.access'));
}
catch (Exception $e) {
  if ($facture) {
    $log->trace('order [id='.$facture->id.'] [status='.$facture->status.']');
  }
  $log->error($e, __METHOD__);
  $err->add($e);
}