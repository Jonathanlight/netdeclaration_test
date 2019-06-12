<?php

try {

  $service = Service::getInstance(38);

  foreach (Souscription::collect(array('filters' => array('service_id' => $service->getId()))) as $souscription) {
    $context = $souscription->context;
    if ($context['price_ht'] == 0) {
      print 'Souscription avec prix HT = 0 € [' . $souscription->getId() . '] - [Etat:' . Souscription::$statuses[$souscription->status] . '] Crée le ' . $souscription->getMeta('created_at') . "  \n";


      /*$factures = $souscription->getFactures();
     if ($factures->count() > 0) {
       $facture = $factures->first();
       print 'Facture[' . $facture->getId() . '] trouvée [Etat:'.Facture::$statuses[$facture->status].']'."\n";
       $data_prices = $facture->data_prices;
       $data_prices['price_ht'] += $context['price_unitaire'];
       $data_prices['price_plus_ht'] += $context['price_unitaire'];
       $data_prices['price_tva'] = $data_prices['percent_tva'] * $data_prices['price_ht'];
       $data_prices['price_ttc'] = $data_prices['price_tva'] * $data_prices['price_ht'];
       //$facture->setAttributes(array('data_prices' => $data_prices,
       //                              'price_ttc' => $data_prices['price_ttc']));
     }
     else {*/



      $context['quantity'] = 1;
      $context['price_ht'] = $context['prix_unitaire'];
      $attributes = array('context' => $context,
                          'price' => $context['price_ht']);



      $factures = $souscription->getFactures();
      if ($factures->count() > 0) {
        $facture = $factures->first();
        if ($facture->status != Facture::STATUS_PAYE && $souscription->status == Souscription::STATUS_ACTIVE) {
          $attributes['status'] = Souscription::STATUS_WAITING_PAIEMENT;
        }
      }

      $souscription->setAttributes($attributes);

      $adherent = $souscription->getAdherent();
      $facture = Facture::getInstance();
      $facture->setAdherent($adherent);
      $facture->addTarif($service->getTarif($adherent, Tarif::PRICE_TYPE_UNITAIRE, 1));
      //continue;
      $facture->calculate();
      $facture->commit(array('status' => Facture::STATUS_NON_PAYE,
                             'is_renew_auto' => 1,
                             'start_at' => $souscription->start_at,
                             'finish_at' => $souscription->finish_at,
                             'method_id' => Facture::getOldMethodID($adherent)));
      $facture->addSouscription($souscription);
      print 'Facture ajouté [' . $facture->getId() . ']' . "\n";
      //}
      

    }
  }

}
catch (Exception $e) {
  print $e->getMessage();
}
