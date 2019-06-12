<?php

$operations = array(
  'check_bic' => array('func' => 'data-check_bic'),
  'check_iban' => array('func' => 'data-check_iban'),
  'must_be_strictly_positive' => array('func' => 'data-must_be_strictly_positive'),
);


$form["tva3517ddr_20160101"] = array(

  'AA' => array('type' => 'number',),
  'AB' => array('type' => 'number', 'length' => 15,),
  'AC' => array('type' => 'number'),
  'AD' => array('type' => 'number', 'length' => 15,),
  'AE' => array('type' => 'number',),
  'AF1' => array('length' => 35),
  'AF2' => array('length' => 35,),
  'AG' => array('type' => 'number',
                'operations' => array($operations['must_be_strictly_positive'])
  ),
  'AH' => array('type' => 'checkbox', 'value' => '1',),
  'AJ' => array('type' => 'checkbox', 'value' => '1',),
  'AK1' => array('type' => 'alphabetic',
                 'length' => 27,
                 'operations' => array($operations['check_iban']),
  ),
  'AK2' => array('type' => 'alphabetic',
                 'length' => 11,
                 'operations' => array($operations['check_bic']),
  ),
  'AK3' => array('type' => '', 'length' => 35,),
  'AK4' => array('type' => '', 'length' => 35,),
  'AF3' => array('type' => '', 'length' => 35,),
  'AL' => array('type' => 'comments', 'length' => 2560, 'rows' => 5),
  'AL1' => array('type' => 'hidden', 'length' => 512,),
  'AL2' => array('type' => 'hidden', 'length' => 512,),
  'AL3' => array('type' => 'hidden', 'length' => 512,),
  'AL4' => array('type' => 'hidden', 'length' => 512,),
  'AL5' => array('type' => 'hidden', 'length' => 512,),
  'BB' => array('type' => 'checkbox', 'value' => '1'),
  'BA' => array('type' => 'date-ssaammjj'),
);

foreach($form["tva3517ddr_20160101"] as $fieldname => $data) {
  $form["tva3517ddr_20160101"][$fieldname]['operations'][]['assert'] = 'tva3517ddr_20160101';
}
