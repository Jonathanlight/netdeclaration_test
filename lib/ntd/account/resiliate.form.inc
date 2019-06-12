<?php

try {

  $adherent = Adherent::getCurrentPrimaryAdherent();
  $opts = array('filters' => array('adherent_id' => $adherent->getId(),
                                   'service_id' => NetDeclarationManager::SERVICE_ADHESION_MAIN_PROFILE,
                                   array(array('|<=|start_at' => Date::today(),
                                               '|>=|finish_at' => Date::today(),
                                               'status' => Souscription::STATUS_ACTIVE),
                                         array('OR' => array(array('status' => Souscription::STATUS_WAITING_PAIEMENT)))),

  ));
  $souscriptions = Souscription::collect($opts);

  $ctx->has_current_souscription = ($souscriptions->count() > 0);

  NtdAccountManager::setCurrentModule(NtdAccountManager::MODULE_RESILIATION);
  NtdAccountManager::setBreadCrumb();
  NtdAccountManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
