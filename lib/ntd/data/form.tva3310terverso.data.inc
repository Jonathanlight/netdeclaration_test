<?php 

$form["tva3310terverso"] = array(
  'NA' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PA' =>
  array(
    'required' => true,
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
    ),
  ),
  'QA' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RA' =>
  array(
    'required' => true,
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
  'SA' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NB' =>
  array(
    'required' => true,
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
            0 => 'PB',
          ),
          'value' => 'JB',
          'operands' =>
          array(
            0 => 'MB',
            1 => 'NB',
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PB' =>
  array(
    'required' => true,
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
    ),
  ),
  'QB' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RB' =>
  array(
    'required' => true,
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
  'SB' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NC' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PC' =>
  array(
    'required' => true,
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
    ),
  ),
  'QC' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RC' =>
  array(
    'required' => true,
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
  'SC' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'ND' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PD' =>
  array(
    'required' => true,
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
    ),
  ),
  'QD' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RD' =>
  array(
    'required' => true,
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
  'SD' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NE' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PE' =>
  array(
    'required' => true,
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
    ),
  ),
  'QE' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RE' =>
  array(
    'required' => true,
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
  'SE' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NF' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PF' =>
  array(
    'required' => true,
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
    ),
  ),
  'QF' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RF' =>
  array(
    'required' => true,
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
  'SF' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NG' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PG' =>
  array(
    'required' => true,
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
    ),
  ),
  'QG' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RG' =>
  array(
    'required' => true,
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
  'SG' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NH' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PH' =>
  array(
    'required' => true,
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
    ),
  ),
  'QH' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RH' =>
  array(
    'required' => true,
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
            0 => 'RH',
          ),
          'value' => 'PH',
          'operands' =>
          array(
            0 => 'FH',
          ),
        ),
      ),
    ),
  ),
  'SH' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NJ' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PJ' =>
  array(
    'required' => true,
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
    ),
  ),
  'QJ' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RJ' =>
  array(
    'required' => true,
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
  'SJ' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NK' =>
  array(
    'required' => true,
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
            0 => 'NL',
          ),
          'operands' =>
          array(
            0 => 'NA',
            1 => 'NB',
            2 => 'NC',
            3 => 'ND',
            4 => 'NE',
            5 => 'NF',
            6 => 'NG',
            7 => 'NH',
            8 => 'NJ',
            9 => 'NK',
          ),
        ),
      ),
    ),
  ),
  'PK' =>
  array(
    'required' => true,
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
    ),
  ),
  'QK' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RK' =>
  array(
    'required' => true,
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
  'SK' =>
  array(
    'required' => true,
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
            0 => 'SL',
          ),
          'operands' =>
          array(
            0 => 'SA',
            1 => 'SB',
            2 => 'SC',
            3 => 'SD',
            4 => 'SE',
            5 => 'SF',
            6 => 'SG',
            7 => 'SH',
            8 => 'SJ',
            9 => 'SK',
          ),
        ),
      ),
    ),
  ),
  'NL' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'PL' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'QL' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RL' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'SL' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'QM' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'RM' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
  'DM' =>
  array(
    'required' => true,
    'type' => 'number',
  ),
);
