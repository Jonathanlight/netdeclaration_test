<?php

try {


  FactureRepository::setFactureStatusBackToPending((int) $req->id);

  $res->sendMessage('La facture a bien été repassée en état à payer');

}
catch (Exception $e) {
  $err->add($e);
}