<?php


$form["ifu2561_20190101"] = array(
    // A..
    'AA01' => array('type' => 'number', 'length' => 13),
    'AA03' => array('type' => 'number', 'length' => 5),
    'AA02' => array('type' => 'number', 'length' => 5),
    'AB' => array(
        'required' => true,
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array(
            'filters' => array('code_table' => 'TNC'),
            'order' => array('id' => 'asc')
        ))->asHash('value', 'name')
    ),
    'AC' => array(
        'required' => true,
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array(
            'filters' => array('code_table' => 'TTC_2561'),

            'order' => array('id' => 'asc')
        ))->asHash('value', 'name')
    ),
    'AD' => array(
        'required' => true,
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array(
            'filters' => array('code_table' => 'TBE_2561'),
            'order' => array('id' => 'asc')
        ))->asHash('value', 'name')
    ),
    'AE02' => array('type' => 'text', 'length' => 30),
    'AE03' => array('type' => 'text', 'length' => 20),
    'AE04' => array('type' => 'text', 'length' => 30),
    'AE09' => array('type' => 'select',
                    'options' => array('' => '') + Dicoedi::collect(array(
                        'filters' => array('code_table' => 'code_postal'),
                        'order' => array('value' => 'asc')
                    ))->asHash('value', 'name')
    ),
    'AE14_1' => array('type' => 'select',
                    'options' => array('' => '')),
    'AE14_2' => array('text', 'length' => 5),
    'AE15' => array('type' => 'text', 'length' => 26),
    'AF01' => array('type' => 'text', 'length' => 15),
    'AF02' => array('type' => 'text', 'length' => 35),
    'AG05' => array('required' => true, 'type' => 'text', 'length' => 32),
    'AG06' => array('type' => 'text', 'length' => 32),
    'AG08' => array('required' => true, 'type' => 'text', 'length' => 26),
    'AG09' => array('required' => true, 'type' => 'number', 'length' => 5),
    'AG14_1' =>  array('type' => 'select',
                     'options' => ''),
    'AG14_2' => array('text', 'length' => 5),
    'AG15' => array('type' => 'text', 'length' => 26),
    'AG16' => array('required' => true, 'type' => 'number', 'length' => 4),
    'AG17'  => array(
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array('filters' => array('code_table' => 'suffixe'),
                'order' => array('id' => 'asc')))->asHash('value', 'name')),
    'AH' => array(
        'type' => 'date-ssaammjj'
    ),
    'AJ' => array(
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array(
            'filters' => array('code_table' => 'TSE'),
            'order' => array('id' => 'asc')
        ))->asHash('value', 'name')
    ),
    'AK' => array('type' => 'number', 'length' => 30),
    'AL' => array(
        'type' => 'select',
        'options' => array('' => '') + Dicoedi::collect(array(
            'filters' => array('code_table' => 'cj'),
            'order' => array('id' => 'asc')
        ))->asHash('value', 'name')
    ),
    'AM' => array('type' => 'number', 'length' => 14),
    'AN' => array(
        'required' => true,
        'type' => 'date-ssmmjj'
    ),
    'AP' => array(
        'required' => true,
        'type' => 'date-ssmmjj'
    ),

    // B..
    'BA' => array('type' => 'number', 'length' => 10),
    'BB' => array('type' => 'number', 'length' => 10),
    'BC' => array('type' => 'number', 'length' => 10),
    'BE' => array('type' => 'number', 'length' => 10),
    'BF' => array('type' => 'number', 'length' => 10),
    'BG' => array('type' => 'number', 'length' => 10),
    'BH' => array('type' => 'number', 'length' => 10),
    'BJ' => array('type' => 'number', 'length' => 15),
    'BK' => array('type' => 'number', 'length' => 15),
    'BN' => array('type' => 'number', 'length' => 10),
    'BP' => array('type' => 'number', 'length' => 10),
    'BR' => array('type' => 'number', 'length' => 10),
    'BS' => array('type' => 'number', 'length' => 10),
    'BT' => array('type' => 'number', 'length' => 10),
    'BU' => array('type' => 'number', 'length' => 15),
    'BV' => array('type' => 'number', 'length' => 10),

    // C..
    'CA' => array('type' => 'number', 'length' => 10),
    'CB' => array('type' => 'number', 'length' => 10),
    'CC' => array('type' => 'number', 'length' => 10),
    'CD' => array('type' => 'number', 'length' => 10),
    'CF' => array('type' => 'number', 'length' => 15),
    'CG' => array('type' => 'number', 'length' => 15),
    'CH' => array('type' => 'number', 'length' => 10),
    'CJ' => array('type' => 'number', 'length' => 15),
    'CK' => array('type' => 'number', 'length' => 15),
    'CL' => array('type' => 'number', 'length' => 15),
    'CM' => array('type' => 'number', 'length' => 15),
    'CN' => array('type' => 'number', 'length' => 15),
    'CP' => array('type' => 'number', 'length' => 15),
    'CR' => array('type' => 'number', 'length' => 10),
    'CS' => array('type' => 'number', 'length' => 15),
    'CT' => array('type' => 'number', 'length' => 10),
    'CU' => array('type' => 'number', 'length' => 10),
    'CV' => array('type' => 'number', 'length' => 10),
    'CW' => array('type' => 'number', 'length' => 10),
    'CX' => array('type' => 'number', 'length' => 10),
    'CY' => array('type' => 'number', 'length' => 10),
    'CZ' => array('type' => 'number', 'length' => 10),

    // D..
    'DA' => array('type' => 'number', 'length' => 10),
    'DB' => array('type' => 'number', 'length' => 10),
    'DC' => array('type' => 'number', 'length' => 15),
    'DD' => array('type' => 'number', 'length' => 15),
    'DE' => array(
        'type' => 'date-ssaammjj'
    ),
    'DF' => array(
        'type' => 'date-ssaammjj'
    ),
    'DG' => array(
        'type' => 'date-ssaammjj'
    ),
    'DH' => array(
        'type' => 'date-ssmmjj'
    ),
    'DI' => array('type' => 'number', 'length' => 15),
    'DJ' => array(
        'type' => 'date-ssmmjj'
    ),
    'DK' => array('type' => 'number', 'length' => 10),
    'DL' => array(
        'required' => false,
        'type' => 'date-ssaammjj',
        'length' => 10
    ),
    'DM' => array('type' => 'number', 'length' => 10),
    'DN' => array('type' => 'number', 'length' => 10),
    'DP' => array('type' => 'number', 'length' => 10),

    // E..
    'EA' => array('type' => 'number', 'length' => 10),
    'EB' => array(
        'type' => 'date-ssaammjj',
        'length' => 10
    ),
    'EC' => array(
        'type' => 'date-ssaammjj',
        'length' => 10
    ),
    'ED' => array('type' => 'number', 'length' => 10),
    'EE' => array('type' => 'number', 'length' => 10),
    'EF' => array('type' => 'number', 'length' => 10),
    'EG' => array('type' => 'number', 'length' => 10),
    'EH' => array('type' => 'number', 'length' => 10),
    'EJ' => array('type' => 'number', 'length' => 10),
    'EK' => array('type' => 'number', 'length' => 10),
    'EL' => array(
        'type' => 'select',
        'options' => array_merge(array('-1' => ''), Dicoedi::collect(array(
            'filters' => array('code_table' => 'TEX'),
            'order' => array('id' => 'asc')
        ))->asHash('value', 'name'))
    ),
    'EM' => array('type' => 'number', 'length' => 15),
    'EN' => array('type' => 'number', 'length' => 15),
    'EP' => array('type' => 'number', 'length' => 15),
    'ER' => array('type' => 'number', 'length' => 15),
    'ES' => array('type' => 'number', 'length' => 15),
    'ET' => array('type' => 'number', 'length' => 15),
    'EU' => array('type' => 'number', 'length' => 15),
    'EV' => array('type' => 'number', 'length' => 15),
    'EW' => array('type' => 'number', 'length' => 15),
    'EX' => array('type' => 'number', 'length' => 15),
    'EY' => array('type' => 'number', 'length' => 15),

    // F..
    'FA' => array('type' => 'text', 'length' => 15),
    'FB' => array(
        'type' => 'date-ssaammjj'
    ),
    'FC' => array(
        'type' => 'date-ssaammjj'
    ),
    'FD' => array('type' => 'number', 'length' => 15),
    'FE' => array('type' => 'number', 'length' => 15),
    'FF' => array('type' => 'number', 'length' => 15),
    'FG' => array('type' => 'number', 'length' => 15),
    'FH' => array('type' => 'number', 'length' => 15),
    'FJ' => array('type' => 'number', 'length' => 15),
    'FK' => array('type' => 'number', 'length' => 15),
    'FL' => array('type' => 'number', 'length' => 15),
    'FM' => array('type' => 'number', 'length' => 15),
    'FP' => array('type' => 'number', 'length' => 15),
    'FR' => array('type' => 'number', 'length' => 15),
    'FS' => array('type' => 'number', 'length' => 15),
    'FN' => array('type' => 'number', 'length' => 15),
    'ZZ1'  => array('type' => 'select',
        'options' => array(
            '1' => 'Non',
            '0' => 'Oui'
        )),
    'ZZ2'  => array('type' => 'select',
        'options' => array(
            '1' => 'Non',
            '0' => 'Oui'
        )),
);


foreach ($form["ifu2561_20190101"] as $fieldname => $data) {
    $form["ifu2561_20190101"][$fieldname]['operations'][]['assert'] = 'ifu2561_20190101';
}
