<?php

try {

  $form = (array) $req->form;


  $service = Service::getInstance((int) $form['service_id']);

  $tarif_forfait = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_FORFAIT);
  $total_price = 0;
  if ($tarif_forfait) {
    $total_price += $tarif_forfait->price;
  }


  if ($service->type == Service::TYPE_EDI) {
    $quantity = (int) $form['quantity'];
    if (empty($quantity) && $ctx->_current_adherent->type != Adherent::TYPE_OGA) {
      throw new Exception('Veuillez saisir le nombre de télétransmission');
    }
    elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_UNITAIRE)) {
      $tarif_unitaire = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_UNITAIRE, $quantity);
      if (!$tarif_unitaire) {
        throw new Exception('Veuillez nous contacter pour établissement devis personnalisé');
      }
    }
    elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIRET)) {
      $tarif_siret = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIRET);
    }
    elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIREN)) {
      $tarif_siren = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIREN);
    }
    elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_NO_FISCAL)) {
      $tarif_no_fiscal = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_NO_FISCAL);
    }
    else {
      throw new Exception('Veuillez nous contacter pour établissement devis personnalisé');
    }
  }
  elseif ($service->hasFlag(Service::FLAG_MANY_SOUSCRIPTIONS_PROCESS)) {
    $adherents = (array) $form['adherents'];

    if (count($adherents) < 1) {
      throw new Exception('Veuillez sélectionner au moins un adhérent.');
    }
    $quantity = count($adherents);
    if ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_UNITAIRE)) {
      $tarif_siret = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_UNITAIRE, $quantity); // $tarif_siret pour avoir le bon langage
      if (!$tarif_siret) {
        throw new Exception('Veuillez nous contacter pour établissement devis personnalisé');
      }
    }

    $required_tarif_forfait = null;
    $main_adherent = Adherent::getCurrentPrimaryAdherent();

    if ($service->service_id > 0) {
      $required_service = $service->getService();
      $opts = array('filters' => array('service_id' => $required_service->getId(),
                                       array(
                                         array('|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED),
                                               '|<=|start_at' => Date::today(),
                                               '|>=|finish_at' => Date::today()),
                                         array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))
                                       )));
      if ($required_service->hasFlag(Service::FLAG_ONLY_ONE_BY_USER)) {
        $main_adherent_souscription = $main_adherent->getSouscriptions($opts);
        if ($main_adherent_souscription->count() < 1) {
          $required_tarif_forfait = $required_service->getTarif($main_adherent, Tarif::PRICE_TYPE_FORFAIT);
        }
      }
      else {
        // récupérer tous les tarifs forfaits pour chaque adhérents
      }

    }

    $ctx->required_tarif_forfait = $required_tarif_forfait;
    $total_price += $required_tarif_forfait->price;
    $ctx->adherents = $adherents;
  }
  else {
    // service requis
    $required_tarif_forfait = null;
    $main_adherent = Adherent::getCurrentPrimaryAdherent();

    if ($service->service_id > 0) {
      $required_service = $service->getService();
      $opts = array('filters' => array('service_id' => $required_service->getId(),
                                       array(
                                         array('|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED),
                                               '|<=|start_at' => Date::today(),
                                               '|>=|finish_at' => Date::today()),
                                         array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))
                                       )));
      if ($required_service->hasFlag(Service::FLAG_ONLY_ONE_BY_USER)) {
        $main_adherent_souscription = $main_adherent->getSouscriptions($opts);
        if ($main_adherent_souscription->count() < 1) {
          $required_tarif_forfait = $required_service->getTarif($main_adherent, Tarif::PRICE_TYPE_FORFAIT);
        }
      }
    }

    $ctx->required_tarif_forfait = $required_tarif_forfait;
    if ($required_tarif_forfait) {
      $total_price += $required_tarif_forfait->price;
    }

    if ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE)) {
      $quantity = 1;
      $souscription_quantity = GreffeManager::getSouscriptionQuantityForCurrentDossier();
      if ($service->service_id > 0 && GreffeManager::isFirstSouscriptionConditionForCurrentDossier()) {
        $required_service = $service->getService();
        if ($required_service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity)) {
          $tarif_forfait_greffe = $required_service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity);
        }
      }
      $tarif_greffe = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity);
    }
  }


  if ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_LOYER)) {
    $quantity = (int) $form['quantity'];
    $tarif_loyer = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_LOYER);
    if (!$tarif_loyer) {
      throw new Exception('Veuillez nous contacter pour établissement devis personnalisé.');
    }
    $total_price += ($tarif_loyer->price * $quantity);
  }



  if ($tarif_unitaire) {
    $total_price += ($tarif_unitaire->price * $quantity);
  }
  if ($tarif_siret) {
    $total_price += ($tarif_siret->price * $quantity);
  }
  if ($tarif_siren) {
    $total_price += ($tarif_siren->price * $quantity);
  }
  if ($tarif_no_fiscal) {
    $total_price += ($tarif_no_fiscal->price * $quantity);
  }
  if ($tarif_greffe) {
    $total_price += ((float)$tarif_forfait_greffe->price + (float)$tarif_greffe->price);
  }


  $ctx->service = $service;
  $ctx->tarif_forfait = $tarif_forfait;
  $ctx->tarif_unitaire = $tarif_unitaire;
  $ctx->tarif_siret = $tarif_siret;
  $ctx->tarif_siren = $tarif_siren;
  $ctx->tarif_no_fiscal = $tarif_no_fiscal;
  $ctx->tarif_loyer = $tarif_loyer;
  $ctx->tarif_forfait_greffe = $tarif_forfait_greffe;
  $ctx->tarif_greffe = $tarif_greffe;
  $ctx->quantity = $quantity;
  $ctx->total_price = $total_price;


  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
