<?php

try {

  $form = (array) $req->form;

  $opts = array('adherent_id' => $ctx->_current_adherent->getId(),
                'id' => (int) $form['souscription_id'],                
                'status' => Souscription::STATUS_ACTIVE);
  if (!Souscription::exists($opts)) {
    throw new MaliciousException('souscription.not.exists');
  }

  $souscription = Souscription::getInstance($opts);
  $ctx->souscription = $souscription;
  $ctx->service = $souscription->getService();

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
