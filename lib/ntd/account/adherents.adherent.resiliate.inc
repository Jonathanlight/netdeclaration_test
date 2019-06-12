<?php

try {

  $current_adherent = Adherent::getCurrentPrimaryAdherent();
  $adherent = Adherent::getInstance(array('id' => (int) $req->id,
                                          'adherent_id' => $current_adherent->getId()));
  $current_souscription = $adherent->getCurrentSouscription(NetDeclarationManager::SERVICE_ADHESION_PROFILE_SECONDAIRE);
  $current_souscription->commit(array('status' => Souscription::STATUS_CANCELLING_ASKED));

  NtdAccountManager::setCurrentModule(NtdAccountManager::MODULE_ADHERENTS);
  NtdAccountManager::setBreadCrumb(array(true, NtdAccountManager::getPageSnippet()->getProperty('title')));
  NtdAccountManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
