<?php

$operations = array(
  'data-integrity-kc' => array('func' => 'data-integrity-kc-2015',
                               'opt' => array('items' => array('KA', 'KB'))
  ),

);


$form["tva3310ca3_20180101"] = array(

  'BA' => array('type' => 'comments', 'length' => 2560,),
  'BA1' => array('type' => 'hidden', 'length' => 512,),
  'BA2' => array('type' => 'hidden', 'length' => 512,),
  'BA3' => array('type' => 'hidden', 'length' => 512,),
  'BA4' => array('type' => 'hidden', 'length' => 512,),
  'BA5' => array('type' => 'hidden', 'length' => 512,),
  'BB' => array('type' => 'checkbox',),
  'HJ' => array('type' => 'checkbox',),
  'BC' => array('type' => 'checkbox', 'value' => '1',),
  'CA' => array('type' => 'number', 'length' => 15,),
  'CB' => array('type' => 'number', 'length' => 15,),
  'CC' => array('type' => 'number', 'length' => 15,),
  'CD' => array('type' => 'number', 'length' => 15,),
  'CE' => array('type' => 'number', 'length' => 15,),
  'CF' => array('type' => 'number', 'length' => 15,),
  'CG' => array('type' => 'number', 'length' => 15,),
  'DA' => array('type' => 'number', 'length' => 15,),
  'DB' => array('type' => 'number', 'length' => 15,),
  'DC' => array('type' => 'number', 'length' => 15,),
  'DD' => array('type' => 'number', 'length' => 15,),
  'DE' => array('type' => 'number', 'length' => 15,),
  'DF' => array('type' => 'number', 'length' => 15,),
  'DG' => array('type' => 'number', 'length' => 15,),
  'DH' => array('type' => 'number', 'length' => 15,),
  'FB' => array('type' => 'number',
                          'length' => 15,
                          'operations' => array(array('func' => 'data-calcul-550',
                                                      'opt' => array('results' => array('GB'),
                                                                     'operands' => array('FB'))),
                                                ),
                ),
  'FC' => array('type' => 'number', 'length' => 15,),
  'FD' => array('type' => 'number',),
  'FG' => array('type' => 'number'),
  'FH' => array('type' => 'number'),
  'FJ' => array('type' => 'number'),
  'FK' => array('type' => 'number'),
  'FM' => array('type' => 'number',
                          'length' => 15,
                          'operations' => array(array('func' => 'data-calcul-850',
                                                      'opt' => array('results' => array('GM'),
                                                                      'operands' => array('FM'))),
                                                ),
                ),
  'FN' => array('type' => 'number',
                          'length' => 15,
                          'operations' => array(array('func' => 'data-calcul-210',
                                                      'opt' => array('results' => array('GN'), 'operands' => array('FN')),),
                                                ),
                ),
  'FP' => array('type' => 'number',
                          'length' => 15,
                          'operations' => array(array('func' => 'data-calcul-2000',
                                                      'opt' => array('results' => array('GP'), 'operands' => array('FP')),),
                                                ),
            ),
  'FR' => array('type' => 'number',
                          'length' => 15,
                          'operations' => array(array('func' => 'data-calcul-1000',
                                                      'opt' => array('results' => array('GR'), 'operands' => array('FR')),),)
                ),
  'GB' => array('type' => 'number',
              'show-form' => 'tva3310ter_20160101'),
  'GC' => array('type' => 'number', 'length' => 15,),
  'GD' => array('type' => 'number',),
  'GG' => array('type' => 'number', 'length' => 15,),
  'GH' => array('type' => 'number',),
  'GJ' => array('type' => 'number', 'length' => 15,),
  'GK' => array('type' => 'number', 'length' => 15,),
  'GM' => array('type' => 'number',),
  'GN' => array('type' => 'number', 'length' => 15,),
  'GP' => array('type' => 'number',),
  'GR' => array('type' => 'number',),
  'HA' => array('type' => 'number', 'length' => 15,),
  'HB' => array('type' => 'number', 'length' => 15,),
  'HC' => array('type' => 'number', 'length' => 15,),
  'HD' => array('type' => 'number', 'length' => 15,),
  'HE' => array('type' => 'pourcentage'),
  'HG' => array('type' => 'number',),
  'HH' => array('type' => 'number',
        'length' => 15,
        'operations' => array(array('func' => 'data-integrity-hh',
            'opt' => array('items' => array('HH', 'HC')),),
            array('func' => 'data-integrity-ce',
                'opt' => array('items' => array('CE', 'HH')),),),
  ),
  'JA' => array('type' => 'number',),
  'JB' => array('type' => 'number',
        'length' => 15,
        'operations' => array(array(
            'func' => 'data-integrity-jb',
            'opt' => array('items' => array('JB', 'JA', 'KJ')),
        ),
        ),
  ),
  'JC' => array('type' => 'number',),
  'KA' => array('type' => 'number',
        'show-form' => 'tva3310ter_20160101',
        'operations' => array($operations['data-integrity-kc']),
  ),
  'KB' => array('type' => 'number',
        'show-form' => 'tva3310a_20160101',
        'operations' => array($operations['data-integrity-kc'])
  ),
  'KE' => array('type' => 'number',),
  'KF' => array('type' => 'checkbox',
        'value' => '1',),
  'KG' => array('type' => 'number',
        'length' => 15,
        'operations' => array(array(
            'func' => 'data-integrity-kg',
            'opt' => array('items' => array('KG', 'HG')),
        ),
        ),
  ),
  'KH' => array('type' => 'number', 'length' => 15,),
  'KJ' => array('type' => 'number',),
  'KL' => array('type' => 'number',),
  'KR' => array('type' => 'number', 'length' => 15,),
  'KS' => array('type' => 'number', 'length' => 15,),
  'KT' => array('type' => 'number', 'length' => 15,),
  'KU' => array('type' => 'number', 'length' => 15,)
);


foreach($form["tva3310ca3_20180101"] as $fieldname => $data) {
  $form["tva3310ca3_20180101"][$fieldname]['operations'][]['assert'] = 'tva3310ca3_20180101';
}
