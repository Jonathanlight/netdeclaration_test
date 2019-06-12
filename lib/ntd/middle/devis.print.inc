<?php

try {

  $estimation = Estimation::getInstance((int) $req->id);

  $ctx->estimation = $estimation;
  $ctx->tarifs = $estimation->getTarifs();
setlocale(LC_TIME, 'fr_FR');
  $res->useTemplates(null, 'skeleton.pdf', 'app/ntd/templates/middle/devis.print.psp');

} catch (Exception $e) { $err->add($e); }
