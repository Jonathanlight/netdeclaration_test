<?php

try {

  $form = (array) $req->form;

  $partenaire = null;

  if ($ctx->_current_adherent->partenaire_id > 0 && Partenaire::exists($ctx->_current_adherent->partenaire_id)) {
    $partenaire = $ctx->_current_adherent->getPartenaire();
  }

  $service = Service::getInstance((int) $form['service_id']);

  $quantity = (int) $form['quantity'];

  $context = Souscription::getSouscriptionContext($service,
                                                  $ctx->_current_adherent,
                                                  array('quantity' => $quantity));
  $record = array(
    'adherent_id' => $ctx->_current_adherent->getId(),
    'partenaire_id' => $partenaire ? $partenaire->getId() : 0,
    'service_id' => $service->getId(),
    'sign_at' => Date::today(),
    'status' => Souscription::STATUS_WAITING_PAIEMENT,
    'context' => $context,
    'price' => $context['price_ht']
  );
  $souscription = Souscription::getInstance();
  $souscription->commit($record);

  // Facture
  $facture = Facture::getInstance();
  $facture->setAdherent($ctx->_current_adherent);


  $tarif_forfait = $service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_FORFAIT);
  if ($tarif_forfait) {
    $facture->addTarif($tarif_forfait, 1);
  }
  if ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_UNITAIRE)) {
    $facture->addTarif($service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_UNITAIRE, $quantity), $quantity);
  }
  elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIRET)) {
    $facture->addTarif($service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIRET), $quantity);
  }
  elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIREN)) {
    $facture->addTarif($service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_SIREN), $quantity);
  }
  elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_NO_FISCAL)) {
    $facture->addTarif($service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_NO_FISCAL), $quantity);
  }
  elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_LOYER)) {
    $facture->addTarif($service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_LOYER), $quantity);
  }
  elseif ($service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE)) {
    $quantity = 1;
    $souscription_quantity = GreffeManager::getSouscriptionQuantityForCurrentDossier();
    if ($service->service_id > 0 && GreffeManager::isFirstSouscriptionConditionForCurrentDossier()) {
      $required_service = $service->getService();
      if ($required_service->hasTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity)) {
        $facture->addTarif($required_service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity));
      }
    }
    $facture->addTarif($service->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_GREFFE, $souscription_quantity));
  }




  if ($service->type == Service::TYPE_EDI && !$service->hasFlag(Service::FLAG_ACCES_EDI_OPTIONNAL)) {
    $ctx->_current_adherent->commit(array('is_free_membership' => 0));
    if (!$ctx->_current_adherent->hasAccesEDI()) {
      $service_acces_edi = Service::getInstance(NetDeclarationManager::SERVICE_ACCES_EDI);
      $tarif_edi = $service_acces_edi->getTarif($ctx->_current_adherent, Tarif::PRICE_TYPE_FORFAIT);
      $record = array(
        'adherent_id' => $ctx->_current_adherent->getId(),
        'partenaire_id' => $partenaire ? $partenaire->getId() : 0,
        'service_id' => $service_acces_edi->getId(),
        'sign_at' => Date::today(),
        'status' => Souscription::STATUS_WAITING_PAIEMENT,
        'context' => array('prix_forfait' => $tarif_edi->price,
                           'price_ht' => $tarif_edi->price),
        'price' => $tarif_edi->price
      );
      if ($partenaire) {
        if ($partenaire->hasService($service_acces_edi->getId()) && $partenaire->status == Partenaire::STATUS_ONLINE) {
          $commission = $tarif_edi->price * (float) $partenaire->commission / 100;
          $record['commission'] = $commission;
          $record['context']['commission'] = $commission;
        }
      }
      $souscription_edi = Souscription::getInstance();
      $souscription_edi->commit($record);

      if ($tarif_edi) {
        $facture->addTarif($tarif_edi, 1);
      }

    }
  }


  // Paiement du service requis
  $main_adherent = Adherent::getCurrentPrimaryAdherent();
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

        $context = Souscription::getSouscriptionContext($required_service,
                                                        $main_adherent,
                                                        array('quantity' => 1));
        $record = array('adherent_id' => $main_adherent->getId(),
                        'service_id' => $required_service->getId(),
                        'sign_at' => Date::today(),
                        'status' => Souscription::STATUS_WAITING_PAIEMENT,
                        'context' => $context,
                        'price' => $context['price_ht']);
        $souscription_required = Souscription::getInstance();
        $souscription_required->commit($record);

        if ($required_tarif_forfait) {
          $facture->addTarif($required_tarif_forfait, 1);
        }
      }
    }
  }

  if ($facture->calculate() > 0) {
    $facture->commit(array(
      'status' => Facture::STATUS_NON_PAYE,
      'method_id' => Facture::getOldMethodID($ctx->_current_adherent)
    ));
    $facture->addSouscription($souscription);
    if ($souscription_edi) $facture->addSouscription($souscription_edi);
    if ($souscription_required) $facture->addSouscription($souscription_required);

    $facture->send();
  }
  else {
    $souscription->setStatus(Souscription::STATUS_ACTIVE);
  }


  Letter::send('souscription.demande.user',
               $ctx->_current_adherent->getEmail(),
               array('adherent.first_name' => $ctx->_current_adherent->first_name,
                     'adherent.last_name' => $ctx->_current_adherent->last_name,
                     'adherent.id' => $ctx->_current_adherent->getId(),
                     'adherent.siret' => $ctx->_current_adherent->siret,
                     'service.name' => $service->name,
                     'footer' => NetDeclaration::getMailFooter()));
  Letter::send('souscription.demande.ntd',
               NetDeclaration::getMailAdmin(),
               array('adherent.first_name' => $ctx->_current_adherent->first_name,
                     'adherent.last_name' => $ctx->_current_adherent->last_name,
                     'adherent.id' => $ctx->_current_adherent->getId(),
                     'adherent.siret' => $ctx->_current_adherent->siret,
                     'service.name' => $service->name,
                     'footer' => NetDeclaration::getMailFooter()));


  $ctx->facture = $facture;
  $ctx->souscription = $souscription;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
