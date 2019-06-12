<?php

$operations = array(
  'data-addition-ad' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('AD'),
                   'operands' => array('AA', 'AB', 'AC')),
  ),
  'data-addition-bd' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('BD'),
                   'operands' => array('BA', 'BB', 'BC')),
  ),
  'data-addition-ge' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('GE'),
                   'operands' => array('GA', 'GB', 'GC', 'GD')),
  ),
  'data-soustraction-cada' => array(
    'func' => 'data-soustraction-cada',
    'opt' => array('items' => array('CA', 'DA', 'AD', 'BD', 'EA')),
  ),
  'data-verification-ea' => array(
    'func' => 'data-verification-ea',
    'opt' => array('items' => array('AD', 'BD', 'DA', 'EA', 'EB'))
  )
);


$form["is2572_2011"] = array(
  'AA' => array('type' => 'number',
                'operations' => array(array('func' => 'data-compare',
                                            'opt' => array('results' => array('AA'),
                                                           'operands' => array('BA'))),
                                      $operations['data-addition-ad'])),

  'AB' => array('type' => 'number',
                'operations' => array(array('func' => 'data-compare',
                                            'opt' => array('results' => array('AB'),
                                                           'operands' => array('BB'))),
                                      $operations['data-addition-ad'])),

  'AC' => array('type' => 'number',
                'operations' => array(array('func' => 'data-compare',
                                            'opt' => array('results' => array('AC'),
                                                           'operands' => array('BC'))),
                                      $operations['data-addition-ad']
                )),

  'AD' => array('type' => 'number',
                'operations' => array($operations['data-soustraction-cada'],
                                      $operations['data-verification-ea'])),

  'BA' => array('type' => 'number',
                'operations' =>
                array(array('func' => 'data-compare',
                            'opt' => array('results' => array('BA'),
                                           'operands' => array('AA'))),
                      $operations['data-addition-bd']
                )),

  'BB' => array('type' => 'number',
                'operations' =>
                array(

                  array('func' => 'data-compare',
                        'opt' => array('results' => array('BB'),
                                       'operands' => array('AB'))),
                  $operations['data-addition-bd']
                )),

  'BC' => array('type' => 'number',
                'operations' =>
                array(

                  array('func' => 'data-compare',
                        'opt' => array('results' => array('BC'),
                                       'operands' => array('AC'))),
                  $operations['data-addition-bd']
                )),

  'BD' => array('type' => 'number',
                'operations' => array($operations['data-soustraction-cada'],
                                      $operations['data-verification-ea'])),

  'CA' => array('type' => 'number',
                'operations' =>
                array(
                  array(
                    'func' => 'data-is2572-paiement',
                    'opt' => array(
                      'operands' => array('CA', 'DA'),
                      'args' => array('p_identif_HA')
                    )
                  )
                )),

  'DA' => array('type' => 'number',
                'operations' =>
                array(

                  $operations['data-verification-ea'],
                  array(
                    'func' => 'data-is2572-paiement',
                    'opt' => array(
                      'operands' => array('CA', 'DA'),
                      'args' => array('p_identif_HA')
                    )
                  )
                )),

  'EA' => array('type' => 'number',
                'operations' => array($operations['data-verification-ea'])),

  'EB' => array('type' => 'number'),

  'FA' => array('type' => 'checkbox',
                'value' => '1'),

  'GA' => array('type' => 'number',
                'operations' => array($operations['data-addition-ge'])),

  'GB' => array('type' => 'number',
                'operations' => array($operations['data-addition-ge'])),

  'GC' => array('type' => 'number',
                'operations' => array($operations['data-addition-ge'])),

  'GD' => array('type' => 'number',
                'operations' => array($operations['data-addition-ge'])),

  'GE' => array('type' => 'number'),

  'HA' => array('type' => 'number'),

  'HB' => array('type' => 'number'),

  'IA' => array('type' => 'number'),

  'JA' => array('type' => 'number'),

  'KA' => array('type' => 'number'),

  'KB' => array('type' => 'number'),

  'KC' => array('type' => 'number'),

  'LA' => array('type' => 'number'),

  'LB' => array('type' => 'number'),

  'LC' => array('type' => 'number'),

  'LD' => array('type' => 'number'),

  'MA' => array('type' => 'number'),

  'MB' => array('type' => 'number'),

  'MC' => array('type' => 'number'),

  'MD' => array('type' => 'number'),

  'NA' => array('type' => 'number'),

  'NB' => array('type' => 'number'),

  'NC' => array('type' => 'number'),

  'ND' => array('type' => 'number'),

  'NE' => array('type' => 'number'),

  'NF' => array('type' => 'number'),

  'NG' => array('type' => 'number'),

  'NH' => array('type' => 'number'),

  'NI' => array('type' => 'number'),

  'NJ' => array('type' => 'number'),

  'NK' => array('type' => 'number'),

  'NL' => array('type' => 'number'),

  'NM' => array('type' => 'number'),

  'NN' => array('type' => 'number'),

  'NO' => array('type' => 'number'),

  'OA' => array('type' => 'number'),

  'OB' => array('type' => 'number'),

  'OC' => array('type' => 'number'),
);

  
