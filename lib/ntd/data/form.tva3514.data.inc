<?php

$operations = array(
  'data-check-need-and-or-input-dg' => array('func' => 'data-check-need-and-or-input',
                                             'opt' => array('results' => array('FA', 'FB', 'FC', 'ED', 'EF', 'EH', 'EK', 'EM', 'EP', 'ER',),
                                                            'operands' => array('DG',),),
  ),
  'data-addition-es' => array('func' => 'data-addition',
                              'opt' => array('results' => array('ES',),
                                             'operands' => array('ED', 'EF', 'EH', 'EK', 'EM', 'EP', 'ER', 'EU'),),
  ),
  'data-addition-gj' => array('func' => 'data-addition',
                              'opt' => array('results' => array('GJ',),
                                             'operands' => array('BA', 'BB', 'BC', 'BD', 'BE', 'BG', 'BH', 'BJ', 'BP', 'BQ', 'BR', 'BT'),),
  ),
  'data-addition-aa' => array('func' => 'data-addition',
                              'opt' => array('results' => array('AA',),
                                             'operands' => array('AB', 'AC',),),
  ),
  'data-addition-fd' => array('func' => 'data-addition',
                              'opt' => array('results' => array('FD',),
                                             'operands' => array('FA', 'FB', 'FC',),),
  ),
  'data-disable-on-da' => array('func' => 'data-disable-on-da',
                                'opt' => array('items' => array('DA', 'DB', 'DC', 'DD', 'DE', 'DF', 'DG',),),
  ),
  'data-disable-on-db' => array('func' => 'data-disable-on-db',
                                'opt' => array('items' => array('DB', 'DC', 'DA', 'DD', 'DE', 'DF', 'DG',),),),
  'data-integrity-dc' => array('func' => 'data-integrity-dc',
                               'opt' => array('items' => array('DC', 'DB',),),),
  'data-integrity-db' => array('func' => 'data-integrity-db',
                               'opt' => array('items' => array('DB', 'DC',),),),
  'data-disable-on-dc' => array('func' => 'data-disable-on-dc',
                                'opt' => array('items' => array('DC', 'DB', 'DA', 'DD', 'DE', 'DF', 'DG',),),),
  'data-disable-if-dd-checked' => array('func' => 'data-disable-if-dd-checked',
                                        'opt' => array('items' => array('DD', 'DF', 'DA', 'DC',),),),
  'data-tva3514-paiement' => array('func' => 'data-tva3514-paiement',
                                   'opt' => array(
                                     'operands' => array('GK', 'GL', 'AA'),
                                     'args' => array('t_identif_HA'))),
  'data-integrity-gk-gl' => array('func' => 'data-integrity-gk-gl',
                                  'opt' => array('items' => array('EA', 'EB', 'GK', 'GL',),),),
  'data-integrity-3514' => array('func' => 'data-integrity-3514'),
);


$form["tva3514"] = array(
  'integrity-3514' => array('operations' => array($operations['data-integrity-3514'])),
  'AA' => array('type' => 'number',
                'operations' => array(array('func' => 'data-disable-on-aa',
                                            'opt' => array('items' => array('AA'))),
                                      $operations['data-tva3514-paiement']),
  ),
  'AB' => array('type' => 'number',
                'operations' => array($operations['data-addition-aa'],),
  ),
  'AC' => array('type' => 'number',
                'operations' => array($operations['data-addition-aa'],),
  ),
  'DA' => array('type' => 'number',
                'operations' => array($operations['data-disable-on-da']),
  ),
  'DB' => array('type' => 'number',
                'operations' => array($operations['data-disable-on-db'],
                                      $operations['data-integrity-dc'],
                                      $operations['data-integrity-db']
                ),
  ),
  'DC' => array('type' => 'number',
                'operations' => array($operations['data-integrity-dc'],
                                      $operations['data-integrity-db'],
                                      $operations['data-disable-on-dc']
                ),
  ),
  'DD' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array($operations['data-disable-if-dd-checked'],),
  ),
  'DF' => array('type' => 'number',
                'operations' => array($operations['data-disable-if-dd-checked'],),
  ),
  'DE' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(0 => array('func' => 'data-disable-if-de-checked', 'opt' => array('items' => array(0 => 'DE', 1 => 'DA', 2 => 'DC',),),),),
  ),
  'DG' => array('type' => 'number',
                'operations' =>
                array(
                  0 => array('func' => 'data-disable-on-dg', 'opt' => array('items' => array('DG', 'DA', 'DB', 'DC', 'DD', 'DE', 'DF', 'BA', 'BB', 'BC', 'BD', 'BE', 'BR', 'BT', 'BG', 'BH', 'BJ', 'BP', 'BQ'),),),
                  1 => $operations['data-check-need-and-or-input-dg'],
                  2 => array('func' => 'data-check-need-and-or-input', 'opt' => array('results' => array(0 => 'EA',), 'operands' => array(0 => 'DG',),),),
                  3 => array('func' => 'data-check-need-and-or-input', 'opt' => array('results' => array(0 => 'EB',), 'operands' => array(0 => 'DG',),),),
                  4 => array('func' => 'data-check-dw-dg', 'opt' => array('results' => array(0 => 'DG',), 'operands' => array(0 => 'DW',),),),
                ),
  ),
  'DW' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(0 => array('func' => 'data-check-dw-dg', 'opt' => array('results' => array(0 => 'DG',), 'operands' => array(0 => 'DW',),),),),
  ),
  'EA' => array('type' => 'date-ssaammjj',
                'operations' => array(array('func' => 'data-check-need-and-or-input',
                                            'opt' => array('results' => array('EA',),
                                                           'operands' => array('DW', 'DG')))),
  ),
  'EB' => array('type' => 'date-ssaammjj',
                'length' => 10,
                'operations' => array(array('func' => 'data-check-need-and-or-input',
                                            'opt' => array('results' => array('EB',),
                                                           'operands' => array('DW', 'DG')))),
  ),
  'EC' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-calcul-1960',
                                                 'opt' => array('results' => array(0 => 'ED',), 'operands' => array(0 => 'EC',),),),
                ),
  ),
  'ED' => array('type' => 'number',
                'operations' => array($operations['data-addition-es'],
                                      $operations['data-check-need-and-or-input-dg'],
                                      array('func' => 'data-check-positiv',
                                            'opt' => array('items' => array('ED', 'EC')))
                ),
  ),
  'EE' => array('type' => 'number',
                'operations' => array(1 => array('func' => 'data-calcul-550',
                                                 'opt' => array('results' => array(0 => 'EF',), 'operands' => array(0 => 'EE',),),),),
  ),
  'EF' => array('type' => 'number',
                'operations' => array(1 => $operations['data-addition-es'],
                                      2 => $operations['data-check-need-and-or-input-dg'],
                                      3 => array('func' => 'data-check-positiv', 'opt' => array('items' => array(0 => 'EF', 1 => 'EE',),),),
                ),
  ),
  'ET' => array('type' => 'number',
                'operations' => array(array('function' => 'data-calcul-percent',
                                            'args' => array('result' => 'tva3514_EU', 'percent' => 7))),
  ),
  'EU' => array('type' => 'number',
                'operations' => array(array('func' => 'data-check-positiv',
                                            'opt' => array('items' => array('EU', 'ET'))),
                                      $operations['data-addition-es'])
  ),
  'EG' => array('type' => 'number',
                'operations' => array(1 => array('func' => 'data-calcul-850',
                                                 'opt' => array('results' => array(0 => 'EH',), 'operands' => array(0 => 'EG',),),
                ),
                ),
  ),
  'EH' => array('type' => 'number',
                'operations' => array(1 => $operations['data-addition-es'],
                                      2 => $operations['data-check-need-and-or-input-dg'],
                                      3 => array('func' => 'data-check-positiv',
                                                 'opt' => array('items' => array(0 => 'EH', 1 => 'EG',),),
                                      ),
                ),
  ),
  'EJ' => array('type' => 'number',
                'operations' => array(1 => array('func' => 'data-calcul-210',
                                                 'opt' => array('results' => array(0 => 'EK',), 'operands' => array(0 => 'EJ',),),
                ),
                ),
  ),
  'EK' => array('type' => 'number',
                'operations' => array(1 => $operations['data-addition-es'],
                                      2 => $operations['data-check-need-and-or-input-dg'],
                                      3 => array('func' => 'data-check-positiv',
                                                 'opt' => array('items' => array(0 => 'EK', 1 => 'EJ',),),
                                      ),
                ),
  ),
  'EL' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-check-positiv', 'opt' => array('items' => array(0 => 'EM', 1 => 'EL',),),),),
  ),
  'EM' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-check-positiv', 'opt' => array('items' => array(0 => 'EM', 1 => 'EL',),),),
                                      1 => $operations['data-addition-es'],
                                      2 => $operations['data-check-need-and-or-input-dg'],
                ),
  ),
  'EN' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-check-positiv', 'opt' => array('items' => array(0 => 'EP', 1 => 'EN',),),),),
  ),
  'EP' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-check-positiv',
                                                 'opt' => array('items' => array(0 => 'EP', 1 => 'EN',),),
                ),
                                      1 => $operations['data-addition-es'],
                                      2 => $operations['data-check-need-and-or-input-dg'],
                ),
  ),
  'EQ' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-check-positiv', 'opt' => array('items' => array(0 => 'ER', 1 => 'EQ',),),),),
  ),
  'ER' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-check-positiv',
                                                 'opt' => array('items' => array(0 => 'ER', 1 => 'EQ',),),),
                                      1 => $operations['data-addition-es'],
                                      2 => $operations['data-check-need-and-or-input-dg'],
                ),
  ),
  'ES' => array('type' => 'number',
                'operations' => array(1 => array('func' => 'data-calcul-ga-gb', 'opt' => array('items' => array(0 => 'GA', 1 => 'GB', 2 => 'ES', 3 => 'FD', 4 => 'GC', 5 => 'GD', 6 => 'GF', 7 => 'GH', 8 => 'GK',),),),
                ),
  ),
  'FA' => array('type' => 'number',
                'operations' =>
                array(
                  0 => $operations['data-addition-fd'],
                  1 => $operations['data-check-need-and-or-input-dg'],
                  2 => array('func' => 'data-integrity-gc-3514', 'opt' => array('items' => array(0 => 'GC', 1 => 'FA', 2 => 'GB',),),),
                ),
  ),
  'FB' => array('type' => 'number',
                'operations' => array(0 => $operations['data-addition-fd'],
                                      1 => $operations['data-check-need-and-or-input-dg'],
                ),
  ),
  'FC' => array('type' => 'number',
                'operations' => array(0 => $operations['data-addition-fd'],
                                      1 => $operations['data-check-need-and-or-input-dg'],
                ),
  ),
  'FD' => array('type' => 'number',
                'operations' => array(1 => array('func' => 'data-calcul-ga-gb', 'opt' => array('items' => array(0 => 'GA', 1 => 'GB', 2 => 'ES', 3 => 'FD', 4 => 'GC', 5 => 'GD', 6 => 'GF', 7 => 'GH', 8 => 'GK',),),),),
  ),
  'GA' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-calcul-gg-3514', 'opt' => array('items' => array(0 => 'GG', 1 => 'GA', 2 => 'GE',),),),),
  ),
  'GB' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-integrity-gc-3514', 'opt' => array('items' => array(0 => 'GC', 1 => 'FA', 2 => 'GB',),),),
                                      1 => array('func' => 'data-soustraction', 'opt' => array('results' => array(0 => 'GD',), 'value' => 'GB', 'operands' => array(0 => 'GC',),),),
                ),
  ),
  'GC' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-integrity-gc-3514', 'opt' => array('items' => array(0 => 'GC', 1 => 'FA', 2 => 'GB',),),),
                                      1 => array('func' => 'data-soustraction', 'opt' => array('results' => array(0 => 'GD',), 'value' => 'GB', 'operands' => array(0 => 'GC',),),),
                ),
  ),
  'GD' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-calcul-gf', 'opt' => array('results' => array(0 => 'GF',), 'operands' => array(0 => 'GD',),),),),
  ),
  'GE' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-calcul-gg-3514', 'opt' => array('items' => array(0 => 'GG', 1 => 'GA', 2 => 'GE',),),),),
  ),
  'GF' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-addition', 'opt' => array('results' => array(0 => 'GK',), 'operands' => array(0 => 'GF', 1 => 'GH',),),),),
  ),
  'GG' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-addition', 'opt' => array('results' => array(0 => 'GL',), 'operands' => array(0 => 'GG', 1 => 'GJ',),),),),
  ),
  'BA' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BB' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BC' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BD' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BE' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BG' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BH' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BJ' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BP' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BQ' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BR' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),
  'BT' => array('type' => 'number',
                'operations' => array($operations['data-addition-gj']),
  ),

  'BK' => array('type' => 'number',
                'readonly' => true,
                'no_recording' => true,
                'operations' => array(),
  ),
  'BL' => array('type' => 'number',
                'readonly' => true,
                'no_recording' => true,
                'operations' => array(),
  ),
  'BM' => array('type' => 'number',
                'readonly' => true,
                'no_recording' => true,
                'operations' => array(),
  ),
  'BN' => array('type' => 'number',
                'readonly' => true,
                'no_recording' => true,
                'operations' => array(),
  ),
  'BO' => array('type' => 'number',
                'readonly' => true,
                'no_recording' => true,
                'operations' => array(),
  ),
  'GH' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-check-negativ', 'opt' => array('items' => array(0 => 'GH', 1 => 'GJ',),),),
                                      1 => array('func' => 'data-addition', 'opt' => array('results' => array(0 => 'GK',), 'operands' => array(0 => 'GF', 1 => 'GH',),),),
                ),
  ),
  'GJ' => array('type' => 'number',
                'operations' => array(array('func' => 'data-addition', 'opt' => array('results' => array('GL',), 'operands' => array('GG', 'GJ',),),),
                                      array('func' => 'data-check-negativ', 'opt' => array('items' => array('GH', 'GJ',),),),
                                      array('func' => 'data-check-need-and-or',
                                            'opt' => array('operands' => array('GJ',),
                                                           'results' => array('BA', 'BB', 'BC', 'BD', 'BE', 'BG', 'BH', 'BJ', 'BP', 'BQ', 'BR', 'BT'),),),
                ),
  ),
  'GK' => array('type' => 'number',
                'operations' => array($operations['data-integrity-gk-gl'],
                                      array('func' => 'data-calcul-gk', 'opt' => array('results' => array('EA', 'EB',), 'operands' => array('GL', 'GK',),),),
                                      $operations['data-tva3514-paiement']

                ),
  ),
  'GL' => array('type' => 'number',
                'operations' => array($operations['data-integrity-gk-gl'],
                                      $operations['data-tva3514-paiement']
                ),
  ),
  'CC' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(array('func' => 'any_operands_all_results_required', 'opt' => array('results' => array('CB'), 'operands' => array('CC')))),
  ),
  'CA' => array('type' => 'checkbox',
  ),
  'CB' => array('type' => 'comments',
                'length' => 2560,
                'operations' => array(array('func' => 'data-check-need-and-or', 'opt' => array('results' => array('CB',), 'operands' => array('CC',),),),),
  ),
  'CB1' => array('type' => 'comments-part',
                 'length' => 512,
  ),
  'CB2' => array('type' => 'comments-part',
                 'length' => 512,
  ),
  'CB3' => array('type' => 'comments-part',
                 'length' => 512,
  ),
  'CB4' => array('type' => 'comments-part',
                 'length' => 512,
  ),
  'CB5' => array('type' => 'comments-part',
                 'length' => 512,
  ),
);
 