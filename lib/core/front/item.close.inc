<?php

try { 

  if (!$req->getUser()->isModerator()) {
    throw new PrivilegeException(l('error.privilege'));
  }

  $item = Item::getInstanceByKey($req->item_key); 
  $item->setBit(Meta::BIT_CLOSED);

  $req->track();

  $res->sendRedirect($item);

}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }