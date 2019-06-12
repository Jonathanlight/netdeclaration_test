<?php

try {

  $souscription = Souscription::getInstance($req->id);  
  $res->sendMessage('Nombre de suivis : "'.$souscription->getSuivisCount().'".');
}
catch (Exception $e) {
  $err->add($e);
}
