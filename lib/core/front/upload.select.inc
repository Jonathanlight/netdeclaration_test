<?php

try {
  
  $ctx->filter = $req->filter;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }