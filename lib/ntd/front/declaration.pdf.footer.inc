<?php

try {

  $declaration = Declaration::getInstanceByKey($req->key);
  $dectype = $declaration->getDectype();

  $opts = array('include' => array('formulairetype'),
                'filters' => array('document_code' => Formulairetype::DOCUMENT_CODE_IDENTIF));
  $formulaires = $declaration->getFormulaires($opts);

  if ($formulaires->count() >= 1) {
    $formulaire = $formulaires->first();
    $ctx->datas = $formulaire->data;
  }

  $ctx->adherent = $declaration->getAdherent();
  $ctx->declaration = $declaration;

  $res->resetTemplates();
  $res->useTemplate();

} catch (Exception $e) { $log->error($e); }
