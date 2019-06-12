<?php

try {

  $user = $req->getUser();

  $facture = Facture::getInstance((int) $req->id);
  if($facture->getAdherent()->getUser()->getId() != $user->getId()) {
    $ctx->_keep_templates = true;
    throw new MaliciousException();
  }
  $ctx->facture = $facture;

  $ctx->address = $facture->data_address;
  $ctx->adherent = $facture->data_adherent;
  $ctx->purchases = $facture->data_purchases;
  $ctx->prices = $facture->data_prices;

  $adherent = $facture->getAdherent();
  $ctx->user = $adherent->getUser();

  $res->setHead($facture);
  $res->useTemplates(null, 'skeleton.pdf', 'facture.print');
  $ctx->_keep_templates = true;

} catch (Exception $e) { $err->add($e); }
