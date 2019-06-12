<?php

$parameter['id'] = 14313;
$parameter['name'] = 'suivipayant';
$parameter['label'] = 'suivipayant';
$parameter['table'] = 'ntd_suivipayant';
$parameter['has_many'] = array('service' => array('through' => 'ntd_service_suivipayant'));