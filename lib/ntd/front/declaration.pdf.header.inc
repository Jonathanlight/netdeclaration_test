<?php

try {

  $declaration = Declaration::getInstanceByKey($req->key);

  $ctx->adherent = $declaration->getAdherent();
  $ctx->declaration = $declaration;

  $res->resetTemplates();
  $res->useTemplate();

} catch (Exception $e) { $log->error($e); }
