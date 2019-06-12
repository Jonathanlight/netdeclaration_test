<?php

try {

  AdherentRepository::changeToPrimaryAdherent($req->id);

  $res->sendMessage('cet Adhérent est devenu l\'adhérent primaire');

}
catch (Exception $e) {
  $err->add($e);
}