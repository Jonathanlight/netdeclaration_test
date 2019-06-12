<?php

try {
  $ftype = Formulairetype::getInstance($req->id);

  if(!Millesime::exists($req->old_millesime_id)) {
    throw new Exception('Ancien Millesime non reconnu');
  }
  if(!Millesime::exists($req->new_millesime_id)) {
    throw new Exception('Nouveau Millesime non reconnu');
  }


  $old_millesime = Millesime::getInstance($req->old_millesime_id);
  $new_millesime = Millesime::getInstance($req->new_millesime_id);

  $changed = $ftype->duplicateMillesime($new_millesime->getId(), $old_millesime->getId());

  $res->sendMessage('Ifields mis à jour : '.count($changed['ifields'])."\n".'Operations mis à jour : '.count($changed['operations']));
}
catch (Exception $e) {
  $err->add($e);
}
