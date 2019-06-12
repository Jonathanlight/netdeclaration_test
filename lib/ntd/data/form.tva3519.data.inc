<?php

$operations = array(
  'data-addition-fc' => array('func' => 'data-addition',
                              'opt' => array('results' => array('FC'),
                                             'operands' => array('EY', 'EZ', 'FA', 'FB'))),
  'addition-eq' => array('func' => 'data-addition',
                         'opt' => array('results' => array('EQ'), 'operands' => array('EB', 'EG', 'EL'))),
  'addition-ep' => array('func' => 'data-addition',
                         'opt' => array('results' => array('EP'), 'operands' => array('EA', 'EF', 'EK'))),
  'addition-ee' => array('func' => 'data-addition',
                         'opt' => array('results' => array('EE'), 'operands' => array('EA', 'EB', 'EC', 'ED'))),
  'addition-er' => array('func' => 'data-addition',
                         'opt' => array('results' => array('ER'), 'operands' => array('EC', 'EH', 'EM'))),
  'addition-es' => array('func' => 'data-addition',
                         'opt' => array('results' => array('ES'), 'operands' => array('ED', 'EI', 'EN'))),
  'addition-et' => array('func' => 'data-addition',
                         'opt' => array('results' => array('ET'), 'operands' => array('EE', 'EJ', 'EO'))),
  'addition-ej' => array('func' => 'data-addition',
                         'opt' => array('results' => array('EJ'), 'operands' => array('EF', 'EG', 'EH', 'EI'))),
  'addition-eo' => array('func' => 'data-addition',
                         'opt' => array('results' => array('EO'), 'operands' => array('EK', 'EL', 'EM', 'EN'))),
  'addition-fe' => array('func' => 'data-addition',
                         'opt' => array('results' => array('FE'), 'operands' => array('FC', 'FD'))),
  'integrity-fg' => array('func' => 'data-integrity-fg',
                          'opt' => array('items' => array('FG', 'FC', 'FE', 'FF', 'DH'))),
  'soustraction-fi' => array('func' => 'data-soustraction',
                             'opt' => array('results' => array('FI'), 'value' => 'FE', 'operands' => array('FG'))),
  'soustraction-fh' => array('func' => 'data-soustraction',
                             'opt' => array('results' => array('FH'), 'value' => 'FF', 'operands' => array('FG'))),
  'only-one-checked-di-dj-dk' => array('function' => 'data-check-set-unchecked',
                                       'args' => array('fields' => array('tva3519_DI', 'tva3519_DJ', 'tva3519_DK'))),
  'data-integrity-3519' => array('func' => 'data-integrity-3519'),
);

$operations['only-one-checked-di-dj-dk'];


$form["tva3519"] = array(
  'integrity-3519' => array('operations' => array($operations['data-integrity-3519'])),
  'DC1' => array('type' => 'alphabetic',
                 'length' => 35,
                 'operations' => array(array('func' => 'data-paiement_3519'))
  ),
  'DC2' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'DC3' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'DC4' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'DC5' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'DC6' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'DC7' => array('type' => 'alphabetic',
                 'length' => 5,
  ),
  'DC8' => array('type' => 'select',
                 'length' => 3,
                 'options' => Country::collect()->asHash('iso3_code', 'name'),
  ),
  'DC9' => array('type' => 'alphabetic',
                 'length' => 512,
  ),
  'DC10' => array('type' => 'alphabetic',
                  'length' => 512,
  ),
  'DD' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(array('func' => 'data-check-set-unchecked',
                                            'opt' => array('results' => array('DE', 'DF'), 'operands' => array('DD')))),
  ),
  'DE' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(array('func' => 'data-check-set-unchecked',
                                            'opt' => array('results' => array('DD', 'DF'), 'operands' => array('DE')))),
  ),
  'DF' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(array('func' => 'data-check-set-unchecked',
                                            'opt' => array('results' => array('DE', 'DD'), 'operands' => array('DF')))),
  ),
  'DG1' => array('type' => 'alphabetic',
                 'required' => true,
                 'length' => 35,
  ),
  'DG2' => array('type' => 'alphabetic',
                 'required' => true,
                 'length' => 35,
  ),
  'DG3' => array('type' => 'alphabetic',
                 'required' => true,
                 'length' => 35,
  ),
  'DG4' => array('type' => 'alphabetic',
                 'required' => true,
                 'length' => 35,
  ),
  'DH' => array('type' => 'number',
                'required' => true,
                'operations' => array(array('func' => 'data-check-positiv-one-item',
                                            'opt' => array('items' => array('DH')))),
  ),
  'FK' => array('type' => 'checkbox',
                'value' => '1',
  ),
  'FL' => array('type' => 'checkbox',
                'value' => '1',
  ),
  'AA1' => array('type' => 'number',
                 'length' => 15,
  ),
  'AA2' => array('type' => 'number',
                 'length' => 27,
  ),
  'AA3' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA4' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'DI' => array('type' => 'checkbox',
                'operations' => array(array('func' => 'data-check-full',
                                            'opt' => array('results' => array('DI'), 'operands' => array('AA1', 'AA2', 'AA3', 'AA4'))),
                                      $operations['only-one-checked-di-dj-dk'],
                                      array('func' => 'data-check-full',
                                            'opt' => array('results' => array('DI'), 'operands' => array('DL'))))
  ),
  'DL' => array('type' => 'date-ssaammjj',
  ),
  'DJ' => array('type' => 'checkbox',
                'operations' => array(array('func' => 'data-check-full',
                                            'opt' => array('results' => array('DJ'), 'operands' => array('DM'))),
                                      $operations['only-one-checked-di-dj-dk'])
  ),
  'DM' => array('type' => 'date-ssaammjj'
  ),
  'DK' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array($operations['only-one-checked-di-dj-dk'],
                                      array('func' => 'data-empty-and-desactive',
                                            'opt' => array('results' => array('DK'), 'operands' => array('AA1', 'AA2', 'AA3', 'AA4')))),
  ),
  'DN' => array('type' => 'number',
                'operations' => array(array('func' => 'data-tva3519-export',
                                            'opt' => array('results' => array('EP'), 'operands' => array('EA', 'EF', 'EK')))),
  ),
  'EA' => array('type' => 'number',
                'operations' => array($operations['addition-ep'],
                                      $operations['addition-ee']),
  ),
  'EB' => array('type' => 'number',
                'operations' => array($operations['addition-eq'],
                                      $operations['addition-ee']),
  ),
  'EC' => array('type' => 'number',
                'operations' => array($operations['addition-er'],
                                      $operations['addition-ee']
                ),
  ),
  'ED' => array('type' => 'number',
                'operations' => array($operations['addition-es'],
                                      $operations['addition-ee']
                ),
  ),
  'EE' => array('type' => 'number',
                'operations' => array($operations['addition-et']),
  ),
  'EF' => array('type' => 'number',
                'operations' => array($operations['addition-ep'],
                                      $operations['addition-ej']),
  ),
  'EG' => array('type' => 'number',
                'operations' => array($operations['addition-eq'],
                                      $operations['addition-ej']),
  ),
  'EH' => array('type' => 'number',
                'operations' => array($operations['addition-er'],
                                      $operations['addition-ej']),
  ),
  'EI' => array('type' => 'number',
                'operations' => array($operations['addition-es'],
                                      $operations['addition-ej']),
  ),
  'EJ' => array('type' => 'number',
                'operations' => array($operations['addition-et']),
  ),
  'EK' => array('type' => 'number',
                'operations' => array($operations['addition-eo'],
                                      $operations['addition-ep']),
  ),
  'EL' => array('type' => 'number',
                'operations' => array($operations['addition-eo'],
                                      $operations['addition-eq']),
  ),
  'EM' => array('type' => 'number',
                'operations' => array($operations['addition-eo'],
                                      $operations['addition-er']),
  ),
  'EN' => array('type' => 'number',
                'operations' => array($operations['addition-eo'],
                                      $operations['addition-es']),
  ),
  'EO' => array('type' => 'number',
                'operations' => array($operations['addition-et']),
  ),
  'EP' => array('type' => 'number',
                'operations' => array(array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('EP'), 'results' => array('EU'))),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_EY', 'percent' => 'tva3519_EU')))
  ),
  'EQ' => array('type' => 'number',
                'operations' => array(array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('EQ'), 'results' => array('EV'))),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_EZ', 'percent' => 'tva3519_EV')))
  ),
  'ER' => array('type' => 'number',
                'operations' => array(array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('ER'), 'results' => array('EW'))),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_FA', 'percent' => 'tva3519_EW')))
  ),
  'ES' => array('type' => 'number',
                'operations' => array(array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('ES'), 'results' => array('EX'))),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_FB', 'percent' => 'tva3519_EX')))
  ),
  'ET' => array('type' => 'number',
  ),
  'EU' => array('type' => 'pourcentage',
                'operations' => array(array('func' => 'data-check-percent',
                                            'opt' => array('results' => array('EU'), 'operands' => array('EU'))),
                                      array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('EP'), 'results' => array('EU'))),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_EY', 'percent' => 'tva3519_EU', 'value' => 'tva3519_EP'))),
  ),
  'EV' => array('type' => 'pourcentage',
                'operations' => array(array('func' => 'data-check-percent',
                                            'opt' => array('results' => array('EV'), 'operands' => array('EV'))),
                                      array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('EQ'), 'results' => array('EV'))),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_EZ', 'percent' => 'tva3519_EV', 'value' => 'tva3519_EQ'))),
  ),
  'EW' => array('type' => 'pourcentage',
                'operations' => array(array('func' => 'data-check-percent',
                                            'opt' => array('results' => array('EW'),
                                                           'operands' => array('EW'))),
                                      array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('ER'),
                                                           'results' => array('EW'))
                                      ),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_FA',
                                                            'percent' => 'tva3519_EW',
                                                            'value' => 'tva3519_ER')),
                ),
  ),
  'EX' => array('type' => 'pourcentage',
                'operations' => array(array('func' => 'data-check-percent',
                                            'opt' => array('results' => array('EX'),
                                                           'operands' => array('EX'))),

                                      array('func' => 'data-check-positiv-set-full',
                                            'opt' => array('operands' => array('ES'),
                                                           'results' => array('EX'))
                                      ),
                                      array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3519_FB',
                                                            'percent' => 'tva3519_EX',
                                                            'value' => 'tva3519_ES'))),
  ),
  'EY' => array('type' => 'number',
                'operations' => array($operations['data-addition-fc']),
  ),
  'EZ' => array('type' => 'number',
                'operations' => array($operations['data-addition-fc']),
  ),
  'FA' => array('type' => 'number',
                'operations' => array($operations['data-addition-fc']),
  ),
  'FB' => array('type' => 'number',
                'operations' => array($operations['data-addition-fc']),
  ),
  'FC' => array('type' => 'number',
                'operations' => array($operations['addition-fe']),
  ),
  'FD' => array('type' => 'number',
                'operations' => array($operations['addition-fe']),
  ),
  'FE' => array('type' => 'number',
                'operations' => array($operations['soustraction-fi'],
                                      $operations['integrity-fg']),
  ),
  'FF' => array('type' => 'number',
                'operations' => array($operations['soustraction-fh'],
                                      $operations['integrity-fg']),
  ),
  'FG' => array('type' => 'number',
                'operations' => array($operations['soustraction-fi'],
                                      $operations['integrity-fg'],
                                      $operations['soustraction-fh']),
  ),
  'FH' => array('type' => 'number',
  ),
  'FI' => array('type' => 'number',
  ),
  'FJ'  => array('type' => 'comments'),
  'FJ1' => array('type' => 'hidden'),
  'FJ2' => array('type' => 'hidden'),
  'FJ3' => array('type' => 'hidden'),
  'FJ4' => array('type' => 'hidden'),
  'FJ5' => array('type' => 'hidden'),
);