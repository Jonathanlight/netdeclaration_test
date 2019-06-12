<?php

try {

  $req->mode = 'signup';
  User::signup();

}
catch (Exception $e) { $err->add($e); }
