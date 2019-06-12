<?php

try {

  $declaration = Declaration::getInstanceAuth((int) $req->id, $user);
  $dectype = $declaration->getDectype();

  $ftypes = $dectype->getFormulairetypes(array('filters' => array('ntd_dectype_formulairetype.type' => Dectype::RELATION_TYPE_OBLIGATOIRE)));
  $formulaires = $declaration->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF)))->asHash('formulairetype_id',
                                                                                                                       'formulairetype_id');
  $missing_requireds = $declaration->getMissingRequired();


  $ogas = Adherent::collect(array('filters' => array('status' => Adherent::STATUS_SUBSCRIPTION_VALIDE,
                                                     'type' => Adherent::TYPE_OGA,
                                                     'adherent_id' => 0),
                                  'order' => array('company' => 'ASC')));

  $ctx->dectype_destinataires = $dectype->destinataires;
  usort($ctx->dectype_destinataires, function ($a, $b) {
    if ($a == Destinataire::TYPE_BDF && $b == Destinataire::TYPE_DGI) {
      return 1;
    }
    elseif ($a == Destinataire::TYPE_DGI && $b == Destinataire::TYPE_BDF) {
      return -1;
    }
    return 1;
  });

  $tmp = array_flip($ctx->dectype_destinataires);
  if (isset($tmp[Destinataire::TYPE_DGI])) {
    unset($tmp[Destinataire::TYPE_DGI]);
    $tmp = array(Destinataire::TYPE_DGI => '') + $tmp;
    $ctx->dectype_destinataires = array_values(array_flip($tmp));
  }

  $ctx->missing_requireds = $missing_requireds;
  $ctx->ogas = $ogas;
  $ctx->declaration = $declaration;
  $ctx->dectype = $dectype;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_DECLARATION);
  NtdMiddleManager::setBreadCrumb('Envoi de la déclaration');
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
