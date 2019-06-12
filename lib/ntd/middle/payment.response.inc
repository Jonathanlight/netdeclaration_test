<?php

try {

  //  Payment::response();

  $user = $req->getUser();

  $facture = Facture::getInstanceByKey($req->item);
  $adherent = NetDeclaration::getCurrentAdherent();

  //if (!$user->hasAccessTo($order)) {
  //  $log->error('order ('.intval($req->id).') bad user_id ('.$req->getUserId().')');
  //  throw new MaliciousException();
  //}
  if ($facture->adherent_id != $adherent->getId()) {
    $log->error('facture(' . intval($facture->getId()) . ') bad adherent (' . $adherent->getId() . ')');
    throw new MaliciousException();
  }


  /*if ($facture->status != Facture::STATUS_PENDING) {
    $log->error('facture(' . intval($facture->getId()) . ') bad status (' . $facture->status . ')');
    throw new Exception('Etat de de la facture invalide.');
  }*/

  $has_e_souscriptions = false;
  foreach ($facture->getSouscriptions() as $souscription) {
    if ($souscription->getService()->type == Service::TYPE_FORMULAIRE) {
      $has_e_souscriptions = true;
    }
  }

  $method = $facture->getMethod();


  $ctx->facture = $facture;
  $ctx->method = $method;
  $ctx->has_e_souscriptions = $has_e_souscriptions;

  //$res->setHead('paiement');
  //$res->useTemplate();

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_FACTURE);
  NtdMiddleManager::setBreadCrumb(array('Factures' => '/middle/factures',
                                        $facture->getType() . ' N°' . $facture->getId() => '/middle/facture/id/' . $facture->getId(),
                                        'Paiement - Confirmation'));
  NtdMiddleManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}