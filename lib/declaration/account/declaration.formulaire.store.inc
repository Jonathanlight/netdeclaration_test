<?php

try {

  $declaration = Declaration::getInstanceAuth((int) $req->declaration_id, $user);

  if ($declaration->status > Declaration::STATUS_EDITABLE) {
    throw new MaliciousException('cette déclaration ne peut être modifiée.');
  }

  $dectype = $declaration->getDectype();
  $ftype = Formulairetype::getInstance((int) $req->formulairetype_id);
  $millesime = $dectype->getFtypeMillesime($ftype);

  $imprime = new Imprime();
  $imprime->setFormulairetype($ftype, $millesime);
  $imprime->setIndex((int) $req->index);
  $imprime->setFieldValues((array) $req->fields);

  // jdrzewinski action : declaration.formulaire.validate
  if ($dectype->hasFlag(Dectype::FLAG_STEP_DISPLAY)) {

    foreach ((array) $dectype->getRequiredFields($ftype->code) as $field_code => $required) {
      $imprime->getField($field_code)->setRequired($required);
    }

    $ifield_formulaire_neant = $imprime->getFieldFormulaireNeant();
    if ($ifield_formulaire_neant) {
      if ($imprime->getField($ifield_formulaire_neant->name)->getValue(0) > 0) {
        $res->sendMessage('Formulaire déposé néant. Aucune erreur n\'a été détectée dans le formulaire déclaratif');
        return;
      }
    }

    // Field validation
    $exceptions = $imprime->validateFields();
    if (count($exceptions) > 0) {
      $errors = array();
      foreach ($exceptions as $exception) {
        $errors[] = array('field' => $exception->getField()->getFullCode(),
                          'index' => $exception->getIndex(),
                          'imprime_index' => $exception->getImprimeIndex(),
                          'operation_name' => 'check',
                          'msg' => $exception->getMessage());
      }
      $ctx->field_errors = $errors;
      throw new Exception('Des erreurs ont été détectés dans le formulaire déclaratif.');
    }

    // Opérations validation
    $exceptions = $imprime->validateOperations(false);
    if (count($exceptions) > 0) {
      $errors = array();
      foreach ($exceptions as $exception) {
        $fields = array();
        foreach ($exception->getFieldFullCodes() as $fieldfullcode) {
          $fields[] = $fieldfullcode;
        }
        $errors[] = array('fields' => $fields,
                          'msg' => $exception->getMessage(),
                          'imprime_index' => $exception->getImprimeIndex(),
                          'operation_name' => $exception->getOperationName());
      }
      $ctx->operation_errors = $errors;
      throw new Exception('Des erreurs ont été détectés dans le formulaire déclaratif.');
    }

    $missing_requireds = $declaration->getMissingRequired();
    if (count($missing_requireds) < 1) {
      $declaration->setStatus(Declaration::STATUS_EDITABLE);
    }
    else {
      $declaration->setStatus(Declaration::STATUS_BROUILLON);
    }

  }

  $formulaire_args = array('declaration_id' => $declaration->getId(),
                           'formulairetype_id' => $imprime->getFormulairetype()->getId(),
                           'position' => $imprime->getIndex());
  $formulaire_commit = array('fields_values' => $imprime->getFieldsValues(),
                             'data' => $imprime->asTradeXpressExportHash(),
                             'status' => Formulaire::STATUS_ACTIF);

  if (Formulaire::exists($formulaire_args)) {
    $formulaire = Formulaire::getInstance($formulaire_args);
  }
  else {
    $formulaire = Formulaire::getInstance();
    $formulaire_commit = array_merge($formulaire_commit, $formulaire_args);
  }

  $formulaire->commit($formulaire_commit);
  $declaration->setMetas(array('updated_at' => Date::now()));

}
catch (Exception $e) {
  $err->add($e);
}
