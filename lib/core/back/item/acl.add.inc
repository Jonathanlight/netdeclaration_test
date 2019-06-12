<?php

try {

  if ($req->id < 1 || empty($req->user)) {
    $req->debug();
    throw new Exception('invalid parameters');
  }

  $item = Item::getInstance(MODEL, $req->id);
  
  if (is_numeric($req->user)) {
    $args = (int) $req->user;
  }
  else {
    $args = array('email' => $req->user);
  }

  $user = User::getInstance($args, array('ignore' => true));

  ACL::grantAccess($user, $item);

}
catch (Exception $e) { $err->add($e); }
