<?php

try {

  /*$destinataires_grouped = array();
  foreach (Destinataire::collect(array('filters' => array('|!=|siret' => ''))) as $destinataire) {
    $destinataires_grouped[$destinataire->suivi_id][] = $destinataire->siret;
  }

  $counts = array();
  foreach ($destinataires_grouped as $suivi_id => $destinataires) {
    if (count(array_unique($destinataires)) != 1) {
      print "siret différents [$suivi_id] : " . var_export($destinataires, true) . "\n";
      $counts['diff']++;
    }
    else {
      $counts['same']++;
    }

  }
  var_export($counts);*/

  $adherents = array();
  foreach (Destinataire::collect(array('filters' => array('|!=|siret' => ''))) as $destinataire) {
    $adherents[Adherent::exists(array('siret' => $destinataire->siret))]++;
  }
  asort($adherents);
  var_export($adherents);

  print 'Terminé';
}
catch (Exception $e) {
  $err->add($e);
}
