<?php

try {

  if (file_exists(Platform::LOCKER)) {
    throw new Exception('locker file exists ['.Platform::LOCKER.'] ; '.
                        'please remove manually or buid');
  }

  $app_name = $req->name;
  if (empty($app_name)) {
    $app_name = Shell::prompt('App name ?');
  }
  else {
    echo 'App name : '.$app_name."\n";
  }
  $app_conf = ETC_PATH.'/applications/'.$app_name.'.conf.inc';
  if (!file_exists($app_conf)) {
    throw new Exception('invalid app ['.$app_name.']');
  }

  $app = App::asAttributes($app_name);

  $extension_name = $app['app.extension'];

  if (!Extension::exists($extension_name)) {
    throw new Exception('invalid extension ['.$extension_name.']');
  }
  
  $extension = Extension::asAttributes($extension_name);

  if ($extension['id'] < Extension::EXTERNAL_THRESHOLD) {
    throw new Exception('invalid extension id ['.$extension['id'].']');
  }

  if (!Shell::confirm('Remove extension : '.$extension_name, true)) return ;

  $opts = array('filters' => array('app' => $app_name));
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
  
  foreach (Model::all() as $model) {
    if (!Model::hasField($model, 'app')) continue ;
    $opts = array('filters' => array('app' => $app_name));
    $items = Item::collect($model, $opts);
    foreach ($items as $item) {
      $item->destroy();
    }
    $dbo->resetAutoIncrement(T($model));
  }

  try {
    $ext = Extension::getInstance($extension_name);
    $ext->archive();
    $ext->uninstall();
    if (is_dir(DOC_PATH.'/'.$extension_name)) {
      Shell::removeDir(DOC_PATH.'/'.$extension_name);
    }
  }
  catch (Exception $e) {
    $log->error($e);
  }
  
  unlink($app_conf);
    
}
catch (Exception $e) { 
  $log->error($e); 
  $err->add($e); 
}
