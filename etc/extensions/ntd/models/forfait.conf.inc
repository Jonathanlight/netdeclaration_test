<?php

$parameter['id'] = 14314;
$parameter['name'] = 'forfait';
$parameter['label'] = 'forfait';
$parameter['table'] = 'ntd_forfait';
$parameter['has_many'] = array('service' => array('through' => 'ntd_forfait_service'));
