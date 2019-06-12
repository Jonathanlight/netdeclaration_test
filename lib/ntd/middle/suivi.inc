<?php

$res->setTitle('account.suivi');

try {

  // build <select> Options
  $fields_options = array('siret_emetteur' => array(),
                          'siret_decl' => array(),
                          'type_doc' => array(),
                          'type_decl' => array());

  $sql = 'SELECT SQL_CACHE #field#, COUNT(*) AS count
            FROM #table_suivi AS s
            JOIN #table_destinataire AS d ON (d.suivi_id = s.id)
           WHERE d.adherent_declarant_id IN ([adherent_ids])
              OR d.adherent_emetteur_id IN ([adherent_ids])
              OR d.adherent_destinataire_id IN ([adherent_ids])
           GROUP BY #field#
           ORDER BY #field# ASC';
  $bindings = array('#table_suivi' => T('suivi'),
                    '#table_destinataire' => T('destinataire'),
                    '[adherent_ids]' => SuiviManager::adherentIds(NetDeclaration::getCurrentAdherent()));
  foreach ($fields_options as $field => $options) {
    $bindings['#field#'] = $field;
    $fields_options[$field] = S('dbo')->query($sql, $bindings)->asHash($field, $field);
    $fields_options[$field] = array_filter($fields_options[$field]);
    foreach ($fields_options[$field] as $field_value => $field_count) {

      $field_value_label = $field_value;
      if (false && SuiviManager::admin()) {
        $fields_options[$field][$field_value] = $field_value_label . ' (' . $field_count . ')';
      }
      else {
        $fields_options[$field][$field_value] = $field_value_label;
      }

    }
  }

  $form = array('limit' => 10);

  $ctx->fields_options = $fields_options;
  $ctx->form = $form;

  $ctx->_keep_templates = true;
  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_SUIVI);
  NtdMiddleManager::setBreadCrumb();
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
