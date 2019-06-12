<?php

try {

  $id = (int) $req->id;
  $adherent = array();
  $show_gestion = false;
  $main_adherent = Adherent::getCurrentPrimaryAdherent();

  if ($req->mode == 'main-adherent') {
    $adherent = $main_adherent->getAttributes();
  }
  elseif ($req->mode == 'current-adherent') {
    $adherent = NetDeclaration::getCurrentAdherent()->getAttributes();
  }
  elseif ($id > 0) {
    $adherent = Adherent::getInstance(array('id' => $id, 'user_id' => $user->getId()))->getAttributes();
  }
  if($adherent['id'] > 0 && in_array($adherent['type'], array(Adherent::TYPE_CEC, Adherent::TYPE_OGA))){
    $_adherent = Adherent::getInstance($adherent['id']);
    $services_availables = $_adherent->getServicesAvailables();
    $show_gestion = in_array(Service::TYPE_EDI, $services_availables->asHash('id', 'type'));
  }

  $ctx->adherent = $adherent;
  $ctx->main_adherent = $main_adherent;
  $ctx->show_gestion = $show_gestion;

}
catch (Exception $e) {
  $err->add($e);
}
