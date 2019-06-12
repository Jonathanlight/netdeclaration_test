<?php

try {

  $facture = Facture::getInstance((int) $req->id);
  $email = $facture->send();

  $res->sendMessage('La facture vient d\'être envoyée à l\'adresse "'.$email .'".');

}
catch (Exception $e) {
  $err->add($e);
}
