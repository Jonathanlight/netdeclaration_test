<?php

try {

  $visit = Visit::getInstance($req->id);
  $visits = $visit->getSiblings();

  $ctx->visit = $visit;
  $ctx->visits = $visits;
  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
