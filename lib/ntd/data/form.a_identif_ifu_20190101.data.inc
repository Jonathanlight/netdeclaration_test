<?php


$form["a_identif_ifu_20190101"] = array(
    // A..
    'AA01'  => array('type' => 'text', 'length' => 14, 'required' => true),
    'AA02'  => array('type' => 'text', 'length' => 34, 'required' => true),
    'AA03'  => array('type' => 'text', 'length' => 15),
    'AA05'  => array('type' => 'text', 'length' => 32, 'required' => true),
    'AA06'  => array('type' => 'text', 'length' => 32),
    'AA08'  => array('type' => 'text', 'length' => 26, 'required' => true),
    'AA09'  => array('type' => 'text', 'length' => 5, 'required' => true),
    'AA11'  => array('required' => true, 'type' => 'text', 'length' => 35),
    'AA12'  => array('required' => true, 'type' => 'number', 'length' => 10),
    'AA13'  => array('required' => true, 'type' => 'text', 'length' => 60),
    'AA14' =>  array('required' => true,
                     'type' => 'select',
                     'options' => ''),
    'AA15'  => array('type' => 'text', 'length' => 15, 'required' => true),
    'AA16'  => array('type' => 'number', 'length' => 5, 'required' => true),
    'AA17'  => array('type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'suffixe'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),

    // B..
    'BA' => array('required' => true,
                    'type' => 'date-ssaa'),

    'BB' => array('required' => true,
                    'type' => 'date-ssaammjj'),

    'BC' => array('required' => true,
                    'type' => 'date-ssaammjj'),

    'BD' => array('required' => true,
                    'type' => 'date-ssaammjj'),

    // C..
    'CB'  => array('type' => 'number', 'length' => 14),
    'CC'  => array('type' => 'select',
                   'required' => true,
                   'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'cj'),
                   'order' => array('id' => 'asc')))->asHash('value', 'name')),

    // D..
    'DA'  => array('required' => true,
                    'type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'tde'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),
);

foreach ($form["a_identif_ifu_20190101"] as $fieldname => $data) {
    $form["a_identif_ifu_20190101"][$fieldname]['operations'][]['assert'] = 'a_identif_ifu_20190101';
}
