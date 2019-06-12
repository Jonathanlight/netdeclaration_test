<?php

try {

  // Pour chaque adhérent
  // recupérer toutes les souscriptions se terminant avant 1 mois
  // recreer une souscription
  // puis pour toutes souscriptions crées par un adhérent, créer une facture les regroupant
  // puis envoyer la facture par mail

  $rapports = array();
  $debugs = array('souscriptions_renew_count' => 0, 'souscriptions_renew_adherent_count' => 0);
  $date_today = Date::today();
  $opts = array('filters' => array('status' => Adherent::STATUS_SUBSCRIPTION_VALIDE));
  if ($req->adherent_id > 0) {
    $opts['filters']['id'] = (int) $req->adherent_id;
  }
  $adherents = Adherent::collect($opts);


  print "Début : \n";
  foreach ($adherents as $adherent) {
    print "Adhérent : " . $adherent->getId() . " (" . $dummy++ . " / " . $adherents->count() . ")\n";
    try {
      $rapports[$adherent->getId()] = $adherent->renewSouscriptions($date_today, false, true, true, true, false);
    } catch (Exception $e) {
      print $e->getMessage();
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
//$mail->send();
