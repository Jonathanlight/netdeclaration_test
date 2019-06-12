<?php

$parameter['id'] = 803;
$parameter['name'] = 'campaign';
$parameter['label'] = 'campagne';
$parameter['table'] = 'psh_campaign';
$parameter['casts'] = array('bases' => 'set',
                            'test_bases' => 'set');
$parameter['belongs_to'] = array('newsletter');
