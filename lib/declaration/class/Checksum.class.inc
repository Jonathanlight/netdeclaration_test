<?php

class Checksum extends ActiveRecord {

  public static function store($item) {

    $item = Item::getInstance($item->getModel(), $item->getId());

    $data = array('attributes' => $item->getAttributes(),
                  'properties' => $item->getProperties());
    unset($data['attributes']['updated_at']);
    unset($data['attributes']['updated_on']);
    $commit = array('checksum' => md5(var_export($data,
                                                 true)));

    if (Checksum::exists(array('model_id' => $item->getModelId(),
                               'record_id' => $item->getId()))
    ) {
      $instance = Checksum::getInstance(array('model_id' => $item->getModelId(),
                                              'record_id' => $item->getId()));
    }
    else {
      $instance = Checksum::getInstance();
      $commit['model_id'] = $item->getModelId();
      $commit['record_id'] = $item->getId();
    }
    $instance->commit($commit);
  }

}