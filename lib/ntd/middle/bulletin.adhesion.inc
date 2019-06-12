<?php

try {

  $id = (int) $req->id;
  if ($id > 0) {
    $adherent = Adherent::getInstance(array('user_id' => $req->getUser()->getId(), 'id' => $id));
  } else {
    $adherent = NetDeclaration::getCurrentAdherent();
  }

  $main_adherent = ($adherent->adherent_id > 0) ? Adherent::getInstance(array('user_id' => $req->getUser()->getId(), 'id' => $adherent->adherent_id)) : $adherent;

  $ctx->main_adherent = $main_adherent;
  $ctx->adherent = $adherent;

  $res->useTemplates(null, 'skeleton.pdf', 'bulletin.adhesion'); 

} catch (Exception $e) { $err->add($e); }
