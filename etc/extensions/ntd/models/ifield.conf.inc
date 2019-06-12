<?php

$parameter['id'] = 14318;
$parameter['name'] = 'ifield';
$parameter['label'] = 'ifield';
$parameter['table'] = 'ntd_ifield';
$parameter['belongs_to'] = array('formulairetype');
$parameter['casts'] = array('millesimes' => 'set');
$parameter['has_many'] = array('millesime' => array('through' => 'ntd_ifield_millesime',
                                                    'cols'    => array('ntd_ifield_millesime.is_extensible' => 'is_extensible')));
