<?php

$res->setMenu('newsletters');
$res->setTitle(l('account.newsletter'));

try {

  $ctx->adherent_primary = Adherent::getCurrentPrimaryAdherent();

  NtdAccountManager::setCurrentModule(NtdAccountManager::MODULE_NEWSLETTERS);
  NtdAccountManager::setBreadCrumb();
  NtdAccountManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
