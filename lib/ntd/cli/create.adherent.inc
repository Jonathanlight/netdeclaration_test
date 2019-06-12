<?php

try {

  if ($req->manual != 'yes') {
    print "manual=yes needed";
    return;
  }

  $adherent = Adherent::getInstance(array('siret' => '43019775600025'));
  print 'Adherent found : '.$adherent->getId()."\n";

  $email = 'caroline.averso@cabinetmattei.net';
  $commit['user']['email'] = $email;
  $commit['user']['password'] = md5('430197756');
  $commit['user']['notices'] = 0;
  $commit['user']['flags'] = 0;

  $commit['user']['name'] = substr($commit['user']['email'], 0, strpos($commit['user']['email'], '@'));
  $commit['user']['locale'] = I18N::LOCALE_FR;
  $commit['user']['status'] = User::STATUS_CONFIRMED;
  $commit['user']['path'] = 'created';

  print "Création de l'utilisateur : ";
  $user = User::getInstance();
  $user->commit($commit['user']);
  print "OK -> " . $user->getId() . "\n";


  print "Création de l'adhérent principal : ";
  $commit['adherent']['adherent_id'] = 0;
  $commit['adherent']['user_id'] = $user->getId();
  $commit['adherent']['level'] = Tarif::ADHERENT_LEVEL_PRIMARY;
  $adherent->commit($commit['adherent']);
  print "OK -> " . $adherent->gteId() . "\n"; 

}
catch (Exception $e) {
  echo $e->getMessage();
}
