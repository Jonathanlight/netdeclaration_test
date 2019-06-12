<?php

try { 

  $user = $req->getUser();

  $name = $req->name;
  $content = $req->content;
  
  if (empty($name) || empty($content)) {
    throw new Exception(l('error.fields.required.all'));
  }

  if (strlen($name) > 90) {
    throw new Exception(l('error.title.size'));
  }

  if (strlen($content) > 20000) {
    throw new Exception(l('error.content.size'));
  }

  $recipient = Item::getInstanceByKey($req->item_key);
  if (Extension::exists('social')) {
    Message::send($user, array($recipient), $name, $content);
  }
  else {
    $content .= "\n\n".ucfirst(l('sent.by')).' '.$user->name;
    $mail = Mail::getInstance();
    $mail->setFrom($user);
    $mail->addRecipient($recipient);
    $mail->setSubject(String::clean($name));
    $mail->setBody(nl2br(String::clean($content)));
    $mail->send();
  }

  $req->track('message.send');
  
  $res->sendMessage(ucfirst(l('message.sent')));

}
catch (AuthException $e) { $err->add($e); }
catch (Exception $e) { $err->add($e); }

