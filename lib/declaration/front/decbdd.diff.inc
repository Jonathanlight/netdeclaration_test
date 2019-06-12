<?php

try {

  if(P('app.state') != 'dev') return;

  $ctx->apps = $ctx->apps = DecBdd::getAll('decbdd.export');

  $res->useTemplates(array(null, 'skeleton.decbdd', true));

}
catch (Exception $e) {
  $err->add($e);
}