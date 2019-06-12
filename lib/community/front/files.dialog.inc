<?php

try {

  $user = $req->getUser();

  $ctx->setAttributes($req);
  $ctx->user = $user;
  $ctx->files = $user->getFiles();

  $res->useTemplate();

}
catch (AuthException $e) { 
  User::signup(array('callback' => 'Kwo.getDialog().refresh()'));
}
catch (Exception $e) { }