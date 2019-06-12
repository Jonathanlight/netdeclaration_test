<?php

try {

  $liasse_service_id = 38;
  $ecice_service_id = 48;

  $souscriptions_liasse_active = Souscription::collect(array('filters' => array('|IN|status' => array(Souscription::STATUS_CANCELLING_ASKED,
                                                                                                      Souscription::STATUS_WAITING_PAIEMENT,
                                                                                                      Souscription::STATUS_ACTIVE),
                                                                                'service_id' => $liasse_service_id,
                                                                                'souscription_renew_id' => 0)));

  $service_ecice = Service::getInstance($ecice_service_id);

  print $souscriptions_liasse_active->count() . "\n";

  $adherent_ids = array();

  foreach ($souscriptions_liasse_active as $souscription_liasse) {
    if (in_array($souscription_liasse->status, array(Souscription::STATUS_ACTIVE,
                                                     Souscription::STATUS_CANCELLING_ASKED))) {
      if (!(strtotime($souscription_liasse->start_at) < time() && strtotime($souscription_liasse->finish_at) > time())) {
        continue;
      }
    }
//    print "souscription : " . $souscription->getId() . "\n";
    $adherent = $souscription_liasse->getAdherent();

    if (in_array($adherent->getId(), $adherent_ids)) {
      continue;
    }

//    print "Adherent : " . $adherent->getId() . "\n";
    $souscription_cices = Souscription::collect(array('filters' => array('service_id' => $ecice_service_id,
                                                                         'souscription_renew_id' => 0,
                                                                         'adherent_id' => $adherent->getId())));
    if ($souscription_cices->count() > 0) {
      print "already have cice. " . ++$trere . " continue\n";
      continue;
    }

    $souscription_cice = Souscription::getInstance();
    $offer_context = Souscription::getSouscriptionContext($service_ecice,
                                                          $adherent,
                                                          array('quantity' => 1));
    $offer_context['prix_forfait'] = 0;
    $offer_context['price_ht'] = 0;

    $souscription_cice->commit(array('adherent_id' => $adherent->getId(),
                                     'service_id' => $ecice_service_id,
                                     'sign_at' => Date::today(),
                                     'start_at' => $souscription_liasse->start_at,
                                     'finish_at' => $souscription_liasse->finish_at,
                                     'price' => 0,
                                     'status' => $souscription_liasse->status,
                                     'context' => $offer_context,
                                     'is_renewable' => $souscription_liasse->is_renewable));

    $adherent_ids[$adherent->getId()] = $adherent->getId();

  }

}
catch (Exception $e) {
  $err->add($e);
}