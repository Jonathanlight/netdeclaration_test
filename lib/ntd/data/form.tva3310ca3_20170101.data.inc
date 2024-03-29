<?php

$operations = array(
  'data-integrity-kc' => array('func' => 'data-integrity-kc-2015',
                               'opt' => array('items' => array('KA', 'KB'))
  ),

);


$form["tva3310ca3_20170101"] = array(

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
  'KH' => array('type' => 'number', 'length' => 15,),
  'KR' => array('type' => 'number', 'length' => 15,),
  'CC' => array('type' => 'number', 'length' => 15,),
  'CD' => array('type' => 'number', 'length' => 15,),
  'CF' => array('type' => 'number', 'length' => 15,),
  'CG' => array('type' => 'number', 'length' => 15,),
  'CE' => array('type' => 'number', 'length' => 15,),
  'DA' => array('type' => 'number', 'length' => 15,),
  'DB' => array('type' => 'number', 'length' => 15,),
  'DC' => array('type' => 'number', 'length' => 15,),
  'DF' => array('type' => 'number', 'length' => 15,),
  'DD' => array('type' => 'number', 'length' => 15,),
  'DG' => array('type' => 'number', 'length' => 15,),
  'DE' => array('type' => 'number', 'length' => 15,),
  'DH' => array('type' => 'number', 'length' => 15,),
  'FP' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array('func' => 'data-calcul-2000',
                                            'opt' => array('results' => array('GP'), 'operands' => array('FP')),),
                                      ),
  ),
  'GP' => array('type' => 'number',),
  'FB' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array('func' => 'data-calcul-550',
                                            'opt' => array('results' => array('GB'),
                                                           'operands' => array('FB'))),
                                      ),
  ),
  'GB' => array('type' => 'number',
                'show-form' => 'tva3310ter_20160101'),
  'FG' => array('type' => 'number'),
  'FH' => array('type' => 'number'),
  'FM' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array('func' => 'data-calcul-850',
                                            'opt' => array('results' => array('GM'),
                                                           'operands' => array('FM'))),
                                      ),
  ),
  'GM' => array('type' => 'number',),
  'FN' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array('func' => 'data-calcul-210',
                                            'opt' => array('results' => array('GN'), 'operands' => array('FN')),),
                                      ),
  ),
  'GN' => array('type' => 'number', 'length' => 15,),
  'FJ' => array('type' => 'number'),
  'FK' => array('type' => 'number'),
  'FC' => array('type' => 'number', 'length' => 15,),
  'GC' => array('type' => 'number', 'length' => 15,),
  'FD' => array('type' => 'number',),
  'GD' => array('type' => 'number',),
  'GG' => array('type' => 'number', 'length' => 15,),
  'KS' => array('type' => 'number', 'length' => 15,),
  'KT' => array('type' => 'number', 'length' => 15,),
  'KU' => array('type' => 'number', 'length' => 15,),
  'GH' => array('type' => 'number',),
  'GJ' => array('type' => 'number', 'length' => 15,),
  'GK' => array('type' => 'number', 'length' => 15,),
  'HA' => array('type' => 'number', 'length' => 15,),
  'HB' => array('type' => 'number', 'length' => 15,),
  'HC' => array('type' => 'number', 'length' => 15,),
  'HH' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array('func' => 'data-integrity-hh',
                                            'opt' => array('items' => array('HH', 'HC')),),
                                      array('func' => 'data-integrity-ce',
                                            'opt' => array('items' => array('CE', 'HH')),),),
  ),
  'HD' => array('type' => 'number', 'length' => 15,),
  'HE' => array('type' => 'pourcentage'),
  'HG' => array('type' => 'number',),
  'KG' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array(
                                        'func' => 'data-integrity-kg',
                                        'opt' => array('items' => array('KG', 'HG')),
                                      ),
                ),
  ),
  'JA' => array('type' => 'number',
  ),
  'JB' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array(
                                        'func' => 'data-integrity-jb',
                                        'opt' => array('items' => array('JB', 'JA', 'KJ')),
                                      ),
                ),
  ),
  'JC' => array('type' => 'number',
  ),
  'KA' => array('type' => 'number',
                'show-form' => 'tva3310ter_20160101',
                'operations' => array($operations['data-integrity-kc']),
  ),
  'KB' => array('type' => 'number',
                'show-form' => 'tva3310a_20160101',
                'operations' => array($operations['data-integrity-kc'])
  ),
  'KL' => array('type' => 'number',),
  'KE' => array('type' => 'number',),
  'KF' => array('type' => 'checkbox',
                'value' => '1',),
  'FR' => array('type' => 'number',
                'length' => 15,
                'operations' => array(array('func' => 'data-calcul-1000',
                                            'opt' => array('results' => array('GR'), 'operands' => array('FR')),),)
  ),
  'GR' => array('type' => 'number',),
  'KJ' => array('type' => 'number',)

);


foreach($form["tva3310ca3_20170101"] as $fieldname => $data) {
  $form["tva3310ca3_20170101"][$fieldname]['operations'][]['assert'] = 'tva3310ca3_20170101';
}
