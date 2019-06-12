<?php

$res->setMenu('adherents.secondaries');
$res->setTitle(l('account.title.adherents.secondaries'));

try {

  $adherent_primary = Adherent::getCurrentPrimaryAdherent();
  $adherents_secondaries = $adherent_primary->getAdherentsSecondaries();

  $ctx->profile = $adherent_primary;
  $ctx->adherents_secondaries = $adherents_secondaries;
  $ctx->profil_secondary_id = (int) $req->profil_secondary_id;
  $ctx->tab = h($req->tab);

  NtdAccountManager::setCurrentModule(NtdAccountManager::MODULE_ADHERENTS);
  NtdAccountManager::setBreadCrumb();
  NtdAccountManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
