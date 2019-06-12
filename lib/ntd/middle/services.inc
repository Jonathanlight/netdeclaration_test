<?php

try {

  $opts = array('filters' => array(array('|<=|start_at' => Date::today(),
                                         '|>=|finish_at' => Date::today(),
                                         '|IN|status' => array(Souscription::STATUS_ACTIVE,
                                                               Souscription::STATUS_CANCELLING_ASKED)),
                                   array('OR' => array('status' => Souscription::STATUS_WAITING_PAIEMENT))),
                'include' => array('service'),
                'order' => array('status' => 'DESC',

                                 'finish_at' => 'ASC',
                                 'service_name' => 'ASC'
                ));
  $souscriptions = NetDeclaration::getCurrentAdherent()->getSouscriptions($opts);
  $ctx->souscriptions = $souscriptions;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb();
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
