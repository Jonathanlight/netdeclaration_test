<?php

//php init.php scaffold extension=shop models=product,order

$mode = 0777;

try {
  
  if (file_exists(Platform::LOCKER)) {
    throw new Exception('locker file exists ['.Platform::LOCKER.'] ; '.
                        'please remove manually or buid');
  }

  if (!$req->hasAttribute('extension', true) ||
      ($req->extension != CORE && strlen($req->extension) < 3)) {
    throw new Exception('invalid extension ['.$req->extension.'], length must be >= 3');
  }

  if (is_numeric($req->extension[0])) {
    throw new Exception('invalid extension ['.$req->extension.'], can not start with a numeric');
  }

  $extension = strtolower($req->extension);
  
  if (in_array($extension, array('front', 'back', 'api', 'account'))) {
    throw new Exception('invalid extension name ['.$req->extension.']');
  }

  if (!is_dir(LIB_PATH.'/'.$extension)) {
    if (!Shell::confirm("\n".'Create extension <'.$extension.'> ?', true)) return ;
    if ($req->id > 500) {
      $extension_id = $req->id;
    }
    else {
      $extension_id = Extension::EXTERNAL_THRESHOLD;
      foreach (Extension::all() as $e) {
        if ($e['id'] >= $extension_id) {
          $extension_id = $e['id'] + 100;
          while ($e['id'] >= $extension_id) {
            $extension_id += 100;
          }
        }
      }
    }
    
    mkdir(LIB_PATH.'/'.$extension.'/back', $mode, true);
    mkdir(LIB_PATH.'/'.$extension.'/class', $mode);
    mkdir(LIB_PATH.'/'.$extension.'/cli', $mode);
    mkdir(LIB_PATH.'/'.$extension.'/infos', $mode);
    mkdir(LIB_PATH.'/'.$extension.'/sql', $mode);

    mkdir(ETC_PATH.'/extensions/'.$extension.'/models', $mode, true);
    $table_prefix = $req->hasAttribute('table_prefix') ? $req->table_prefix : $extension;
    $table_prefix = trim($table_prefix, '_*') . '_*';
    file_put_contents(ETC_PATH.'/extensions/'.$extension.'/parameters.conf.inc', 
'<?php

$parameter[\'id\'] = '.$extension_id.';
$parameter[\'name\'] = \''.$extension.'\';
$parameter[\'table_prefix\'] = \''.$table_prefix.'\';
');

    mkdir(LIB_PATH.'/'.$extension.'/account', $mode);
    mkdir(LIB_PATH.'/'.$extension.'/front', $mode);

    if (!is_dir(APP_PATH.'/'.$extension)) {
      mkdir(APP_PATH.'/'.$extension.'/pix', $mode, true);
      mkdir(APP_PATH.'/'.$extension.'/templates', $mode);
      mkdir(APP_PATH.'/'.$extension.'/locales', $mode);
      mkdir(APP_PATH.'/'.$extension.'/scripts', $mode);
      mkdir(APP_PATH.'/'.$extension.'/styles', $mode);
      file_put_contents(APP_PATH.'/'.$extension.'/scripts/front.js', 
                        'if (!Kwo) var Kwo = {};'."\n");
      touch(APP_PATH.'/'.$extension.'/styles/front.css');
      if (file_exists(APP_PATH.'/test/pix/favicon.png')) {
        copy(APP_PATH.'/test/pix/favicon.png',
             APP_PATH.'/'.$extension.'/pix/favicon.png');
      }
      if (file_exists(PIX_PATH.'/favicon.ico')) {
        copy(PIX_PATH.'/favicon.ico',
             APP_PATH.'/'.$extension.'/pix/favicon.ico');
      }
      /*      file_put_contents(APP_PATH.'/'.$extension.'/locales/messages_en.inc',
                        '<?php'."\n\n".'$words = array();');
      file_put_contents(APP_PATH.'/'.$extension.'/locales/messages_fr.inc',
      '<?php'."\n\n".'$words = array();');*/
    }
  }
  else {
    $extension_id = Extension::parameter($extension, 'id');
    $table_prefix = Extension::parameter($extension, 'table_prefix');
    if ($extension_id < 1) {
      throw new Exception('error extension_id ('.$extension_id.')');
    }
  }
  
  if (!is_dir(LIB_PATH.'/'.$extension.'/xml')) {
    mkdir(LIB_PATH.'/'.$extension.'/xml', $mode);
  }

  $models = array();
  if ($req->hasAttribute('model', true)) {
    $models = explode(',', $req->model);
  }
  elseif ($req->hasAttribute('models', true)) {
    $models = explode(',', $req->models);
  }

  if (count($models) >= 1) {
    $model_id = $extension_id; 
    foreach (Model::all() as $id => $model) {
      if (Model::parameter($model, 'extension') === $extension && $id >= $model_id) {
        $model_id = $id + 1;
      }
    }
  }

  sort($models);
  
  $table_prefix = rtrim($table_prefix, '*');
  $table_prefix = empty($table_prefix) ? $extension.'_' : $table_prefix;

  $invalid_models = array('association', 'bitmap', 'branch', 
                          'context', 'developer', 
                          'editor', 'file', 'folder', 'item', 
                          'record', 'workspace');

  $uis = array('edit', 'home', 'finder');
  foreach ($models as $model) {
    $model = strtolower(trim($model));
    if (in_array($model, $invalid_models)) {
      $log->warn('model name forbidden ['.$model.']');
      continue ;
    }
    if (substr($model, -2) == 'ie') { 
      $tmp = substr($model, 0, -2).'y';
      if (Model::exists($tmp) === true) {
        throw new Exception('model ['.$tmp.'] exists');
      }
    }
    if (file_exists(LIB_PATH.'/'.CORE.'/class/'.ucfirst($model).'.class.inc')) {
      $log->warn('model name forbidden ['.$model.'], class exists in '.CORE);
      continue ;
    }
    if (substr($model, -1) === 's') {
      throw new Exception('invalid name, final s forbidden ('.$model.')');
    }
    if (!Valid::isAlphanum($model, true)) {
      throw new Exception('invalid name, only letters are accepted ('.$model.')');
    }
    if (strlen($model) <= 2) {
      throw new Exception('bad model ('.$model.')');
    }
    if (Model::exists($model) === true) {
      $log->warn('model ['.$model.'] exists');
      continue ;
    }
    $class = LIB_PATH.'/'.$extension.'/class/'.ucfirst($model).'.class.inc';
    if (!file_exists($class)) {
      file_put_contents($class, '<?php'."\n\n".'class '.ucfirst($model).' extends ActiveRecord {}');
    }
    $conf = ETC_PATH.'/extensions/'.$extension.'/models/'.$model.'.conf.inc';
    if (!file_exists($conf)) {
      $table = $table_prefix.$model;
      file_put_contents($conf, '<?php

$parameter[\'id\'] = '.$model_id.';
$parameter[\'name\'] = \''.$model.'\';
$parameter[\'label\'] = \''.$model.'\';
$parameter[\'table\'] = \''.$table.'\';'."\n");
      $model_id++;
    }
    if (!$dbo->hasTable($table)) {
      $dbo->exec("CREATE TABLE ".$dbo->name().".`".$table."` (
`id` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`content` TEXT NOT NULL ,
`description` TEXT NOT NULL ,
`flags` INT UNSIGNED NOT NULL default '0',
`image` VARCHAR( 255 ) NOT NULL ,
`name` VARCHAR( 255 ) NOT NULL,
`status` TINYINT UNSIGNED NOT NULL DEFAULT '0'
) ENGINE = MYISAM");
    }
    foreach ($uis as $ui) {
      $dest = LIB_PATH.'/'.$extension.'/xml/'.strtolower($model).'.'.$ui.'.xml';
      if (!file_exists($dest)) {
        $src = LIB_PATH.'/'.CORE.'/xml/item/'.$ui.'.xml';
        if (!file_exists($src)) continue ;
        copy($src, $dest);
      }
    }
  }

  Shell::chownDir(APP_PATH);

  touch(Platform::LOCKER);

}
catch (Exception $e) { $log->error($e); }
