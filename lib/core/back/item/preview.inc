<?php

try {

  if ($req->hasAttribute('item_key', true)) {
    $item = Item::getInstanceByKey($req->item_key);
    $url = $item->asUrl();
    $sep = strpos($url, '?') === false ? '?' : '&';
    $url .= $sep.'p=y'; 
  }
  else {
    $url = $req->url;
  }

  $ctx->url = $url;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
