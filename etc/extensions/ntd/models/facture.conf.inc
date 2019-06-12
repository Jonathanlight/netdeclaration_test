<?php

$parameter['id'] = 14311;
$parameter['name'] = 'facture';
$parameter['label'] = 'facture';
$parameter['table'] = 'ntd_facture';
$parameter['casts'] = array(
  'data_adherent' => 'array',
  'data_address' => 'array',
  'data_purchases' => 'array',
  'data_prices' => 'array',
  'data_reglement' => 'array'
);
$parameter['belongs_to'] = array('adherent');
$parameter['has_many'] = array('souscription' => array('through' => 'ntd_facture_souscription'),
                               'payment' => array('through' => 'ntd_payment_facture',
                                                  'cols' => array('ntd_payment_facture.amount' => 'payment_facture_amount')));
