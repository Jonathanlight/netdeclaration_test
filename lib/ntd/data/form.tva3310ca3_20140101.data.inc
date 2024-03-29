<?php


$operations = array(
  'addition-gh' => array('func' => 'data-addition',
                         'opt' => array('results' => array('GH'),
                                        'operands' => array('GP', 'GB', 'FH', 'GM', 'GN', 'FK', 'GC', 'GD', 'GG', 'GR'),),
  ),
  'data-calcul-ja' => array('func' => 'data-calcul-ca3-ja',
                            'opt' => array('results' => array('JA'),
                                           'operands' => array('GH', 'HG', 'tva3310ter_20140101_RM')),
  ),
  'data-calcul-ka' => array('func' => 'data-calcul-ca3-ka',
                            'opt' => array('results' => array('KA'),
                                           'operands' => array('GH', 'HG', 'tva3310ter_20140101_QM')),
  ),
  'data-calcul-ke' => array('func' => 'data-calcul-ke',
                            'opt' => array('results' => array('KE'),
                                           'operands' => array('KA', 'KB', 'KC', 'KD', 'KL')),
  ),

  'addition-ba' => array('func' => 'data-addition',
                         'opt' => array('results' => array('tva3515sd_BA'),
                                        'operands' => array('KA', 'KB')),
  ),


  'data-integrity-cc' => array('func' => 'data-integrity-cc',
                               'opt' => array('items' => array('CC', 'GJ'))
  ),
  'data-integrity-gj-2014' => array('func' => 'data-integrity-gj-2014',
                                    'opt' => array('items' => array('GJ', 'CC', 'GH', 'GK')),
  ),
  'data-integrity-gk' => array('func' => 'data-integrity-gk',
                               'opt' => array('items' => array('GK', 'GH', 'GJ')),
  ),
  'data-addition-hg' => array('func' => 'data-addition',
                              'opt' => array('results' => array('HG'),
                                             'operands' => array('HA', 'HB', 'HC', 'HD'))
  ),
  'data-integrity-kc' => array('func' => 'data-integrity-kc',
                               'opt' => array('items' => array('KC', 'KA', 'KB', 'KD'))
  ),
  'data-integrity-gh' => array('func' => 'data-integrity-gh',
                               'opt' => array('left' => array('CA', 'CB', 'KH', 'CC', 'CF', 'CG'),
                                              'right' => array('FP', 'FB', 'FM', 'FN', 'FC', 'FD', 'FR'))
  ),
  'soustraction-jc' => array('func' => 'data-soustraction',
                             'opt' => array('results' => array('JC'),
                                            'value' => 'JA',
                                            'operands' => array('JB', 'KJ')),
  )
);


$form["tva3310ca3_20140101"] = array(
  'BA' => array('type' => 'comments',
                'length' => 2560,
                'operations' => array(array('func' => 'data-check-need-and-or',
                                            'opt' => array('results' => array('BA'), 'operands' => array('BC')))),
  ),
  'BA1' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'BA2' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'BA3' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'BA4' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'BA5' => array('type' => 'hidden',
                 'length' => 512,
  ),
  'BB' => array('type' => 'checkbox',
  ),
  'HJ' => array('type' => 'checkbox',
  ),
  'BC' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(array('func' => 'data-check-need-and-or',
                                            'opt' => array('results' => array(0 => 'BA',), 'operands' => array(0 => 'BC',),),),),
  ),
  'CA' => array('type' => 'number',
                'operations' => array($operations['addition-gh'], $operations['data-integrity-gh']),
  ),
  'CB' => array('type' => 'number',
                'operations' => array($operations['addition-gh'], $operations['data-integrity-gh']),
  ),
  'KH' => array('type' => 'number',
                'operations' => array($operations['addition-gh'], $operations['data-integrity-gh']),
  ),
  'CC' => array('type' => 'number',
                'operations' => array($operations['data-integrity-cc'], $operations['addition-gh']),
  ),
  'CD' => array('type' => 'number',
                'operations' => array(array('func' => 'data-integrity-cd',
                                            'opt' => array('items' => array('CD', 'CC'))),),
  ),
  'CF' => array('type' => 'number',
                'operations' => array($operations['addition-gh'], $operations['data-integrity-gh']),
  ),
  'CG' => array('type' => 'number',
                'operations' => array($operations['addition-gh'], $operations['data-integrity-gh']),
  ),
  'CE' => array('type' => 'number',
  ),
  'DA' => array('type' => 'number',
  ),
  'DB' => array('type' => 'number',
  ),
  'DC' => array('type' => 'number',
  ),
  'DF' => array('type' => 'number',
  ),
  'DD' => array('type' => 'number',
  ),
  'DG' => array('type' => 'number',
  ),
  'DE' => array('type' => 'number',
  ),
  'FP' => array('type' => 'number',
                'operations' => array(array('func' => 'data-calcul-2000',
                                            'opt' => array('results' => array('GP'), 'operands' => array('FP')),),
                $operations['data-integrity-gh']),
  ),
  'GP' => array('type' => 'number',
                'operations' => array($operations['addition-gh']),
  ),
  'FB' => array('type' => 'number',
                'operations' => array(array('func' => 'data-calcul-550',
                                            'opt' => array('results' => array('GB'),
                                                           'operands' => array('FB'))),
                $operations['data-integrity-gh']),
  ),
  'GB' => array('type' => 'number',
                'show-form' => 'tva3310ter_20140101',
                'operations' => array($operations['addition-gh']),
  ),
  'FG' => array('type' => 'number',
                'readonly' => true,
  ),
  'FH' => array('type' => 'number',
                'readonly' => true,
  ),
  'FM' => array('type' => 'number',
                'operations' => array(array('func' => 'data-calcul-850',
                                            'opt' => array('results' => array('GM'),
                                                           'operands' => array('FM'))),
                $operations['data-integrity-gh']),
  ),
  'GM' => array('type' => 'number',
                'operations' => array($operations['addition-gh']),
  ),
  'FN' => array('type' => 'number',
                'operations' => array(array('func' => 'data-calcul-210',
                                            'opt' => array('results' => array('GN'), 'operands' => array('FN')),),
                                      $operations['addition-gh'],
                $operations['data-integrity-gh']),
  ),
  'GN' => array('type' => 'number',
                'operations' => array($operations['addition-gh']),
  ),
  'FJ' => array('type' => 'number',
                'readonly' => true,
  ),
  'FK' => array('type' => 'number',
                'readonly' => true,
  ),
  'FC' => array('type' => 'number',
                'operations' => array($operations['data-integrity-gh'])
  ),
  'GC' => array('type' => 'number',
                'operations' => array($operations['addition-gh'],
                                      array(
                                        'func' => 'data-integrity-gc-2014',
                                        'opt' => array('items' => array('GC', 'FC')),),),
  ),
  'FD' => array('type' => 'number',
                'operations' => array($operations['data-integrity-gh'])
  ),
  'GD' => array('type' => 'number',
                'operations' => array($operations['addition-gh']),
  ),
  'GG' => array('type' => 'number',
                'operations' => array($operations['addition-gh']),
  ),
  'GH' => array('type' => 'number',
                'operations' => array($operations['data-calcul-ja'],
                                      $operations['data-calcul-ka'],
                                      $operations['data-integrity-gh']),
  ),
  'GJ' => array('type' => 'number',
                'operations' => array($operations['data-integrity-cc'], $operations['data-integrity-gj-2014']),
  ),
  'GK' => array('type' => 'number',
                'operations' => array($operations['data-integrity-gk']),
  ),
  'HA' => array('type' => 'number',
                'operations' => array($operations['data-addition-hg'])
  ),
  'HB' => array('type' => 'number',
                'operations' => array($operations['data-addition-hg']),
  ),
  'HC' => array('type' => 'number',
                'operations' => array($operations['data-addition-hg']),
  ),
  'HH' => array('type' => 'number',
                'operations' => array(array('func' => 'data-integrity-hh',
                                            'opt' => array('items' => array('HH', 'HC')),),
                                      array('func' => 'data-integrity-ce',
                                            'opt' => array('items' => array('CE', 'HH')),),),
  ),
  'HD' => array('type' => 'number',
                'operations' => array($operations['data-addition-hg']),
  ),
  'HE' => array('type' => 'pourcentage',
                'operations' => array(array('func' => 'data-check-percent',
                                            'opt' => array('results' => array('HE',), 'operands' => array('HE')),),),
  ),
  'HG' => array('type' => 'number',
                'operations' => array($operations['data-calcul-ja'],
                                      $operations['data-calcul-ka'],
                ),
  ),
  'KG' => array('type' => 'number',
                'operations' => array(array(
                  'func' => 'data-integrity-kg',
                  'opt' => array('items' => array('KG', 'HG')),
                ),
                ),
  ),
  'JA' => array('type' => 'number',
                'operations' => array($operations['soustraction-jc'],),
  ),
  'JB' => array('type' => 'number',
                'operations' => array($operations['soustraction-jc'],
                                      array(
                                        'func' => 'data-integrity-jb',
                                        'opt' => array('items' => array('JB', 'JA', 'KJ')),
                                      ),
                ),
  ),
  'JC' => array('type' => 'number',
  ),
  'KA' => array('type' => 'number',
                'show-form' => 'tva3310ter_20140101',
                'operations' => array($operations['data-integrity-kc'], $operations['data-calcul-ke'], $operations['addition-ba']),
  ),
  'KB' => array('type' => 'number',
                'show-form' => 'tva3310a_20140101',
                'operations' => array($operations['data-integrity-kc'], $operations['data-calcul-ke'], $operations['addition-ba'])
  ),
  'KC' => array('type' => 'number',
                'operations' => array($operations['data-integrity-kc'], $operations['data-calcul-ke'])
  ),
  'KD' => array('type' => 'number',
                'operations' => array($operations['data-integrity-kc'], $operations['data-calcul-ke'])
  ),
  'KL' => array('type' => 'number',
                'operations' => array($operations['data-calcul-ke'])
  ),
  'KE' => array('type' => 'number',
  ),
  'KF' => array('type' => 'checkbox',
                'value' => '1',
                'operations' => array(array(
                  'func' => 'disable-form',
                  'opt' => array('items' => array('KF', 'BA1', 'BA2', 'BA3', 'BA4', 'BA5', 'BC'))
                ),
                ),
  ),
  'FR' => array('type' => 'number',
                'operations' => array(array('func' => 'data-calcul-1000',
                                            'opt' => array('results' => array('GR'), 'operands' => array('FR')),),
                $operations['data-integrity-gh'])
  ),
  'GR' => array('type' => 'number',
                'operations' => array($operations['addition-gh'])
  ),
  'KJ' => array('type' => 'number',
                'operations' => array($operations['soustraction-jc'],),
  )
);
