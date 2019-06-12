<?php

try {

  $ctx->declarations = $ctx->_current_adherent->getDeclarations(array('filters' => array('status' => Declaration::STATUS_EDITABLE),
                                                                      'limit' => 5));
  $destinataires = Destinataire::collect(array('include' => array('suivi'),
                                               'filters' => array('flg_ack' => 0,
                                                                  array(T('suivi') . '.adherent_declarant_id' => $ctx->_current_adherent->getId(),
                                                                        T('suivi') . '.adherent_emetteur_id' => $ctx->_current_adherent->getId())),
                                               'limit' => 5));


  $sql = "SELECT SQL_SMALL_RESULT SQL_CALC_FOUND_ROWS
            ntd_declaration.*,
            ntd_destinataire.id AS destinataire_id,
            ntd_suivi.id AS suivi_id,
            ntd_suivi.date_depot AS suivi_date_depot,
            ntd_destinataire.message AS destinataire_message
            FROM ntd_destinataire
            JOIN ntd_suivi ON (ntd_suivi.id = ntd_destinataire.suivi_id)
            JOIN ntd_declaration ON (ntd_suivi.declaration_id = ntd_declaration.id)
           WHERE ntd_destinataire.flg_ack = '0'
             AND (ntd_suivi.adherent_declarant_id = :adherent_id:
                  OR ntd_suivi.adherent_emetteur_id = :adherent_id:)
             AND ntd_declaration.old_declaration_id = 0
           LIMIT 5
           OFFSET 0";
  //$ctx->declarations_suivi_error = S('dbo')->query($sql, array(':adherent_id:' => $ctx->_current_adherent->getId()))->asCollection('Declaration');
  //$ctx->declarations_suivi_error->trace();

//  $ctx->declarations_suivi_error = $ctx->_current_adherent->getDeclarations(array('include' => array('suivi'),
//                                                                                  'filters' => array(T('suivi') . '.id' => $destinataires->asSet('suivi_id'))));
  $ctx->factures = $ctx->_current_adherent->getFactures(array('filters' => array('|IN|status' => array(Facture::STATUS_NON_PAYE,
                                                                                                       Facture::STATUS_PENDING),
                                                                                 '|>|price_ttc' => 0,
                                                                                 'type' => Facture::TYPE_FACTURE),
                                                              'limit' => 5,
                                                              'metas' => array('created_at'),
                                                              'order' => array('created_at' => 'ASC')));
  $ctx->souscriptions = $ctx->_current_adherent->getSouscriptions(array('filters' => array('status' => Souscription::STATUS_ACTIVE,
                                                                                           '|<|finish_at' => date('d-m-Y', strtotime(Date::today() . ' +30 days')),
                                                                                           '|>=|finish_at' => Date::today()),
                                                                        'limit' => 5));

  // show help ?
  $cookie = $req->getCookie();
  if (!$cookie->hasAttribute('middle.help.shown')) {
    $cookie->setAttribute('middle.help.shown', 1);
    $ctx->show_middle_help = true;
  }


  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_HOME);
  NtdMiddleManager::setBreadCrumb();
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
