<?php

$form["p_identif_20151020"] = array(
  'KD' => array('required' => true,
                'readonly' => true,
                'length' => 7,
  ),
  'AA1' => array('required' => true,
                 'readonly' => true,
                 'type' => 'number',
                 'length' => 14,
  ),
  'AA2' => array('readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA3' => array('type' => 'alphabetic',
                 'readonly' => true,
                 'length' => 35,
  ),
  'AA4' => array('readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA5' => array('readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA6' => array('required' => true,
                 'readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA7' => array('readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA8' => array('required' => true,
                 'readonly' => true,
                 'type' => 'alphabetic',
                 'length' => 35,
  ),
  'AA9' => array('required' => true,
                 'readonly' => true,
                 'type' => 'number',
                 'length' => 5,
  ),
  'BB' => array('type' => 'date-ssaammjj'),
  'CA' => array('required' => true,
                'type' => 'date-ssaammjj'),
  'CB' => array('required' => true,
                'type' => 'date-ssaammjj'),
  'KF' => array('required' => true,
                'type' => 'date-ssaamm'),
  'GA' => array('readonly' => true,
                'type' => 'number',
                'length' => 23,
  ),
  'HA' => array('type' => 'number',
                'length' => 24,
                'operations' =>
                array(
                  1 =>
                  array(
                    'func' => 'data-check-positiv-one-item',
                    'opt' =>
                    array(
                      'items' =>
                      array(
                        0 => 'HA',
                      ),
                    ),
                  ),
                  array('func' => 'data-need-iban-if-amount', 'opt' => array('items' => array('HA', 'GA'))),
                ),
  ),
  'KA' => array('type' => 'number',
                'length' => 24,
                'readonly' => true,
  ),
  'GB' => array('readonly' => true,
                'type' => 'number',
                'length' => 23,
  ),
  'HB' => array('type' => 'number',
                'length' => 24,
                'operations' =>
                array(
                  1 =>
                  array(
                    'func' => 'data-check-positiv-one-item',
                    'opt' =>
                    array(
                      'items' =>
                      array(
                        0 => 'HB',
                      ),
                    ),
                  ),
                  array('func' => 'data-need-iban-if-amount', 'opt' => array('items' => array('HB', 'GB'))),
                )
  ),
  'KB' => array('type' => 'number',
                'length' => 24,
                'readonly' => true,
  ),
  'GC' => array('readonly' => true,
                'type' => 'number',
                'length' => 23,
  ),
  'HC' => array('type' => 'number',
                'length' => 24,
                'operations' =>
                array(
                  1 =>
                  array(
                    'func' => 'data-check-positiv-one-item',
                    'opt' =>
                    array(
                      'items' =>
                      array(
                        0 => 'HC',
                      ),
                    ),
                  ),
                  array('func' => 'data-need-iban-if-amount', 'opt' => array('items' => array('HC', 'GC'))),
                ),
  ),
  'KC' => array('type' => 'number',
                'length' => 24,
                'readonly' => true,
  )
);
