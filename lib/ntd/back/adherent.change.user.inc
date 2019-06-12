<?php

try {

  $record = (array) $req->record;
  AdherentRepository::changePrimaryAdherentUser($record['adherent_id'], $record['user_id']);


  $res->sendMessage('L\'utilisateur a bien été changé.');

}
catch (Exception $e) {
  $err->add($e);
}
