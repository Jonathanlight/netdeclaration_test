<?php

try {

  $offer = Offer::getInstance((int) $req->id);
  
  $offer->deliver();

  $res->sendMessage('Le message a bien été envoyé aux destinataires de tests.');

}
catch (Exception $e) { $err->add($e); }
