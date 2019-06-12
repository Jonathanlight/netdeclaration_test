<?php

try { 

  $item = Item::getInstanceByKey($req->item);
  $row = array($item->getModel().'_id' => $item->getId());

  $relation = Item::getInstanceByKey($req->relation);
  $field = $relation->getModel().'_id';

  $row = array();
  $table = $dbo->getTable($req->table);
  if ($req->table == T($relation)) {
    $row['id'] = $relation->getId();
  }
  elseif ($table->hasField($field)) {
    $row[$item->getModel().'_id'] = $item->getId();
    $row[$field] = $relation->getId();
  }
  else {
    $row[$item->getModel().'_id'] = $item->getId();
    $row['model_id'] = $relation->getModelId();
    $row['record_id'] = $relation->getId();
  }
  
  $where = '';
  foreach ($row as $key => $value) {
    $where .= ' AND '.$key.'='.$value;
  }

  $dbo->exec('DELETE FROM '.$table->name()
             .    ' WHERE 1'.$where
             .    ' LIMIT 1');

  $item->onRelationDestroy($relation);

}
catch (Exception $e) { $err->add($e); }
