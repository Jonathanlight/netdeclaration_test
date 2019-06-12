<?php

class FactureRepository {

  public static function setFactureStatusBackToPending($facture_id) {
    $facture = Facture::getInstance((int) $facture_id);
    $facture->setStatus(Facture::STATUS_NON_PAYE);

    $souscriptions = $facture->getSouscriptions();
    foreach ($souscriptions as $souscription) {
      $souscription->setStatus(Souscription::STATUS_WAITING_PAIEMENT);
    }
  }

}