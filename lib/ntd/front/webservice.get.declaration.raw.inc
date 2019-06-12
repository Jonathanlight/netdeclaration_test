<?php

$res->resetTemplates();

try {

  //NetDeclarationManager::manageWebServiceAccess();

  $datas = array();
  $declaration = Declaration::getInstance((int) $req->id);

  try {
    $declarant = $emetteur = $declaration->getAdherent();

    $dectype = $declaration->getDectype();
    if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
      //$declaration->generateTradeExpressData();
    }


    $formulaires = array();
    if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
      foreach ($dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
        foreach ($declaration->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF,
                                                                       'formulairetype_id' => $ftype->getId()),
                                                    'order' => array('position' => 'ASC',
                                                                     'id' => 'ASC',))) as $formulaire) {
          $formulaires[] = $formulaire;
        }
      }
    }
    else {
      $formulaires = $declaration->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF),
                                                        'order' => array('position' => 'ASC',
                                                                         'formulairetype_id' => 'ASC',
                                                                         'id' => 'ASC',)));
    }


    if ($declarant->adherent_id > 0) {
      $emetteur = Adherent::getInstance((int) $declarant->adherent_id);
    }

    $entete_row = array(
      'EtatExport' => $declaration->status,
      'TypeDoc' => Formulairetype::$document_codes[$dectype->document_code_export],
      'TypeDeclaration' => $dectype->code,
      'RefEnvoi' => $declaration->getId(),

      'Emetteur_SIRET' => substr($emetteur->siret, 0, 35),
      'Emetteur_Qualite' => substr(Adherent::$export_types[$emetteur->type], 0, 35),
      'Emetteur_Nom1' => substr($emetteur->company, 0, 35),
      'Emetteur_Nom2' => substr('', 0, 35),
      'Emetteur_Rue1' => substr($emetteur->address, 0, 35),
      'Emetteur_Rue2' => substr($declarant->address_1, 0, 35),
      'Emetteur_Rue3' => substr($declarant->address_2, 0, 35),
      'Emetteur_Ville' => substr($emetteur->city, 0, 35),
      'Emetteur_CodePostal' => substr($emetteur->zipcode, 0, 5),
      'Emetteur_Pays' => substr($emetteur->getCountry()->code, 0, 3),


      'Declarant_SIRET' => substr($declarant->siret, 0, 35),
      'Declarant_Nom1' => substr($declarant->company, 0, 35),
      'Declarant_Nom2' => substr('', 0, 35),
      'Declarant_Rue1' => substr($declarant->address, 0, 35),
      'Declarant_Rue2' => substr($declarant->address_1, 0, 35),
      'Declarant_Rue3' => substr($declarant->address_2, 0, 35),
      'Declarant_Ville' => substr($declarant->city, 0, 35),
      'Declarant_CodePostal' => substr($declarant->zipcode, 0, 5),
      'Declarant_Pays' => substr($declarant->getCountry()->code, 0, 3),
    );


    if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
      foreach (Destinataire::$types as $type => $label) {
        $entete_row['Dest' . $type] = (int) isset($declaration->destinataires[$type]);
      }
      if ($declaration->destinataires[Destinataire::TYPE_OGA]['siret_oga']) {
        $oga_details = array('siret' => $declaration->destinataires[Destinataire::TYPE_OGA]['siret_oga']);
        $oga_details_agrement = $declaration->destinataires[Destinataire::TYPE_OGA]['idoga'];
      }
    }
    else {
      $oga_details = null;
      foreach ($formulaires as $formulaire) {
        $data = $formulaire->data;
        if (!empty($data['OGA'])) {
          $oga_details = array('siret' => $data['OGA']);
          $oga_details_agrement = $data['IDOGA'];
          break;
        }
      }

    }
    if ($oga_details !== null && Adherent::exists($oga_details)) {
      $adherent_oga = Adherent::getInstance($oga_details);
      $entete_row['DestOGA'] = 1;
      $entete_row['OGA_NoRefInterneOGA'] = substr($oga_details_agrement, 0, 70);
      $entete_row['OGA_SIRET'] = substr($adherent_oga->siret, 0, 35);

      $entete_row['OGA_Nom1'] = substr($adherent_oga->company, 0, 35);
      $entete_row['OGA_Nom2'] = substr('', 0, 35);

      $entete_row['OGA_Rue1'] = substr($adherent_oga->address, 0, 35);
      $entete_row['OGA_Rue2'] = substr($adherent_oga->address_1, 0, 35);
      $entete_row['OGA_Rue3'] = substr($adherent_oga->address_2, 0, 35);

      $entete_row['OGA_Ville'] = substr($adherent_oga->city, 0, 35);
      $entete_row['OGA_CodePostal'] = substr($adherent_oga->zipcode, 0, 5);
      $entete_row['OGA_Pays'] = substr($adherent_oga->getCountry()->code, 0, 3);

    }
    else {
      $entete_row['DestOGA'] = 0;
    }

    $identif_row = array();
    $formulaire_rows = array();
    $formulairetype_counts = array();
    foreach ($formulaires as $formulaire) {
      $row = array();

      $formulaire_type = $formulaire->getFormulairetype();
      $formulaire_prefix = $formulaire_type->prefix_export;

      $millesime = $dectype->getMillesime();
      $ftype_is_repetable = $formulaire_type->isRepetable($millesime);

      if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM) && $ftype_is_repetable) {
        $formulairetype_counts[$formulaire_type->getId()]++;
        $formulaire_prefix .= '/' . ($formulairetype_counts[$formulaire_type->getId()]);
      }

      foreach ($formulaire->fields_values as $field => $values) {
        $row[$formulaire_prefix . '_' . $field] = var_export($values, true);
      }
      if ($dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM) && $formulaire_type->document_code == Formulairetype::DOCUMENT_CODE_IDENTIF) {
        $identif_row = $row;
      }
      else {
        $formulaire_rows[$formulaire->getId()] = $row;
      }
    }
    array_walk_recursive($rows, "Declaration::cleanWebserviceValue");

    $rows = array();
    $rows[] = $entete_row;
    if ($identif_row) {
      $rows[] = $identif_row;
    }
    foreach ($formulaire_rows as $row) {
      $rows[] = $row;
    }

  }
  catch (Exception $e) {
    S('log')->error($e);
    S('log')->debug($declaration->getAttributes(), __METHOD__);
    print $e->getMessage();
    $rows = false;
  }



  if ($rows !== false) {
    $datas[] = $rows;
  }


  $csv = new CsvWriter(array('eol' => "\n", 'separator' => '|'));
  foreach ($datas as $rows) {
    foreach ($rows as $row) {
      $_row = array();
      foreach ($row as $key => $value) {
        $_row[$key] = "$key=$value";
      }
      $csv->append($_row);
    }
    $csv->append(array('END' => 'END'));
  }

}
catch (Exception $e) {
  $log->error($e);
  $res->write($e->getMessage());
}
