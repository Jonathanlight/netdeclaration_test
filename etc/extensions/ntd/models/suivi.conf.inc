<?php

$parameter['id'] = 14308;
$parameter['name'] = 'suivi';
$parameter['label'] = 'suivi';
$parameter['table'] = 'ntd_suivi';
$parameter['has_many'] = array('destinataire' => array('dependent' => true),
                               'souscription' => array('through' => 'ntd_souscription_suivi'));
