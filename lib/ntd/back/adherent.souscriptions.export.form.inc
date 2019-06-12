<?php

try {

  $opts = array('filters' => array('status' => Partenaire::STATUS_ONLINE));

  $partenaires = Partenaire::collect($opts);

  $ctx->partenaires = $partenaires;

  $res->useTemplate();

} catch (Exception $e) { $err->add($e); }
