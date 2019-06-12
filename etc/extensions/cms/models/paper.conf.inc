<?php

$parameter['id'] = 401;
$parameter['name'] = 'paper';
$parameter['label'] = 'dossier';
$parameter['table'] = 'cms_paper';
$parameter['has_many'] = array('paragraph' => array('structure' => 'tree',
                                                    'dependent' => true));
