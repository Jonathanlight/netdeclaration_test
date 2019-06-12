<?php

try {

  if (!$req->hasAttributes('zipcode', true)) {
    throw new Exception(l('error'));
  }

  if ($req->hasAttribute('all')) {
    $codes = GreffeManager::getCodesInsee($req->zipcode, true);
  }
  else {
    $codes = GreffeManager::getCodesInseeOnline($req->zipcode, true);
  }
  $ctx->codes = $codes;

  $res->setFormat(Response::FORMAT_JSON);

}
catch (Exception $e) { $err->add($e); }