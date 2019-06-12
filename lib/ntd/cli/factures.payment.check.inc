<?php

try {


  foreach (Facture::collect(array('filters' => array('status' => Facture::STATUS_PAYE))) as $facture) {
    if ($facture->method_id < 1) {
      //print "FACTURE [" . $facture->getId() . "] Pas de méthode de paiement ..\n";
      //continue;
    }
    if ($facture->method_id != 1) continue;
    $payed = false;
    $payments = $facture->getPayments();
    foreach ($payments as $payment) {
      if ($payment->isReceived()) {
        $payed = true;
      }
    }
    if (!$payed) {
      print "FACTURE [" . $facture->getId() . "] Aucun paiement trouvé \n";
    }
  }


}
catch (Exception $e) {
  print $e->getMessage();
}
