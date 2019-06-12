<?php

$parameter['id'] = 14306;
$parameter['name'] = 'souscription';
$parameter['label'] = 'souscription';
$parameter['table'] = 'ntd_souscription';
$parameter['has_many'] = array('suivi' => array('through' => 'ntd_souscription_suivi'), 
                               'facture' => array('through' => 'ntd_facture_souscription'));
$parameter['belongs_to'] = array('adherent', 'service');
$parameter['casts'] = array('context' => 'hash');
