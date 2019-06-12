<?php

try {

  $user = $req->getUser();

  $item = Item::getInstanceByKey($req->item_key);

  $filters = array('model_id' => $item->getModelId(),
                   'record_id' => $item->getId(),
                   'user_id' => $user->getId());
  
  $dbo->update('cty_item_alert',
               array('status' => 0),
               array('filters' => $filters));

  $res->write(l('alert.stop'));

}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }

