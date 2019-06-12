<?php

try { 

  //$req->debug();

  $models = String::asSet($req->models);

  $model = $req->getAttribute('model') ?: $models[0];

  $opts = array('order' => array('name'),
                'limit' => 250,
                'offset' => (int) $req->offset);
  $filters = array();
  if ($req->hasAttribute('query', true)) {
    if (is_numeric($req->query)) {
      $filters['id'] = (int) $req->query;
    }
    else {
      $filters['|%%|name'] = $req->query;
    }
  }

  $item = null;
  if ($req->hasAttribute('item', true)) {
    $item = Item::getInstanceByKey($req->item); 
    /*    if ($item->hasAttribute($model.'_id')) {
      $filters['|<>|id'] = $item->getAttribute($model.'_id');
      }*/
  }
  


  if ($req->hasAttribute('exclude', true)) { 
    $exclude = $req->exclude;
    if (is_numeric($exclude) || strpos($exclude, ',') !== false) {
      $filters['|<>|id'] = String::asSet($exclude);
    }
    elseif ($item instanceof ActiveRecord) {
      $table = $dbo->getTable($req->exclude);
      $field = $item->getModel().'_id';
      if ($table->hasField($model.'_id')) {
        $set = $dbo->asSet('SELECT '.$model.'_id'
                           .' FROM '.$table->name()
                           .' WHERE '.$field.'='.$item->getId()); 
      }
      else {
        $set = $dbo->asSet('SELECT record_id'
                           .' FROM '.$table->name()
                           .' WHERE '.$field.'='.$item->getId()
                           .  ' AND model_id='.Model::id($model)); 
      }
      $filters['|<>|id'] = $set;
    }
  }

  if (!empty($filters)) {
    $opts['filters'] = $filters;
  }

  if ($req->hasAttribute('caller_model', true) && $model == 'heading') {
    $filters['model_id'] = I($req->getAttribute('caller_model'));
  }

  if (!empty($filters)) {
    $opts['filters'] = $filters;
  }

  $items = Item::collect($model, $opts);

  if ($req->hasAttribute('caller_model', true)) { 
    if ($req->hasAttribute('caller_item', true)) {
      $item = Item::getInstanceByKey($req->getAttribute('caller_item'));
    }
    else {
      $item = Item::getInstance($req->getAttribute('caller_model'));
    }
    $args = array('collection' => $items);
    $item->hook('onPick', $args);
  }

  /*   if ($req->hasAttribute('item', true)) { 
     $item = Item::getInstanceByKey($req->item);
     if (method_exists($item, 'onPick')) { 
       $item->onPick($items);
     }
   }*/
  
  $ctx->query = $req->query;
  $ctx->items = $items; 
  $ctx->title = 'sélection d’un élément';
  $ctx->models = $models;
  $ctx->model = $model;

  $res->useTemplate('//item.picker');

}
catch (Exception $e) { $err->add($e); }