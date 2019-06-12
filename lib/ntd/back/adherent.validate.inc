<?php

try {

  $adherent = Adherent::getInstance((int) $req->id);
  $adherent->setStatus(Adherent::STATUS_SUBSCRIPTION_VALIDE);

  $res->sendMessage('L\'inscription de cet adhérent a été validée. Il peut désormais accéder à son espace personnel.');

}
catch (Exception $e) {
  $err->add($e);
}
