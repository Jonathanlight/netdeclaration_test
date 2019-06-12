<?php

try {

  $facture = Facture::getInstance((int) $req->id); 

  $facture->setStatus(Facture::STATUS_RESILIE);

} catch (Exception $e) { $err->add($e); }
