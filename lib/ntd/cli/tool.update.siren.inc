<?php

try {

  $adherents = Adherent::collect();
  foreach ($adherents as $adherent) {
    $adherent->updateSiren();
  }

} catch (Exception $e) {
  $err->add($e);
}
