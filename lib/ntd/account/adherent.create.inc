<?php

try {


  $main_adherent = Adherent::getCurrentPrimaryAdherent();
  $commit = (array) $req->adherent;

  if (in_array($commit['type'], array(Adherent::TYPE_ENTREPRISE, Adherent::TYPE_INTERNATIONAL, Adherent::TYPE_PRO_SANTE))) {
    unset($commit['has_email_declaration']);
    unset($commit['email_edi']);
  }

  $commit['partenaire_id'] = 0;
  if ($commit['partenaire_code'] && Partenaire::exists(array('code' => $commit['partenaire_code']))) {
    $commit['partenaire_id'] = Partenaire::id(array('code' => $commit['partenaire_code']));
  }
  $commit['user_id'] = $user->getId();
  $commit['adherent_id'] = $main_adherent->getId();
  $commit['status'] = Adherent::STATUS_SUBSCRIPTION_PENDING;
  $commit['level'] = Tarif::ADHERENT_LEVEL_SECONDARY;


  Adherent::validateAdherent($commit);
  $adherent = Adherent::getInstance();

  $h = array('host' => $req->getClient('host'),
      'ip' => long2ip($req->getClient('ip')),
      'date' => Date::now(),
      'cgu_version' => P('cgu.version'));

  $commit['cgu_sign_key'] = Adherent::generateKey($h);
  $commit['cgu_sign_infos'] = serialize($h);
  $commit['last_cgu_sign_infos'] = serialize($h);

  $adherent->commit($commit);


  $ctx->adherent_id = $adherent->getId();
  NetDeclaration::setCurrentAdherent($adherent->getId());


  $res->sendMessage(l('flash.save.success'));

}
catch (Exception $e) {
  $err->add($e);
}
