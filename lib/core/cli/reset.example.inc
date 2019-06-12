<?php

return false;

try {

  $models = array('purchase', 'order', 'cart', 'addressee', 
                  'transaction', 'debit', 'credit'
                  'user', 'person',
                  'favorite',
                  'sponsorship', 'notification',
                  'comment', 'abuse');
  foreach ($models as $model) {
    if (!Model::exists($model)) continue ;
    echo "- $model \n";
    $items = Item::collect($model);
    foreach ($items as $item) {
      $item->destroy();
    }
    $dbo->getTable(T($model))->truncate();
  }

  $tables = $dbo->getTables('tkr_*');
  foreach ($tables as $table) {
    echo $table."\n";
    $table->truncate();
  }

  $fields = array('abuse=0', 'comment=0', 'comment=0',
                  'visit=0', 'display=0', 'user=0', 
                  'dislike=0', 'like=0',
                  'rate=0', 'rating=0');
  $dbo->exec('UPDATE '.Meta::TABLE.' SET '.join(', ', $fields));

  $tables = array(Captcha::TABLE, Item::TABLE_REVISION,
                  Item::TABLE_LOG, Intent::TABLE, 
                  'sys_url', 'sys_draft', 'psh_smtp');
  foreach ($tables as $table) {
    if (!$dbo->hasTable($table, false)) {
      S('log')->trace('table unknown : '.$table);
      continue ;
    }
    $dbo->getTable()->truncate();
  }

  $tables = $dbo->getTables('sch_*');
  foreach ($tables as $table) {
    echo $table."\n";
    $table->truncate();
  }
  
  $set = (array) P('extension.search.models');
  foreach ($set as $model_id) {
    if ($model_id < 1) continue ;
    $model_name = Model::name($model_id);
    $items = Item::collect($model_name);
    foreach ($items as $item) {
      $item->index();
    }
  }

  foreach ($dbo->getTables() as $table) {
    $table->repair();
    $table->optimize();
  }


}
catch (Exception $e) { $err->add($e); }
