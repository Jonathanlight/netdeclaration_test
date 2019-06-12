<?php

try {

  $show_gestion = false;
  if(in_array($ctx->_current_adherent->type, array(Adherent::TYPE_CEC, Adherent::TYPE_OGA))){
    $services_availables = $ctx->_current_adherent->getServicesAvailables();
    $show_gestion = in_array(Service::TYPE_EDI, $services_availables->asHash('id', 'type'));
  }

  $ctx->show_gestion = $show_gestion;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_ADHERENT);
  NtdMiddleManager::setBreadCrumb('Adhérent');
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
