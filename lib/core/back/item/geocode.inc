<?php

try {

  $item = Item::getInstance(MODEL, (int) $req->id);

  $geo = array();
  $geolocation_id = Geolocation::id(array('model_id' => $item->getModelId(), 
                                          'record_id' => $item->getId()));
  if ($geolocation_id > 1) {
    $geo = Geolocation::getInstance($geolocation_id)->getAttributes();
  }

  $ctx->item = $item;
  $ctx->geo = $geo;
  $ctx->formatted_address = $item->address;

  $res->useTemplate('//item.geocode');

}
catch (Exception $e) { $err->add($e); }
