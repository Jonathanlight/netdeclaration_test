<?php

try {

  $services_offer_id = array(
    52, // => Réception EDI CVA [1330 & 1329DEF]
    71, // => Émission IAT => *CEC adhérent au Portail
    72, // => Émission CRM => *CEC adhérent au Portail
  );

  $filters = array('type' => Adherent::TYPE_OGA);
  $adherents = Adherent::collect(array('filters' => $filters));

  foreach ($adherents as $adherent) {
    print 'Adherent : ' . $adherent->getId() . PHP_EOL;

    // Check Accès EDI valide
    $args = array(
      'adherent_id'   => $adherent->getId(),
      'service_id'    => 32, // Accès EDI
      'status'        => Souscription::STATUS_ACTIVE,
      '|<=|start_at'  => date('Y-m-d'),
      '|>=|finish_at' => date('Y-m-d')
    );

    if (count(Souscription::collect(array('filters' => $args))) == 0) {
      continue;
    }


    // Ajout des Souscriptions
    foreach ($services_offer_id as $service_offer_id) {
      $args = array(
        'adherent_id'   => $adherent->getId(),
        'service_id'    => $service_offer_id,
        'status'        => Souscription::STATUS_ACTIVE,
        '|<=|start_at'  => date('Y-m-d'),
        '|>=|finish_at' => date('Y-m-d')
      );

      if (count(Souscription::collect(array('filters' => $args))) > 0) {
        continue;
      }

      $souscription = Souscription::getInstance();
      $service = Service::getInstance($service_offer_id);

      $record = array(
        'sign_at'       => '2016-07-01',
        'start_at'      => '2016-07-01',
        'finish_at'     => '2017-07-01',
        'price'         => 0,
        'is_renewable'  => 1,
        'status'        => Souscription::STATUS_ACTIVE
      );

      $opts = array(
        'quantity' => 1
      );

      $souscription = Souscription::createSouscription($service, $adherent, $record, $opts);
      $souscription->setAttribute('price', $record['price']);

      print '-- Souscription : ' . $souscription->getId() . PHP_EOL;
    }
  }

}
catch (Exception $e) {
  $err->add($e);
}
