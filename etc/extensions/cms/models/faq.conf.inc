<?php

$parameter['id'] = 415;
$parameter['name'] = 'faq';
$parameter['label'] = 'faq';
$parameter['table'] = 'cms_faq';
$parameter['has_many'] = array('component' => array('dependent' => true,
                                                    'order' => array('position')));
