<?php

try {

  $form = (array) $req->form;

  $destinataires_opts = SuiviManager::getDestinatairesOpts($form, NetDeclaration::getCurrentAdherent());
  $destinataires_opts['offset'] = (int) $form['offset'];
  $destinataires_opts['limit'] = (int) $form['limit'];
  //$destinataires_opts['filters']['|%%|'.T('suivi') . '.list_dest'] = ',';
  $destinataires = Destinataire::collect($destinataires_opts);


  $destinataires_counts = array();
  $suivis_destinataires = array();
  foreach ($destinataires as $destinataire) {
    $destinataires_counts[$destinataire->suivi_id]++;
    if (!isset($suivis_destinataires[$destinataire->suivi_id]['suivi'])) {
      $suivis_destinataires[$destinataire->suivi_id]['suivi'] = $destinataire->getSuivi();
    }
    $suivis_destinataires[$destinataire->suivi_id]['destinataires'][$destinataire->getId()]['destinataire'] = $destinataire;
  }

  // functionnality (count souscription by suivi) disable
  /*if (SuiviManager::admin()) {
    $souscriptions = S('dbo')->asArray('SELECT *
                                     FROM ntd_souscription_suivi AS ss
                                     WHERE destinataire_id IN ([adherent_ids])',
                                       array('[adherent_ids]' => $destinataires->asSet('id')));
    $destinataires_souscriptions = array();
    foreach ($souscriptions as $souscription) {
      $destinataires_souscriptions[$souscription['destinataire_id']][] = $souscription['souscription_id'];
      $suivis_destinataires[$souscription['suivi_id']]['destinataires'][$souscription['destinataire_id']]['souscriptions'][] = $souscription;
    }
  }*/


  $ctx->adherent_ids = SuiviManager::adherentIds(NetDeclaration::getCurrentAdherent());
  $ctx->destinataires = $destinataires;
  $ctx->destinataires_souscriptions = $destinataires_souscriptions;
  $ctx->suivis_destinataires = $suivis_destinataires;

  NtdMiddleManager::useTemplate(false);

}
catch (Exception $e) {
  $err->add($e);
}
