<?php

try {

  $args = array(
    'from' => $req->from,
    'to'   => $req->to
  );
  $ctx->contents = FactureRecoveryManager::getContentsByAdherent($args);

  NtdMiddleManager::useTemplate(false);

} catch (Exception $e) {
  $err->add($e);
}
