<?php


$form["das2tv_20190101"] = array(
    // A..
    'AD' => array('type' => 'number', 'length' => 14, 'required' => false),
    'AA14' => array('required' => false,
                     'type' => 'select',
                     'options' => ''),
    'AE02' => array('type' => 'text', 'length' => 30),
    'AE03' => array('type' => 'text', 'length' => 20),
    'AF01' => array('type' => 'number', 'length' => 14),
    'AF02' => array('type' => 'text', 'length' => 35),
    'AF03' => array('type' => 'text', 'length' => 15),
    'AG05' => array('type' => 'text', 'length' => 32, 'required' => false),
    'AG06' => array('type' => 'text', 'length' => 32),
    'AG08' => array('type' => 'text', 'length' => 26, 'required' => false),
    'AG09' => array('type' => 'number', 'length' => 5, 'required' => false),
    'AG14_1' => array('type' => 'select',
                    'options' => array('' => '-')),
    'AG14_2' => array('text', 'length' => 5),
    'AG15' => array('type' => 'text', 'length' => 15, 'required' => false),
    'AG16' => array('type' => 'number', 'length' => 5, 'required' => false),
    'AG17'  => array('type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'suffixe'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),
    'AH' => array('type' => 'text', 'length' => 30),

    // B..
    'BA' => array('type' => 'number', 'length' => 10),
    'BB' => array('type' => 'number', 'length' => 10),
    'BC' => array('type' => 'number', 'length' => 10),
    'BD' => array('type' => 'number', 'length' => 10),
    'BE' => array('type' => 'number', 'length' => 10),

    // C..
    'CA'  => array('type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'TNR'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),

    'CB'  => array( 'type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'TIR'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),

    'CC'  => array( 'type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'TAN'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),

    'CD'  => array( 'type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'TRS'),
                    'order' => array('id' => 'asc')))->asHash('value', 'name')),
    'ZZ1'  => array('type' => 'select',
                    'options' => array(
                        '1' => 'Non',
                        '0' => 'Oui'
                    )),
);

foreach ($form["das2tv_20190101"] as $fieldname => $data) {
    $form["das2tv_20190101"][$fieldname]['operations'][]['assert'] = 'das2tv_20190101';
}
