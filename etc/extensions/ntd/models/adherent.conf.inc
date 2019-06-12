<?php

$parameter['id'] = 14302;
$parameter['name'] = 'adherent';
$parameter['label'] = 'adherent';
$parameter['profile_id'] = 8;
$parameter['table'] = 'ntd_adherent';
$parameter['has_many'] = array('souscription' => array('dependent' => true),
                               'declaration'  => array('dependent' => true),
                               'iban'         => array('dependent' => true),
                               'facture'      => array('dependent' => true));
$parameter['casts'] = array('old_sirets' => 'hash',
                            'sign_infos' => 'hash');
