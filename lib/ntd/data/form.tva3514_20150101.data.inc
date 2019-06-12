<?php

$form["tva3514_20150101"] = array(
  'HA' => array('type' => 'number',),
  'HB' => array('type' => 'number',),
  'HC' => array('type' => 'number',),
  'DE' => array('type' => 'checkbox', 'value' => '1',),
  'IA' => array('type' => 'number',),
  'IB' => array('type' => 'number',),
  'IC' => array('type' => 'number'),
  'ID' => array('type' => 'number',),
  'CC' => array('type' => 'checkbox', 'value' => '1'),
  'CA' => array('type' => 'checkbox',),
  'CB' => array('type' => 'comments', 'length' => 2560),
  'CB1' => array('type' => 'comments-part', 'length' => 512,),
  'CB2' => array('type' => 'comments-part', 'length' => 512,),
  'CB3' => array('type' => 'comments-part', 'length' => 512,),
  'CB4' => array('type' => 'comments-part', 'length' => 512,),
  'CB5' => array('type' => 'comments-part', 'length' => 512,)
);

foreach($form["tva3514_20150101"] as $fieldname => $data) {
  $form["tva3514_20150101"][$fieldname]['operations'][]['assert'] = 'tva3514_20150101';
}