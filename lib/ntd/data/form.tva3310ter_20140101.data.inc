<?php

$operations = array(
  'data-addition-dl' => array('func' => 'data-addition',
                              'opt' => array('results' => array('DL',), 'operands' => array('DA', 'DB', 'DC', 'DD', 'DE', 'DF', 'DG', 'DH', 'DJ', 'DK',),),
  ),
  'data-addition-nl' => array('func' => 'data-addition',
                              'opt' => array('results' => array('NL',), 'operands' => array('NA', 'NB', 'NC', 'ND', 'NE', 'NF', 'NG', 'NH', 'NJ', 'NK',),),),
  'data-addition-fa' => array('func' => 'data-addition',
                              'opt' => array('results' => array('FA',), 'operands' => array('DA', 'EA',),),
  ),
  'data-addition-fb' => array('func' => 'data-addition',
                              'opt' => array('results' => array('FB',), 'operands' => array('DB', 'EB',),),
  ),
  'data-addition-el' => array('func' => 'data-addition',
                              'opt' => array('results' => array('EL',), 'operands' => array('EA', 'EB', 'EC', 'ED', 'EE', 'EF', 'EG', 'EH', 'EJ', 'EK',),),
  ),
  'data-calcul-ja' => array('func' => 'data-calcul-ca3-ja',
                            'opt' => array('results' => array('tva3310ca3_20140101_JA'),
                                           'operands' => array('tva3310ca3_20140101_GH', 'tva3310ca3_20140101_HG', 'RM')),
  ),
  'data-calcul-ka' => array('func' => 'data-calcul-ca3-ka',
                            'opt' => array('results' => array('tva3310ca3_20140101_KA'),
                                           'operands' => array('tva3310ca3_20140101_GH', 'tva3310ca3_20140101_HG', 'QM'))
  ),
  'data-integrity-ter-20140101' => array('func' => 'data-integrity-3310ter-20140101'),
);

$operations['data-calcul-ja'];

$form["tva3310ter_20140101"] = array(
  'integrity-3310ter-20140101' => array('operations' => array($operations['data-integrity-3310ter-20140101'])),
  'AA' =>
  array(
    'type' => 'comments',
    'length' => 2560,
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-check-need-and-or',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'AA',
          ),
          'operands' =>
          array(
            0 => 'AC',
          ),
        ),
      ),
    ),
  ),
  'AA1' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'AA2' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'AA3' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'AA4' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'AA5' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'AC' =>
  array(
    'type' => 'checkbox',
    'value' => '1',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-check-need-and-or',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'AA',
          ),
          'operands' =>
          array(
            0 => 'AC',
          ),
        ),
      ),
    ),
  ),
  'AB' =>
  array(
    'type' => 'float',
    'value' => 0,
    'operations' =>
    array(
    ),
  ),
  'BA' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CA' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BB' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CB' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BC' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CC' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BD' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CD' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BE' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CE' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BF' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CF' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BG' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CG' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BH' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CH' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BJ' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CJ' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'BK' =>
  array(
    'type' => 'alphabetic',
    'length' => 512,
  ),
  'CK' =>
  array(
    'type' => 'float',
    'operations' =>
    array(
    ),
  ),
  'DA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      $operations['data-addition-fa'],
    ),
  ),
  'EA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      $operations['data-addition-fa'],
    ),
  ),
  'FA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RA',
          ),
          'value' => 'PA',
          'operands' =>
          array(
            0 => 'FA',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QA',
          ),
          'operands' =>
          array(
            0 => 'FA',
            1 => 'PA',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QA',
          ),
          'value' => 'FA',
          'operands' =>
          array(
            0 => 'PA',
          ),
        ),
      ),
    ),
  ),
  'DB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      $operations['data-addition-fb'],
    ),
  ),
  'EB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      $operations['data-addition-fb'],
    ),
  ),
  'FB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RB',
          ),
          'value' => 'PB',
          'operands' =>
          array(
            0 => 'FB',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QB',
          ),
          'operands' =>
          array(
            0 => 'FB',
            1 => 'PB',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QB',
          ),
          'value' => 'FB',
          'operands' =>
          array(
            0 => 'PB',
          ),
        ),
      ),
    ),
  ),
  'DC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FC',
          ),
          'operands' =>
          array(
            0 => 'DC',
            1 => 'EC',
          ),
        ),
      ),
    ),
  ),
  'EC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FC',
          ),
          'operands' =>
          array(
            0 => 'DC',
            1 => 'EC',
          ),
        ),
      ),
    ),
  ),
  'FC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RC',
          ),
          'value' => 'PC',
          'operands' =>
          array(
            0 => 'FC',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QC',
          ),
          'operands' =>
          array(
            0 => 'FC',
            1 => 'PC',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QC',
          ),
          'value' => 'FC',
          'operands' =>
          array(
            0 => 'PC',
          ),
        ),
      ),
    ),
  ),
  'DD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FD',
          ),
          'operands' =>
          array(
            0 => 'DD',
            1 => 'ED',
          ),
        ),
      ),
    ),
  ),
  'ED' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FD',
          ),
          'operands' =>
          array(
            0 => 'DD',
            1 => 'ED',
          ),
        ),
      ),
    ),
  ),
  'FD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RD',
          ),
          'value' => 'PD',
          'operands' =>
          array(
            0 => 'FD',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QD',
          ),
          'operands' =>
          array(
            0 => 'FD',
            1 => 'PD',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QD',
          ),
          'value' => 'FD',
          'operands' =>
          array(
            0 => 'PD',
          ),
        ),
      ),
    ),
  ),
  'DE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FE',
          ),
          'operands' =>
          array(
            0 => 'DE',
            1 => 'EE',
          ),
        ),
      ),
    ),
  ),
  'EE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FE',
          ),
          'operands' =>
          array(
            0 => 'DE',
            1 => 'EE',
          ),
        ),
      ),
    ),
  ),
  'FE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QE',
          ),
          'operands' =>
          array(
            0 => 'FE',
            1 => 'PE',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QE',
          ),
          'value' => 'FE',
          'operands' =>
          array(
            0 => 'PE',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RE',
          ),
          'value' => 'PE',
          'operands' =>
          array(
            0 => 'FE',
          ),
        ),
      ),
    ),
  ),
  'DF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FF',
          ),
          'operands' =>
          array(
            0 => 'DF',
            1 => 'EF',
          ),
        ),
      ),
    ),
  ),
  'EF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FF',
          ),
          'operands' =>
          array(
            0 => 'DF',
            1 => 'EF',
          ),
        ),
      ),
    ),
  ),
  'FF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RF',
          ),
          'operands' =>
          array(
            0 => 'FF',
            1 => 'PF',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RF',
          ),
          'value' => 'PF',
          'operands' =>
          array(
            0 => 'FF',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QF',
          ),
          'value' => 'FF',
          'operands' =>
          array(
            0 => 'PF',
          ),
        ),
      ),
    ),
  ),
  'DG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FG',
          ),
          'operands' =>
          array(
            0 => 'DG',
            1 => 'EG',
          ),
        ),
      ),
    ),
  ),
  'EG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FG',
          ),
          'operands' =>
          array(
            0 => 'DG',
            1 => 'EG',
          ),
        ),
      ),
    ),
  ),
  'FG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RG',
          ),
          'value' => 'PG',
          'operands' =>
          array(
            0 => 'FG',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QG',
          ),
          'operands' =>
          array(
            0 => 'FG',
            1 => 'PG',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QG',
          ),
          'value' => 'FG',
          'operands' =>
          array(
            0 => 'PG',
          ),
        ),
      ),
    ),
  ),
  'DH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FH',
          ),
          'operands' =>
          array(
            0 => 'DH',
            1 => 'EH',
          ),
        ),
      ),
    ),
  ),
  'EH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FH',
          ),
          'operands' =>
          array(
            0 => 'DH',
            1 => 'EH',
          ),
        ),
      ),
    ),
  ),
  'FH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RH',
          ),
          'value' => 'PH',
          'operands' =>
          array(
            0 => 'FH',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QH',
          ),
          'operands' =>
          array(
            0 => 'FH',
            1 => 'PH',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QH',
          ),
          'value' => 'FH',
          'operands' =>
          array(
            0 => 'PH',
          ),
        ),
      ),
    ),
  ),
  'DJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FJ',
          ),
          'operands' =>
          array(
            0 => 'DJ',
            1 => 'EJ',
          ),
        ),
      ),
    ),
  ),
  'EJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FJ',
          ),
          'operands' =>
          array(
            0 => 'DJ',
            1 => 'EJ',
          ),
        ),
      ),
    ),
  ),
  'FJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QJ',
          ),
          'value' => 'FJ',
          'operands' =>
          array(
            0 => 'PJ',
          ),
        ),
      ),
    ),
  ),
  'DK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-dl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FK',
          ),
          'operands' =>
          array(
            0 => 'DK',
            1 => 'EK',
          ),
        ),
      ),
    ),
  ),
  'EK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-el'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FK',
          ),
          'operands' =>
          array(
            0 => 'DK',
            1 => 'EK',
          ),
        ),
      ),
    ),
  ),
  'FK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RK',
          ),
          'value' => 'PK',
          'operands' =>
          array(
            0 => 'FK',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QK',
          ),
          'operands' =>
          array(
            0 => 'FK',
            1 => 'PK',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QK',
          ),
          'value' => 'FK',
          'operands' =>
          array(
            0 => 'PK',
          ),
        ),
      ),
    ),
  ),
  'DL' =>
  array(
    'type' => 'number',
    'show-form' => 'tva3310CA3_20140101',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FL',
          ),
          'operands' =>
          array(
            0 => 'DL',
            1 => 'EL',
          ),
        ),
      ),
    ),
  ),
  'EL' =>
  array(
    'type' => 'number',
    'show-form' => 'tva3310CA3_20140101',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'FL',
          ),
          'operands' =>
          array(
            0 => 'DL',
            1 => 'EL',
          ),
        ),
      ),
      /*array('function' => 'copy-value',
            'args' => array('target' => 'tva3310ca3_GG'))*/
    ),
  ),
  'FL' =>
  array(
    'type' => 'number',
    'show-form' => 'tva3310CA3_20140101',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'FL',
            1 => 'PL',
          ),
        ),
      ),
      /*array('function' => 'copy-value',
            'args' => array('target' => 'tva3310ca3_GH'))*/
    ),
  ),
  'GA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JA',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'HA',
          ),
        ),
      ),
    ),
  ),
  'HA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JA',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'HA',
          ),
        ),
      ),
    ),
  ),
  'JA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PA',
          ),
          'operands' =>
          array(
            0 => 'JA',
            1 => 'MA',
            2 => 'NA',
          ),
        ),
      ),
    ),
  ),
  'KA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MA',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'KA',
          ),
        ),
      ),
    ),
  ),
  'LA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MA',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'KA',
          ),
        ),
      ),
    ),
  ),
  'MA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PA',
          ),
          'operands' =>
          array(
            0 => 'JA',
            1 => 'MA',
            2 => 'NA',
          ),
        ),
      ),
    ),
  ),
  'GB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JB',
          ),
          'operands' =>
          array(
            0 => 'GB',
            1 => 'HB',
          ),
        ),
      ),
    ),
  ),
  'HB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JB',
          ),
          'operands' =>
          array(
            0 => 'GB',
            1 => 'HB',
          ),
        ),
      ),
    ),
  ),
  'JB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      2 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PB',
          ),
          'operands' =>
          array(
            0 => 'JB',
            1 => 'MB',
            2 => 'NB',
          ),
        ),
      ),
    ),
  ),
  'KB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MB',
          ),
          'operands' =>
          array(
            0 => 'KB',
            1 => 'LB',
          ),
        ),
      ),
    ),
  ),
  'LB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MB',
          ),
          'operands' =>
          array(
            0 => 'KB',
            1 => 'LB',
          ),
        ),
      ),
    ),
  ),
  'MB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PB',
          ),
          'operands' =>
          array(
            0 => 'JB',
            1 => 'MB',
            2 => 'NB',
          ),
        ),
      ),
    ),
  ),
  'GC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JC',
          ),
          'operands' =>
          array(
            0 => 'GC',
            1 => 'HC',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
    ),
  ),
  'HC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JC',
          ),
          'operands' =>
          array(
            0 => 'GC',
            1 => 'HC',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
    ),
  ),
  'JC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PC',
          ),
          'operands' =>
          array(
            0 => 'JC',
            1 => 'MC',
            2 => 'NC',
          ),
        ),
      ),
    ),
  ),
  'KC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MC',
          ),
          'operands' =>
          array(
            0 => 'KC',
            1 => 'LC',
          ),
        ),
      ),
    ),
  ),
  'LC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MC',
          ),
          'operands' =>
          array(
            0 => 'KC',
            1 => 'LC',
          ),
        ),
      ),
    ),
  ),
  'MC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PC',
          ),
          'operands' =>
          array(
            0 => 'JC',
            1 => 'MC',
            2 => 'NC',
          ),
        ),
      ),
    ),
  ),
  'GD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JD',
          ),
          'operands' =>
          array(
            0 => 'GD',
            1 => 'HD',
          ),
        ),
      ),
    ),
  ),
  'HD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JD',
          ),
          'operands' =>
          array(
            0 => 'GD',
            1 => 'HD',
          ),
        ),
      ),
    ),
  ),
  'JD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PD',
          ),
          'operands' =>
          array(
            0 => 'JD',
            1 => 'MD',
            2 => 'ND',
          ),
        ),
      ),
    ),
  ),
  'KD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MD',
          ),
          'operands' =>
          array(
            0 => 'KD',
            1 => 'LD',
          ),
        ),
      ),
    ),
  ),
  'LD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MD',
          ),
          'operands' =>
          array(
            0 => 'KD',
            1 => 'LD',
          ),
        ),
      ),
    ),
  ),
  'MD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PD',
          ),
          'operands' =>
          array(
            0 => 'JD',
            1 => 'MD',
            2 => 'ND',
          ),
        ),
      ),
    ),
  ),
  'GE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JE',
          ),
          'operands' =>
          array(
            0 => 'GE',
            1 => 'HE',
          ),
        ),
      ),
    ),
  ),
  'HE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JE',
          ),
          'operands' =>
          array(
            0 => 'GE',
            1 => 'HE',
          ),
        ),
      ),
    ),
  ),
  'JE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PE',
          ),
          'operands' =>
          array(
            0 => 'JE',
            1 => 'ME',
            2 => 'NE',
          ),
        ),
      ),
    ),
  ),
  'KE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'ME',
          ),
          'operands' =>
          array(
            0 => 'KE',
            1 => 'LE',
          ),
        ),
      ),
    ),
  ),
  'LE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'ME',
          ),
          'operands' =>
          array(
            0 => 'KE',
            1 => 'LE',
          ),
        ),
      ),
    ),
  ),
  'ME' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PE',
          ),
          'operands' =>
          array(
            0 => 'JE',
            1 => 'ME',
            2 => 'NE',
          ),
        ),
      ),
    ),
  ),
  'GF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JF',
          ),
          'operands' =>
          array(
            0 => 'GF',
            1 => 'HF',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
    ),
  ),
  'HF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JF',
          ),
          'operands' =>
          array(
            0 => 'GF',
            1 => 'HF',
          ),
        ),
      ),
    ),
  ),
  'JF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PF',
          ),
          'operands' =>
          array(
            0 => 'JF',
            1 => 'MF',
            2 => 'NF',
          ),
        ),
      ),
    ),
  ),
  'KF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MF',
          ),
          'operands' =>
          array(
            0 => 'KF',
            1 => 'LF',
          ),
        ),
      ),
    ),
  ),
  'LF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MF',
          ),
          'operands' =>
          array(
            0 => 'KF',
            1 => 'LF',
          ),
        ),
      ),
    ),
  ),
  'MF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PF',
          ),
          'operands' =>
          array(
            0 => 'JF',
            1 => 'MF',
            2 => 'NF',
          ),
        ),
      ),
    ),
  ),
  'GG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JG',
          ),
          'operands' =>
          array(
            0 => 'GG',
            1 => 'HG',
          ),
        ),
      ),
    ),
  ),
  'HG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JG',
          ),
          'operands' =>
          array(
            0 => 'GG',
            1 => 'HG',
          ),
        ),
      ),
    ),
  ),
  'JG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PG',
          ),
          'operands' =>
          array(
            0 => 'JG',
            1 => 'MG',
            2 => 'NG',
          ),
        ),
      ),
    ),
  ),
  'KG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MG',
          ),
          'operands' =>
          array(
            0 => 'KG',
            1 => 'LG',
          ),
        ),
      ),
    ),
  ),
  'LG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MG',
          ),
          'operands' =>
          array(
            0 => 'KG',
            1 => 'LG',
          ),
        ),
      ),
    ),
  ),
  'MG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PG',
          ),
          'operands' =>
          array(
            0 => 'JG',
            1 => 'MG',
            2 => 'NG',
          ),
        ),
      ),
    ),
  ),
  'GH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JH',
          ),
          'operands' =>
          array(
            0 => 'GH',
            1 => 'HH',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
    ),
  ),
  'HH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JH',
          ),
          'operands' =>
          array(
            0 => 'GH',
            1 => 'HH',
          ),
        ),
      ),
    ),
  ),
  'JH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PH',
          ),
          'operands' =>
          array(
            0 => 'JH',
            1 => 'MH',
            2 => 'NH',
          ),
        ),
      ),
    ),
  ),
  'KH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MH',
          ),
          'operands' =>
          array(
            0 => 'KH',
            1 => 'LH',
          ),
        ),
      ),
    ),
  ),
  'LH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MH',
          ),
          'operands' =>
          array(
            0 => 'KH',
            1 => 'LH',
          ),
        ),
      ),
    ),
  ),
  'MH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PH',
          ),
          'operands' =>
          array(
            0 => 'JH',
            1 => 'MH',
            2 => 'NH',
          ),
        ),
      ),
    ),
  ),
  'GJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JJ',
          ),
          'operands' =>
          array(
            0 => 'GJ',
            1 => 'HJ',
          ),
        ),
      ),
    ),
  ),
  'HJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JJ',
          ),
          'operands' =>
          array(
            0 => 'GJ',
            1 => 'HJ',
          ),
        ),
      ),
    ),
  ),
  'JJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PJ',
          ),
          'operands' =>
          array(
            0 => 'JJ',
            1 => 'MJ',
            2 => 'NJ',
          ),
        ),
      ),
    ),
  ),
  'KJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MJ',
          ),
          'operands' =>
          array(
            0 => 'KJ',
            1 => 'LJ',
          ),
        ),
      ),
    ),
  ),
  'LJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MJ',
          ),
          'operands' =>
          array(
            0 => 'KJ',
            1 => 'LJ',
          ),
        ),
      ),
    ),
  ),
  'MJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PJ',
          ),
          'operands' =>
          array(
            0 => 'JJ',
            1 => 'MJ',
            2 => 'NJ',
          ),
        ),
      ),
    ),
  ),
  'GK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'GL',
          ),
          'operands' =>
          array(
            0 => 'GA',
            1 => 'GB',
            2 => 'GC',
            3 => 'GD',
            4 => 'GE',
            5 => 'GF',
            6 => 'GG',
            7 => 'GH',
            8 => 'GJ',
            9 => 'GK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JK',
          ),
          'operands' =>
          array(
            0 => 'GK',
            1 => 'HK',
          ),
        ),
      ),
    ),
  ),
  'HK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'HL',
          ),
          'operands' =>
          array(
            0 => 'HA',
            1 => 'HB',
            2 => 'HC',
            3 => 'HD',
            4 => 'HE',
            5 => 'HF',
            6 => 'HG',
            7 => 'HH',
            8 => 'HJ',
            9 => 'HK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JK',
          ),
          'operands' =>
          array(
            0 => 'GK',
            1 => 'HK',
          ),
        ),
      ),
    ),
  ),
  'JK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PK',
          ),
          'operands' =>
          array(
            0 => 'JK',
            1 => 'MK',
            2 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'KK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'KL',
          ),
          'operands' =>
          array(
            0 => 'KA',
            1 => 'KB',
            2 => 'KC',
            3 => 'KD',
            4 => 'KE',
            5 => 'KF',
            6 => 'KG',
            7 => 'KH',
            8 => 'KJ',
            9 => 'KK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MK',
          ),
          'operands' =>
          array(
            0 => 'KK',
            1 => 'LK',
          ),
        ),
      ),
    ),
  ),
  'LK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'LL',
          ),
          'operands' =>
          array(
            0 => 'LA',
            1 => 'LB',
            2 => 'LC',
            3 => 'LD',
            4 => 'LE',
            5 => 'LF',
            6 => 'LG',
            7 => 'LH',
            8 => 'LJ',
            9 => 'LK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'MK',
          ),
          'operands' =>
          array(
            0 => 'KK',
            1 => 'LK',
          ),
        ),
      ),
    ),
  ),
  'MK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PK',
          ),
          'operands' =>
          array(
            0 => 'JK',
            1 => 'MK',
            2 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'GL' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JL',
          ),
          'operands' =>
          array(
            0 => 'GL',
            1 => 'HL',
          ),
        ),
      ),
    ),
  ),
  'HL' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'JL',
          ),
          'operands' =>
          array(
            0 => 'GL',
            1 => 'HL',
          ),
        ),
      ),
    ),
  ),
  'JL' => array('type' => 'number',
                'show-form' => 'tva3310CA3_20140101',
                'operations' => array( /*array('function' => 'copy-value',
                                            'args' => array('target' => 'tva3310ca3_HA'))*/
                ),
  ),
  'KL' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'ML',
          ),
          'operands' =>
          array(
            0 => 'KL',
            1 => 'LL',
          ),
        ),
      ),
    ),
  ),
  'LL' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'ML',
          ),
          'operands' =>
          array(
            0 => 'KL',
            1 => 'LL',
          ),
        ),
      ),
    ),
  ),
  'ML' => array('type' => 'number',
                'show-form' => 'tva3310CA3',
                'operations' => array( /*array('function' => 'copy-value',
                                            'args' => array('target' => 'tva3310ca3_HB'))*/),
  ),
  'NA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PA',
          ),
          'operands' =>
          array(
            0 => 'JA',
            1 => 'MA',
            2 => 'NA',
          ),
        ),
      ),
    ),
  ),
  'PA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RA',
          ),
          'value' => 'PA',
          'operands' =>
          array(
            0 => 'FA',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QA',
          ),
          'operands' =>
          array(
            0 => 'FA',
            1 => 'PA',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QA',
          ),
          'value' => 'FA',
          'operands' =>
          array(
            0 => 'PA',
          ),
        ),
      ),
    ),
  ),
  'QA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RA' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      $operations['data-addition-nl'],
      2 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PB',
          ),
          'operands' =>
          array(
            0 => 'JB',
            1 => 'MB',
            2 => 'NB',
          ),
        ),
      ),
    ),
  ),
  'PB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RB',
          ),
          'value' => 'PB',
          'operands' =>
          array(
            0 => 'FB',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QB',
          ),
          'operands' =>
          array(
            0 => 'FB',
            1 => 'PB',
          ),
        ),
      ),
      4 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QB',
          ),
          'value' => 'FB',
          'operands' =>
          array(
            0 => 'PB',
          ),
        ),
      ),
    ),
  ),
  'QB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RB' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PC',
          ),
          'operands' =>
          array(
            0 => 'JC',
            1 => 'MC',
            2 => 'NC',
          ),
        ),
      ),
    ),
  ),
  'PC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RC',
          ),
          'value' => 'PC',
          'operands' =>
          array(
            0 => 'FC',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QC',
          ),
          'operands' =>
          array(
            0 => 'FC',
            1 => 'PC',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QC',
          ),
          'value' => 'FC',
          'operands' =>
          array(
            0 => 'PC',
          ),
        ),
      ),
    ),
  ),
  'QC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RC' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'ND' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PD',
          ),
          'operands' =>
          array(
            0 => 'JD',
            1 => 'MD',
            2 => 'ND',
          ),
        ),
      ),
    ),
  ),
  'PD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RD',
          ),
          'value' => 'PD',
          'operands' =>
          array(
            0 => 'FD',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QD',
          ),
          'operands' =>
          array(
            0 => 'FD',
            1 => 'PD',
          ),
        ),
      ),
      4 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QD',
          ),
          'value' => 'FD',
          'operands' =>
          array(
            0 => 'PD',
          ),
        ),
      ),
    ),
  ),
  'QD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RD' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PE',
          ),
          'operands' =>
          array(
            0 => 'JE',
            1 => 'ME',
            2 => 'NE',
          ),
        ),
      ),
    ),
  ),
  'PE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QE',
          ),
          'operands' =>
          array(
            0 => 'FE',
            1 => 'PE',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QE',
          ),
          'value' => 'FE',
          'operands' =>
          array(
            0 => 'PE',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RE',
          ),
          'value' => 'PE',
          'operands' =>
          array(
            0 => 'FE',
          ),
        ),
      ),
    ),
  ),
  'QE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RE' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PF',
          ),
          'operands' =>
          array(
            0 => 'JF',
            1 => 'MF',
            2 => 'NF',
          ),
        ),
      ),
    ),
  ),
  'PF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RF',
          ),
          'operands' =>
          array(
            0 => 'FF',
            1 => 'PF',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RF',
          ),
          'value' => 'PF',
          'operands' =>
          array(
            0 => 'FF',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QF',
          ),
          'value' => 'FF',
          'operands' =>
          array(
            0 => 'PF',
          ),
        ),
      ),
    ),
  ),
  'QF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RF' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PG',
          ),
          'operands' =>
          array(
            0 => 'JG',
            1 => 'MG',
            2 => 'NG',
          ),
        ),
      ),
    ),
  ),
  'PG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RG',
          ),
          'value' => 'PG',
          'operands' =>
          array(
            0 => 'FG',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QG',
          ),
          'operands' =>
          array(
            0 => 'FG',
            1 => 'PG',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QG',
          ),
          'value' => 'FG',
          'operands' =>
          array(
            0 => 'PG',
          ),
        ),
      ),
    ),
  ),
  'QG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
    ),
  ),
  'RG' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PH',
          ),
          'operands' =>
          array(
            0 => 'JH',
            1 => 'MH',
            2 => 'NH',
          ),
        ),
      ),
    ),
  ),
  'PH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RH',
          ),
          'value' => 'PH',
          'operands' =>
          array(
            0 => 'FH',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QH',
          ),
          'operands' =>
          array(
            0 => 'FH',
            1 => 'PH',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QH',
          ),
          'value' => 'FH',
          'operands' =>
          array(
            0 => 'PH',
          ),
        ),
      ),
    ),
  ),
  'QH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RH' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
    ),
  ),
  'NJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PJ',
          ),
          'operands' =>
          array(
            0 => 'JJ',
            1 => 'MJ',
            2 => 'NJ',
          ),
        ),
      ),
    ),
  ),
  'PJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RJ',
          ),
          'value' => 'PJ',
          'operands' =>
          array(
            0 => 'FJ',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QJ',
          ),
          'operands' =>
          array(
            0 => 'FJ',
            1 => 'PJ',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QJ',
          ),
          'value' => 'FJ',
          'operands' =>
          array(
            0 => 'PJ',
          ),
        ),
      ),
      4 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RJ',
          ),
          'value' => 'PJ',
          'operands' =>
          array(
            0 => 'FJ',
          ),
        ),
      ),
    ),
  ),
  'QJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RJ' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      $operations['data-addition-nl'],
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PK',
          ),
          'operands' =>
          array(
            0 => 'JK',
            1 => 'MK',
            2 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RK',
          ),
          'value' => 'PK',
          'operands' =>
          array(
            0 => 'FK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'PL',
          ),
          'operands' =>
          array(
            0 => 'PA',
            1 => 'PB',
            2 => 'PC',
            3 => 'PD',
            4 => 'PE',
            5 => 'PF',
            6 => 'PG',
            7 => 'PH',
            8 => 'PJ',
            9 => 'PK',
          ),
        ),
      ),
      2 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QK',
          ),
          'operands' =>
          array(
            0 => 'FK',
            1 => 'PK',
          ),
        ),
      ),
      3 =>
      array(
        'func' => 'data-soustraction',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QK',
          ),
          'value' => 'FK',
          'operands' =>
          array(
            0 => 'PK',
          ),
        ),
      ),
    ),
  ),
  'QK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QK',
          ),
          'operands' =>
          array(
            0 => 'FK',
            1 => 'PK',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QL',
          ),
          'operands' =>
          array(
            0 => 'QA',
            1 => 'QB',
            2 => 'QC',
            3 => 'QD',
            4 => 'QE',
            5 => 'QF',
            6 => 'QG',
            7 => 'QH',
            8 => 'QJ',
            9 => 'QK',
          ),
        ),
      ),
    ),
  ),
  'RK' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-addition',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'RL',
          ),
          'operands' =>
          array(
            0 => 'RA',
            1 => 'RB',
            2 => 'RC',
            3 => 'RD',
            4 => 'RE',
            5 => 'RF',
            6 => 'RG',
            7 => 'RH',
            8 => 'RJ',
            9 => 'RK',
          ),
        ),
      ),
    ),
  ),
  'NL' =>
  array(
    'type' => 'number',
    'operations' => array( /*array('function' => 'copy-value',
                                  'args' => array('target' => 'tva3310ca3_HC'))*/)
  ),
  'PL' =>
  array(
    'type' => 'number',
    'show-form' => 'tva3310CA3_20140101',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-check-non-egal-to-zero',
        'opt' =>
        array(
          'results' =>
          array(
            0 => 'QG',
          ),
          'operands' =>
          array(
            0 => 'FG',
            1 => 'PG',
          ),
        ),
      ),
      /*array('function' => 'copy-value',
            'args' => array('target' => 'tva3310ca3_KG'))*/
    ),
  ),
  'QL' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      1 =>
      array(
        'func' => 'data-calcul-qm-2014',
        'opt' =>
        array(
          'items' =>
          array(
            0 => 'QM',
            1 => 'QL',
            2 => 'RL',
          ),
        ),
      ),
    ),
    3 =>
    array(
      'func' => 'data-calcul-rm-2014',
      'opt' =>
      array(
        'items' =>
        array(
          0 => 'RM',
          1 => 'RL',
          2 => 'QL',
        ),
      ),
    ),
  ),
  'RL' =>
  array(
    'type' => 'number',
    'operations' =>
    array(
      0 =>
      array(
        'func' => 'data-calcul-rm-2014',
        'opt' =>
        array(
          'items' =>
          array(
            0 => 'RM',
            1 => 'RL',
            2 => 'QL',
          ),
        ),
      ),
      1 =>
      array(
        'func' => 'data-calcul-qm-2014',
        'opt' =>
        array(
          'items' =>
          array(
            0 => 'QM',
            1 => 'QL',
            2 => 'RL',
          ),
        ),
      ),
    ),
  ),
  'QM' => array('type' => 'number',
                'operations' => array(
                  array('func' => 'data-check-positiv-zero',
                        'opt' => array('operands' => array('QM', 'RM'), 'results' => array('AB')))
                ),
  ),
  'RM' => array('type' => 'number',
                'operations' => array(
                  array('func' => 'data-check-positiv-zero',
                        'opt' => array('operands' => array('QM', 'RM'), 'results' => array('AB')))
                ),
  ),
);
