<?php

try {

  $souscription = Souscription::getInstance($req->id);
  $adherent = $souscription->getAdherent();

  $date_today = Date::today();
  $messages = array();

  $finish_before = ($adherent->type == Adherent::TYPE_CEC) ? Date::today() : Date::toDb(strtotime('next month', strtotime($date_today)));
  if (Date::asTimestamp($souscription->finish_at) >= Date::asTimestamp($finish_before)) {
    $messages[] = "La souscription se termine après le $finish_before. Date de fin de la souscription : $souscription->finish_at";
  }
  if (Date::asTimestamp($souscription->finish_at) < Date::asTimestamp($date_today)) {
    $messages[] = "La souscription se termine avant la date d'aujourdhui";
  }
  if ($souscription->status != Souscription::STATUS_ACTIVE) {
    $messages[] = "La souscription n'est pas active";
  }
  if ($souscription->souscription_renew_id > 0) {
    $messages[] = "La souscription a déjà été renouvellée. [ID de la nouvelle souscription : $souscription->souscription_renew_id]";
  }

  $souscriptions_already_renewed = $adherent->getSouscriptions(array('filters' => array('|>=|start_at' => $finish_before,
                                                                                        'service_id' => $souscription->service_id,
                                                                                        '|IN|status' => array(Souscription::STATUS_ACTIVE,
                                                                                                              Souscription::STATUS_WAITING_PAIEMENT))));
  if ($souscriptions_already_renewed->count() > 0) {
    $messages[] = "La souscription a déjà été renouvellée, sans passer par la facturation automatique. [ID de la nouvelle(s) souscription(s) : "
        . implode(', ', $souscriptions_already_renewed->count()) . "]";
  }


  if (Service::exists($souscription->service_id)) {
    $service = $souscription->getService();
    if ($service->type == Service::TYPE_EDI) {
      $quantity_used = $souscription->getSuivisCount();
      if (!($quantity_used > 0) && $adherent->type != Adherent::TYPE_OGA) {
        $messages[] = "Aucune tranmission effectuée avec ce service (compte : ".$souscription->getSuivisCount().") et cet adhérent n'est pas OGA.";
      }
    }
  }
  else {
    $messages[] = "Le service associé n'existe plus. [ID du service : $souscription->service_id]";
  }


  if (count($messages) > 0) {
    $messages = implode("\n", $messages);
  } else {
    $messages = "Cette souscription peut-être renouvellée";
  }
  $res->sendMessage($messages);

}
catch (Exception $e) {
  $err->add($e);
}
