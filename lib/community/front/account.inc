<?php

try {

  $uid = $req->getUserId();

  $actions = AccountManager::actions();
  $action = current($actions);


  $res->sendRedirect($action['action']);

}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }