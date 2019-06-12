<?php

try {

  $souscription = Souscription::getInstance($req->id);  
  Suivi::collect($souscription->getSuiviCollectionOpts())->trace();
}
catch (Exception $e) {
  $err->add($e);
}
