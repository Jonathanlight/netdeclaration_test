<?php

try {

  $item = Item::getInstanceByKey($req->item_key);

  $elts = array(array('elt' => 'text',
                      'name' => 'name',
                      'label' => l('subject'),
                      'required' => true),
                array('elt' => 'text',
                      'name' => 'content',
                      'label' => l('content'),
                      'rows' => 8,
                      'required' => true));
  
  $events = array('submit' => array('label' => l('save'),
                                    'action' => 'Kwo.getDialog().onSubmit(this)'));
  
  $opts = array('layout' => 'hbox',
                'wide' => true,
                'elts' => $elts,
                'events' => $events);
  
  $ctx->form = Elt::form($opts);

  $req->track();

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }