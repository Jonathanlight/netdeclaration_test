<?php

$parameter['id'] = 14303;
$parameter['name'] = 'service';
$parameter['label'] = 'service';
$parameter['table'] = 'ntd_service';
$parameter['has_many'] = array('tarif' => array('dependent' => true),
                               'suivipayant' => array('through' => 'ntd_service_suivipayant'),
                               'dectype' => array('through' => 'ntd_service_dectype'));
$parameter['casts'] = array('adherent_types' => 'set',
                            'formulaire_types' => 'set',
                            'type_doc_edi' => 'set',
                            'flags_export_adherent' => 'bits',
                            'flags_export_adherent_reception' => 'bits',
                            'flags' => 'bits',
);
