<?php

try {

  if ($req->id < 1 || $req->user_id < 1) {
    $req->debug();
    throw new Exception('invalid parameters');
  }

  $item = Item::getInstance(MODEL, $req->id);

  $user = User::getInstance($req->user_id);

  ACL::removeAccess($user, $item);

}
catch (Exception $e) { $err->add($e); }
