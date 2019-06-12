<?php

try {

  $souscriptions = NetDeclaration::getCurrentAdherent()->getSouscriptions(array('filters' => array('|<=|start_at' => Date::today(),
                                                                                                   '|>=|finish_at' => Date::today(),
                                                                                                   'status' => Souscription::STATUS_ACTIVE)));
  $ctx->souscriptions = $souscriptions;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
