<?php

try {

  $adherent = Adherent::getCurrentPrimaryAdherent();

  $current_souscription = $adherent->getCurrentSouscription(NetDeclarationManager::SERVICE_ADHESION_MAIN_PROFILE);
  $current_souscription->commit(array('status' => Souscription::STATUS_CANCELLING_ASKED));

  $res->sendRedirect('/account/ntd/resiliate.form');

}
catch (Exception $e) {
  $err->add($e);
}
