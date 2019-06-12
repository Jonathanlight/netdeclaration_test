<?php

try {

  if ($user->email == $req->email) return ;

  if ($req->getUser()->setEmail($req->email) === false) { 
    throw new Exception(l('error')); 
  }

  $user->requestEmailConfirmation();
 
  $res->sendMessage(l('alert.email.changed'));

}
catch (Exception $e) {
  $req->track('email modification', Tracker::CATEGORY_ERROR);
  $err->add($e); 
}