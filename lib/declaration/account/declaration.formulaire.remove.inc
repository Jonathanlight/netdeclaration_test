<?php

try {

  $declaration = Declaration::getInstanceAuth((int) $req->declaration_id, $user);
  if ($declaration->status > Declaration::STATUS_EDITABLE) {
    throw new MaliciousException('cette déclaration ne peut être modifiée.');
  }

  $formulaire_args = array('declaration_id' => $declaration->getId(),
                           'formulairetype_id' => (int) $req->formulairetype_id,
                           'position' => (int) $req->index);  

  $formulaire = Formulaire::getInstance($formulaire_args);
  $formulaire->setStatus(Formulaire::STATUS_REMOVED);

}
catch (Exception $e) {
  $err->add($e);
}
