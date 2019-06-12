<?php

try {

  $adherent = $ctx->_current_adherent;


  $commit = (array) $req->adherent;

  if (in_array($commit['type'], array(Adherent::TYPE_ENTREPRISE, Adherent::TYPE_INTERNATIONAL, Adherent::TYPE_PRO_SANTE))) {
    unset($commit['has_email_declaration']);
    unset($commit['email_edi']);
  }

  if ($commit['partenaire_code']) {
    if (Partenaire::exists(array('code' => $commit['partenaire_code']))) {
      $commit['partenaire_id'] = Partenaire::id(array('code' => $commit['partenaire_code']));
    }
    else {
      $commit['partenaire_id'] = 0;
    }
  }
  else {
    $commit['partenaire_id'] = 0;
  }


  unset($commit['id']);
  unset($commit['user_id']);
  unset($commit['adherent_id']);
  $commit['id'] = $adherent->getId();
  $commit['type'] = $adherent->type;
  $commit['cec_ordre'] = $adherent->cec_ordre;
  $commit['cec_flags'] = $adherent->cec_flags;
  $commit['oga_agrement'] = $adherent->oga_agrement;
  if (!isset($commit['is_main_adherent_billing_address'])) {
      $commit['is_main_adherent_billing_address'] = 0;
  }

  Adherent::validateAdherent($commit);
  $adherent->commit($commit);

  $res->sendMessage(l('flash.save.success'));

}
catch (Exception $e) {
  $err->add($e);
}
