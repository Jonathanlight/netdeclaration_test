<?php

try {

  $facture = Facture::getInstance(array('id' => (int) $req->facture_id,
                                        'adherent_id' => $ctx->_current_adherent->getId()));

  $ctx->methods = Method::collect(array('filters' => array('status' => 1)));
  $ctx->facture = $facture;
  $ctx->snippet = Snippet::getInstance('account.paiement');

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_FACTURE);
  NtdMiddleManager::setBreadCrumb(array('Factures' => '/middle/factures',
                                        $facture->getType() . ' N°' . $facture->getId() => '/middle/facture/id/' . $facture->getId(),
                                        'Paiement - Choix'));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
