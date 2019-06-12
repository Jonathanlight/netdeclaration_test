<?php

class Conversion extends ActiveRecord
{
  const FLAG_DUBIOUS = 1;

  public static $flags = array(self::FLAG_DUBIOUS => 'douteux');

  const MEDIA_WEB = 1;
  const MEDIA_WEBSERVICE = 2;
  const MEDIA_PHONE = 3;
  const MEDIA_ADMIN = 4;
  const MEDIA_CALLCENTER = 5;

  public static $medias = array(self::MEDIA_WEB => 'web',
                                self::MEDIA_WEBSERVICE => 'webservice',
                                self::MEDIA_PHONE => 'téléphone',
                                self::MEDIA_ADMIN => 'backoffice',
                                self::MEDIA_CALLCENTER => 'call center');

  public static $types = array();

  public static function add($item, $opts=null) {
    $opts = (array) $opts;
    $model_id = 0;
    $record_id = 0;
    $visit_id = (int) $opts['visit_id'];
    $user_id = (int) $opts['user_id'];
    $media = (int) $opts['media'] ?: self::MEDIA_WEB;
    $medium = 0;
    $source = 0;
    try {
      if ($item instanceof ActiveRecord) {
        $metas = $item->getMetas();
        $visit_id = $visit_id > 0 ? $visit_id : (int) $metas['visit'];
        $user_id = $user_id > 0 ? $user_id : (int) $metas['user'];
        $model_id = $item->getModelId();
        $record_id = $item->getId();
      }
      elseif (is_array($item)) {
        $model_id = (int) $item['model_id'];
        $record_id = (int) $item['record_id'];
      }
      if ($model_id < 1 || $record_id < 1) {
        S('log')->trace('model_id ('.$model_id.'),'
                        .' record_id ('.$record_id.') required',
                        __METHOD__);
        return ;
      }
      $dbo = S('dbo');
      if ($media == self::MEDIA_WEB) {
        if ($visit_id < 1) {
          S('log')->trace('visit_id ('.$visit_id.')',
                          __METHOD__);
          return ;
        }
        $set = $dbo->fetchArray('SELECT medium, source'
                                .' FROM '.Visit::TABLE
                                .' WHERE id='.intval($visit_id)); //visit_id= ERREUR
        $medium = (int) $set[0];
        $source = (int) $set[1];
      }

      $row = array('model_id' => $model_id,
                   'record_id' => $record_id,
                   'media' => $media,
                   'medium' => $medium,
                   'source' => $source,
                   'visit_id' => $visit_id);

      if ($opts['unique'] == true) {
        if ($dbo->getTable(T('conversion'))->hasRow($row)) {
          // S('log')->trace('goal already exists', __METHOD__);
          return ;
        }
      }
      if (method_exists($item, 'getConversionWorth')) {
        $row['worth'] = $item->getConversionWorth($opts);
      }
      $row['user_id'] = $user_id;
      $dbo->insert(T('conversion'), $row);
      if ($dbo->affectedRows() >= 1) {
        if ($visit_id >= 1) {
          $visit = Visit::getInstance($visit_id);
          $visit->increment('conversions');
        }
        S('app')->hook('onConvert',
                       array('item' => $item,
                             'opts' => $opts));
      }
    }
    catch (Exception $e) { S('log')->error($e, __METHOD__); }
  }

  public static function types() {
    $set = S('dbo')->asSet('SELECT DISTINCT model_id'
                           .' FROM '.T('conversion'));
    $types = array();
    foreach ($set as $model_id) {
      if (Model::exists($model_id)) {
        $name = N($model_id);
      }
      else {
        $name = '* model ('.$model_id.') *';
      }
      $types[$model_id] = $name;
    }
    return $types;
  }

  public static function remove(ActiveRecord $item) {
    $visit_id = (int) $item->getMeta('visit');
    if ($visit_id < 1) {
      S('log')->trace('item ['.$item->getModelId().':'.$item->getId().']'
                      .' should have a meta_visit > 0',
                      __METHOD__);
      return ;
    }
    $visit = Visit::getInstance($visit_id);
    $visit->decrement('conversions');
    try {
      $n = S('dbo')->exec('DELETE FROM '.T('conversion')
                          .    ' WHERE model_id='.$item->getModelId()
                          .      ' AND record_id='.$item->getId()
                          .      ' AND visit_id='.$visit_id);
      if ($n >= 1) {
        S('app')->hook('onConversionRemove',
                           array('item' => $item));
      }
    }
    catch (Exception $e) { S('log')->error($e, __METHOD__); }
  }

  public static function asTableRow($row) {
    $set = array();
    $html = '';
    return $html;
  }

  public function getName($locale=null) {
    return self::getType($this->model_id, $record_id);
  }

  public static function getType($model_id, $record_id) {
    $name = N($model_id);
    if ($model_id == Model::id('goal') && $record_id > 0) {
      $name = self::$goals[$record_id];
    }
    return $name;
  }

  private static $strings = array();
  private static $goals = array();

  public function asFinderHash($hash) {
    $hash['type'] = self::getType($this->model_id, $this->record_id);
    try {
      $item = Item::getInstance($this->model_id, $this->record_id,
                                array('ignore' => true));
      $hash['name'] = $item->getName();
    }
    catch (Exception $e) {
      $hash['name'] = '-';
      //      $this->log->error($e, __METHOD__);
    }
    $hash['media'] = self::$medias[$hash['media']];
    $hash['medium'] = Tracker::$mediums[$hash['medium']];
    $hash['source'] = self::$strings[$hash['source']];
    if ($hash['source'][0] == '|') {
      list (, $medium, $id) = explode('|', $hash['source']);
      try {
        $item = Item::getInstance($medium, $id, array('ignore' => true));
        $hash['source'] = $item->getName();
      }
      catch (Exception $e) {
        $model = Model::exists($medium) ? N($medium) : $medium;
        $hash['source'] = '** '.$model.' ('.$id.') **';
//        S('log')->error($e, __METHOD__);
      }
    }
    $hash['term'] = self::$strings[$hash['term']];
    $hash['campaign'] = self::$strings[$hash['campaign']];
    return $hash;
  }

  public function onFind($finder) {
    $strings = array();
    foreach ($finder->getCollection() as $elt) {
      $strings[$elt->source]++;
      $strings[$elt->term]++;
      $strings[$elt->campaign]++;
    }
    self::$goals = Model::asHash('goal', 'code');
    $strings = array_keys($strings);
    self::$strings = $this->dbo->asHash('SELECT id, name'
                                        .' FROM '.Tracker::TABLE_STRING
                                        .' WHERE id IN ([id])',
                                        array('[id]' => $strings));
  }

}