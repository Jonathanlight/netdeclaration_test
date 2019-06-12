<?php

$parameter['id'] = 14304;
$parameter['name'] = 'tarif';
$parameter['label'] = 'tarif';
$parameter['table'] = 'ntd_tarif';
$parameter['casts'] = array('adherent_types' => 'set');
$parameter['belongs_to'] = array('service');
$parameter['has_many'] = array('service' => array('through' => 'ntd_tarif_service'));
