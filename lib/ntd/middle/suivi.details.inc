<?php

try {

  $suivi = Suivi::getInstance((int)$req->id);
  $destinataire_id = (int) $req->destinataire_id;
  $destinataire = null;
  if($destinataire_id > 0) {
    $destinataire = Destinataire::getInstance(array('suivi_id' => $suivi->getId(), 'id' => $destinataire_id));    
  }

  $ctx->suivi = $suivi;
  $ctx->destinataire = $destinataire;

  NtdMiddleManager::useTemplate(false);

}
catch (Exception $e) {
  $err->add($e);
}
