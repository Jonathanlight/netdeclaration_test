<?php

$form["cvae1329ac_20150101"] = array(
  'AA' => array('type' => 'number',),
  'AB' => array('type' => 'number',),
  'AD' => array('type' => 'number',),
  'AC' => array('type' => 'pourcentage',),
  'BA' => array('type' => 'number',),
  'BB' => array('type' => 'number',),
  'BC' => array('type' => 'checkbox', 'value' => '1',),
  'CA' => array('type' => 'number',),
  'CB' => array('type' => 'number',),
  'DA' => array('type' => 'number',),
  'DB' => array('type' => 'number',),
  'EA' => array('type' => 'number',),
  'EB' => array('type' => 'number',),
  'EC' => array('type' => 'number',),
  'ED' => array('type' => 'number',),
  'GA' => array('type' => 'checkbox', 'value' => '1'),
  'GB' => array('type' => 'number',),
  'HA' => array('type' => 'number',),
  'KA' => array('type' => 'number',),
);

foreach($form["cvae1329ac_20150101"] as $fieldname => $data) {
  $form["cvae1329ac_20150101"][$fieldname]['operations'][]['assert'] = 'cvae1329ac_20150101';
}