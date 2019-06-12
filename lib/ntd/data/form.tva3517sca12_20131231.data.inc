<?php

$operations = array(
  'data-addition-fr' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('FR'),
                   'operands' => array('FS', 'FF', 'FB', 'FU', 'FV', 'FD', 'FJ', 'FG', 'FY', 'VP', 'EZ', 'FL', 'FM', 'FN', 'FP', 'GE')),
  ),
  'data-calcul-sb' => array('func' => 'data-calcul-sb',
                            'opt' => array('results' => array('SB'),
                                           'operands' => array('QN', 'QA', 'QS', 'QT', 'QD', 'QE', 'QF', 'QH', 'QJ',
                                                               'VC', 'VQ', 'VJ', 'VE', 'VF',
                                                               'KL', 'KM',
                                                               'RM', 'RH', 'RJ', 'RK', 'RL', 'RN', 'RF', 'RG'))),
  'data-calcul-rd' => array('func' => 'data-calcul-rd',
                            'opt' => array('results' => array('RD'),
                                           'operands' => array('QN', 'QA', 'QS', 'QT', 'QD', 'QE', 'QF', 'QH', 'QJ',
                                                               'VC', 'VQ', 'VJ', 'VE', 'VF',
                                                               'KL', 'KM',
                                                               'RM', 'RH', 'RJ', 'RK', 'RL', 'RN', 'RF', 'RG')),
  ),


  'data-check-need-and-or-ca' => array('func' => 'data-check-need-and-or', 'opt' => array('results' => array('CA'), 'operands' => array('VK'))),
  'data-check-need-and-or-ua' => array('func' => 'data-check-need-and-or', 'opt' => array('results' => array('UA'), 'operands' => array('TA'))),
  'data-check-need-and-or-ub' => array('func' => 'data-check-need-and-or', 'opt' => array('results' => array('UB'), 'operands' => array('TB'))),
  'data-check-need-and-or-uc' => array('func' => 'data-check-need-and-or', 'opt' => array('results' => array('UC'), 'operands' => array('TC'))),
  'data-check-need-and-or-ud' => array('func' => 'data-check-need-and-or', 'opt' => array('results' => array('UD'), 'operands' => array('TD'))),

  'data-calcul-percent-fs' => array('function' => 'data-calcul-percent', 'args' => array('result' => 'tva3517sca12_20131231_FS', 'percent' => 19.60)),
  'data-calcul-percent-ge' => array('function' => 'data-calcul-percent', 'args' => array('result' => 'tva3517sca12_20131231_GE', 'percent' => 7)),

  'data-calcul-550-ff' => array('func' => 'data-calcul-550', 'opt' => array('results' => array('FF'), 'operands' => array('EF'))),
  'data-calcul-850-fu' => array('func' => 'data-calcul-850', 'opt' => array('results' => array('FU'), 'operands' => array('EU'))),
  'data-calcul-210-fv' => array('func' => 'data-calcul-210', 'opt' => array('results' => array('FV'), 'operands' => array('EV'))),

  'data-check-positiv-ge-gd' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('GE', 'GD'))),
  'data-check-positiv-ej-fj' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EJ', 'FJ'))),
  'data-check-positiv-eg-fg' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EG', 'FG'))),
  'data-check-positiv-ey-fy' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EY', 'FY'))),
  'data-check-positiv-vn-vp' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('VN', 'VP'))),
  'data-check-positiv-eh-ez' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EH', 'EZ'))),
  'data-check-positiv-el-fl' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EL', 'FL'))),
  'data-check-positiv-em-fm' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EM', 'FM'))),
  'data-check-positiv-en-fn' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EN', 'FN'))),
  'data-check-positiv-ep-fp' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('EP', 'FP'))),

  'data-calcul-va' => array('func' => 'data-calcul-va', 'opt' => array('results' => array('VA'), 'operands' => array('FR', 'FL', 'FM', 'EQ', 'HC'))),
  'data-integrity-eq' => array('func' => 'data-integrity-eq', 'opt' => array('items' => array('EQ', 'FP'))),

  'data-addition-gc' => array('func' => 'data-addition', 'opt' => array('results' => array('GC'), 'operands' => array('FR', 'GA', 'GB'))),
  'data-addition-kd' => array('func' => 'data-addition', 'opt' => array('results' => array('KD'), 'operands' => array('HC', 'JA', 'KA', 'KB'))),
  'data-addition-hc' => array('func' => 'data-addition', 'opt' => array('results' => array('HC'), 'operands' => array('HA', 'HB'))),
  'data-addition-mm' => array('func' => 'data-addition', 'opt' => array('results' => array('MM'), 'operands' => array('MD', 'MF', 'MH', 'MK'))),
  'data-addition-mn' => array('func' => 'data-addition', 'opt' => array('results' => array('MN'), 'operands' => array('ME', 'MG', 'MJ', 'ML'))),
  'data-addition-ma' => array('func' => 'data-addition', 'opt' => array('results' => array('MA'), 'operands' => array('MM', 'MN'))),
  'data-addition-sc' => array('func' => 'data-addition', 'opt' => array('results' => array('SC'), 'operands' => array('SA', 'SB'))),

  'data-calcul-na' => array('func' => 'data-calcul-na', 'opt' => array('results' => array('NA'), 'operands' => array('LA', 'MC', 'LB', 'MA', 'MB', 'NB', 'NC'))),
  'data-calcul-nb' => array('func' => 'data-calcul-nb', 'opt' => array('results' => array('NB'), 'operands' => array('MA', 'MB', 'LA', 'MC'))),
  'data-calcul-nc' => array('func' => 'data-calcul-nc', 'opt' => array('results' => array('NC'), 'operands' => array('LB', 'NB', 'MA', 'MB', 'MC'))),

  'data-calcul-la-or-lb' => array('func' => 'data-calcul-la-or-lb', 'opt' => array('items' => array('LA', 'LB', 'GC', 'KD')))

);

$operations['data-calcul-na'];

$form["tva3517sca12_20131231"] = array(
  'VL' => array('type' => 'checkbox',
  ),
  'VK' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array($operations['data-check-need-and-or-ca']),
  ),
  'CA' => array('type' => 'comments',
                'length' => 2560,
                'operations' => array($operations['data-check-need-and-or-ca']),
  ),
  'CA1' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'CA2' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'CA3' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'CA4' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'CA5' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'EA' => array('type' => 'number',
  ),
  'EB' => array('type' => 'number',
  ),
  'EC' => array('type' => 'number',
  ),
  'ED' => array('type' => 'number',
  ),
  'VM' => array('type' => 'number',
  ),
  'EX' => array('type' => 'number',
  ),
  'ES' => array('type' => 'number',
                'operations' => array($operations['data-calcul-percent-fs']),
  ),
  'FS' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr']),
  ),
  'EF' => array('type' => 'number',
                'operations' => array($operations['data-calcul-550-ff']),
  ),
  'FF' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr']),
  ),
  'GD' => array('type' => 'number',
                'operations' => array($operations['data-calcul-percent-ge']),
  ),
  'GE' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-ge-gd'],
                                      $operations['data-addition-fr'])
  ),
  'FA' => array('type' => 'number',
                'readonly' => true,
  ),
  'FB' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-fr']),
  ),
  'EU' => array('type' => 'number',
                'operations' => array($operations['data-calcul-850-fu']),
  ),
  'FU' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr']),
  ),
  'EV' => array('type' => 'number',
                'operations' => array($operations['data-calcul-210-fv']),
  ),
  'FV' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr']),
  ),
  'FC' => array('type' => 'number',
                'readonly' => true,
  ),
  'FD' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-fr']),
  ),
  'EJ' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-ej-fj']),
  ),
  'FJ' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr'],
                                      $operations['data-check-positiv-ej-fj']),
  ),
  'EG' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-eg-fg'],
                                      array(
                                        'func' => 'data-integrity-fg-3517',
                                        'opt' => array('items' => array('FG', 'EG')),),),
  ),
  'FG' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr'],
                                      $operations['data-check-positiv-eg-fg'],
                                      array(
                                        'func' => 'data-integrity-fg-3517',
                                        'opt' => array('items' => array('FG', 'EG')),),),
  ),
  'EY' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-ey-fy']),
  ),
  'FY' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr'],
                                      $operations['data-check-positiv-ey-fy']),
  ),
  'VN' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-vn-vp']),
  ),
  'VP' => array('type' => 'number',
                'operations' => array($operations['data-addition-fr'],
                                      $operations['data-check-positiv-vn-vp']),
  ),
  'EH' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-eh-ez']),
  ),
  'EZ' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-eh-ez'],
                                      $operations['data-addition-fr']),
  ),
  'EL' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-el-fl']),
  ),
  'FL' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-el-fl'],
                                      $operations['data-calcul-va'],
                                      $operations['data-addition-fr']),
  ),
  'EM' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-em-fm']),
  ),
  'FM' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-em-fm'],

                                      $operations['data-calcul-va'],
                                      $operations['data-addition-fr']),
  ),
  'EN' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-en-fn']),
  ),
  'FN' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-en-fn'],
                                      $operations['data-addition-fr']),
  ),
  'EP' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-ep-fp']),
  ),
  'FP' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-ep-fp'],
                                      $operations['data-addition-fr']),
  ),
  'EQ' => array('type' => 'number',
                'operations' => array($operations['data-integrity-eq']),
  ),
  'FR' => array('type' => 'number',
                'operations' => array($operations['data-addition-gc'],
                                      $operations['data-calcul-va']),
  ),
  'GA' => array('type' => 'number',
                'operations' => array($operations['data-addition-gc']),
  ),
  'GB' => array('type' => 'number',
                'operations' => array($operations['data-addition-gc']),
  ),
  'GC' => array('type' => 'number',
                'operations' => array($operations['data-calcul-la-or-lb']),
  ),
  'HA' => array('type' => 'number',
                'operations' => array($operations['data-addition-hc']),
  ),
  'HB' => array('type' => 'number',
                'operations' => array($operations['data-addition-hc']),
  ),
  'HC' => array('type' => 'number',
                'operations' => array($operations['data-addition-kd'],
                                      $operations['data-calcul-va']),
  ),
  'JA' => array('type' => 'number',
                'operations' => array($operations['data-addition-kd']),
  ),
  'KA' => array('type' => 'number',
                'operations' => array($operations['data-addition-kd']),
  ),
  'KB' => array('type' => 'number',
                'operations' => array($operations['data-addition-kd']),
  ),
  'JB' => array('type' => 'pourcentage',
                'operations' => array(
                  0 =>
                  array(
                    'func' => 'data-check-percent',
                    'opt' =>
                    array(
                      'results' =>
                      array(
                        0 => 'JB',
                      ),
                      'operands' =>
                      array(
                        0 => 'JB',
                      ),
                    ),
                  ),
                ),
  ),
  'KD' => array('type' => 'number',
                'operations' => array($operations['data-calcul-la-or-lb']),
  ),
  'FE' => array('type' => 'number',
                'operations' => array(
                  array(
                    'func' => 'data-integrity-fe',
                    'opt' =>
                    array(
                      'items' =>
                      array(
                        0 => 'FE',
                        1 => 'KD',
                      ),
                    ),
                  ),
                ),
  ),
  'LA' => array('type' => 'number',
                'operations' => array($operations['data-calcul-nb'],
                                      $operations['data-calcul-na']),
  ),
  'LB' => array('type' => 'number',
                'operations' => array($operations['data-calcul-na'],
                                      $operations['data-calcul-nc']),
  ),
  'MD' => array('type' => 'number',
                'operations' => array($operations['data-addition-mm']),
  ),
  'ME' => array('type' => 'number',
                'operations' => array($operations['data-addition-mn']),
  ),
  'MF' => array('type' => 'number',
                'operations' => array($operations['data-addition-mm']),
  ),
  'MG' => array('type' => 'number',
                'operations' => array($operations['data-addition-mn']),
  ),
  'MH' => array('type' => 'number',
                'operations' => array($operations['data-addition-mm']),
  ),
  'MJ' => array('type' => 'number',
                'operations' => array($operations['data-addition-mn']),
  ),
  'MK' => array('type' => 'number',
                'operations' => array($operations['data-addition-mm']),
  ),
  'ML' => array('type' => 'number',
                'operations' => array($operations['data-addition-mn']),
  ),
  'MM' => array('type' => 'number',
                'operations' => array($operations['data-addition-ma']),
  ),
  'MN' => array('type' => 'number',
                'operations' => array($operations['data-addition-ma']),
  ),
  'MA' => array('type' => 'number',
                'operations' => array($operations['data-calcul-nb'],
                                      $operations['data-calcul-na'],
                                      $operations['data-calcul-nc']),
  ),
  'MB' => array('type' => 'number',
                'operations' => array($operations['data-calcul-nb'],
                                      $operations['data-calcul-na'],
                                      $operations['data-calcul-nc']),
  ),
  'MC' => array('type' => 'number',
                'operations' => array($operations['data-calcul-nb'],
                                      $operations['data-calcul-na'],
                                      $operations['data-calcul-nc']),
  ),
  'NA' => array('type' => 'number',
                'operations' => array(0 => array('func' => 'data-report',
                                                 'opt' =>
                                                 array(
                                                   'results' =>
                                                   array(
                                                     0 => 'SA',
                                                   ),
                                                   'operands' =>
                                                   array(
                                                     0 => 'NA',
                                                   ),
                                                 )),
                                      1 => $operations['data-calcul-nc'],
                ),
  ),
  'NB' => array('type' => 'number',
                'operations' => array($operations['data-calcul-nc']),
  ),
  'NC' => array('type' => 'number',
                'operations' => array(0 =>
                array(
                  'func' => 'data-report',
                  'opt' =>
                  array(
                    'results' =>
                    array(
                      0 => 'RA',
                    ),
                    'operands' =>
                    array(
                      0 => 'NC',
                    ),
                  ),
                ),
                ),
  ),
  'QA' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'QS' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'QT' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'QD' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'QE' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'QF' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'QH' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'BR' => array('type' => 'number',
  ),
  'BT' => array('type' => 'number',
  ),
  'KE' => array('type' => 'number',
                'readonly' => true,
  ),
  'KF' => array('type' => 'number',
                'readonly' => true,
  ),
  'KG' => array('type' => 'number',
                'readonly' => true,
  ),
  'QJ' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'VC' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'VQ' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'VJ' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'VE' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'VF' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'KL' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'KM' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'RM' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),
  'RH' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),
  'RJ' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),
  'RK' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),
  'RL' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),
  'RN' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),
  'RF' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),
  'RG' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd'])
  ),

  'KH' => array('type' => 'number',
                'readonly' => true,
  ),
  'KJ' => array('type' => 'number',
                'readonly' => true,
  ),
  'QN' => array('type' => 'number',
                'operations' => array($operations['data-calcul-sb'],
                                      $operations['data-calcul-rd']),
  ),
  'RA' => array('type' => 'number',
                'operations' =>
                array(
                  0 =>
                  array(
                    'func' => 'data-integrity-rb',
                    'opt' =>
                    array(
                      'items' =>
                      array(
                        0 => 'RB',
                        1 => 'RA',
                      ),
                    ),
                  ),
                ),
  ),
  'RB' => array('type' => 'number',
                'operations' =>
                array(
                  0 =>
                  array(
                    'func' => 'data-integrity-rb',
                    'opt' =>
                    array(
                      'items' =>
                      array(
                        0 => 'RB',
                        1 => 'RA',
                      ),
                    ),
                  ),
                ),
  ),
  'RC' => array('type' => 'number',
  ),
  'RE' => array('type' => 'number',
  ),
  'RD' => array('type' => 'number',
  ),
  'SA' => array('type' => 'number',
                'operations' => array($operations['data-addition-sc']),
  ),
  'SB' => array('type' => 'number',
                'operations' => array($operations['data-addition-sc']),
  ),
  'SC' => array('type' => 'number',
                'operations' => array(array('func' => 'data-paiement_3517sca12',
                                            'opt' => array('operands' => array('SC'))))
  ),
  'SD' => array('type' => 'checkbox',
                'operations' =>
                array(
                  0 =>
                  array(
                    'func' => 'data-disable',
                    'opt' =>
                    array(
                      'items' =>
                      array(
                        0 => 'SD',
                        1 => 'CA1',
                        2 => 'CA2',
                        3 => 'CA3',
                        4 => 'CA4',
                        5 => 'CA5',
                        6 => 'RA',
                        7 => 'RB',
                      ),
                    ),
                  ),
                ),
  ),
  'TA' => array('type' => 'checkbox',
                'value' => 1,
                'operations' => array($operations['data-check-need-and-or-ua']),
  ),
  'UA' => array('type' => 'date-ssaa',
                'length' => 4,
                'operations' => array($operations['data-check-need-and-or-ua']),
  ),
  'TB' => array('type' => 'checkbox',
                'value' => 1,
                'operations' => array($operations['data-check-need-and-or-ub']),
  ),
  'UB' => array('type' => 'date-ssaa',
                'length' => 4,
                'operations' => array($operations['data-check-need-and-or-ub']),
  ),
  'TC' => array('type' => 'checkbox',
                'value' => 1,
                'operations' => array($operations['data-check-need-and-or-uc']),
  ),
  'UC' => array('type' => 'date-ssaa',
                'length' => 4,
                'operations' => array($operations['data-check-need-and-or-uc']),
  ),
  'TD' => array('type' => 'checkbox',
                'value' => 1,
                'operations' => array($operations['data-check-need-and-or-ud']),
  ),
  'UD' => array('type' => 'date-ssaa',
                'length' => 4,
                'operations' => array($operations['data-check-need-and-or-ud']),
  ),
  'VA' => array('type' => 'number',
  ),
  'NL' => array('type' => 'number',
  ),
  'VG' => array('type' => 'checkbox',
  ),
  'VH' => array('type' => 'checkbox',
  ),
  'NM1' => array('type' => 'number',
                 'length' => 5,
  ),
  'NM2' => array('type' => 'number',
                 'length' => 5,
  ),
  'NM3' => array('length' => 13,
  ),
  'NM4' => array('length' => 35,
  ),
  'NM5' => array('length' => 35,
  )
);

  