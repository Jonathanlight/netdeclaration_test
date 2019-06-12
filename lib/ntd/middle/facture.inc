<?php

try {

  $facture = Facture::getInstance((int) $req->id);

  if ($facture->getAdherent()->user_id !== $ctx->_current_adherent->user_id) {
    throw new MaliciousException();
  }

  $ctx->facture = $facture;
  $ctx->address = $facture->data_address;
  $ctx->adherent = $facture->data_adherent;
  $ctx->purchases = $facture->data_purchases;
  $ctx->prices = $facture->data_prices;

  /*if ($req->template == 'print') {
    $ctx->_keep_templates = true;
    $res->useTemplates(array(null, 'ntd:account.facture.print'));
    $res->setLink('stylesheet', array('media' => 'print', 'href' => '/app/ntd/styles/print.css', 'type' => 'text/css'));
  }
  else {
    $res->setLink('stylesheet', array('media' => 'print', 'href' => '/app/ntd/styles/front.css', 'type' => 'text/css'));
    $res->setLink('stylesheet', array('media' => 'print', 'href' => '/app/ntd/styles/account.css', 'type' => 'text/css'));
    $res->setLink('stylesheet', array('media' => 'print', 'href' => '/app/ntd/styles/print.css', 'type' => 'text/css'));
  }*/

  //$res->setTitle($facture->getType() . ' N°' . $facture->getId());
  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_FACTURE);
  NtdMiddleManager::setBreadCrumb(array('Factures' => '/middle/factures',
                                        $facture->getType() . ' N°' . $facture->getId()));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO($facture->getType() . ' N°' . $facture->getId());
  NtdMiddleManager::setPageTitle($facture->getType() . ' N°' . $facture->getId());

}
catch (Exception $e) {
  $err->add($e);
}
