<?php

try {

  $record = (array) $req->record;
  AdherentRepository::becomePrimaryAdherentForUser($record['adherent_id'], $record['user_id']);

  $res->sendMessage('L\'adhérent est devenu l\'adhérent primaire sur l\'utilisateur sélectionné.');

}
catch (Exception $e) {
  $err->add($e);
}
