<?php

$parameter['id'] = 14325;
$parameter['name'] = 'partenaire';
$parameter['label'] = 'partenaire';
$parameter['table'] = 'ntd_partenaire';
$parameter['has_many'] = array('service' => array('through' => 'ntd_partenaire_service'));
