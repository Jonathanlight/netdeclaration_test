<?php

try {

  $dbo->exec('CREATE TABLE sys_country_20131231 SELECT * FROM  sys_country');
  $log->trace('sys_country has been duplicated');

  $france = Country::getInstance(250);
  $france->setAttribute('taxes', '0.2');

  $mail = new Mail();
  $mail->setFrom(P('mail.from.email'), P('mail.from.name'));
  $mail->setReplyTo('jdrzewinski@kernix.com');
  $mail->addRecipient('jdrzewinski@kernix.com', 'Jérôme Drzewinski');
  $mail->setSubject('Changement du taux de TVA : réussi');
  $mail->setBody('Le changement du taux de TVA s\'est correctement effectué');
  $mail->send();

} catch (Exception $e) { $err->add($e); }
