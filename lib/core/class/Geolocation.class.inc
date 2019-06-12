<?php

class Geolocation extends ActiveRecord {

  public static function geocode($item, $opts=null) {
    $id = Geolocation::id(array('model_id' => $item->getModelId(),
                                'record_id' => $item->getId()));
    $geo = Geolocation::getInstance($id >= 1 ? $id : true);

    if ($opts['address']) {
      $param = 'address='.urlencode($opts['address']);
    }
    elseif ($opts['latitude'] && $opts['longitude']) {
      $param = 'latlng='.trim($opts['latitude']).','.trim($opts['longitude']);
    }

    $url = 'http://maps.googleapis.com/maps/api/geocode/json?sensor=false&language=en&'.$param;

    $json = file_get_contents($url);
    $json = json_decode($json, true);
    $res = $json['results'][0];

    $row = array('model_id' => $item->getModelId(),
                 'record_id' => $item->getId(),
                 'address' => $res['formatted_address'],
                 'latitude' => $res['geometry']['location']['lat'],
                 'locale' => I18N::LOCALE_EN,
                 'longitude' => $res['geometry']['location']['lng'],
                 'name' => $item->getName(),
                 'zoom' => 10);

    foreach ($res['address_components'] as $component) {
      switch ($component["types"][0]) {
        case "postal_code": $row['postal_code'] = $component["long_name"]; break;
        case "locality": $row['locality'] = $component["long_name"]; break;
        case "sublocality": $row['sublocality'] = $component["long_name"]; break;
        case "country":
          $row['country'] = $component["long_name"];
          $row['country_id'] = Country::id(array('code' => $component["short_name"]));
          break;
        case "administrative_area_level_1": $row['admin1'] = $component["long_name"]; break;
        case "administrative_area_level_2": $row['admin2'] = $component["long_name"]; break;
        case "administrative_area_level_3": $row['admin3'] = $component["long_name"]; break;
      }
    }

    $geo->commit($row);

    $attributes = array();
    if ($item->hasAttributes('latitude', 'longitude')) {
      $attributes['latitude'] = $row['latitude'];
      $attributes['longitude'] = $row['longitude'];
      $item->setMetas($attributes);
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

}