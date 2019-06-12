<?php

try {

  $current_adherent = NetDeclaration::getCurrentAdherent();

  $opts = array('filters' => array(array('|<=|start_at' => Date::today(),
                                         '|>=|finish_at' => Date::today(),
                                         'status' => Souscription::STATUS_ACTIVE),
                                   array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))));
  $souscriptions = $current_adherent->getSouscriptions($opts);


  $classic_filters = array('|%%|adherent_types' => $current_adherent->type,
                           '|!IN|type' => array(Service::TYPE_ADHESION, Service::TYPE_AUTRE),
                           'status' => Service::STATUS_ONLINE);
  if ($souscriptions->count() > 0) {
    $classic_filters['|!IN|id'] = $souscriptions->asHash('id', 'service_id');
  }


  $opts = array('filters' => $classic_filters);

  if ($current_adherent->isMainAdherent()) {
    $ctx->adherents = Adherent::getAllAdherent($current_adherent->user_id,
                                               array('order' => array('adherent_id' => 'ASC',
                                                                      'company' => 'ASC')));

    $filters = array('|&|flags' => Service::FLAG_MANY_SOUSCRIPTIONS_PROCESS,
                     'status' => Service::STATUS_ONLINE);
    if ($ctx->adherents->count() == 1 && $souscriptions->count() > 0) {
      $filters['|!IN|id'] = $souscriptions->asHash('id', 'service_id');
    }
    $opts['filters'][]['OR'] = $filters;
  }
  else {
    $opts['filters'][]['OR'] = array('|&|flags' => Service::FLAG_MANY_SOUSCRIPTIONS_PROCESS,
                                     'status' => Service::STATUS_ONLINE,
                                     '|!IN|id' => $souscriptions->asHash('id', 'service_id'));
    $ctx->adherents = Adherent::collect(array('filters' => array('id' => $current_adherent->getId())));
  }

  $service_efis = Service::collect(array('filters' => array('type' => Service::TYPE_FORMULAIRE,
                                                            $opts['filters']),
                                         'order' => array('position_catalogue' => 'ASC')));
  $service_edis = Service::collect(array('filters' => array('type' => Service::TYPE_EDI,
                                                            $opts['filters']),
                                         'order' => array('position_catalogue' => 'ASC')));


  $ctx->service_efis = $service_efis;
  $ctx->service_edis = $service_edis;


  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}


