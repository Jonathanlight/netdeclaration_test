<?php

try {

  if (!$req->hasAttribute('id', true) || !$req->hasAttribute('document_type', true)) {
    throw new Exception(c(l('error')));
  }

  $greffe = Greffe::getInstance((int)$req->id);
  $document_type = (int)$req->document_type;
  $documents = $greffe->getDocuments();

  $greffe_documents = array();
  foreach ($documents as $document) {
    if ($document['type'] != $document_type) {
      $greffe_documents[] = $document;
    }
  }

  $greffe->setDocuments($greffe_documents);

}
catch (Exception $e) { $err->add($e); }
