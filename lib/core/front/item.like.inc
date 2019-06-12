<?php

try {
  
  $user = $req->getUser();

  $item = Item::getInstanceByKey($req->item_key);

  $table = $dbo->getTable(Intent::TABLE);
  $row = array('model_id' => $item->getModelId(),
               'record_id' => $item->getId(),
               'type' => Intent::TYPE_LIKE,
               'user_id' => $user->getId()); 
  if (!$table->hasRow($row)) { 
    $item->track(Intent::TYPE_LIKE);
  }

  $n = $item->getMeta('`like`');

  $ctx->like_count = $n;

}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }
