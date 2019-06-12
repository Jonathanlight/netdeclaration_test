<?php

try {


  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_DEVIS);
  NtdMiddleManager::setBreadCrumb(array('Devis'));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
