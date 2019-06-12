<?php

try {

  $facture = Facture::getInstanceByKey($req->item);

  $adherent = NetDeclaration::getCurrentAdherent();
  if ($facture->adherent_id != $adherent->getId()) {
    throw new MaliciousException('bad adherent');
  }
  if ($facture->status != Facture::STATUS_PENDING) {
    throw new MaliciousException('bad facture status');
  }

  $ctx->adherent = $adherent;
  $ctx->facture = $facture;
  $ctx->method = $facture->getMethod();


  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_FACTURE);
  NtdMiddleManager::setBreadCrumb(array('Factures' => '/middle/factures',
                                        $facture->getType() . ' N°' . $facture->getId() => '/middle/facture/id/' . $facture->getId(),
                                        'Paiement - Prélèvement'));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
