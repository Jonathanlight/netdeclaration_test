<?php

try {

  $iban = array('type' => Iban::TYPE_PRIMARY);

  $opts = array('adherent_id' => $ctx->_current_adherent->getId(),
                'type' => Iban::TYPE_PRIMARY);
  if (Iban::exists($opts)) {
    $iban = Iban::getInstance($opts)->getAttributes();
  }

  $ctx->iban = $iban;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_IBAN_PRIMARY);
  NtdMiddleManager::setBreadCrumb('Ibans prmiary');
  NtdMiddleManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
