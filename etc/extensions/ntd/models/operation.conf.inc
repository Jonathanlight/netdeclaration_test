<?php

$parameter['id'] = 14319;
$parameter['name'] = 'operation';
$parameter['label'] = 'operation';
$parameter['table'] = 'ntd_operation';
$parameter['belongs_to'] = array('formulairetype');
$parameter['casts'] = array('method_args' => 'hash',
                            'millesimes' => 'set');
