<?php

try { 

  $item = Item::getInstanceByKey($req->item_key);

  $ctx->item = $item;

  $req->track();

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }