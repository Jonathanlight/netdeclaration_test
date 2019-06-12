<?php

$operations = array(
  'soustraction-ac' => array('func' => 'data-soustraction',
                             'opt' => array('results' => array('AC'),
                                            'value' => 'AA',
                                            'operands' => array('AB'))),
  'integrity-ab' => array('func' => 'data-integrity-ab-ts2501',
                          'opt' => array('items' => array('AA', 'AB'))),
  'paiement' => array('func' => 'data-ts2501-paiement',
                      'opt' => array('operands' => array('AC'),
                                     'args' => array('p_identif_HA'))
  )
);

$form["ts2501"] = array(
  'AA' => array('type' => 'number',
                'operations' => array($operations['soustraction-ac'],
                                      $operations['integrity-ab']),
  ),
  'AB' => array('type' => 'number',
                'operations' => array($operations['soustraction-ac'],
                                      $operations['integrity-ab'],
                                      array('func' => 'data-must_be_inferior_or_egal', 'opt' => array('field' => 'AA')))
  ),
  'AC' => array('type' => 'number',
                'operations' => array($operations['paiement']),
  ),
);