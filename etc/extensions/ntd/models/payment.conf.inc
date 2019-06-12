<?php

$parameter['id'] = 14317;
$parameter['name'] = 'payment';
$parameter['label'] = 'payment';
$parameter['table'] = 'ntd_payment';
$parameter['has_many'] = array('facture' => array('through' => 'ntd_payment_facture',
                                                  'cols' => array('ntd_payment_facture.amount' => 'payment_facture_amount')));
