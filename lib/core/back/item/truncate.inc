<?php

try {
  
  $item = Item::getInstance(MODEL, $req->id);

  $n = $item->truncate();

  $msg  = 'opération réalisée avec succès : '."\n";
  $msg .= $n.' objets supprimé(s)';

  $res->sendMessage($msg);
  
}
catch (Exception $e) { $err->add($e); }
