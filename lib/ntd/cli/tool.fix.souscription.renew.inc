<?php

try {
  $rapports = array();
  $debugs = array('souscriptions_renew_count' => 0, 'souscriptions_renew_adherent_count' => 0);

  $opts = array('filters' => array('status' => Adherent::STATUS_SUBSCRIPTION_VALIDE));
  if ($req->adherent_id > 0) {
    $opts['filters']['id'] = (int) $req->adherent_id;
  }
  $adherents = Adherent::collect($opts);


  print "Début : \n";
  foreach ($adherents as $adherent) {
    print "Adhérent : " . $adherent->getId() . " (" . $dummy++ . " / " . $adherents->count() . ")\n";
    try {

      $souscriptions = $adherent->getSouscriptions(array('filters' => array('|&|flags'      => Souscription::FLAG_FACTURE_ALREADY_SEND,
                                                                            '|>=|finish_at' => '2016-01-06')));

      print $souscriptions->asSql();
      foreach ($souscriptions as $key => $souscription) {
        $souscription->unsetFlag(Souscription::FLAG_FACTURE_ALREADY_SEND);
      }

      // 2015-01-06 -> 2015-01-14
      for ($i=0; $i<9; $i++) {
        $date_today = date('Y-m-d', strtotime('2016-01-06 +'.$i.' days'));
        print $date_today."\n";
       $adherent->renewSouscriptions($date_today, false, true, true, true, false);
      }
    } catch (Exception $e) {
      print $e->getMessage();
    }
  }
  print "\n\nOK\n";
}
catch (Exception $e) {
  $log->error($e);
}
