<?php

try {

  $user = User::getInstance(array('email' => $req->email),
                            array('ignore' => true));
  
  if ($user->status <= User::STATUS_CLOSED) {
    $log->trace('invalid user ['.$user->email.']');
    throw new Exception();
  }

  //$link = 'http://'.$req->getServer('host');
  //$link .= '/account/community/password?credential='.$user->getCredential();
  $link = H::url('/account/ntd/password', array('credential' => $user->getCredential()));

  $link = '<a href="'.$link.'">'.l('click.here').'</a>';
  
  Letter::send('password.reset', $user, 
               array('link' => $link),
               array('locale' => $res->getLocale()));

  $req->track();
  
  $res->sendMessage(l('alert.password.sent'));  

}
catch (Exception $e) { $err->add(l('error.email.unknown')); }
