<?php

try {

  $id = (int) $req->declaration_id;

  if ($id < 1) {
    $adherent = NetDeclaration::getCurrentAdherent();
    $declaration_dectype = Dectype::getInstance((int) $req->dectype_id);

    $declaration = Declaration::getInstance();

    $attrs = array('adherent_id' => $adherent->getId(),
                   'dectype_id' => $declaration_dectype->getId());

    $attrs['status'] = $declaration_dectype->hasFlag(Dectype::FLAG_STEP_DISPLAY) ? Declaration::STATUS_BROUILLON : Declaration::STATUS_EDITABLE;

    $declaration->commit($attrs);

    $res->sendRedirect('/account/declaration/wrapper',
                       array('declaration_id' => $declaration->getId()));
    return;
  }



  $declaration = Declaration::getInstance($id);
  $declaration_dectype = $declaration->getDectype();
  $adherent = $declaration->getAdherent();

  // instanciation des imprimes
  $formulaires_by_ftypes = array();
  foreach ($declaration->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF),
                                              'order' => array('id' => 'ASC',
                                                               'position' => 'ASC'))) as $formulaire) {
    $formulaires_by_ftypes[$formulaire->formulairetype_id][] = $formulaire;
  }

  $default_values_binded = array(
    'adherent_frp' => $adherent->frp,
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
    $millesime = Millesime::getInstance($ftype->ftype_millesime_id);
    $itemplate = Itemplate::getInstance(array('millesime_id' => $millesime->getId(),
                                              'status' => 1,
                                              'formulairetype_id' => $ftype->getId()));
    $ftypes_imprimes[$ftype->code] = array('ftype' => $ftype,
                                           'itemplate' => $itemplate,
                                           'millesime' => $millesime);
    $ftypes_imprimes_options[$ftype->code] = $ftype->title_code;
    foreach ((array) $formulaires_by_ftypes[$ftype->getId()] as $formulaire) {
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

    $ftype_is_repetable = $ftype->isRepetable($millesime);
    if ($ftype_is_repetable) {
      $ftypes_imprimes[$ftype->code]['model'] = createImprimeEmpty($ftype, $declaration_dectype, $default_values_binded, $millesime);
    }
    elseif (count($ftypes_imprimes[$ftype->code]['imprimes']) < 1) {
      $ftypes_imprimes[$ftype->code]['imprimes'][] = createImprimeEmpty($ftype, $declaration_dectype, $default_values_binded, $millesime);
    }

  }



  $return_link = $req->getClient('referer');
  if (strpos($from, 'suivi') === false && strpos($from, 'declarer') === false) {
    $return_link = '/middle/declarer';
  }
  if(strpos($return_link, '/middle/declarer') !== false)  {
    $return_link = H::url('/middle/declarations');
  }

  $ctx->return_link = $return_link;


  $ctx->dectype = $declaration_dectype;
  $ctx->declaration = $declaration;
  $ctx->adherent = $adherent;
  $ctx->ftypes_imprimes = $ftypes_imprimes;
  $ctx->ftypes_imprimes_options = $ftypes_imprimes_options;
  $ctx->return_link = $return_link;

  $ctx->_keep_templates = true;
  $res->useTemplates(array(null, true));
  $res->setTitle($declaration_dectype->getName());

}
catch (Exception $e) {
  $err->add($e);
}


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
