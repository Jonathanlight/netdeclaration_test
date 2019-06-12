<?php

try { 

  $base = Item::getInstanceByKey($req->item_key);

  $req->track();
  $base->track();

  $ctx->base = $base;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
