<?php

try {

  $souscription = Souscription::getInstance((int) $req->id);
  $souscription->setStatus(Souscription::STATUS_CANCELLED);

  /*foreach ($souscription->getFactures() as $facture) {
    $opts = array('filters' => array('|>|price' => 0,
                                     '|!=|status' => Souscription::STATUS_CANCELLED));
    if ($facture->getSouscriptions($opts)->count() < 1) {
      $facture->setStatus(Facture::STATUS_RESILIE);
    }
  }*/
  // Ordre de netdec, passage du status a la main

  $adherent = $souscription->getAdherent();

  $facture = Facture::getInstance();
  $facture->setAdherent($adherent);
  $facture->addPurchase(array(
    'name' => h($req->record['label']),
    'price' => h($req->record['amount']),
    'quantity' => 1));
  if ($facture->calculate() != 0) {
    $facture->commit(array('status' => Facture::STATUS_NON_PAYE, 'type' => Facture::TYPE_AVOIR));
    $facture->addSouscription($souscription);
    $facture->send();
  }

  $res->sendMessage('Cette souscription a été résiliée. Le service associé a été désactivé. La facture de remboursement a été envoyée à l\adhérent');

}
catch (Exception $e) {
  $err->add($e);
}
