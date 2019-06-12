<?php

$form["is2572_2015"] = array(
  'PN' => array('type' => 'number',),
  'PT' => array('type' => 'number',),
  'PV' => array('type' => 'number',),
  'AD' => array('type' => 'number',),
  'PR' => array('type' => 'number',),
  'PQ' => array('type' => 'number',),
  'PU' => array('type' => 'number',),
  'PW' => array('type' => 'number',),
  'BD' => array('type' => 'number',),
  'PS' => array('type' => 'number',),
  'CA' => array('type' => 'number',),
  'DA' => array('type' => 'number',),
  'EA' => array('type' => 'number',),
  'EB' => array('type' => 'number'),
  'TA' => array('type' => 'number',),
  'TB' => array('type' => 'number',),
  'GC' => array('type' => 'number',),
  'GD' => array('type' => 'number',),
  'GE' => array('type' => 'number'),
  'PM' => array('type' => 'number'),
  'IA' => array('type' => 'number'),
  'JA' => array('type' => 'number'),
  'KA' => array('type' => 'number'),
  'KB' => array('type' => 'number'),
  'KC' => array('type' => 'number'),
  'LA' => array('type' => 'number'),
  'LB' => array('type' => 'number'),
  'LC' => array('type' => 'number'),
  'LD' => array('type' => 'number'),
  'LE' => array('type' => 'number'),
  'LF' => array('type' => 'number'),
  'MA' => array('type' => 'number'),
  'MB' => array('type' => 'number'),
  'MC' => array('type' => 'number'),
  'MD' => array('type' => 'number'),
  'ME' => array('type' => 'number'),
  'NA' => array('type' => 'number'),
  'NB' => array('type' => 'number'),
  'NC' => array('type' => 'number'),
  'ND' => array('type' => 'number'),
  'NE' => array('type' => 'number'),
  'NF' => array('type' => 'number'),
  'NG' => array('type' => 'number'),
  'NH' => array('type' => 'number'),
  'NJ' => array('type' => 'number'),
  'NK' => array('type' => 'number'),
  'NL' => array('type' => 'number'),
  'NM' => array('type' => 'number'),
  'NN' => array('type' => 'number'),
  'NO' => array('type' => 'number'),
  'OA' => array('type' => 'number'),
  'OB' => array('type' => 'number'),
  'OC' => array('type' => 'number'),
  'OD' => array('type' => 'number'),
  'RD' => array('type' => 'alphabetic'), // todo
  'RE' => array('type' => 'number'),
  'RF' => array('type' => 'number'),

  'RA' => array('type' => 'number'),
  'RB' => array('type' => 'number'),
  'RC' => array('type' => 'number'),
  'RG' => array('type' => 'number'),
  'RH' => array('type' => 'number'),
  'RJ' => array('type' => 'number'),
  'RK' => array('type' => 'number'),
  'RL' => array('type' => 'number'),
  'RM' => array('type' => 'number'),
  'RN' => array('type' => 'number'),
  'RR' => array('type' => 'alphabetic'),

  'RP' => array('type' => 'number'),
  'RS' => array('type' => 'number'),
  'RT' => array('type' => 'number'),
  'RU' => array('type' => 'number'),
  'RV' => array('type' => 'number'),
  'RX' => array('type' => 'number'),
  'RY' => array('type' => 'number'),
  'RW' => array('type' => 'number'),
  'RZ' => array('type' => 'number'),
  'PA' => array('type' => 'number'),
  'PB' => array('type' => 'number'),
  'PC' => array('type' => 'number'),
  'PD' => array('type' => 'number'),

  'PE' => array('type' => 'select', 'options' => array(
    '' => '-',
    'TVA' => 'TVA',
    'TS' => 'Taxe sur les salaires',
    'TA' => 'Taxe d\'apprentissage',
    'FPC' => 'Formation Professionnelle continue',
    'PEC' => 'Participation des employeurs à l\'effort de construction',
    'TVS' => 'Taxe sur les véhicules de sociétés',
  )),
  'PF' => array('type' => 'date-ssaammjj'),
  'PG' => array('type' => 'number'),
  'PH' => array('type' => 'select', 'options' => array(
    '' => '-',
    'TVA' => 'TVA',
    'TS' => 'Taxe sur les salaires',
    'TVS' => 'Taxe sur les véhicules de sociétés',

  )),
  'PJ' => array('type' => 'date-ssaammjj'),
  'PK' => array('type' => 'number'),
  'PL' => array('type' => 'number'),

);


foreach ($form["is2572_2015"] as $fieldname => $data) {
  $form["is2572_2015"][$fieldname]['operations'][]['assert'] = 'is2572_2015';
}