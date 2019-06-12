<?php

try {

  $sirets = array();
  foreach (Adherent::collect() as $adherent) {
    $adherent_sirets = array($adherent->siret => $adherent->siret);
    //$sirets[$adherent->siret]++;
    foreach ($adherent->old_sirets as $siret) {
      //$sirets[$siret]++;
      $adherent_sirets[$siret] = $siret;
    }
    foreach($adherent_sirets as $siret ) {
      $sirets[$siret][] = $adherent->user_id;
    }
  }

  asort($sirets);
  foreach ($sirets as $siret => $adherent_ids) {
    $adherent_ids = array_unique($adherent_ids);
    if (count($adherent_ids) > 1) {
      print 'SIRET [' . $siret . '] ' . implode(', ', $adherent_ids) . "\n";
    }
  }

  print 'Terminé';
  return;
  $sirets = array();
  foreach (Suivi::collect(array('filters' => array('adherent_id' => 99999999),
                                'group' => 'siret_emetteur')) as $suivi) {
    $adherents = Adherent::collect(array('filters' => array('siret' => $suivi->siret_emetteur,
                                                            array('OR' => array('|%%|old_sirets' => $suivi->siret_emetteur)))));

    print 'Siret : ' . $suivi->siret_emetteur . ': ' . "\n";
    foreach ($adherents as $adherent) {
      print $adherent->company . ' : (SIRET = ' . $adherent->siret . ')';
      if (count($adherent->old_sirets) > 0) {
        print ' (Anciens SIRETs = ' . implode(', ', $adherent->old_sirets) . ")";
      }
      print "\n";
    }
    print "\n";
  }

}
catch (Exception $e) {
  $err->add($e);
}
