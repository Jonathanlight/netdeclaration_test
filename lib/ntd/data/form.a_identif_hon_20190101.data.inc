<?php


$form["a_identif_hon_20190101"] = array(
    // A..
    'AA01' => array('type' => 'text', 'length' => 14, 'required' => true),
    'AA02' => array('type' => 'text', 'length' => 35),
    'AA03' => array('type' => 'text', 'length' => 15),
    'AA05' => array('type' => 'text', 'length' => 32),
    'AA06' => array('type' => 'text', 'length' => 32),
    'AA08' => array('type' => 'text', 'length' => 26),
    'AA09' => array('type' => 'number', 'length' => 5),
    'AA11' => array('type' => 'text', 'length' => 35),
    'AA12' => array('type' => 'number', 'length' => 10),
    'AA13' => array('type' => 'text', 'length' => 60),
    'AA16' => array('type' => 'number', 'length' => 5),
    'AA17' => array(
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array(
            'filters' => array('code_table' => 'suffixe'),
            'order' => array('id' => 'asc')
        ))->asHash('value', 'name')
    ),
    'AB01' => array('type' => 'number', 'length' => 14, 'required' => true),
    'AB05' => array('type' => 'text', 'length' => 32),
    'AB06' => array('type' => 'text', 'length' => 32),
    'AB08' => array('type' => 'text', 'length' => 26),
    'AB09' => array('type' => 'number', 'length' => 5),
    'AB14' => array(
        'type' => 'select',
        'options' => array(),
    ),
    'AB15' => array('type' => 'text', 'length' => 25),
    'AA14' => array(
        'type' => 'select',
        'options' => array(),
    ),
    'AA15' => array('type' => 'text', 'length' => 25),
    'AB16' => array('type' => 'number', 'length' => 5),
    'AB17' => array(
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array(
            'filters' => array('code_table' => 'suffixe'),
            'order' => array('id' => 'asc')
        ))->asHash('value', 'name')
    ),

    // B..
    'BA' => array(
        'required' => true,
        'type' => 'date-ssaa'
    ),

    'BD' => array(
        'required' => true,
        'type' => 'date-ssaammjj'
    ),

    'BB' => array(
        'required' => true,
        'type' => 'date-ssaammjj'
    ),

    'BC' => array(
        'required' => true,
        'type' => 'date-ssaammjj'
    ),

    // C..
    'CA' => array('type' => 'number', 'length' => 5, 'required' => true),
    'CB' => array('type' => 'number', 'length' => 14),
);


foreach ($form["a_identif_hon_20190101"] as $fieldname => $data) {
    $form["a_identif_hon_20190101"][$fieldname]['operations'][]['assert'] = 'a_identif_hon_20190101';
}
