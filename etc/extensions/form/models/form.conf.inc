<?php

$parameter['id'] = 601;
$parameter['name'] = 'form';
$parameter['label'] = 'formulaire';
$parameter['table'] = 'frm_form';
$parameter['has_many'] = array('submission' => array('dependent' => true),
                               'field' => array('dependent' => true));
$parameter['casts'] = array('fields' => 'hash');
