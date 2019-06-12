<?php

try {

  $item = Item::getInstance(MODEL, $req->id);

  $ctx->setAttributes($req);
  $ctx->recipients = String::asSet($req->recipients);
  $ctx->item = $item;

  $item->onLetterSend();

  if (count($ctx->recipients) < 1) {
    throw new Exception('Veuillez préciser les adresses emails des destinataires');
  }

  foreach ($ctx->recipients as $email) {
    $mail = Mail::getInstance();
    $mail->setSubject($ctx->subject);
    $mail->setBody($ctx->body, true);
    $mail->setRecipient($email);
    if (!empty($ctx->from_email)) {
      $mail->setFrom($ctx->from_email, $ctx->from_name);
    }
    $mail->send();
  }

  $res->sendMessage('Le message a bien été envoyé à '.count($ctx->recipients).' destinataire(s)');

}
catch (Exception $e) { $err->add($e); }
