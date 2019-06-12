<?php

try {
  
  $item = Item::getInstanceByKey($req->item_key);

  $elts = array(array('elt' => 'hidden',
                      'name' => 'item_key',
                      'value' => $item->getKey()),
                array('elt' => 'text',
                      'name' => 'content',
                      'rows' => 8,
                      'html' => true));

  $events = array('submit' => array('label' => l('save'),
                                    'action' => 'Kwo.getDialog().onSubmit(this)'));

  $opts = array('layout' => 'hbox',
                'wide' => true,
                'elts' => $elts,
                'events' => $events);
  
  $ctx->form = Elt::form($opts);

  $ctx->item = $item;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }

