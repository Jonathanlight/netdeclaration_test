<?php

$operations = array(
  'report-bc-bd' => array('func' => 'data-report-BC-BD',
                          'opt' => array('items' => array('CB', 'CA', 'BC', 'BD'))),
  'soustraction-da-db-3515sd' => array('func' => 'data-soustraction-da-db-3515sd',
                                       'opt' => array('items' => array('DC', 'DD', 'DA', 'DB'))),
  'report DA -> CB' => array('func' => 'data-report',
                             'opt' => array('results' => array('DA'), 'operands' => array('CB'))),
  'copytva3310ca3_KD' => array('function' => 'copy-value',
                               'args' => array('target' => 'tva3310ca3_KD')),
  'copy_tva3310ca3_KC' => array('function' => 'copy-value',
                                'args' => array('target' => 'tva3310ca3_KC')),
  'integrity-CA-3515SD' => array('func' => 'data-integrity-ca-3515sd',
                                 'opt' => array('items' => array('CA', 'BD')))
);


$form["tva3515sd_20190101"] = array(
  'AA' => array('type' => 'date-ssaamm',
                'required' => true
  ),
  'AB' => array('type' => 'date-ssaamm',
                'required' => true
  ),
  'BB' => array('type' => 'number',),
  'BC' => array('type' => 'number',
                'operations' => array($operations['report-bc-bd']),
  ),
  'BD' => array('type' => 'number',
                'operations' => array($operations['report-bc-bd']),
  ),
  'BE' => array('type' => 'number',
                'operations' => array(),
  ),
  'BF' => array('type' => 'number',
                'operations' => array(),
  ),
  'CA' => array('type' => 'number',
                'operations' => array($operations['integrity-CA-3515SD']),
  ),
  'CB' => array('type' => 'number',
                'operations' => array($operations['report DA -> CB']),
  ),
  'DA' => array('type' => 'number',
                'operations' => array(/*$operations['soustraction-da-db-3515sd']*/),
  ),
  'DB' => array('type' => 'number',
                'operations' => array(/*$operations['soustraction-da-db-3515sd']*/),
  ),
  'DC' => array('type' => 'number',
                'operations' => array($operations['copytva3310ca3_KD'])
  ),
  'DD' => array('type' => 'number',
                'operations' => array($operations['copy_tva3310ca3_KC'])
  ),
  'EB' => array('type' => 'checkbox', 'value' => '1',),
  'EA' => array('type' => 'comments',),
  'EA1' => array('type' => 'hidden',),
  'EA2' => array('type' => 'hidden',),
  'EA3' => array('type' => 'hidden',),
  'EA4' => array('type' => 'hidden',),
  'EA5' => array('type' => 'hidden',),
);

foreach($form["tva3515sd_20190101"] as $fieldname => $data) {
  $form["tva3515sd_20190101"][$fieldname]['operations'][]['assert'] = 'tva3515sd_20190101';
}
