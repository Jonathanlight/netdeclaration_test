<?php

$form["f_identif_20160101"] = array(
  'KD' => array('readonly' => true,
                'type' => 'readonly',
                'length' => 6
  ),
  'AA' => array('required' => true,
                'readonly' => true,
                'type' => 'readonly',
                'length' => 14,
  ),
  'AB' => array('required' => true,
                'type' => 'number',
                'length' => 6,
  ),
  'AA1' => array('required' => true,
                'readonly' => true,
                'type' => 'alphabetic',
                'length' => 35,
  ),
  'AA2' => array('readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA3' => array('readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA4' => array('type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA5' => array('readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA6' => array('readonly' => true,
                 'required' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA7' => array('readonly' => true,
                 'required' => true,
                 'type' => 'readonly',
                 'length' => 5,
  ),
  'AA8' => array('readonly' => true,
                 'required' => true,
                 'type' => 'alphabetic',
                 'length' => 2,
  ),
  'AA13' => array('required' => true,
                  'type' => 'alphabetic',
                  'length' => 35,
  ),
  'BA' => array('required' => true,
                'type' => 'data-select',
                'options' => 'tcf',
  ),
  'BB' => array('required' => true,
                'type' => 'data-select',
                'options' => 'trf',
  ),
  'BC' => array('type' => 'data-select',
                'options' => 'tbs',
                'operations' => array(array('func' => 'data-isFieldRequired',
                                            'opt' => array('is_required' => true,
                                                           'items' => array('BA' => array('BA', 'BC', 'RF', 'FL')))))
  ),
  'OGA' => array('type' => 'number',
                 'readonly' => true,
                 'operations' => array(array('func' => 'data-check-full',
                                             'opt' => array('results' => array('OGA'),
                                                            'operands' => array('IDOGA')))),
  ),
  'IDOGA' => array('type' => 'number',
  ),
  'BD' => array('type' => 'data-select',
                'options' => 'tcd',
  ),
  'BF' => array('required' => true,
                'type' => 'data-select',
                'options' => 'tdp',
  ),
  'CA' => array('required' => true,
                'type' => 'date-ssaammjj'
  ),
  'CB' => array('required' => true,
                'type' => 'date-ssaammjj'
  ),
  'CC' => array('required' => true,
                'type' => 'counter-select',
                'max' => 100,
  ),
  'CD' => array('type' => 'date-ssaammjj',
                'operations' => array(array('func' => 'data-isFieldRequired',
                                            'opt' => array('is_required' => true,
                                                           'items' => array('BA' => array('BC', 'RF', 'FL')))))
  ),
  'CE' => array('type' => 'counter-select',
                'max' => 100,
                'operations' => array(array('func' => 'data-isFieldRequired',
                                            'opt' => array('is_required' => true,
                                                           'items' => array('BA' => array('BC', 'RF', 'FL')))))
  ),
  'DA' => array('required' => true,
                'type' => 'alphabetic',
                'length' => 3,
                'value' => 'EUR'
  )
);
