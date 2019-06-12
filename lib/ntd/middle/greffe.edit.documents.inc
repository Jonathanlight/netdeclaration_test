<?php

try {

  $id = (int)$req->getAttribute('id');

  if (!Greffe::exists($id)) {
    throw new Exception(l('error'));
  }

  $greffe = Greffe::getInstance($id);
  $ctx->greffe = $greffe;

  if ($greffe->souscription_id == 0) {
    throw new Exception('Souscription invalide');
  }

  $type_compte = $greffe->compte_type;
  $forme_juridique = $greffe->forme_juridique;
  $is_gerant = $greffe->is_gerant;
  $mode_direction = $greffe->mode_direction;
  $compte_public = $greffe->is_public;

  $docs = array();
  foreach (GreffeManager::getRequiredDocs($type_compte, $forme_juridique, $is_gerant, $mode_direction, $compte_public) as $doc) {
    $docs[$doc] = GreffeManager::$docs[$doc];
  }
  $ctx->documents = $docs;
  $ctx->registered_documents = $greffe->getDocuments();

  if (!empty($greffe->documents)) {
    $ctx->reponse_documents = array();
    foreach ($greffe->documents as $document) {
      $ctx->reponse_documents[] = array('name' => $document,
                                        'url'  => '/' . $greffe->getResponseDocumentPath() . '/' . $document);
    }
  }

  $ctx->liasse_declaration = GreffeManager::getLiasse($greffe);


  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_GREFFE);
  NtdMiddleManager::setBreadCrumb(array('Greffe'  => '/middle/greffe',
                                        'Edition' => '/middle/greffe.edit/-/id/' . $greffe->getId(),
                                        'Pièces à fournir'));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) { $err->add($e); }