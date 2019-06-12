<?php

try {

  $opts = array('filters' => array('locale' => $res->getLocale()),
                'order' => array('position'),
                'properties' => array('label'));

  $ctx->motives = Motive::collect($opts)->asHash('id', 'label');
  $ctx->item = $req->item;  

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }