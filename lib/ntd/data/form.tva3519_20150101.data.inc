<?php

$form["tva3519_20150101"] = array(
  'DC1' => array('type' => 'alphabetic', 'length' => 35),
  'DC2' => array('type' => 'alphabetic', 'length' => 35,),
  'DC3' => array('type' => 'alphabetic', 'length' => 35,),
  'DC4' => array('type' => 'alphabetic', 'length' => 35,),
  'DC5' => array('type' => 'alphabetic', 'length' => 35,),
  'DC6' => array('type' => 'alphabetic', 'length' => 35,),
  'DC7' => array('type' => 'alphabetic', 'length' => 5,),
  'DC8' => array('type' => 'select', 'length' => 3, 'options' => Country::collect(array('order' => array('name' => 'ASC')))->asHash('iso3_code', 'name'),),
  'DC9' => array('type' => 'alphabetic', 'length' => 512,),
  'DC10' => array('type' => 'alphabetic', 'length' => 512,),
  'DD' => array('type' => 'checkbox', 'value' => '1',),
  'DE' => array('type' => 'checkbox', 'value' => '1',),
  'DF' => array('type' => 'checkbox', 'value' => '1'),
  'DG1' => array('type' => 'alphabetic', 'length' => 35,),
  'DG2' => array('type' => 'alphabetic', 'length' => 35,),
  'DG3' => array('type' => 'alphabetic', 'length' => 35,),
  'DG4' => array('type' => 'alphabetic', 'length' => 35,),
  'DH' => array('type' => 'number',),
  'DN' => array('type' => 'number',),
  'FK' => array('type' => 'checkbox', 'value' => '1',),
  'FL' => array('type' => 'checkbox', 'value' => '1',),
  'AA1' => array('type' => 'number', 'length' => 15,),
  'AA2' => array('type' => 'number', 'length' => 27,),
  'AA3' => array('type' => 'alphabetic', 'length' => 35,),
  'AA4' => array('type' => 'alphabetic', 'length' => 35,),
  'DI' => array('type' => 'checkbox'),
  'DL' => array('type' => 'date-ssaammjj',),
  'DJ' => array('type' => 'checkbox', 'operations' => array()),
  'DM' => array('type' => 'date-ssaammjj'),
  'DK' => array('type' => 'checkbox', 'value' => '1',),
  'FJ' => array('type' => 'comments', 'length' => 2560,),
  'FJ1' => array('type' => 'hidden', 'length' => 512,),
  'FJ2' => array('type' => 'hidden', 'length' => 512,),
  'FJ3' => array('type' => 'hidden', 'length' => 512,),
  'FJ4' => array('type' => 'hidden', 'length' => 512,),
  'FJ5' => array('type' => 'hidden', 'length' => 512,),
);

foreach($form["tva3519_20150101"] as $fieldname => $data) {
  $form["tva3519_20150101"][$fieldname]['operations'][]['assert'] = 'tva3519_20150101';
}
