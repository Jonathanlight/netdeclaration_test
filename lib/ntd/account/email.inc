<?php

try {

  NtdAccountManager::setCurrentModule(NtdAccountManager::MODULE_EMAIL);
  NtdAccountManager::setBreadCrumb();
  NtdAccountManager::useTemplate();

}
catch (Exception $e) { $err->add($e); }
