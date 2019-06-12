<?php

try {

  $ctx->domtom = (int) $req->domtom;
  $ctx->title = base64_decode($req->head_title);
  $ctx->page = (int) $req->page;
  $ctx->topage = (int)$req->topage;

  $res->useTemplates(null, 'skeleton.pdf', true);

}
catch (Exception $e) {
  $err->add($e);
}