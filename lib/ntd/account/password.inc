<?php

try {

  NtdAccountManager::setCurrentModule(NtdAccountManager::MODULE_PASSWORD);
  NtdAccountManager::setBreadCrumb();
  NtdAccountManager::useTemplate();

}
catch (Exception $e) { $err->add($e); }