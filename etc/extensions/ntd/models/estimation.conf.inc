<?php

$parameter['id'] = 14330;
$parameter['name'] = 'estimation';
$parameter['label'] = 'estimation';
$parameter['table'] = 'ntd_estimation';
$parameter['has_many'] = array('tarif' => array('through' => 'ntd_estimation_tarif',
                                                'cols' => array(
                                                  'ntd_estimation_tarif.quantity' => 'estimation_quantity',
                                                  'ntd_estimation_tarif.amount_unitary' => 'estimation_amount_unitary',
                                                  'ntd_estimation_tarif.amount_total' => 'estimation_amount_total',
                                                )));