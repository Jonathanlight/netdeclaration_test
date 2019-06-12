<?php

$parameter['id'] = 14307;
$parameter['name'] = 'declaration';
$parameter['label'] = 'declaration';
$parameter['table'] = 'ntd_declaration';
$parameter['belongs_to'] = array('dectype');
$parameter['has_many'] = array('formulaire' => array('dependent' => true));
$parameter['has_one'] = array('suivi');
$parameter['casts'] = array('destinataires' => 'hash');