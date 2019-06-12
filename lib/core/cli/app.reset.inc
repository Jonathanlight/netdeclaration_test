<?php

return false;

try {
  
  $models = array('comment', 'abuse', 
                  'valuation',
                  'purchase', 'order', 'addressee', 'shipment', 'payment',
                  'transaction', 'debit', 'credit', 'movement',
                  'favorite', 'user', 'person', 'announcement',
                  'discussion', 'invitation', 'message',
                  'topic', 
                  'submission',
                  'conversion', 'affiliate',
                  'sponsorship', 'notification', 'suggestion', 'subscription', 
                  'task', 'email', 'url');
  foreach ($models as $model) {
    if (!Model::exists($model)) {
      $log->trace('Model ['.$model.'] does not exist');
      continue ;
    }
    echo "- $model \n";
    $items = Item::collect($model);
    foreach ($items as $item) {
      try {
        $item->destroy();
      }
      catch (Exception $e) {
        $log->error($e);
      }
    }
    $dbo->getTable(T($model))->truncate();
  }
  
  $tables = array('cty_acl', 'cty_auth_attempt', 'cty_user_information', 'cty_privilege_user',
                  'psh_smtp', 'psh_base_email', 'psh_act', 'psh_queue',
                  'shp_discount_purchase', 'shp_discount_order', 'shp_discount_item',
                  'soc_blacklist', 'soc_stream', 'soc_group_user', 'soc_message_user', 'soc_friend',
                  'sys_draft', 'sys_ping',
                  Captcha::TABLE, Item::TABLE_REVISION, Item::TABLE_LOG, Intent::TABLE);
  foreach ($tables as $table) {
    if (!$dbo->hasTable($table, false)) {
      S('log')->trace('table unknown : '.$table);
      continue ;
    }
    $dbo->getTable($table)->truncate();
  }
  
  $metas = array('abuse', 'comment', 'comment', 'cluster',
                 'visit', 'display', 'user', 'subscription',
                 'dislike', 'like',
                 'rate', 'rating');
  foreach ($metas as &$meta) {
    $meta = '`'.$meta.'`=0'; 
  }
  $dbo->exec('UPDATE '.Meta::TABLE.' SET '.join(', ', $metas));
  
  $prefixes = array('tkr_*', 'alt_*');
  foreach ($prefixes as $prefix) {
    $tables = $dbo->getTables($prefix);
    foreach ($tables as $table) {
      echo $table."\n";
      $table->truncate();
    }
  }
  
  if (Model::exists('engine')) {
    $tables = array(Document::TABLE, 
                    Engine::TABLE_BUCKET, Engine::TABLE_INDEX, 
                    Engine::TABLE_STEM);
    foreach ($tables as $table) {
      if (!$dbo->hasTable($table, false)) {
        S('log')->trace('table unknown : '.$table);
        continue ;
      }
      $dbo->getTable($table)->truncate();
    }
    $models = (array) P('extension.search.models');
    foreach ($models as $model) {
      $items = Item::collect($model);
      foreach ($items as $item) {
        $item->index();
      }
    }
  }
  
  foreach ($dbo->getTables() as $table) {
    $table->repair();
    $table->optimize();
  }
  
  try {
    S('app')->hook('onAppReset');
  }
  catch (Exception $e) {
    $log->error($e);
  }
  
  if (Model::exists('user')) {
    User::clean();
  }
  
  Cache::clean();
  Session::clean();
  Logger::clean();
  UploadManager::clean();
  
  echo '- Update : Cookie Names (maybe)' . "\n";
  echo '- Execute : item.clean' . "\n";
  
}
catch (Exception $e) { $err->add($e); }
