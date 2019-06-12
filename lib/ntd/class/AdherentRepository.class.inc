<?php


class AdherentRepository {

  public static function changeToPrimaryAdherent($adherent_id) {
    $adherent = Adherent::getInstance((int) $adherent_id);
    $user = $adherent->getUser();
    $primary_adherent = $adherent->getAdherent();
    foreach ($user->getAdherents() as $user_adherent) {
      $user_adherent->setAttributes(array('adherent_id' => $adherent->getId()));
    }
    $adherent->setAttributes(array('adherent_id' => 0,
                                   'level' => 1));
    $primary_adherent->setAttribute('level', 2);
  }

  public static function changePrimaryAdherentUser($adherent_id, $new_user_id) {
    $adherent = Adherent::getInstance((int) $adherent_id);
    if ($adherent->adherent_id > 0) {
      throw new Exception('adherent must be primary');
    }
    $user = User::getInstance((int) $new_user_id);

    $adherent->setAttribute('user_id', $user->getId());
    foreach ($adherent->getAdherents() as $sub_adherent) {
      $sub_adherent->setAttribute('user_id', $user->getId());
    }
  }

  public static function becomePrimaryAdherentForUser($adherent_id, $new_user_id) {
    $adherent = Adherent::getInstance((int) $adherent_id);
    if ($adherent->adherent_id == 0) {
      throw new Exception('adherent must be secondary');
    }
    $user = User::getInstance((int) $new_user_id);
    if (Adherent::collect(array('filters' => array('user_id' => $user->getId())))->count() > 0) {
      throw new Exception('user must not have adherent linked to');
    }

    $adherent->setAttributes(array('user_id' => $user->getId(),
                                   'adherent_id' => 0,
                                   'level' => 1));

  }
}
