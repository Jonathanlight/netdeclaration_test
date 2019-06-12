<?php

try {

  $declaration = Declaration::getInstanceByKey($req->key);
  $declaration_dectype = $declaration->getDectype();
  $adherent = $declaration->getAdherent();

  $formulaire_codes = array();
  if ($req->hasAttribute('formulaire_codes', true)) {
    $formulaire_codes = (array)$req->formulaire_codes;
  }

  if ($declaration_dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {

    $formulaires = $declaration->getFormulaires();
    $formulairesAsArray = array();

    foreach ($formulaires as $form) {
        $formulairesAsArray[] = array(
            'id' => $form->getId(),
            'formulairetype_id' => $form->formulairetype_id,
            'position' => $form->position,
        );
    }

    foreach ($declaration_dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
      foreach ($formulairesAsArray as $form) {
          if ($form['formulairetype_id'] == $ftype->getId()) {
              $formulaires_data[$ftype->getId()][] = array('formulairetype' => $ftype,
                                                         'id' => $form['id']);
          }
      }
    }

    $ctx->formulaires_data = $formulaires_data;
  }
  else {

    $formulaires_by_ftypes = array();
    foreach ($declaration->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF),
                                                'order' => array('id' => 'ASC',
                                                                 'position' => 'ASC'))) as $formulaire) {
      $formulaires_by_ftypes[$formulaire->formulairetype_id][] = $formulaire;
    }

    $default_values_binded = array(
      'adherent_identity' => $adherent->identity(),
      'adherent_siret' => $adherent->siret,
      'adherent_siren' => substr($adherent->siret, 0, 9),
      'adherent_company' => $adherent->company,
      'adherent_company_1' => $adherent->company_bis,
      'adherent_function' => $adherent->function,
      'adherent_forme_juridique' => $adherent->forme_juridique,
      'adherent_address' => $adherent->address,
      'adherent_address_1' => $adherent->address_1,
      'adherent_address_2' => $adherent->address_2,
      'adherent_zipbox' => $adherent->zipbox,
      'adherent_city' => $adherent->city,
      'adherent_zipcode' => $adherent->zipcode,
      'adherent_phone' => $adherent->phone,
      'adherent_email' => $adherent->email,
      'adherent_country' => Country::getInstance($adherent->country_id)->getId()
    );

    $ftypes_imprimes = array();
    $ftypes_imprimes_options = array();

    foreach ($declaration_dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {

      if ($req->hasAttribute('ftype_id', true)) {
        if ($ftype->getId() != $req->ftype_id) continue ;
      }
      if ($ftype->ftype_type != Dectype::RELATION_TYPE_OBLIGATOIRE) {
        if (empty($formulaires_by_ftypes[$ftype->getId()])) continue ;
      }
      if (!empty($formulaire_codes) && !in_array($ftype->code, $formulaire_codes) && $ftype->ftype_type != Dectype::RELATION_TYPE_OBLIGATOIRE) {
        continue ;
      }

      $millesime = Millesime::getInstance($ftype->ftype_millesime_id);
      $itemplate = Itemplate::getInstance(array('millesime_id' => $millesime->getId(),
                                                'status' => 1,
                                                'formulairetype_id' => $ftype->getId()));

      if (empty($ftypes_imprimes[$ftype->code])) {
        $ftypes_imprimes[$ftype->code] = array('ftype' => $ftype,
                                               'itemplate' => $itemplate,
                                               'millesime' => $millesime);
      }
      $ftypes_imprimes_options[$ftype->code] = $ftype->title_code;
      foreach ((array) $formulaires_by_ftypes[$ftype->getId()] as $formulaire) {

        if (empty($ftypes_imprimes[$formulaire->getFormulairetype()->code])) {
          $ftypes_imprimes[$formulaire->getFormulairetype()->code] = array('ftype' => $formulaire->getFormulairetype(),
                                                                           'itemplate' => $itemplate,
                                                                           'millesime' => $millesime);
        }
        $ftypes_imprimes_options[$formulaire->getFormulairetype()->code] = $formulaire->getFormulairetype()->title_code;
        $imprime = new Imprime();
        $imprime->setFormulaire($formulaire, $millesime);

        foreach ($imprime->getFields() as $field) {
          if (strlen($field->default_value) < 1) continue;
          $default_value = $field->default_value;
          if (substr($default_value, 0, 2) == '((') {
            $key = substr($default_value, 2, -2);
            $default_value = $default_values_binded[$key];
          }
          $field->setDefaultValue($default_value);
        }
        foreach ((array) $declaration_dectype->getRequiredFields($ftype->code) as $field_code => $required) {
          $imprime->getField($field_code)->setRequired($required);
        }
        foreach ((array) $declaration_dectype->getDefaultValues($ftype->code) as $field_code => $default_value) {
          $imprime->getField($field_code)->setDefaultValue($default_value);
        }

        $ftypes_imprimes[$ftype->code]['imprimes'][] = $imprime;

      }

      if (count($ftypes_imprimes[$ftype->code]['imprimes']) < 1) {
        $ftypes_imprimes[$ftype->code]['imprimes'][] = createImprimeEmpty($ftype, $declaration_dectype, $default_values_binded, $millesime);
      }

    }

    $ctx->ftypes_imprimes = $ftypes_imprimes;
    $ctx->ftypes_imprimes_options = $ftypes_imprimes_options;

  }

  $ctx->dectype = $declaration_dectype;
  $ctx->declaration_dectype = $declaration_dectype;
  $ctx->declaration = $declaration;
  $ctx->adherent = $adherent;

  $res->reset();
  $res->useTemplate();

} catch (Exception $e) { $err->add($e); }

function createImprimeEmpty($ftype, $declaration_dectype, $default_values_binded, $millesime) {
  $imprime = new Imprime();
  $imprime->setFormulairetype($ftype, $millesime);
  $imprime->setIndex(0);
  foreach ($imprime->getFields() as $field) {
    if (strlen($field->default_value) < 1) continue;
    $default_value = $field->default_value;
    if (substr($default_value, 0, 2) == '((') {
      $key = substr($default_value, 2, -2);
      $default_value = $default_values_binded[$key];
    }
    $field->setDefaultValue($default_value);
  }
  foreach ((array) $declaration_dectype->getRequiredFields($ftype->code) as $field_code => $required) {
    $imprime->getField($field_code)->setRequired($required);
  }
  foreach ((array) $declaration_dectype->getDefaultValues($ftype->code) as $field_code => $default_value) {
    $imprime->getField($field_code)->setDefaultValue($default_value);
  }
  return $imprime;
}
