<?php

$form["is2571_2015"] = array(
  'FA' => array('type' => 'number'),
  'FB' => array('type' => 'number'),
  'FC' => array('type' => 'number'),
  'FD' => array('type' => 'number'),
  'FE' => array('type' => 'number'),
  'FF' => array('type' => 'number'),
  'FG' => array('type' => 'number'),
  'FH' => array('type' => 'number'),
  'FK' => array('type' => 'select', 'options' => array(
    '' => '',
    'TVA' => 'TVA',
    'TS' => 'Taxe sur les salaires',
    'TVS' => 'Taxe sur les véhicules de sociétés'
  )),
  'FM' => array('type' => 'date-ssaammjj'),
  'CA' => array('type' => 'number',),
  'DA' => array('type' => 'checkbox', 'value' => '1'),
  'CC' => array('type' => 'number',),
  'CD' => array('type' => 'number',),
  'CF' => array('type' => 'number',),
  'DB' => array('type' => 'checkbox', 'value' => '1'),
  'CE' => array('type' => 'number',),
  'CG' => array('type' => 'number',),
  'CH' => array('type' => 'number',)
);

foreach ($form["is2571_2015"] as $fieldname => $data) {
  $form["is2571_2015"][$fieldname]['operations'][]['assert'] = 'is2571_2015';
}
