<?php


$form["tva3310ter_20170101"] = array(
  'AA'  => array('type' => 'comments', 'length' => 2560),
  'AA1' => array('type' => 'hidden', 'length' => 512),
  'AA2' => array('type' => 'hidden', 'length' => 512),
  'AA3' => array('type' => 'hidden', 'length' => 512),
  'AA4' => array('type' => 'hidden', 'length' => 512),
  'AA5' => array('type' => 'hidden', 'length' => 512),
  'AB'  => array('type' => 'float', 'value' => 0),
  'AC'  => array('type' => 'checkbox', 'value' => '1'),
  'BM'  => array('type' => 'alphabetic'),
  'CM'  => array('type' => 'pourcentage'),
  'DL'  => array('type' => 'number', 'show-form' => 'tva3310CA3_20170101'),
  'DM'  => array('type' => 'number'),
  'EL'  => array('type' => 'number', 'show-form' => 'tva3310CA3_20170101'),
  'EM'  => array('type' => 'number'),
  'FL'  => array('type' => 'number', 'show-form' => 'tva3310CA3_20170101'),
  'FM'  => array('type' => 'number'),
  'GL'  => array('type' => 'number'),
  'GM'  => array('type' => 'number'),
  'HL'  => array('type' => 'number'),
  'HM'  => array('type' => 'number'),
  'JL'  => array('type' => 'number', 'show-form' => 'tva3310CA3_20170101'),
  'JM'  => array('type' => 'number'),
  'KL'  => array('type' => 'number'),
  'KM'  => array('type' => 'number'),
  'LL'  => array('type' => 'number'),
  'LM'  => array('type' => 'number'),
  'ML'  => array('type' => 'number', 'show-form' => 'tva3310CA3_20170101'),
  'MM'  => array('type' => 'number'),
  'NL'  => array('type' => 'number'),
  'NM'  => array('type' => 'number'),
  'PL'  => array('type' => 'number', 'show-form' => 'tva3310CA3_20170101'),
  'PM'  => array('type' => 'number'),
  'QL'  => array('type' => 'number'),
  'QM'  => array('type' => 'number'),
  'QN'  => array('type' => 'number'),
  'RL'  => array('type' => 'number'),
  'RM'  => array('type' => 'number'),
  'RN'  => array('type' => 'number'),
);


foreach ($form["tva3310ter_20170101"] as $fieldname => $data) {
  $form["tva3310ter_20170101"][$fieldname]['operations'][]['assert'] = 'tva3310ter_20170101';
}
