<?php

try {

  if (GreffeManager::getCurrentDossier()) {
    throw new Exception('Un dossier est déjà en cours d\'édition');
  }

  $adherent = NetDeclaration::getCurrentAdherent();
  $dossier = Greffedossier::getInstance();

  $attrs = array('adherent_id' => $adherent->getId());
  $dossier->commit($attrs);

}
catch (Exception $e) { $err->add($e); }