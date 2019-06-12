<?php

try {

  $destinataires_opts = SuiviManager::getDestinatairesOpts((array) $req->form,
                                                           NetDeclaration::getCurrentAdherent());

  $destinataires = Destinataire::collect($destinataires_opts);

  $columns = array('suivi_declaration_id',
                   'suivi_ref_message',
                   'suivi_intervenant',
                   'suivi_message',
                   'suivi_origine',
                   'suivi_date_depot',
                   'suivi_type_doc',
                   'suivi_sens',
                   'suivi_type_mess',
                   'suivi_type_decl',
                   'suivi_liste_formulaire',
                   'suivi_siret_emetteur',
                   'suivi_siret_decl',
                   'suivi_nom_decl',
                   'suivi_no_interchange',
                   'suivi_no_message',
                   'suivi_debut_periode',
                   'suivi_fin_periode',
                   'suivi_list_dest',
                   'destinataire_id',
                   'destinataire_ref_message',
                   'destinataire_no_dest',
                   'destinataire_type_dest',
                   'destinataire_siret',
                   'destinataire_nom_dest',
                   'destinataire_no_interchange',
                   'destinataire_no_message',
                   'destinataire_status',
                   'destinataire_date_ack',
                   'destinataire_message',
                   'destinataire_flg_depot',
                   'destinataire_flg_envoi',
                   'destinataire_flg_ack');
  $csv = CsvWriter::getInstance(array('encoding' => 'UTF-8',
                                      'columns' => $columns,
                                      'filename' => 'suivi.export.' . String::urlify(Date::now()) . '.csv'));
  foreach ($destinataires as $destinataire) {
    $row = array();
    foreach ($columns as $column) {
      $field = $column;
      if (substr($field, 0, 13) == 'destinataire_') {
        // 13 => strlen('destinataire_')
        $field = substr($field, 13);
      }
      $row[$column] = $destinataire->getAttribute($field);
    }
    $csv->append($row);
  }

}
catch (Exception $e) {
  $err->add($e);
}
