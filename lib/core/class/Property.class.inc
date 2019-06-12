<?php

class Property extends ActiveRecord {
  
  const FLAG_INDEXABLE = 1;
  const FLAG_LOCALIZED = 2;
  const FLAG_REQUIRED = 4;

  public static $flags = array(self::FLAG_INDEXABLE => 'indexable',
                               self::FLAG_LOCALIZED => 'traduisible',
                               self::FLAG_REQUIRED => 'obligatoire');

  protected function onBeforeCommit(&$attr) {
    if (!$this->isItem() && empty($attr['name'])) {
      throw new ActiveRecordException('nom obligatoire');
    }
    if (isset($attr['name']) && is_numeric($attr['name'])) {
      throw new ActiveRecordException('nom invalide');
    }
    if (Model::hasField($attr['model_id'], $attr['name'])) {
      throw new ActiveRecordException('une property ne peut avoir le même '.
                                      'nom qu’un attribut');
    }
  }
  
  protected function onAlter() {
    ConfigManager::model(N($this->model_id));
  }
  
  public function asFinderHash($hash) {
    $model = Model::name($hash['model_id']);
    $hash['model_id'] = $model ? $model : $hash['model_id'];
    return $hash;
  }
  
  protected function onAfterDestroy() {
    $this->dbo->exec('DELETE FROM '.Item::TABLE_PROPERTY
                     .    ' WHERE property_id='.$this->getId());
  }
 
  public static function models() {
    $models = array();
    foreach (Model::all() as $id => $name) {
      if (!Model::hasField($name, 'locales')) continue ;
      $models[$id] = $name;
    }
    asort($models);
    return $models;
  }

}