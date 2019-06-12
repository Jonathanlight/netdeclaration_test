<?php

$form["is2571_2016"] = array(
  'CA' => array('type' => 'number', 'length' => 15,),
  'CC' => array('type' => 'number', 'length' => 15,),
  'CD' => array('type' => 'number', 'length' => 15,),
  'CE' => array('type' => 'number', 'length' => 15,),
  'CF' => array('type' => 'number', 'length' => 15,),
  'CG' => array('type' => 'number', 'length' => 15,),
  'CH' => array('type' => 'number',),
  'DA' => array('type' => 'checkbox', 'value' => '1'),
  'DB' => array('type' => 'checkbox', 'value' => '1'),
  'FA' => array('type' => 'number'),
  'FB' => array('type' => 'number', 'length' => 15,),
  'FC' => array('type' => 'number', 'length' => 15,),
  'FD' => array('type' => 'number', 'length' => 15,),
  'FE' => array('type' => 'number', 'length' => 15,),
  'FF' => array('type' => 'number', 'length' => 15,),
  'FG' => array('type' => 'number', 'length' => 15,),
  'FH' => array('type' => 'number', 'length' => 15,),
  'FK' => array('type' => 'select', 'options' => array(
    ''    => '',
    'TVA' => 'TVA',
    'TS'  => 'Taxe sur les salaires',
    'TVS' => 'Taxe sur les véhicules de sociétés'
  )),
  'FM' => array('type' => 'date-ssaammjj'),
);

foreach ($form["is2571_2016"] as $fieldname => $data) {
  $form["is2571_2016"][$fieldname]['operations'][]['assert'] = 'is2571_2016';
}
