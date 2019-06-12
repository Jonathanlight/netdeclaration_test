<?php

try {

  $opts = array('filters' => array('|>|price_ttc' => 0),
                'order' => array('id' => 'DESC'));
  $factures = $ctx->_current_adherent->getFactures($opts);

  $ctx->statuses = array(
    Facture::STATUS_RESILIE => 'Résiliée',
    Facture::STATUS_NON_PAYE => 'À payer',
    Facture::STATUS_PENDING => 'En attente du paiement',
    Facture::STATUS_PAYE => 'Payée',
  );

  $ctx->factures = $factures;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_FACTURE);
  NtdMiddleManager::setBreadCrumb(array('Factures'));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
