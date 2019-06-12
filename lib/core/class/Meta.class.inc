<?php

class Meta {

  const TABLE = 'sys_item_meta';

  const BIT_FAVORITE = 1;
  const BIT_DESTROYED = 2;
  const BIT_HIDDEN = 4;
  const BIT_LOCKED = 8;
  const BIT_PINNED = 16;
  const BIT_PROTECTED = 32;
  const BIT_ETERNAL = 64;
  const BIT_NEW = 128;
  const BIT_ALERT = 256;
  const BIT_CLOSED = 512;
  const BIT_RESOURCES = 1024;
  const BIT_TWEETED = 2048;
  const BIT_PROMOTED = 4096;
  const BIT_PINGED = 8192;

  const FIELD_MODEL = 'model';
  const FIELD_RECORD = 'record';

  public static function decrement($item, $key, $value=1) {
    return self::increment($item, $key, $value, '-');
  }

  public static function increment($item, $key, $value=1, $sign='+') {
    if ($item instanceof ActiveRecord) {
      $model_id = (int) $item->getModelId();
      $record_id = (int) $item->getId();
    }
    elseif (isset($item['model'])) {
      $model_id = (int) $item['model_id'];
      $record_id = (int) $item['record_id'];
    }
    else {
      $model_id = (int) $item[0];
      $record_id = (int) $item[1];
    }
    if (!Model::hasMetas($model_id)) return false;
    $dbo = S('dbo');
    $filters = array(self::FIELD_MODEL => $model_id,
                     self::FIELD_RECORD => $record_id);
    $ret = $dbo->update(self::TABLE,
                        array('`'.$key.'`=`'.$key.'`'.$sign.'1'),
                        array('filters' => $filters));
    if ($ret < 1) {
      $value = (int) ($sign === '+');
      $dbo->insert(self::TABLE,
                   array(self::FIELD_MODEL => $model_id,
                         self::FIELD_RECORD => $record_id,
                         $key => $value));
    }
  }

  public static function get($item, $key=null) {
    if ($item instanceof ActiveRecord) {
      $model_id = (int) $item->getModelId();
      $record_id = (int) $item->getId();
    }
    elseif (isset($item['model_id'])) {
      $model_id = (int) $item['model_id'];
      $record_id = (int) $item['record_id'];
    }
    else {
      $model_id = (int) $item[0];
      $record_id = (int) $item[1];
    }
    if (!Model::hasMetas($model_id)) return false;
    $args = func_get_args();
    if (!is_string($key)) {
      if (empty($key)) $cols = '*';
      else {
        if (count($args) > 2) array_shift($args);
        else $args = $key;
        $cols = '`'.join('`, `', $args).'`';
      }
      $hash = S('dbo')->fetchHash('SELECT '.$cols
                                  .' FROM '.self::TABLE
                                  .' WHERE '.self::FIELD_MODEL.'='.$model_id
                                  .  ' AND '.self::FIELD_RECORD.'='.$record_id);
      return $hash ? $hash : array();
    }
    return S('dbo')->fetchValue('SELECT '.$key
                                .' FROM '.self::TABLE
                                .' WHERE '.self::FIELD_MODEL.'='.$model_id
                                .  ' AND '.self::FIELD_RECORD.'='.$record_id);
  }

  public static function set($item, $key, $value) {
    if ($item instanceof ActiveRecord) {
      $model_id = (int) $item->getModelId();
      $record_id = (int) $item->getId();
    }
    elseif (isset($item['model_id'])) {
      $model_id = (int) $item['model_id'];
      $record_id = (int) $item['record_id'];
    }
    else {
      $model_id = (int) $item[0];
      $record_id = (int) $item[1];
    }
    if (!Model::hasMetas($model_id)) return false;
    $dbo = S('dbo');
    $filters = array(self::FIELD_MODEL => $model_id,
                     self::FIELD_RECORD => $record_id);
    $ret = $dbo->update(self::TABLE,
                        array($key => $value),
                        array('filters' => $filters,
                              'modifiers' => array('IGNORE')));
    if ($ret < 1) {
      $dbo->insert(self::TABLE,
                   array(self::FIELD_MODEL => $model_id,
                         self::FIELD_RECORD => $record_id,
                         $key => $value));
      $ret = $dbo->affectedRows();
    }
    return $ret >= 1;
  }

}

