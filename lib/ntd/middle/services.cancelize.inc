<?php

try {

  $form = (array) $req->form;

  $opts = array('adherent_id' => NetDeclaration::getCurrentAdherent()->getId(),
                'id' => (int) $form['souscription_id'],
                'status' => Souscription::STATUS_ACTIVE);
  if (!Souscription::exists($opts)) {
    throw new MaliciousException('souscription.not.exists');
  }

  $souscription = Souscription::getInstance($opts);
  $souscription->commit(array('status' => Souscription::STATUS_CANCELLING_ASKED));

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SERVICE);
  NtdMiddleManager::setBreadCrumb(array(true, NtdMiddleManager::getPageSnippet()->getProperty('title')));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
