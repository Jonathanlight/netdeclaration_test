<?php

try { 
  
  $item = Item::getInstanceByKey($req->item);
  
  $motive = Motive::getInstance($req->motive_id);

  $content = String::clean($req->content);
  $full_name = String::clean($req->full_name);
  $email = String::clean($req->email);

  $attributes = array('model_id' => $item->getModelId(),
                      'record_id' => $item->getId(),
                      'content' => $content,
                      'motive_id' => (int) $req->motive_id,
                      'full_name' => $full_name,
                      'email' => $email);

  $abuse = Abuse::getInstance();
  $abuse->commit($attributes);
  $abuse->setVisit($req);
  
  if ($req->isAuthenticated()) {
    $user = $req->getUser();
    $abuse->setUser($user);
    Letter::send('abuse.report.confirm', $user);
  }

  if ($motive->hasFlag(Motive::FLAG_WARN)) {
    $hash = array('motive' => (string) $motive,
                  'about' => $content,
                  'url' => $req->getClient('referer'),
                  'target' => $item->getModel().' ('.$item->getId().')');
    foreach (array('name', 'title', 'content') as $field) {
      if (!$item->hasAttribute($field)) continue ;
      $hash['target - '.$field] = $item->getAttribute($field);
    }
    $hash = array_merge($hash, 
                        $req->getClient());
    $recipients = empty($motive->recipients) 
                ? P('contact.admin')
                : String::asSet($motive->recipients);
    $mail = Mail::getInstance();
    $mail->setSubject('abuse report : '.$item->getModel());
    $mail->setBody($hash);
    $mail->addRecipient($recipients);
    $mail->send();
  }

  if ($motive->hasFlag(Motive::FLAG_HIDE)) {
    $item->hide();
  }

  if ($item->user_id > 0) {
    try {
      $user = User::getInstance($item->user_id);
      $user->setFlag(User::FLAG_ABUSE);
    }
    catch (Exception $e) { $log->error($e); }
  }

  $item->incrementMeta('abuse');

  $req->track();

  $res->sendMessage(l('abuse.report.ack'));

}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }
