<?php

try {

  //  $req->debug();

  $items = $req->items;

  foreach ($items as $record_id => $attributes) {
    $item = Item::getInstance(MODEL, $record_id);
    foreach ($attributes as $key => $value) {
      try {
        $item->setFinderAttribute($key, $value);
      }
      catch (Exception $e) {
        $log->error($e);
      }
    }
  }

  $res->sendMessage("modifications effectuées");

}
catch (Exception $e) { $err->add($e); }
