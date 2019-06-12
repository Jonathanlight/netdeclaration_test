<?php

$form["das2t_20190101"] = array(

    // A..
    'AA01' => array('type' => 'number', 'length' => 14, 'required' => true),
    'AA02'  => array('type' => 'text', 'length' => 35, 'required' => true),
    'AA03'  => array('type' => 'text', 'length' => 15),
    'AA05' => array('type' => 'text', 'length' => 32, 'required' => true),
    'AA06' => array('type' => 'text', 'length' => 32),
    'AA08' => array('type' => 'text', 'length' => 26, 'required' => true),
    'AA09' => array('type' => 'number', 'length' => 5, 'required' => true),
    'AA14' =>  array('required' => true,
                    'type' => 'select',
                    'options' => ''),
    'AA15' => array('type' => 'text', 'length' => 32, 'required' => true),
    'AA16' => array('type' => 'number', 'length' => 5, 'required' => true),
    'AA17'  => array('type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'suffixe'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),
    'AB' => array('type' => 'number', 'length' => 5),
    'AC' => array('type' => 'number', 'length' => 40),
    'AD' => array('type' => 'date-ssmmjj'),
    'AE' => array('type' => 'number', 'length' => 14),

    'UA'  => array('type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'TNR'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),
    // T..
    'TA' => array('type' => 'number', 'length' => 12),
    'TB' => array('type' => 'number', 'length' => 12),
    'TC' => array('type' => 'number', 'length' => 12),
    'TD' => array('type' => 'number', 'length' => 12),
);

foreach ($form["das2t_20190101"] as $fieldname => $data) {
    $form["das2t_20190101"][$fieldname]['operations'][]['assert'] = 'das2t_20190101';
}
