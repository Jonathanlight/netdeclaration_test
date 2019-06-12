<?php

$operations = array(
  'data-addition-ce' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('CE'),
                   'operands' => array('CA', 'CB', 'CC', 'CD', 'CF')),
  ),
  'data-addition-ch' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('CH'),
                   'operands' => array('CE', 'CG')),
  ),
  'paiement' => array('func' => 'data-is2571-paiement',
                      'opt' => array('operands' => array('CH'),
                                     'args' => array('p_identif_HA')))
);

$form["is2571_2013"] = array(
  'BA' => array('type' => 'number'),

  'CA' => array('type' => 'number',
                'operations' => array($operations['data-addition-ce'])),

  'DA' => array('type' => 'checkbox',
                'value' => '1'),

  'CB' => array('type' => 'number',
                'operations' => array($operations['data-addition-ce'])),

  'CC' => array('type' => 'number',
                'operations' => array($operations['data-addition-ce'])),

  'CD' => array('type' => 'number',
                'operations' => array($operations['data-addition-ce'])),
  'CF' => array('type' => 'number',
                'operations' => array($operations['data-addition-ce'])),

  'DB' => array('type' => 'checkbox',
                'value' => '1'),

  'CE' => array('type' => 'number',
                'operations' => array($operations['data-addition-ch'])),
  'CG' => array('type' => 'number',
                'operations' => array($operations['data-addition-ch'])
  ),
  'CH' => array('type' => 'number',
                'operations' => array($operations['paiement'])
  )
);
