<?php

try {

  print "Début : \n";

  $date_tomorrow = Date::toDB(strtotime('tomorrow'), false); // TODO :'2012-07-01';  
  $adherents = Adherent::collect(array('filters' => array('status' => Adherent::STATUS_SUBSCRIPTION_VALIDE)));

  $rapports = array();
  foreach ($adherents as $adherent) {
    $microtime = microtime(true);
    print "Adhérent : " . $adherent->getId() . " (" . ++$adherents_count . " / " . $adherents->count() . ")";
    try {
      $rapport = $adherent->renewSouscriptions($date_tomorrow, true, false, true, true, false);
      if ($rapport['souscriptions_count'] > 0) {
        $rapports[$adherent->getId()] = $rapport;
      }
    } catch (Exception $e) {
      $rapports[$adherent->getId()]['exception'] = $e->getMessage();
    }
    print ' : ' . number_format((microtime(true) - $microtime), 3) . " s\n";
  }

  print "\n\nOK\n";

}
catch (Exception $e) {
  print $e->getMessage();
}

$body = '<h1>Rapport (' . count($rapports) . ' rapports)</h1>';
$body .= '<style type="text/css">.table-facture-summary { border:1px solid #000000; }
.table-facture-summary { border:1px solid #000000; }
.table-facture-summary td,
.table-facture-summary th { border: 1px solid #000000; line-height: 20px; padding: 2px;  }</style> ';

foreach ($rapports as $adherent_id => $rapport) {
  if (count($rapport['days'][$date_tomorrow]['souscription']) > 0 && $rapport['days'][$date_tomorrow]['facture'] != null) {
      $body .= "<h2>Adhérent N°$adherent_id </h2>";
      $body .= H::inc('lib/ntd/templates/adherent.souscriptions.renew.psp',
          array('rapport' => $rapport));
  }

}

$mail = new Mail();
$mail->setSubject('[NTD][Reconduction tacite][Prévisions pour le ' . H::date($date_tomorrow) . '] Rapport (' . P('app.domain') . ')');
$mail->setBody($body, 'ntd:skeleton.mail.rapport');
//$mail->addRecipient('npinchon@kernix.com');
$mail->addRecipient('bbechade@kernix.com');
$mail->addRecipient('shumbert@kernix.com');
$mail->addRecipient('jasmar@kernix.com');
$mail->send();
