<?php

try { 
  
  $item = Item::getInstance(MODEL, (int) $req->id);

  $row = $req->getAttribute('row');

  $id = Geolocation::id(array('model_id' => $item->getModelId(),
                              'record_id' => $item->getId()));
  
  $row += array('model_id' => $item->getModelId(),
                'record_id' => $item->getId());

  if ($req->hasAttribute('country_code', true)) {
    $row['country_id'] = is_numeric($req->country_code)
                       ? $req->country_code
                       : Country::id(array('code' => $req->country_code));
  }

  $row['name'] = $item->getName();

  $args = $id > 0 ? intval($id) : true;

  $geolocation = Geolocation::getInstance($args);
  $geolocation->commit($row);
  
  $attributes = array();

  if ($item->hasAttributes('latitude', 'longitude')) {
    $attributes['latitude'] = $row['latitude'];
    $attributes['longitude'] = $row['longitude'];
  }
  
  $item->setMetas($attributes);
  
  if ($item->hasAttributes('radius')) {
    $attributes['radius'] = $row['radius'];
  }
  
  foreach (array('admin1', 'country_id') as $key) {
    if ($item->hasAttribute($key)) {
      $attributes[$key] = $row[$key];
    }
  }
  
  if (!empty($attributes)) {
    $item->commit($attributes);
  }

}
catch (Exception $e) { $err->add($e); }
