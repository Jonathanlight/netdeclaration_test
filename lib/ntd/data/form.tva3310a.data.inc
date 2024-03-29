<?php

$operations = array(
  'data-addition-cn' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('CN'),
                   'operands' => array('CA', 'CB', 'CC', 'AF', 'CE', 'CF', 'CJ', 'CK', 'CM', 'CP', 'CQ', 'CR',),
    ),
  ),
  'data-addition-bn' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('BN',),
                   'operands' => array('BA', 'BB', 'BC', 'AE', 'BE', 'BF', 'BJ', 'BK', 'BM', 'BP', 'BQ', 'BR',),
    ),
  ),
  'data-addition-hb' => array(
    'func' => 'data-addition',
    'opt' => array('results' => array('HB'),
                   'operands' => array('FA', 'FB', 'HE', 'FE', 'FF', 'FG', 'JD', 'FJ', 'JB', 'JC', 'JE',
                                       'HF', 'FR', 'KF', 'FT', 'KG', 'FV', 'HH', 'HI', 'KA', 'KB',
                                       'KC', 'KD', 'KE', 'KJ', 'KL', 'KS', 'KN', 'KO', 'KP', 'KQ', 'KR',
                                       'KT', 'KU')
    ),
  ),
  'data-check-need-and-or-da-db' => array('func' => 'data-check-need-and-or', 'opt' => array('results' => array('DA',), 'operands' => array('DB',),),),
  'data-check-positiv-ba-ca' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('BA', 'CA',),),),
  'data-check-positiv-bc-cc' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('BC', 'CC',),),),
  'data-check-positiv-bm-cm' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('BM', 'CM',),),),
  'data-check-positiv-br-cr' => array('func' => 'data-check-positiv', 'opt' => array('items' => array('BR', 'CR',),),),


  'data-calcul-210-cb-bb' => array('func' => 'data-calcul-210', 'opt' => array('results' => array('CB',), 'operands' => array('BB',),),),
  'data-calcul-210-cf-bf' => array('func' => 'data-calcul-210', 'opt' => array('results' => array('CF',), 'operands' => array('BF',),),),
  'data-calcul-090-ce-be' => array('func' => 'data-calcul-090', 'opt' => array('results' => array('CE',), 'operands' => array('BE',),),),
  'data-calcul-800-cj-bj' => array('func' => 'data-calcul-800', 'opt' => array('results' => array('CJ',), 'operands' => array('BJ',),),),
  'data-calcul-1300-ck-bk' => array('func' => 'data-calcul-1300', 'opt' => array('results' => array('CK',), 'operands' => array('BK',),),),
  'data-calcul-105-cp-bp' => array('func' => 'data-calcul-105', 'opt' => array('results' => array('CP',), 'operands' => array('BP',),),),
  'data-calcul-175-cq-bq' => array('func' => 'data-calcul-175', 'opt' => array('results' => array('CQ',), 'operands' => array('BQ',),),),

  'copy-value-bn' => array('function' => 'copy-value', 'args' => array('target' => 'tva3310ca3_FD')),
  'copy-value-cn' => array('function' => 'copy-value', 'args' => array('target' => 'tva3310ca3_GD')),
  'copy-value-hb' => array('function' => 'copy-value', 'args' => array('target' => 'tva3310ca3_KB')),


);

$fields = array(
  'comment_part' => array('type' => 'hidden', 'length' => 512,),

);

  
$form["tva3310a"] = array(
  'DA' =>
  array(
    'type' => 'comments',
    'length' => 2560,
    'operations' => array($operations['data-check-need-and-or-da-db']),
  ),
  'DA1' => $fields['comment_part'],
  'DA2' => $fields['comment_part'],
  'DA3' => $fields['comment_part'],
  'DA4' => $fields['comment_part'],
  'DA5' => $fields['comment_part'],
  'DB' => array('required' => false,
                'type' => 'checkbox',
                'value' => '1',
                'operations' => array($operations['data-check-need-and-or-da-db']),
  ),
  'BA' => array('type' => 'number',
                'operations' => array($operations['data-addition-bn'],
                                      $operations['data-check-positiv-ba-ca']),
  ),
  'CA' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn'],
                                      $operations['data-check-positiv-ba-ca']),
  ),
  'BB' => array('type' => 'number',
                'operations' => array($operations['data-calcul-210-cb-bb'],
                                      $operations['data-addition-bn'],),
  ),
  'CB' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn']),
  ),
  'BC' => array('type' => 'number',
                'operations' => array($operations['data-addition-bn'],
                                      $operations['data-addition-bc-cc']),
  ),
  'CC' => array('type' => 'number',
                'operations' => array($operations['data-addition-bc-cc'],
                                      $operations['data-addition-cn']),
  ),
  'AE' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-bn'],),
  ),
  'AF' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-cn']),
  ),
  'BE' => array('type' => 'number',
                'operations' => array($operations['data-calcul-090-ce-be'],
                                      $operations['data-addition-bn']),
  ),
  'CE' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn']),
  ),
  'BF' => array('type' => 'number',
                'operations' => array($operations['data-calcul-210-cf-bf'],
                                      $operations['data-addition-bn'],),
  ),
  'CF' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn'],),
  ),
  'BJ' => array('type' => 'number',
                'operations' => array($operations['data-calcul-800-cj-bj'],
                                      $operations['data-addition-bn']),
  ),
  'CJ' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn'],),
  ),
  'BK' => array('type' => 'number',
                'operations' => array($operations['data-calcul-1300-ck-bk'],
                                      $operations['data-addition-bn'],),
  ),
  'CK' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn'],),
  ),
  'BM' => array('type' => 'number',
                'operations' => array($operations['data-addition-bn'],
                                      $operations['data-check-positiv-bm-cm']),
  ),
  'CM' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn'],
                                      $operations['data-check-positiv-bm-cm']),
  ),
  'BP' => array('type' => 'number',
                'operations' => array($operations['data-calcul-105-cp-bp'],
                                      $operations['data-addition-bn'],),
  ),
  'CP' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn'],),
  ),
  'BQ' => array('type' => 'number',
                'operations' => array($operations['data-calcul-175-cq-bq'],
                                      $operations['data-addition-bn'],),
  ),
  'CQ' => array('type' => 'number',
                'operations' => array($operations['data-addition-cn'],),
  ),
  'BR' => array('type' => 'number',
                'operations' => array($operations['data-addition-bn'],
                                      $operations['data-check-positiv-br-cr']),
  ),
  'CR' => array('type' => 'number',
                'operations' => array($operations['data-check-positiv-br-cr'],
                                      $operations['data-addition-cn']),
  ),
  'BN' => array('type' => 'number',
                'operations' => array($operations['copy-value-bn'])
  ),
  'CN' => array('type' => 'number',
                'operations' => array($operations['copy-value-cn'])
  ),
  'FA' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FB' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'HE' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FE' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FF' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FG' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'JD' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FJ' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'JB' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'JC' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'JE' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'HF' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FR' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KF' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FT' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KG' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'FV' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'HH' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'HI' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),  
  'KA' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KB' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KC' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KD' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KE' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['data-addition-hb'],),
  ),
  'HB' => array('type' => 'number',
                'readonly' => true,
                'operations' => array($operations['copy-value-hb']),
  ),
  'JA' => array(
    'type' => 'comments',
    'length' => 2560,    
  ),
  'JA1' => $fields['comment_part'],
  'JA2' => $fields['comment_part'],
  'JA3' => $fields['comment_part'],
  'JA4' => $fields['comment_part'],
  'JA5' => $fields['comment_part'],
  'KJ' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KL' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KS' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KN' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KO' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KP' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KQ' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KR' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KT' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
  'KU' => array('type' => 'number',
                'operations' => array($operations['data-addition-hb'],),
  ),
);
