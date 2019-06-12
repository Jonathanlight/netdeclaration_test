<?php

$parameter['id'] = 14322;
$parameter['name'] = 'dectype';
$parameter['label'] = 'dectype';
$parameter['table'] = 'ntd_dectype';
$parameter['casts'] = array('params' => 'hash',
                            'destinataires' => 'set');
$parameter['has_many'] = array('formulairetype' => array('through' => 'ntd_dectype_formulairetype',
                                                         'cols' => array('ntd_dectype_formulairetype.position' => 'ftype_position',
                                                                         'ntd_dectype_formulairetype.type' => 'ftype_type',
                                                                         'ntd_dectype_formulairetype.required_formulairetype_id' => 'ftype_required_formulairetype_id',
                                                                         'ntd_dectype_formulairetype.millesime_id' => 'ftype_millesime_id')),
                               'service' => array('through' => 'ntd_service_dectype'));
$parameter['belongs_to'] = array('millesime');
