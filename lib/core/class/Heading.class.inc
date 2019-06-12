<?php

class Heading extends ActiveRecord {
 
  public static function models() {
    $hash = array();
    foreach (P('heading_models') as $model) {
      if (!Model::exists($model)) continue ;
      $hash[Model::id($model)] = Model::label($model);
    }
    asort($hash);
    return $hash;
  }
   
  protected function onAfterDestroy() {
    try {
      $record = array('heading_id' => 0);
      $opts = array('filters' => array('heading_id' => $this->getId()));
      foreach (P('heading_models') as $model) {
        if (!Model::exists($model)) continue ;
        $this->dbo->update(T($model), $record, $opts);
        $this->dbo->debug();
      }
    }
    catch (Exception $e) { S('log')->error($e, __METHOD__); }
  }

  public function asPickerRow() {
    $row = $this->code;
    if ($this->name != $this->code) {
      $row .= ' : '.$this->name;  
    }
    $row .= '<br/>';
    $row .= Model::name($this->model_id).' / '.$this->app;
    return $row;
  }

  public function asEditHash() {
    $ht = array();
    if (!$this->isItem() && 
	S('req')->hasAttribute('caller_model', true)) {
      $ht = array('model_id' => I(S('req')->getAttribute('caller_model')));
    }
    if (S('req')->hasAttribute('caller_item', true)) {
      $item = S('req')->getAttribute('caller_item');
      $item = Item::getInstanceByKey($item);
      if ($item->hasAttribute('app')) {
	$ht['app'] = $item->getAttribute('app');
      }
      else if ($item->hasAttribute('heading_id') && $item->heading_id >= 1) {
	try {
	  $heading = Heading::getInstance($item->heading_id);
	  $ht['app'] = $heading->getAttribute('app');
	}
	catch (Exception $e) {
	  S('log')->error($e, __METHOD__);
	}
      }
    }
    return $ht;
  }

}