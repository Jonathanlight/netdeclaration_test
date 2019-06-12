<?php

try {

  if (false) {
    S('dbo')->query("UPDATE `ntd_suivi`
                   SET `adherent_declarant_id` = '0',
                       `adherent_emetteur_id` = '0',
                       `flags` = '0'");
    S('dbo')->query("UPDATE `ntd_destinataire`
                   SET `adherent_destinataire_id` = '0',
                       `flags` = '0'");
    S('dbo')->query("TRUNCATE `ntd_souscription_suivi`");
  }

  print 'begin : ';
  $suivis = Suivi::collect(array('filters' => array('adherent_emetteur_id' => 0,
                                                    'adherent_declarant_id' => 0)));
  $progress = new CliUIProgress('SUIVIS', $suivis->count(), 1);
  print $suivis->count() . "\n";
  foreach ($suivis as $suivi) {
    try {
      $suivi->unsetFlag(Suivi::FLAG_ADHERENT_EMETTEUR_CACHED);
      $suivi->unsetFlag(Suivi::FLAG_ADHERENT_DECLARANT_CACHED);
      $suivi->cache();
    }
    catch (Exception $e) {
      $log->error($e);
    }
    $progress->iterate();
  }
  /*
    $destinataires = Destinataire::collect(array('filters' => array('suivi_date_depot' => Date::DATE_NULL)));
    $progress = new CliUIProgress('DESTINATAIRES', $destinataires->count(), 1000);
    foreach ($destinataires as $destinataire) {
      try {
        $destinataire->cache();
      }
      catch (Exception $e) {
        $log->error($e);
      }
      $progress->iterate();
    }*/

  print 'Terminé ';

}
catch (Exception $e) {
  print $e->getMessage();
}
