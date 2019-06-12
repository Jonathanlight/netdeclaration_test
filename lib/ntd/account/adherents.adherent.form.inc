<?php

try {

  $adherent = array();
  $show_gestion = false;
  $main_adherent = Adherent::getCurrentPrimaryAdherent();

  $ctx->adherent = $adherent;
  $ctx->main_adherent = $main_adherent;
  $ctx->show_gestion = $show_gestion;

  NtdAccountManager::setCurrentModule(NtdAccountManager::MODULE_ADHERENTS);
  NtdAccountManager::setBreadCrumb(array(true, NtdAccountManager::getPageSnippet()->getProperty('title')));
  NtdAccountManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
