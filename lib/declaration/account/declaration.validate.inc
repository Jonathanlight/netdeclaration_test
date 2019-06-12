<?php

try {

  $declaration = Declaration::getInstanceAuth((int) $req->declaration_id, $user);
  $dectype = $declaration->getDectype();

  $ftypes = $dectype->getFormulairetypes(array('filters' => array('ntd_dectype_formulairetype.type' => Dectype::RELATION_TYPE_OBLIGATOIRE)));
  $formulaires = $declaration->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF)))->asHash('formulairetype_id',
                                                                                                                       'formulairetype_id');
  $missing_requireds = $declaration->getMissingRequired();
  if (count($missing_requireds) > 0) {
    $alert = 'Attention, cette déclaration semble incomplète, les formulaires sont manquants et ne seront pas transmis : '."\n\n - ";
    $alert .= implode("\n - ", $missing_requireds);
    $alert .= "\n\n".' Vous ne pourrez pas valider votre déclaration.'."\n";    
    throw new Exception($alert);
  }          

}
catch (Exception $e) {
  $err->add($e);
}
