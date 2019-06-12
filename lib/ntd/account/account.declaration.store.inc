<?php

try {

  // TODO : verifier que l'adhérent est le bon
  $user = $req->getUser();
  $declaration_commit = (array) $req->declaration;


  // VERIFICATION DES FORMULAIRES
  $declaration_dectype = Dectype::getInstance($declaration_commit['dectype_id']);
  $params = array('declaration_formulairetype' => $declaration_dectype,
                  'declaration_data' => array());

  $maxOccurences = 1;
  foreach ($declaration_dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
    if (!$req->hasAttribute($ftype->name)) continue;

    foreach ((array) $req->getAttribute($ftype->name) as $field_name => $field_value) {
        if (count($field_value) > $maxOccurences) {
            $maxOccurences = count($field_value);
        }
      $params['declaration_data'][$ftype->name . '_' . $field_name] = $field_value;
    }
  }

  $errors = array();
  foreach ($declaration_dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
    if (!$req->hasAttribute($ftype->name)) continue;
    $data = (array) $req->getAttribute($ftype->name);
    Formulaire::initData($ftype->name);
    Formulaire::$cast = true;

    for ($i = 0; $i < $maxOccurences; $i++) {
        $millesime = Millesime::getInstance($ftype->ftype_millesime_id);
        if (!$ftype->isRepetable($millesime) && $i > 0) {
            continue;
        }


        $declaration_data = array();
        foreach ($params['declaration_data'] as $fieldName => $values) {
            $declaration_data[$fieldName] = $values[$i];
        }
        $paramsOccurence = $params;
        $paramsOccurence['declaration_data'] = $declaration_data;
        $dataFormatted = array();
        foreach ($paramsOccurence['declaration_data'] as $fieldName => $declarationDatum) {
            if (preg_match('/^' . $ftype->name . '/', $fieldName)) {
                $dataFormatted[$ftype->name][str_replace($ftype->name . '_', '', $fieldName)] = $declarationDatum;
            }
        }

        Formulaire::validForm($ftype->name,
            Formulaire::asValidationData($ftype->name,
                $dataFormatted),
            $paramsOccurence);

        $errors = FormulaireErrors::displayErrors(Formulaire::$errors) + $errors;
        if (sizeof($errors) > 0) {
            $ctx->errors = $errors;
            $ctx->occurence = $i;
            $ctx->ftype_code = $ftype->code;
            throw new Exception('Des erreurs ont été détectés dans le formulaire déclaratif.');
        }
    }
  }

  // ENREGISTREMENTS DES FORMULAIRES
  $id = (int) $req->id;
  if ($id > 0) {
    $declaration = Declaration::getInstance(array('id' => $id, 'status' => Declaration::STATUS_EDITABLE));
    $adherent = $declaration->getAdherent();
  }
  else {
    $declaration = Declaration::getInstance();
    $adherent = Adherent::getInstance(array('user_id' => $user->getId(), 'id' => (int) $req->adherent_id));
    $declaration_commit['adherent_id'] = $adherent->getId();
  }

  $declaration->commit($declaration_commit);
  $formsIdSaved = array();
  foreach ($declaration_dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
    if ($req->hasAttribute($ftype->name)) {

      $data = (array) $req->getAttribute($ftype->name);
      $opts = (array) $req->getAttribute($ftype->name.'_opts');

      for ($i = 0; $i < $maxOccurences; $i++) {
          $millesime = Millesime::getInstance($ftype->ftype_millesime_id);
          if (!$ftype->isRepetable($millesime) && $i > 0) {
              continue;
          }

          $declaration_data = array();
          foreach ($params['declaration_data'] as $fieldName => $values) {
              $declaration_data[$fieldName] = $values[$i];
          }
          $paramsOccurence = $params;
          $paramsOccurence['declaration_data'] = $declaration_data;

          Formulaire::validForm($ftype->name, Formulaire::asValidationData($ftype->name, $req->getAttributes()), $paramsOccurence);
          $dataFormatted = array();
          foreach ($paramsOccurence['declaration_data'] as $fieldName => $declarationDatum) {
              if (preg_match('/^' . $ftype->name . '/', $fieldName)) {
                  $dataFormatted[str_replace($ftype->name . '_', '', $fieldName)] = $declarationDatum;
              }
          }
          $data = Formulaire::formatData($ftype->name, $dataFormatted, $paramsOccurence);

          $formulaire_commit = array();
          $formulaire_commit['data'] = $dataFormatted;
          $formulaire_commit['opts'] = $opts;


          $formulaire_commit['status'] = Formulaire::STATUS_ACTIF;
          if ($declaration->isLoaded() && Formulaire::exists(array('declaration_id' => $declaration->getId(), 'formulairetype_id' => $ftype->getId(), 'position' => $i))) {
              $formulaire = Formulaire::getInstance(array('declaration_id' => $declaration->getId(), 'formulairetype_id' => $ftype->getId(), 'position' => $i));
          } else {
              $formulaire = Formulaire::getInstance();
              $formulaire_commit['declaration_id'] = $declaration->getId();
              $formulaire_commit['formulairetype_id'] = $ftype->getId();
          }
          $formulaire_commit['position'] = $i;
          $formulaire->commit($formulaire_commit);
          $formsIdSaved[] = $formulaire->getId();
      }
    }
    elseif ($declaration->isLoaded() && Formulaire::exists(array('declaration_id' => $declaration->getId(), 'formulairetype_id' => $ftype->getId()))) {
      $formulaire = Formulaire::getInstance(array('declaration_id' => $declaration->getId(), 'formulairetype_id' => $ftype->getId()));
      $formulaire->destroy(); // cas : formulaire annexe retirés
    }
  }

  foreach ($declaration->getFormulaires()->asSet('id') as $formId) {
      if (!in_array($formId, $formsIdSaved)) {
          $formToDestroy = Formulaire::getInstance($formId);
          $formToDestroy->destroy();
      }
  }

  $ctx->id = $declaration->getId();
  $ctx->adherent_id = $declaration->getAdherent()->getId();

  $mail = new Mail();
  $mail->addRecipient("npinchon@kernix.com", "Nicolas PINCHON");
  $mail->addRecipient("bbechade@kernix.com", "Bertrand Bechade");
  $mail->setSubject("[" . P('app.domain') . "][NTD] Modification de la déclaration N°" . $declaration->getId());
  $mail->setBody('Pour y accéder : <a href="http://' . P('app.domain') . '/account/ntd/account.declaration.edit/-/declaration_id/' . $declaration->getId() . '">lien</a>');
  //$mail->send();

}
catch (Exception $e) {
  $err->add($e);
}
