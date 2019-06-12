<?php

$operations = array(
  'soustraction-bc' => array('func' => 'data-soustraction',
                             'opt' => array('results' => array('BC'), 'value' => 'BA', 'operands' => array('BB'))),
  'soustraction-bd' => array('func' => 'data-soustraction',
                             'opt' => array('results' => array('BD'), 'value' => 'BB', 'operands' => array('BA'))),
  'report-bc-bd' => array('func' => 'data-report-BC-BD',
                          'opt' => array('items' => array('CB', 'CA', 'BC', 'BD'))),
  'soustraction-da-db-3515sd' => array('func' => 'data-soustraction-da-db-3515sd',
                                       'opt' => array('items' => array('DC', 'DD', 'DA', 'DB'))),
  'tva3515sd-bc' => array('func' => 'data-tva3515sd-bc',
                          'opt' => array('results' => array('BC'), 'operands' => array('BB', 'BA'))),
  'report-BA' => array('func' => 'data-report',
                       'opt' => array('results' => array('DB'), 'operands' => array('BA'))),
  'report DA -> CB' => array('func' => 'data-report',
                             'opt' => array('results' => array('DA'), 'operands' => array('CB'))),
  'copytva3310ca3_KD' => array('function' => 'copy-value',
                               'args' => array('target' => 'tva3310ca3_KD')),
  'copy_tva3310ca3_KC' => array('function' => 'copy-value',
                                'args' => array('target' => 'tva3310ca3_KC')),
  'integrity-CA-3515SD' => array('func' => 'data-integrity-ca-3515sd',
                                 'opt' => array('items' => array('CA', 'BD')))
);


$form["tva3515sd_20150101"] = array(
  'AA' => array('type' => 'date-ssaamm',
                'required' => true
  ),
  'AB' => array('type' => 'date-ssaamm',
                'required' => true
  ),
  'BA' => array('type' => 'number',
                'operations' => array($operations['soustraction-bc'],
                                      $operations['tva3515sd-bc'],
                                      $operations['soustraction-bd'],
                                      $operations['report-BA']),
  ),
  'BB' => array('type' => 'number',
                'operations' => array($operations['soustraction-bc'],
                                      $operations['soustraction-bd']),
  ),
  'BC' => array('type' => 'number',
                'operations' => array($operations['report-bc-bd']),
  ),
  'BD' => array('type' => 'number',
                'operations' => array($operations['report-bc-bd']),
  ),
  'CA' => array('type' => 'number',
                'operations' => array($operations['integrity-CA-3515SD']),
  ),
  'CB' => array('type' => 'number',
                'operations' => array($operations['report DA -> CB']),
  ),
  'DA' => array('type' => 'number',
                'operations' => array($operations['soustraction-da-db-3515sd']),
  ),
  'DB' => array('type' => 'number',
                'operations' => array($operations['soustraction-da-db-3515sd']),
  ),
  'DC' => array('type' => 'number',
                'operations' => array($operations['copytva3310ca3_KD'])
  ),
  'DD' => array('type' => 'number',
                'operations' => array($operations['copy_tva3310ca3_KC'])
  ),
  'EB' => array('type' => 'checkbox', 'value' => '1',),
  'EA' => array('type' => 'comments', 'length' => 2560,),
  'EA1' => array('type' => 'hidden', 'length' => 512,),
  'EA2' => array('type' => 'hidden', 'length' => 512,),
  'EA3' => array('type' => 'hidden', 'length' => 512,),
  'EA4' => array('type' => 'hidden', 'length' => 512,),
  'EA5' => array('type' => 'hidden', 'length' => 512,),
);

foreach($form["tva3515sd_20150101"] as $fieldname => $data) {
  $form["tva3515sd_20150101"][$fieldname]['operations'][]['assert'] = 'tva3515sd_20150101';
}