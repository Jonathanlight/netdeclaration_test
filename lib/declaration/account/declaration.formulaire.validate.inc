<?php

try {

  $declaration = Declaration::getInstanceAuth((int) $req->declaration_id, $user);
  $dectype = $declaration->getDectype();
  $ftype = Formulairetype::getInstance((int) $req->formulairetype_id);
  $millesime = $dectype->getFtypeMillesime($ftype);

  $imprime = new Imprime();
  $imprime->setFormulairetype($ftype, $millesime);
  $imprime->setIndex((int) $req->index);
  $imprime->setFieldValues((array) $req->fields);
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

  // Formulairetype requirements
  if ($dectype->hasRequiredFormulairetypeRelation($ftype)) {
    $required_ftype = $dectype->getRequiredFormulairetypeRelation($ftype);

    $filters = array('filters' => array('formulairetype_id' => $required_ftype->getId(),
                                        'status'            => Formulaire::STATUS_ACTIF));
    $forms = $declaration->getFormulaires($filters);

    if ($forms->count() == 0) {
      throw new Exception('Le formulaire "'.$required_ftype->code.'" est requis puisque vous avez renseigné le formulaire "'.$ftype->code.'"');
    }
  }


  $res->sendMessage('Aucune erreur n\'a été détectée dans le formulaire déclaratif');

}
catch (Exception $e) {
  $err->add($e);
}
