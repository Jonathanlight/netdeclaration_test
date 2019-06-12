<?php

$parameter['id'] = 926;
$parameter['name'] = 'tree';
$parameter['label'] = 'arborescence';
$parameter['table'] = 'tre_tree';
$parameter['has_many'] = array('node' => array('structure' => 'tree',
                                               'dependent' => true));
