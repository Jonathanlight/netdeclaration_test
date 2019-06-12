<?php

try {

  $service = Service::getInstance(49); // Accès Greffe
  $type = 1;

  // $service = Service::getInstance(50); // Greffe
  // $type = 3;

  $adherent = Adherent::getInstance(2);
  $quantity = null;
  $date = null;

  $tarif = $service->getTarif($adherent, $type, $quantity, $date);
  echo 'Tarif : ' . ($tarif ? var_export($tarif->getAttributes(), true) : 'AUCUN');

}
catch (Exception $e) { $err->add($e); }