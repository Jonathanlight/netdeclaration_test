<?php

try {

  //$req->debug();

  $id = (int) $req->id;

  $item = Item::getInstance(MODEL, $id ?: true);

  if (method_exists($item, 'onBeforeStore')) {
    $item->onBeforeStore();
  }

  $record = $req->record;
  $properties = $req->properties;
  $branch = $req->getBranch();
  $branches = $req->getBranches();

  if ($req->hasAttribute('xml_file', true)) {
    $doc = new DOMDocument();
    $doc->preserveWhiteSpace = false;
    $doc->load($req->getAttribute('xml_file'));
    $xpath = new DOMXPath($doc);
    $query = '//elem';
    $nodes = $xpath->query($query);
    foreach ($nodes as $node) {
      $field = $node->getAttribute('field');
      if (empty($field)) continue ;
      $value = $record[$field];
      if ($node->hasAttribute('required')) {
        if (empty($value)) {
          throw new Exception('veuillez remplir les champs obligatoires ['.$field.']');
        }
      }
      if ($node->hasAttribute('mode') && $node->getAttribute('mode') == 'rich') {
        if (strlen($value) > 5) {
          $value = String::tidy($value);
          $value = str_replace(array('%28%28', '%29%29'), array('((', '))'), $value);
          $record[$field] = $value;
        }
      }
    }
  }

  if (isset($record['published_on']) &&
      Date::isNull($record['published_on'])) {
    $record['published_on'] = Date::today();
  }
  if (isset($record['published_at']) &&
      Date::isNull($record['published_at'])) {
    $record['published_at'] = Date::now();
  }

  if (!$item->isItem()) {

    /*    if (Model::hasField(MODEL, 'app') && empty($record)) {
      $record['app'] = S('app')->getName();
      }*/

    if (Model::hasOwner($item) && !TreeManager::isNode($item) && count($branch) >= 1) {
      $branch_keys = array_keys($branch);
      $model_key = $branch_keys[1];
      list ($model, ) = explode('_', $model_key);
      $record['model_id'] = Model::id($model);
      $record['record_id'] = $branch[$model_key];
    }
    if (Model::isProfile(MODEL)) {
      $record['user_id'] = $branch['user_id'];
    }

  }

  $belongs_to = (array) Model::parameter(MODEL, 'belongs_to');
  foreach ($belongs_to as $model => $relation) {
    $key = $relation['foreign_key'];
    if ($item->isItem() && isset($record[$key]) && $record[$key] < 1) {
      if ($branch[$key] >= 1) {
        $record[$key] = $branch[$key];
      }
      else {
        throw new Exception('veuillez associer un objet de type '.
                            '<'.strtoupper(Model::label($model)).'>');
      }
    }
    elseif (!$item->isItem()) {
      if ($record[$key] < 1) {
        if ($branch[$key] >= 1) {
          $record[$key] = $branch[$key];
        }
        elseif ($branches[$key] >= 1) {
          $record[$key] = $branches[$key];
        }
      }
      if ($record[$key] < 1) {
        throw new Exception('veuillez associer un objet de type'.
                            '<'.strtoupper(Model::label($model)).'>');
      }
    }
  }

  if (isset($record['heading_id']) && $record['heading_id'] < 1) {
    throw new Exception('veuillez préciser une rubrique');
  }

  $item->commit($record);

  if (is_array($properties)) {
    $props = array();
    $opts = array('filters' => array('model_id' => $item->getModelId()));
    foreach (Property::collect($opts) as $property) {
      $props[$property->getId()] = $property;
    }
    foreach ($properties as $locale => $h) {
      foreach ($h as $property_id => $value) {
        if (!($props[$property_id] instanceof ActiveRecord)) {
          S('log')->error('unknown property_id ('.$property_id.')', __METHOD__);
          continue ;
        }
        if (strpos($value, '<') >= 1 && strpos($value, '>') > 1) {
          $value = String::tidy($value);
          $value = str_replace(array('%28%28', '%29%29'), array('((', '))'), $value);
        }
        $value = String::texturize($value);
        $value = trim($value);
        if (in_array($value, array('<br>', '<br />', '<br/>'))) {
          $value = '';
        }
        $rows[$property_id] = $value;
      }
      $item->setProperties($rows, $locale);
    }

    $ope = $locale >= 1 ? ' < 1' : ' >= 1';
    $dbo->exec('DELETE FROM '.Item::TABLE_PROPERTY
               .    ' WHERE locale'.$ope
               .      ' AND model_id='.$item->getModelId()
               .      ' AND record_id='.$item->getId());
  }

  if ($req->hasAttribute('relations')) {
    foreach ($req->relations as $model => $values) {
      $set = $item->getItems($model)->asSet();
      $has_many = Model::parameter($item->getModel(), 'has_many');
      $through = $has_many[$model]['through'];
      if (empty($through)) continue ;
      $values = empty($values) ? array() : $values;
      if ($dbo->getTable($through)->hasField('id')) continue ;
      $item_foreign_key = Model::parameter(MODEL, 'foreign_key');
      $model_foreign_key = Model::parameter($model, 'foreign_key');
      $skip = array();
      foreach ($values as $id) {
        if (in_array($id, $set)) {
          $skip[] = $id;
          continue ;
        }
        $dbo->insert($through,
                     array($item_foreign_key => $item->getId(),
                           $model_foreign_key => $id));
      }
      foreach ($set as $id) {
        if (in_array($id, $skip)) continue ;
        $dbo->exec('DELETE FROM '.$through
                   .' WHERE '.$item_foreign_key.'='.$item->getId()
                   .  ' AND '.$model_foreign_key.'='.$id);
      }
    }
  }

  if ($item->isNew()) {
    $item->setMetas(array('admin' => $admin->getId()));
  }

  if (method_exists($item, 'onAfterStore')) {
    $item->onAfterStore();
  }

  $ctx->setAttributes($item);

  $ctx->is_node = TreeManager::isNode($item);
  $ctx->model = $item->getModel();

}
catch (DuplicateRecordException $e) { $err->add(l('error.item.duplicate')); }
catch (Exception $e) {
  $log->error($e);
  $err->add($e);
}

