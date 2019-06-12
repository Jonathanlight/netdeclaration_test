<?php

try {

  $user = $req->getUser();

  $adherent = Adherent::getInstance(array('id' => (int) $req->adherent_id, 'user_id' => $user->getId()));

  $id = (int) $req->id;
  $commit = (array) $req->iban;
  $commit['numero_iban'] = str_replace(array(' ', '-'), array('', ''), $commit['numero_iban']);
  Iban::validateIban($commit);

  if ($id > 0) {
    $iban = Iban::getInstance(array('id' => $id, 'adherent_id' => $adherent->getId()));
    unset($commit['adherent_id']);
    unset($commit['type']);
  }
  else {
    if ($adherent->getIbans(array('filters' => array('type' => Iban::TYPE_SECONDARY)))->count() >= Iban::MAX_IBAN_PER_ADHERENT) {
      throw new Exception('cant.create.other.IBAN.account');
    }
    $iban = Iban::getInstance();
    $commit['adherent_id'] = $adherent->getId();    
  }


  $iban->commit($commit);

  $res->sendMessage(l('flash.save.success'));

}
catch (Exception $e) {
  $err->add($e);
}
