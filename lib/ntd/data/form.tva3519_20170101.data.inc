<?php

$operations = array(
  'check_bic' => array('func' => 'data-check_bic'),
  'check_iban' => array('func' => 'data-check_iban'),
);

$form["tva3519_20170101"] = array(
  'AA1' => array('type' => 'alphabetic',
                 'length' => 11,
                 'operations' => array($operations['check_bic'])),
  'AA2' => array('type' => 'alphabetic',
                 'length' => 27,
                 'operations' => array($operations['check_iban'])),
  'AA3' => array('type' => 'alphabetic', 'length' => 35,),
  'AA4' => array('type' => 'alphabetic', 'length' => 35,),
  'DC1' => array('type' => 'alphabetic', 'length' => 35),
  'DC10' => array('type' => 'alphabetic', 'length' => 512,),
  'DC2' => array('type' => 'alphabetic', 'length' => 35,),
  'DC3' => array('type' => 'alphabetic', 'length' => 35,),
  'DC4' => array('type' => 'alphabetic', 'length' => 35,),
  'DC5' => array('type' => 'alphabetic', 'length' => 35,),
  'DC6' => array('type' => 'alphabetic', 'length' => 35,),
  'DC7' => array('type' => 'alphabetic', 'length' => 5,),
  'DC8' => array('type' => 'select', 'length' => 3, 'options' => Country::collect(array('order' => array('name' => 'ASC')))->asHash('iso3_code', 'name'),),
  'DC9' => array('type' => 'alphabetic', 'length' => 512,),
  'DD' => array('type' => 'checkbox', 'value' => '1',),
  'DE' => array('type' => 'checkbox', 'value' => '1',),
  'DF' => array('type' => 'checkbox', 'value' => '1'),
  'DG1' => array('type' => 'alphabetic', 'length' => 38,),
  'DG2' => array('type' => 'alphabetic', 'length' => 38,),
  'DG3' => array('type' => 'alphabetic', 'length' => 38,),
  'DG4' => array('type' => 'alphabetic', 'length' => 38,),
  'DH' => array('type' => 'number', 'length' => 15,),
  'DI' => array('type' => 'checkbox'),
  'DJ' => array('type' => 'checkbox', 'operations' => array()),
  'DK' => array('type' => 'checkbox', 'value' => '1',),
  'DL' => array('type' => 'date-ssaammjj',),
  'DM' => array('type' => 'date-ssaammjj'),
  'DN' => array('type' => 'number'),
  'FJ' => array('type' => 'comments', 'length' => 2560,),
  'FJ1' => array('type' => 'hidden', 'length' => 512,),
  'FJ2' => array('type' => 'hidden', 'length' => 512,),
  'FJ3' => array('type' => 'hidden', 'length' => 512,),
  'FJ4' => array('type' => 'hidden', 'length' => 512,),
  'FJ5' => array('type' => 'hidden', 'length' => 512,),
  'FK' => array('type' => 'checkbox', 'value' => '1',),
  'FL' => array('type' => 'checkbox', 'value' => '1',),
);

foreach($form["tva3519_20170101"] as $fieldname => $data) {
  $form["tva3519_20170101"][$fieldname]['operations'][]['assert'] = 'tva3519_20170101';
}
