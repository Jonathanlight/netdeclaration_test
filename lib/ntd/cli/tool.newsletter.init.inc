<?php

try {

  print 'Création des Bases ...' . PHP_EOL;

  foreach (NetDeclaration::$newsletter_bases as $key => $value) {
    if (!Base::exists(array('code' => $key))) {
      $base = Base::getInstance();
      $record = array(
        'code' => $key,
        'name' => $value,
        'app'  => 'ntd'
      );
      $base->commit($record);
    }
  }

  print '... Terminé !' . PHP_EOL;


  print 'Ajout des adhérents à leurs bases respectives ...' . PHP_EOL;

  $base_publique = Base::getInstance(NetDeclaration::NEWSLETTER_BASE_PUBLIC);
  $newsletter_types = array_flip(Adherent::$newsletter_bases);

  foreach (NetDeclaration::$newsletter_bases as $key => $value) {
    if ($key == NetDeclaration::NEWSLETTER_BASE_PUBLIC) {
      continue;
    }

    print '--- Base ' . $value . PHP_EOL;

    $base = Base::getInstance(array('code' => $key));

    $filters = array(
      'type' => $newsletter_types[$key]
    );
    $adherents = Adherent::collect(array('filters' => $filters));

    foreach ($adherents as $adherent) {
      $user = $adherent->getUser();
      $email = $user->email;

      if ($user->status <= User::STATUS_CLOSED) {
        continue;
      }

      if (!$base->hasEmail($email)) {
        $base->addEmail($email);
      }

      if (!$base_publique->hasEmail($email)) {
        $base_publique->addEmail($email);
      }
    }
  }

  print '... Terminé !' . PHP_EOL;

} catch (Exception $e) {
  $err->add($e);
}
