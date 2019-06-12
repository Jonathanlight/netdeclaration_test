<?php

try {

  // Pour chaque adhérent
  // recupérer toutes les souscriptions se terminant avant 1 mois
  // recreer une souscription
  // puis pour toutes souscriptions crées par un adhérent, créer une facture les regroupant
  // puis envoyer la facture par mail

  $adherent_ids = S('dbo')->asSet("SELECT DISTINCT adherent_id  FROM `ntd_souscription` WHERE `finish_at` > '2014-12-01' AND status = -10 AND souscription_renew_id = 0");

  print "Début : \n";
  foreach ($adherent_ids as $adherent_id) {
    $adherent = Adherent::getInstance($adherent_id);
    print "Adhérent : " . $adherent->getId() . " (" . $dummy++ . " / " . count($adherent_ids) . ")\n";

    for ($day_timestamp = strtotime('2014-12-01'); $day_timestamp < time() - 86400; $day_timestamp += 86400) {

      $date_today = Date::toDb($day_timestamp);
      print "day : ".$date_today."\n";

      $rapports = array();

      try {
        $rapports[$adherent->getId()] = $adherent->renewSouscriptions($date_today, false, false);
      }
      catch (Exception $e) {
        print $e->getMessage();
      }
    }

  }
  print "\n\nOK\n";


}
catch (Exception $e) {
  $log->error($e);
}

$body = "<h1>Rapport</h1>";
foreach ($rapports as $key_adherents => $rapport_adherents) {
  if (!is_array($rapport_adherents)) {
    $body .= "<p><strong>$key_adherents : </strong>$rapport_adherents</p>";
    continue;
  }

  $body .= "<h2>Adhérent [ID:$key_adherents] </h2>";
  foreach ($rapport_adherents as $key_adherent => $rapport_adherent) {
    if (!is_array($rapport_adherent)) {
      $body .= "<p><strong>$key_adherent : </strong>$rapport_adherent</p>";
      continue;
    }

    $body .= "<h3>Date $key_adherent </h3>";
    foreach ($rapport_adherent as $key_souscriptions => $rapport_souscriptions) {
      if (!is_array($rapport_souscriptions)) {
        $body .= "<p><strong>$key_souscriptions : </strong>$rapport_souscriptions</p>";
        continue;
      }
      $body .= "<h4>Souscription [ID:$key_souscriptions] </h4>";
      foreach ($rapport_souscriptions as $key_souscription => $rapport_souscription) {
        if (!is_array($rapport_souscription)) {
          $body .= "<p><strong>$key_souscription : </strong>$rapport_souscription</p>";
          continue;
        }
      }
    }
  }
}

$mail = new Mail();
$mail->setSubject('[NTD][Reconduction tacite] Rapport ' . P('app.domain'));
//file_put_contents('doc/ntd/rapport.txt', $body);
$mail->setBody(nl2br($body));
$mail->addRecipient('npinchon@kernix.com');
$mail->addRecipient('bbechade@kernix.com');
$mail->send();
