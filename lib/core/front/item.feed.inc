<?php

try {

  $res->setContentType('rss');

  if ($res->isCached()) return ;

  $item = Item::getInstanceByKey($req->item_key);
  
  $res->write($item->asFeed());

}
catch (Exception $e) { $err->add($e); }
