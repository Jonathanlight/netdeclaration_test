<?php

try {

  if (!$req->hasAttribute('adherent', true)) {
    throw new Exception(c(l('error')));
  }

  $record = $req->adherent;
  if (empty($record['zipcode'])) {
    throw new Exception(c(l('error')));
  }

  $filters = array('status' => Greffecommune::STATUS_ONLINE,
                   'id'     => (int)$record['greffecommune_id']);
  $greffes = Greffecommune::collect(array('filters' => $filters));

  $eligible = $greffes->count() > 0;

  $ctx->eligible = $eligible;
  $res->setFormat(Response::FORMAT_JSON);

}
catch (Exception $e) {
  $err->add($e);
}
