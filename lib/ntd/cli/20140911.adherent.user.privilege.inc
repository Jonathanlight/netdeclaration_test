<?php

try {

  foreach(Adherent::collect() as $adherent) {
    $adherent->getUser()->addPrivilege(NetDeclarationManager::PRIVILEGE_ADHERENT_MIDDLE);
  }

}
catch (Exception $e) {
  $err->add($e);
}