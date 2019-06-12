<?php

$form["tva3514_20160101"] = array(
  'CA'  => array('type' => 'checkbox'),
  'CB'  => array('type' => 'comments', 'length' => 2560),
  'CB1' => array('type' => 'comments-part', 'length' => 512),
  'CB2' => array('type' => 'comments-part', 'length' => 512),
  'CB3' => array('type' => 'comments-part', 'length' => 512),
  'CB4' => array('type' => 'comments-part', 'length' => 512),
  'CB5' => array('type' => 'comments-part', 'length' => 512),
  'CC'  => array('type' => 'checkbox', 'value' => '1'),
  'DE'  => array('type' => 'checkbox', 'value' => '1'),
  'HA'  => array('type' => 'number', 'length' => 15),
  'HB'  => array('type' => 'number', 'length' => 15),
  'HC'  => array('type' => 'number'),
  'IA'  => array('type' => 'number', 'length' => 15),
  'IB'  => array('type' => 'number', 'length' => 15),
  'IC'  => array('type' => 'number'),
  'ID'  => array('type' => 'number', 'length' => 15),
);

foreach($form["tva3514_20160101"] as $fieldname => $data) {
  $form["tva3514_20160101"][$fieldname]['operations'][]['assert'] = 'tva3514_20160101';
}