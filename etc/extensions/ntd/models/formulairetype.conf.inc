<?php

$parameter['id'] = 14310;
$parameter['name'] = 'formulairetype';
$parameter['label'] = 'formulairetype';
$parameter['table'] = 'ntd_formulairetype';
$parameter['casts'] = array('formulairetype_required' => 'set',
                            'millesimes' => 'set',);
$parameter['has_many'] = array('declaration',
                               'dectype' => array('through' => 'ntd_dectype_formulairetype',
                                                  'cols' => array('ntd_dectype_formulairetype.position' => 'ftype_position',
                                                                  'ntd_dectype_formulairetype.type' => 'ftype_type',
                                                                  'ntd_dectype_formulairetype.millesime_id' => 'ftype_millesime_id')),
                               'millesime' => array('through' => 'ntd_formulairetype_millesime',
                                                    'cols'     => array('ntd_formulairetype_millesime.is_repetable' => 'ftype_is_repetable',
                                                                        'ntd_formulairetype_millesime.is_v1'        => 'ftype_is_v1')));
