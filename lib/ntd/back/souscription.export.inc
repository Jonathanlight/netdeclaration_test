<?php

try {

  $csv_export_columns = array(
    'id' => 'Souscription ID',
    'adherent_siret' => 'Siret Adhérent',
    'adherent_company' => 'Raison sociale adhérent',
    'user_email' => 'E-mail adhérent',
    'status_label' => 'Statut',
    'start_at' => 'Date de début',
    'finish_at' => 'Date de fin',
    'facture_id' => 'ID facture liée à la souscription',
    'service_name' => 'Service associé',
  );

  $csv = new CsvWriter(array('filename' => str_replace('-', '_', Date::today()).".souscription.export.csv"));
  $csv->append(array_map("encodeUTF8ToWin1252", $csv_export_columns));
  foreach (Souscription::collect() as $souscription) {
    try {
      $csv->append(array_map("encodeUTF8ToWin1252", $souscription->asCsvHash(array_keys($csv_export_columns))));
    } catch (Exception $e) {
      $log->error($e);
    }
  }

}
catch (Exception $e) {
  $err->add($e);
}

function encodeUTF8ToWin1252($field) {
  return iconv('UTF-8', 'windows-1252', $field);
}