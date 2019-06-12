<?php

try {

  $form = (array) $req->form;
  $adherent = array('type' => $form['adherent_type'],
                    'level' => $form['adherent_level']);
  $main_adherent = $adherent;

  if (empty($form['demandeur_name'])) {
    throw new Exception('Veuillez saisir le Nom du demandeur');
  }

  if (empty($form['demandeur_details'])) {
    throw new Exception('Veuillez saisir les Informations du demandeur');
  }

  if (empty($form['expire_at'])) {
    throw new Exception('Une date de validité doit être saisie');
  }


  $estimation = Estimation::getInstance();
  $estimation->commit(array(
                        'adherent_level' => $form['adherent_level'],
                        'demandeur_name' => $form['demandeur_name'],
                        'demandeur_details' => $form['demandeur_details'],
                        'adherent_type' => $form['adherent_type'],
                        'country_id' => $form['country_id'],
                        'expire_at' => $form['expire_at'],
                        'name' => $form['name'],
                        'tax_percent' => $form['tax_percent'],
                      ));

  $has_service_acces_edi = false;

  foreach (array_filter((array) $form['services_included']) as $service_id) {
    $service = Service::getInstance($service_id);


    if ($service->hasFlag(Service::FLAG_MANY_SOUSCRIPTIONS_PROCESS)) {
      $adherents = array();

      if ($service->service_id > 0) {
        $required_service = $service->getService();
        if ($required_service->hasFlag(Service::FLAG_ONLY_ONE_BY_USER)) {
          $required_tarif_forfait = $required_service->getTarif($main_adherent, Tarif::PRICE_TYPE_FORFAIT);
          $estimation->addTarif($required_tarif_forfait, 1);
        }
      }


      $nb_adherents = (int) $form['services'][$service->getId()]['adherents'];

      $tarif_unitaire = $service->getTarif($main_adherent, Tarif::PRICE_TYPE_UNITAIRE, $nb_adherents); // $tarif_siret pour avoir le bon langage

//      for ($i = 0; $i < $nb_adherents; $i++) {
        $estimation->addTarif($tarif_unitaire, $nb_adherents);

        // offer E-CVAE Service if service == E-liasse (ID = 38)
        $service_eliasse_id = 38;
        $service_cvae_id = 13;
        if ($service->getId() == $service_eliasse_id) {
          $cvae_service = Service::getInstance($service_cvae_id);
          $tarif_forfait = $cvae_service->getTarif($adherent, Tarif::PRICE_TYPE_FORFAIT);
          if ($tarif_forfait) {
            $estimation->addTarif($tarif_forfait, $nb_adherents, 0);
          }
        }
//      }
    }
    else {
      $quantity = (int) $form['services'][$service->getId()]['quantity'];

      $tarif_forfait = $service->getTarif($adherent, Tarif::PRICE_TYPE_FORFAIT);
      if ($tarif_forfait) {
        $estimation->addTarif($tarif_forfait, 1);
      }
      if ($service->hasTarif($adherent, Tarif::PRICE_TYPE_UNITAIRE)) {
        $estimation->addTarif($service->getTarif($adherent, Tarif::PRICE_TYPE_UNITAIRE, $quantity), $quantity);
      }
      elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_SIRET)) {
        $estimation->addTarif($service->getTarif($adherent, Tarif::PRICE_TYPE_SIRET), $quantity);
      }
      elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_SIREN)) {
        $estimation->addTarif($service->getTarif($adherent, Tarif::PRICE_TYPE_SIREN), $quantity);
      }
      elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_NO_FISCAL)) {
        $estimation->addTarif($service->getTarif($adherent, Tarif::PRICE_TYPE_NO_FISCAL), $quantity);
      }
      elseif ($service->hasTarif($adherent, Tarif::PRICE_TYPE_LOYER)) {
        $estimation->addTarif($service->getTarif($adherent, Tarif::PRICE_TYPE_LOYER), $quantity);
      }

      if ($service->type == Service::TYPE_EDI
        && !$service->hasFlag(Service::FLAG_ACCES_EDI_OPTIONNAL)
      ) {

        $service_acces_edi = Service::getInstance(NetDeclarationManager::SERVICE_ACCES_EDI);
        $tarif_edi = $service_acces_edi->getTarif($adherent, Tarif::PRICE_TYPE_FORFAIT);
        if ($tarif_edi && !$has_service_acces_edi) {
          $estimation->addTarif($tarif_edi, 1);
          $has_service_acces_edi = true;
        }
      }
    }

  }

  $res->sendData($estimation->generatePdf());
}
catch (Exception $e) {
  $err->add($e);
}
