<?php

try {

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_GREFFE);
  NtdMiddleManager::setBreadCrumb(array('Greffe'));
  NtdMiddleManager::useTemplate(false);
  NtdMiddleManager::setSEO();

}
catch (Exception $e) { $err->add($e); }