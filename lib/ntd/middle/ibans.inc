<?php

try {

  $ctx->ibans = $ctx->_current_adherent->getSecondariesIbans();

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_IBAN_SECONDARY);
  NtdMiddleManager::setBreadCrumb('Ibans');
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
