<?php

try {

  $csv_export_columns = array(
    'id' => 'Adhérent ID',

    'user_email' => 'E-mail adhérent',
    'civility_label' => 'civilité',
    'last_name' => 'nom',
    'first_name' => 'prénom',
    'type_label' => 'type',
    'cec_flags_avocat' => 'avocat',
    'company' => 'raison sociale',
    'company_bis' => 'complément raison sociale',
    'siret' => 'siret',
    'cec_ordre' => 'Numéro CEC',
    'adherent_id_label' => 'Primaire / Secondaire',

    'phone' => 'contact téléphone',
    'fax' => 'contact fax',
    'address' => 'contact adresse',
    'address_1' => 'contact adresse 1',
    'address_2' => 'contact adresse 2',
    'zipcode' => 'contact CP',
    'city' => 'contact ville',
    'country_id_label' => 'contact pays',

    'billing_company' => 'facturation raison sociale',
    'billing_address' => 'facturation adresse',
    'billing_zipbox' => 'facturation boîte postale',
    'billing_zipcode' => 'facturation CP',
    'billing_city' => 'facturation ville',
    'billing_country_id_label' => 'facturation pays',
    'billing_mail' => 'facturation Mail',
    'billing_payment_mode_label' => 'Mode de paiement',
    'partenaire_id' => 'Partenaire'
  );

  $csv = new CsvWriter(array('filename' => str_replace('-', '_', Date::today()).".adherent.export.csv"));
  $csv->append(array_map("encodeUTF8ToWin1252", $csv_export_columns));
  foreach (Adherent::collect() as $adherent) {
    try {
      $csv->append(array_map("encodeUTF8ToWin1252", $adherent->asCsvHash(array_keys($csv_export_columns))));
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
