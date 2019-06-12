<?php

try {

    $fields = Ifield::collect(array('filters' => array(array('type' => Ifield::TYPE_CCI_C889_7111),
                                                       array('OR' => array('type_segment' => 'cci')))));
    $millesimes = Millesime::collect();
    foreach ($fields as $field) {
        foreach ($millesimes as $millesime) {
            if ($field->isExtensible($millesime)) {
                if (!$field->hasFlag(Ifield::FLAG_CCI_DEFAULT)) {
                    $field->setFlag(Ifield::FLAG_CCI_DEFAULT);
                }
            }
        }
    }
} catch(Exception $e) {
    $err->add($e);
}