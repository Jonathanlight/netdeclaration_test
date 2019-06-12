<?php

try {

  if (empty($req->email)) return ;

  if (!Email::isValid($req->email, true)) {
    throw new Exception(l('error.email.invalid'));
  }

  $recipient_id = Email::asId($req->email);
  
  $old = $user->getInformation('recipient_id');

  if ($recipient_id >= 1 && $recipient_id != $old) {
    $dbo->exec('UPDATE '.Base::TABLE_EMAIL
               .' SET email_id='.$recipient_id
               .' WHERE email_id='.$old);
    $user->setInformation('recipient_id', $recipient_id);
  }

  $res->setFlash(l('recipient.saved'));

}
catch (Exception $e) { $err->add($e); }
