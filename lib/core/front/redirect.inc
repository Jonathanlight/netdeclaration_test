<?php

try { 

  $url = '/';

  if ($req->hasAttribute('item', true)) {
    $item = Item::getInstanceByKey($req->item_key);
    $item->track(Intent::TYPE_REDIRECT);
    $url = $item->asUrl();
  }
  
  if ($req->hasAttribute('url', true)) {
    $url = $req->url;
  }
  
  $req->track();

  $url = H::url($url);

  $res->sendRedirect($url);

}
catch (Exception $e) { $err->add($e); }
