<?php

try {

  $res->setContentType('rss');

  if ($res->isCached()) return ;

  $item = Item::getInstanceByKey($req->item_key);
  
  $entries = $item->getComments(array('last' => 10));
  
  $res->write($item->asFeed($entries));

}
catch (Exception $e) { $err->add($e); }
