<?php

try {

  $adherent = Adherent::getInstance(array('id' => (int) $req->id,
                                          'user_id' => $user->getId()));
  NetDeclaration::setCurrentAdherent($adherent->getId());

}
catch (Exception $e) {
  $err->add($e);
}
