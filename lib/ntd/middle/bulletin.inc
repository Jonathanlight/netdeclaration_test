<?php

try {


  $adherent = Adherent::getCurrentPrimaryAdherent();
  if (false && $adherent->status == Adherent::STATUS_SUBSCRIPTION_VALIDE) {
    //$res->sendRedirect('/page/-/code/ntd.front.bulletin.ok');
  }
  else {
    NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_ADHERENT);
    NtdMiddleManager::setBreadCrumb();
    NtdMiddleManager::useTemplate();
    //$page = Page::getInstance('ntd.front.bulletin');
    NtdMiddleManager::setSEO();
  }

}
catch (Exception $e) {
  $err->add($e);
}