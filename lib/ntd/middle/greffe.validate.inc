<?php

try {

  $greffe = Greffe::getInstance((int)$req->id);
  $ctx->greffe = $greffe;

  if ($greffe->souscription_id == 0) {
    throw new Exception('Souscription invalide');
  }

  if ($greffe && !empty($greffe->documents)) {
    $ctx->reponse_documents = array();
    foreach ($greffe->documents as $document) {
      $ctx->reponse_documents[] = array('name' => $document,
                                        'url'  => '/' . $greffe->getResponseDocumentPath() . '/' . $document);
    }
  }

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_GREFFE);
  NtdMiddleManager::setBreadCrumb(array('Greffe'           => '/middle/greffe',
                                        'Edition'          => '/middle/greffe.edit/-/id/' . $greffe->getId(),
                                        'Pièces à fournir' => '/middle/greffe.document.edit/-/id/' . $greffe->getId(),
                                        'Validation'));
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();

}
catch (Exception $e) { $err->add($e); }