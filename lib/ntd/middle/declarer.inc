<?php

try {

  $current_adherent = NetDeclaration::getCurrentAdherent();

  $services = Service::collect(array('filters' => array('type' => Service::TYPE_FORMULAIRE,
                                                        'status' => Service::STATUS_ONLINE)));
  $available_service_ids = $current_adherent->getAvailableServiceFormulaireIDs();

  $services_dectypes = array();
  foreach ($services as $service) {
    $services_dectypes[$service->getId()] = $service->getDectypes(array('include' => array('millesime'),
                                                                        'filters' => array('|>|status' => 0),
                                                                        'order' => array(T('millesime') . '.name' => 'DESC',
                                                                                         'document_code' => 'ASC',
                                                                                         'position' => 'ASC',
                                                                                         'name' => 'ASC')));
  }

  $services_sorted = array();
  foreach ($services as $service) {
    if (in_array($service->getId(), $available_service_ids)) {
      $services_sorted[] = $service;
    }
  }
  foreach ($services as $service) {
    if (!in_array($service->getId(), $available_service_ids)) {
      $services_sorted[] = $service;
    }
  }

  /*$service_selected_id = $req->getCookie()->getAttribute('action:services:service_selected');
  if (!$services->getItemID($service_selected_id)) {
    $service_selected_id = reset($services_sorted)->getId();
    $req->getCookie()->setAttribute('action:services:service_selected', $service_selected_id);
  }*/
  $service_selected_id = reset($services_sorted)->getId();


  $ctx->services = $services_sorted;
  $ctx->services_dectypes = $services_dectypes;
  $ctx->available_service_ids = $available_service_ids;
  $ctx->service_selected_id = $service_selected_id;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_DECLARATION);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();


}
catch (Exception $e) {
  $err->add($e);
}
