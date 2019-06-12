<?php

try {

  $res->useTemplates(null, 'skeleton.pdf', true);
  $ctx->domtom = (int) $req->domtom;

}
catch (Exception $e) {
  $err->add($e);
}