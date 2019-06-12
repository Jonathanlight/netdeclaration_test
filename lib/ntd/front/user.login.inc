<?php

try {

  if (!$req->isAuthenticated()) {
    throw new Exception($ctx->_auth_errors);
  }

  $ctx->user_id = $req->getUser()->getId();
  $res->sendRedirect('/middle');

}
catch (Exception $e) { $err->add($e); }