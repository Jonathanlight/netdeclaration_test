<?php

try {

  if (!$req->hasAttribute('newsletter', true)) {
    throw new Exception(c(l('error')));
  }

  $newsletters = (array)$req->newsletter;
  $adherent = Adherent::getCurrentPrimaryAdherent();
  $subscribed_newsletter_id = $adherent->getSubscribedNewsletterBases()->asSet('id');
  $user = $adherent->getUser();
  $email = $user->email;

  foreach ($newsletters as $key => $newsletter_id) {
    if (!Base::exists($newsletter_id)) {
      unset($newsletters[$key]);
      continue;
    }
    $base = Base::getInstance($newsletter_id);
    if (!$base->hasEmail($email)) {
      $base->addEmail($email, true);
    }
  }

  $to_remove = array_diff($subscribed_newsletter_id, $newsletters);
  foreach ($to_remove as $newsletter_id) {
    $base = Base::getInstance($newsletter_id);
    if ($base->hasEmail($email)) {
      $base->removeEmail($email);
    }
  }

  $res->sendMessage(l('alert.newsletter.changed'));


} catch (Exception $e) {
  $err->add($e);
}
