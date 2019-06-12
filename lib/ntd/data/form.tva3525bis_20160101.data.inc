<?php

$form["tva3525bis_20160101"] = array(
  'AC' => array('type' => 'checkbox',),
  'AD' => array('type' => 'checkbox', 'value' => '1'),
  'BB' => array('type' => 'number', 'length' => 15),
  'BC' => array('type' => 'number', 'length' => 15),
  'BD' => array('type' => 'number'),
  'BE' => array('type' => 'checkbox', 'value' => '1'),
  'DA' => array('type' => 'comments', 'length' => 2560,),
  'DA1' => array('type' => 'hidden', 'length' => 512,),
  'DA2' => array('type' => 'hidden', 'length' => 512,),
  'DA3' => array('type' => 'hidden', 'length' => 512,),
  'DA4' => array('type' => 'hidden', 'length' => 512,),
  'DA5' => array('type' => 'hidden', 'length' => 512,),
);

foreach ($form["tva3525bis_20160101"] as $fieldname => $data) {
  $form["tva3525bis_20160101"][$fieldname]['operations'][]['assert'] = 'tva3525bis_20160101';
}
