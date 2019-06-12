<?php

try {

  $form = (array) $req->form;
  $service = Service::getInstance((int) $form['service_id']);

  $main_adherent = Adherent::getCurrentPrimaryAdherent();
  $adherents = array();

  if ($service->service_id > 0) {
    $required_service = $service->getService();
    if ($required_service->hasFlag(Service::FLAG_ONLY_ONE_BY_USER)) {
      $opts = array('filters' => array('service_id' => $required_service->getId(),
                                       array(
                                         array('|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED),
                                               '|<=|start_at' => Date::today(),
                                               '|>=|finish_at' => Date::today()),
                                         array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))
                                       )));
      $main_adherent_souscription = $main_adherent->getSouscriptions($opts);
      if ($main_adherent_souscription->count() < 1) {
        $required_tarif_forfait = $required_service->getTarif($main_adherent, Tarif::PRICE_TYPE_FORFAIT);
        $facture = Facture::getInstance();
        $facture->setAdherent($main_adherent);
        $facture->addTarif($required_tarif_forfait, 1);

        $context = Souscription::getSouscriptionContext($required_service,
                                                        $main_adherent,
                                                        array('quantity' => 1));
        $record = array('adherent_id' => $main_adherent->getId(),
                        'service_id' => $required_service->getId(),
                        'sign_at' => Date::today(),
                        'status' => Souscription::STATUS_WAITING_PAIEMENT,
                        'context' => $context,
                        'price' => $context['price_ht']);
        $souscription = Souscription::getInstance();
        $souscription->commit($record);

        $adherents[$main_adherent->getId()]['facture'] = $facture;
        $adherents[$main_adherent->getId()]['souscriptions'][] = $souscription;
      }
    }
  }


  $quantity = count($form['adherents']);

  $tarif_unitaire = $service->getTarif($main_adherent, Tarif::PRICE_TYPE_UNITAIRE, $quantity); // $tarif_siret pour avoir le bon langage
  $context = array();
  $context['prix_unitaire'] = $tarif_unitaire->price;
  $context['quantity'] = 1;
  $context['qty_min'] = $tarif_unitaire->qty_min;
  $context['qty_max'] = $tarif_unitaire->qty_max;
  $context['price_type'] = $tarif_unitaire->price_type;
  $context['price_ht'] = 1 * $tarif_unitaire->price;

  foreach ((array) $form['adherents'] as $adherent) {
    $adherent = Adherent::getInstance($adherent);

    $exists_opts = array('filters' => array('service_id' => $service->getId(),
                                            'adherent_id' => $adherent->getId(),
                                            array(
                                              array('|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED),
                                                    '|<=|start_at' => Date::today(),
                                                    '|>=|finish_at' => Date::today()),
                                              array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))
                                            )));
    if (Souscription::collect($exists_opts)->count() > 0) {
      S('log')->trace($exists_opts, 'Souscription already exists');
      continue;
    }


    $adherents[$adherent->getId()]['adherent'] = $adherent;

    $record = array('adherent_id' => $adherent->getId(),
                    'service_id' => $service->getId(),
                    'sign_at' => Date::today(),
                    'status' => Souscription::STATUS_WAITING_PAIEMENT,
                    'context' => $context,
                    'price' => $context['price_ht']);
    $souscription = Souscription::getInstance();
    $souscription->commit($record);
    $adherents[$adherent->getId()]['souscriptions'][] = $souscription;


    // Facture
    if ($adherents[$adherent->getId()]['facture']) {
      $facture = $adherents[$adherent->getId()]['facture'];
    }
    else {
      $facture = Facture::getInstance();
      $facture->setAdherent($adherent);
    }
    $facture->addTarif($tarif_unitaire, 1);
    $adherents[$adherent->getId()]['facture'] = $facture;


    // offer E-CVAE Service if service == E-liasse (ID = 38)
    $service_eliasse_id = 38;
    $services_id_offer = array(13, 48);
    if ($service->getId() == $service_eliasse_id) {
      foreach ($services_id_offer as $service_id_offer) {
        $exists_opts = array('filters' => array('service_id' => $service_id_offer,
                                                'adherent_id' => $adherent->getId(),
                                                array(
                                                  array('|IN|status' => array(Souscription::STATUS_ACTIVE, Souscription::STATUS_CANCELLING_ASKED),
                                                        '|<=|start_at' => Date::today(),
                                                        '|>=|finish_at' => Date::today()),
                                                  array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))
                                                )));
        if (Souscription::collect($exists_opts)->count() < 1) {
          $offer_service = Service::getInstance($service_id_offer);
          $offer_context = Souscription::getSouscriptionContext($offer_service,
                                                               $adherent,
                                                               array('quantity' => 1));
          $offer_context['prix_forfait'] = 0;
          $offer_context['price_ht'] = 0;
          $record = array('adherent_id' => $adherent->getId(),
                          'service_id' => $service_id_offer,
                          'sign_at' => Date::today(),
                          'status' => Souscription::STATUS_WAITING_PAIEMENT,
                          'context' => $offer_context,
                          'price' => 0);
          $souscription = Souscription::getInstance();
          $souscription->commit($record);
          $adherents[$adherent->getId()]['souscriptions'][] = $souscription;
          $facture->addPurchase(array(
                                  'name' => '(Service offert) ' . $offer_service->name,
                                  'price' => 0,
                                  'quantity' => 1,
                                  'date_from' => null,
                                  'date_to' => null,
                                  'force_display' => 1,
                                ));
        }
      }

    }

    Letter::send('souscription.demande.user',
                 $adherent->getEmail(),
                 array('adherent.first_name' => $adherent->first_name,
                       'adherent.last_name' => $adherent->last_name,
                       'adherent.id' => $adherent->getId(),
                       'adherent.siret' => $adherent->siret,
                       'service.name' => $service->name,
                       'footer' => NetDeclaration::getMailFooter()));
    Letter::send('souscription.demande.ntd',
                 NetDeclaration::getMailAdmin(),
                 array('adherent.first_name' => $adherent->first_name,
                       'adherent.last_name' => $adherent->last_name,
                       'adherent.id' => $adherent->getId(),
                       'adherent.siret' => $adherent->siret,
                       'service.name' => $service->name,
                       'footer' => NetDeclaration::getMailFooter()));
  }


  foreach ($adherents as $adherent_id => $adherent_hash) {
    $facture = $adherent_hash['facture'];
    if ($facture->calculate() > 0) {
      $facture->commit(array(
                         'status' => Facture::STATUS_NON_PAYE,
                         'method_id' => Facture::getOldMethodID($adherent)
                       ));
      foreach ((array) $adherent_hash['souscriptions'] as $souscription) {
        $facture->addSouscription($souscription);
      }
      $facture->send();
    }
    else {
      foreach ((array) $adherent_hash['souscriptions'] as $souscription) {
        $souscription->setStatus(Souscription::STATUS_ACTIVE);
      }
      unset($adherents[$adherent_id]['facture']);
    }
  }


  $ctx->adherents = $adherents;
  $ctx->service = $service;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();
}
catch (Exception $e) {
  $err->add($e);
}
