<?php

try {

  $item = Item::getInstanceByKey($req->item_key);

  $html = Resource::asRows($item);

  //  $log->trace($html);

  $res->write($html);

}
catch (Exception $e) { $err->add($e); }
