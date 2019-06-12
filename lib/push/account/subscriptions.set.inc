<?php

try { 

  $email_id = Email::getInstance(array('email' => $user->email))->getId();

  foreach ($req->bases as $base_id => $flag) {
    $base = Base::getInstance($base_id);
    if (!$base->hasFlag(Base::FLAG_PUBLIC)) continue ; 
    if ($base->hasEmail($email_id)) {
      if ($flag == 0) {
        $base->removeEmail($email_id);
      }
    }
    elseif ($flag == 1) { 
      $base->addEmail($email_id, true);
    }
  }

  $res->setFlash(l('flash.save.success'));

}
catch (Exception $e) { $err->add($e); }
