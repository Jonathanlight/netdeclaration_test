<?php

try {

  if (!is_array($req->id)) return ;

  $i = 0; 
  foreach ($req->id as $id) {
    try {
      $item = Item::getInstance(MODEL, $id);
      $item->accept();
      $i++;
    }
    catch (Exception $e) { $log->error($e); }
  }
  $res->sendMessage($i . ' élément(s) accepté(s)');

}
catch (Exception $e) { $err->add($e); }
