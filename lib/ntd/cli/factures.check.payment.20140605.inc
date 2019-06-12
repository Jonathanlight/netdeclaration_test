<?php

try {

  $opts = array('filters' => array('|IN|status' => array(Facture::STATUS_NON_PAYE, Facture::STATUS_PENDING),
                                   '|>|price_ttc' => 0,
                                   '|!=|is_renew_auto' => 2,
                                   'type' => Facture::TYPE_FACTURE));

  $opts['filters']['start_at'] = Date::today();
  foreach ($factures = Facture::collect($opts) as $facture) {
    $adherent = $facture->getAdherent();
    $bindings = array('prenom' => $adherent->first_name,
                      'nom' => $adherent->last_name,
                      'siret' => $adherent->siret,
                      'company_name' => $adherent->getBillingAddressHash('company'),
                      'id_facture' => $facture->getId(),
                      'signature' => l('snippet:letter.footer'),
                      'link' => '<a href="' . H::url('/account/ntd/account.facture', array('id' => $facture->getId())) . '">Lien vers la facture</a> '
    );
    if ($adherent->type != Adherent::TYPE_CEC) { // cf https://mantis.kernix.com/view.php?id=13994
      Letter::send('facture.check.payment.day.0', $adherent->getEmailFacture(), $bindings); // $adherent->getEmail()
    }
  }

  $opts['filters']['start_at'] = date('Y-m-d', strtotime('- 20 days'));
  foreach ($factures = Facture::collect($opts) as $facture) {
    $adherent = $facture->getAdherent();
    $bindings = array('prenom' => $adherent->first_name,
                      'nom' => $adherent->last_name,
                      'siret' => $adherent->siret,
                      'company_name' => $adherent->getBillingAddressHash('company'),
                      'id_facture' => $facture->getId(),
                      'signature' => l('snippet:letter.footer'),
                      'link' => '<a href="' . H::url('/account/ntd/account.facture', array('id' => $facture->getId())) . '">Lien vers la facture</a> '
    );

    Letter::send('facture.check.payment.day.20', $adherent->getEmailFacture(), $bindings); // $adherent->getEmail()
  }

  $opts['filters']['start_at'] = date('Y-m-d', strtotime('- 40 days'));
  foreach ($factures = Facture::collect($opts) as $facture) {
    $adherent = $facture->getAdherent();
    $bindings = array('prenom' => $adherent->first_name,
                      'nom' => $adherent->last_name,
                      'siret' => $adherent->siret,
                      'company_name' => $adherent->getBillingAddressHash('company'),
                      'id_facture' => $facture->getId(),
                      'signature' => l('snippet:letter.footer'),
                      'link' => '<a href="' . H::url('/account/ntd/account.facture', array('id' => $facture->getId())) . '">Lien vers la facture</a> '
    );
    Letter::send('facture.check.payment.day.40', $adherent->getEmailFacture(), $bindings); // $adherent->getEmail()
  }

  $opts['filters']['start_at'] = date('Y-m-d', strtotime('- 48 days'));
  foreach ($factures = Facture::collect($opts) as $facture) {
    foreach ($facture->getSouscriptions() as $souscription) {
      $souscription->setAttribute('status', Souscription::STATUS_CANCELLED);
      $souscription->setFlag(Souscription::FLAG_CANCELLED_FACTURE_NON_PAYE);
    }
  }
  if ($factures->count() > 0) {
    $mail = new Mail();
    $mail->setSubject('[NTD][' . $req->action() . '] Souscriptions désactivées pour facture non payées depuis + de 48 jours');
    $mail->setBody('Ids des Factures impayées : ' . implode(', ', $factures->asHash('id', 'id')));
    $mail->addRecipient(P('contact.devel'));
    $mail->addRecipient('bbechade@kernix.com');
//    $mail->send();
  }


}
catch (Exception $e) {
  $log->error($e);
  $mail = new Mail();
  $mail->setSubject('[NTD][' . $req->action() . '] Erreur');
  $mail->setBody(nl2br($e->getMessage()));
  $mail->addRecipient(P('contact.devel'));
//  $mail->send();
}

$mail = new Mail();
$mail->setSubject('[NTD][' . $req->action() . '] Succès');
$mail->setBody('Mails de rappel de factures bien envoyées.');
$mail->addRecipient(P('contact.devel'));
$mail->addRecipient('bbechade@kernix.com');
//$mail->send();
