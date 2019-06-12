<?php

try {
  
  if (App::number() != 1) {
    throw new Exception('there should be a single app');
  }
  
  $apps = array(S('app')->getName(), '');
  
  $opts = array('filters' => array('|<>|app' => $apps));
  $headings = Heading::collect($opts);
  if (count($headings) >= 1) {
    $ids = $headings->asSet('id');
    $models = (array) P('heading_models');
    $filters = array('heading_id' => $ids);
    $opts = array('filters' => $filters);
    foreach ($models as $model) {
      $items = Item::collect($model, $opts);
      foreach ($items as $item) {
        $item->destroy();
      }
      $dbo->resetAutoIncrement(T($model));
    }
  }
  
  $opts = array('filters' => array('|<>|app' => $apps));
  foreach (Model::all() as $model) {
    if (!Model::hasField($model, 'app')) continue ;
    $items = Item::collect($model, $opts);
    foreach ($items as $item) {
      $item->destroy();
    }
    $dbo->resetAutoIncrement(T($model));
  }
  
}
catch (Exception $e) { 
  $log->error($e);
  $err->add($e); 
}
