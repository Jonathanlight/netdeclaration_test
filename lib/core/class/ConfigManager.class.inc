<?php

class ConfigManager
{
  private static $trace = 0;

  const DBCACHE = 'dbcache.conf.inc';
  const JS_PLATFORM = 'app/core/scripts/platform.js';

  public static function checkSyntax($file_path) {
    $out = null;
    $ret = null;
    exec(Shell::PHP_BIN.' -l '.$file_path, $out, $ret);
    if ($ret != 0) {
      array_shift($out);
      throw new Exception(join(', ', $out));
      S('log')->debug($out, $file_path);
    }
    return true;
  }

  public static function platform() {

    $dbo = S('dbo');
    $log = S('log');

    if (!is_writable(ETC_PATH)) {
      throw new Exception(ETC_PATH.' is not writable');
    }

    $model_tables = array();
    $table2model = array();

    $js = '';

    self::trace('load and check models');
    foreach (glob(ETC_PATH.'/extensions/*/models/*.conf.inc') as $file_path) {
      self::checkSyntax($file_path);
      $parameter = array();
      include $file_path;
      if (!$dbo->hasTable($parameter['table'])) {
        throw new Exception('table ['.$parameter['table'].'] does not exist');
      }
      $model_tables[] = $parameter['table'];
      $table2model[$parameter['table']] = $parameter['name'];
      $js .= 'kwo.platform.models["'.$parameter['id'].'"] = "'.$parameter['name'].'";'."\n";
    }

    self::trace('write : '.self::JS_PLATFORM);
    file_put_contents(self::JS_PLATFORM, $js);

    self::trace('check extensions');
    foreach (glob(ETC_PATH.'/extensions/*/parameters.conf.inc') as $file_path) {
      self::checkSyntax($file_path);
    }

    $locker = Platform::LOCKER;

    $tmp_path = ETC_PATH.'/cache.tmp';
    $old_path = ETC_PATH.'/'.Model::PATH.'.'.time();

    $platform = '<?php'."\n\n";

    if (!is_dir($tmp_path)) {
      mkdir($tmp_path);
    }
    else {
      foreach (glob($tmp_path.'/*') as $file_path) {
        unlink($file_path);
      }
    }

    self::trace('load extensions');
    $scripts = array();
    $arr = array();
    foreach (glob(ETC_PATH.'/extensions/*/parameters.conf.inc') as $file_path) {
      $parameter = array();
      list (, , $name) = explode('/', $file_path);
      include $file_path;
      $arr[$parameter['id']] = $name;
      if (file_exists(APP_PATH.'/'.$name.'/controller.js') && 
          $name != CORE && 
          $parameter['id'] < Extension::EXTERNAL_THRESHOLD) {
        $scripts[] = $name;
      }
    }
    $platform .= '$extensions = '.var_export($arr, true).';'."\n";
    $platform .= "\n";

    $arr = array();

    self::trace('load models');
    $models = array();
    $profiles = array();
    foreach (glob(ETC_PATH.'/extensions/*/models/*.conf.inc') as $file_path) {
      try {
        $parameter = array();
        include $file_path;
        list (, , $extension) = explode('/', $file_path);
        $model = $parameter['name'];
        $parameter['extension'] = $extension;
        $parameter['foreign_key'] = $model.'_id';
        $parameters = self::model($model, $parameter);

        $models[$model] = $parameters;
        $arr[$parameters['id']] = $model;
        if ($parameters['profile_id'] > 0) {
          $profiles[$parameters['profile_id']] = $model;
        }
      }
      catch (Exception $e) { $log->error($e); }
    }
    ksort($arr);
    $platform .= '$models = '.var_export($arr, true).';'."\n\n";

    self::trace('load classes');
    $classes = array();
    foreach (glob(LIB_PATH.'/*/class/*.class.inc') as $file_path) {
      if (strpos($file_path, '/'.CORE.'/') !== false) {
        continue ;
      }
      $class = basename($file_path, '.class.inc');
      list (, $extension) = explode('/', $file_path);
      $classes[$class] = $extension;
    }
    $platform .= '$classes = '.var_export($classes, true).';'."\n";
    $platform .= "\n";
    
    self::trace('load apps');
    $regexp = array();
    foreach (glob(ETC_PATH.'/applications/*.conf.inc') as $file_path) {
      $register = array();
      include $file_path;
      $regexp[$register['app.regex']] = $file_path;
    }
    
    $register = array();
    
    self::trace('load item_tables');
    $register['item_tables'] = array(Meta::TABLE);
    foreach ($dbo as $table) {
      if ($table->hasFields('heading_id')) {
        $register['heading_models'][] = $table2model[$table->name()];
      }
      if (in_array($table->name(), $model_tables)) continue ;
      if (substr($table->name(), 0, 3) == 'tkr') continue ;
      if ($table->hasFields('model_id', 'record_id')) {
        $register['item_tables'][] = $table->name();
      }
    }

    ksort($profiles);

    $register['profiles'] = $profiles;
    $register['controllers'] = $scripts;
    $register['regexp'] = $regexp;
    $register['metas'] = $dbo->getTable(Meta::TABLE)->getFields();

    $platform .= '$register = '.var_export($register, true).';'."\n";
    
    self::trace('write : platform.conf.inc');
    file_put_contents($tmp_path.'/platform.conf.inc', $platform);

    $stat = Shell::stat();

    self::trace('chown / chgrp : platform.conf.inc');
    chown($tmp_path.'/platform.conf.inc', $stat['uid']);
    chgrp($tmp_path.'/platform.conf.inc', $stat['gid']);

    self::trace('relations');
    foreach ($models as $name => $parameters) {
      if (!$parameters['has_many']) continue ;
      foreach ($parameters['has_many'] as $key => $relation) {
        if ($relation['through'] === null) continue ;
        if ($models[$key]['has_many'][$name] != null) continue ;
        $relation['foreign_key'] = $name.'_id';
        $parameters['has_many'][$name] = $relation;
      }
    }
    
    self::trace('chown / chgrp : directory');
    chown($tmp_path, $stat['uid']);
    chgrp($tmp_path, $stat['gid']);

    self::trace('write : config model files');
    foreach ($models as $name => $parameters) {
      $file = $tmp_path.'/'.$name.'.conf.inc';
      $ret  = '<?php'."\n\n";
      $ret .= '$parameters = '.var_export($parameters, true).';'."\n";
      file_put_contents($file, $ret);
      chown($file, $stat['uid']);
      chgrp($file, $stat['gid']);
    }

    self::trace('renaming');
    rename(ETC_PATH.'/'.Model::PATH, $old_path);
    rename($tmp_path, ETC_PATH.'/'.Model::PATH);
    
    if (file_exists($old_path.'/'.self::DBCACHE)) {
      rename($old_path.'/'.self::DBCACHE,
             ETC_PATH.'/'.Model::PATH.'/'.self::DBCACHE);
    }
    
    self::trace('cleaning');
    foreach (glob($old_path.'/*.*') as $file_path) {
      unlink($file_path);
    }
    rmdir($old_path);

    self::trace('removing '.$locker);
    if (file_exists($locker)) {
      unlink($locker);
      self::trace('locker removal');
    }
    
    if (!file_exists(ETC_PATH.'/'.Model::PATH.'/'.self::DBCACHE)) {
      self::trace('dbcachebuild');
      self::DBCacheBuild();
    }

    self::trace('end');

  }

  public static function model($model, $parameters=null) {
//    $model = N($model);

    $file = null;
    if ($parameters === null) {
      $file = ETC_PATH.'/'.Model::PATH.'/'.$model.'.conf.inc';
      if (!file_exists($file)) {
        S('log')->error($file, __METHOD__);
        throw new ActiveRecordException();
      }
      include $file;
    }

    if (empty($parameters)) {
      S('log')->error('no parameters', __METHOD__);
      throw new ActiveRecordException();
    }

    unset($parameters['properties']);

    $properties = S('dbo')->asHash('SELECT *'
                                   .' FROM sys_property'
                                   .' WHERE model_id='.$parameters['id']
                                   .' ORDER BY name',
                                   null, 'name', 'id');
    if (!empty($properties)) {
      $parameters['properties'] = $properties;
    }

    if (!isset($parameters['label'])) {
      $parameters['label'] = $parameters['name'];
    }

    if ($parameters['profile_id'] > 0) {
      if (isset($parameters['belongs_to'])) {
        $parameters['belongs_to'] = (array) $parameters['belongs_to'];
        if (!in_array('user', $parameters['belongs_to'])) {
          $parameters['belongs_to'][] = 'user';
        }
      }
      else {
        $parameters['belongs_to'] = array('user');
      }
    }

    foreach (array('belongs_to', 'has_one', 'has_many') as $relation) {
      if (!isset($parameters[$relation])) continue ;
      $parameters[$relation] = (array) $parameters[$relation];
      $hash = array();
      foreach ($parameters[$relation] as $key => $value) {
        if (!is_array($value)) {
          $key = $value;
          $value = array();
        }
        if (!Model::exists($key)) continue ;
        $value['foreign_key'] = $key.'_id';
        if (isset($value['through'])) {
          $value['through_cols'] = S('dbo')->getTable($value['through'])->getFields();
          //          unset($value['through_cols'][0]);
          //          unset($value['through_cols'][1]);
          //          sort($value['through_cols']);
        }
        $hash[$key] = $value;
      }
      //      S('log')->debug($hash);
      $parameters[$relation] = $hash;
    }
    $parameters['metas'] = !isset($parameters['metas']) || $parameters['metas'] == true ? true : false;

    $table = $parameters['table'];
    $columns = $fields = array();
    foreach (S('dbo')->getTable($table)->getColumns() as $column) {
      $field = $column['Field'];
      $type = $column['Type'];
      if ($field === 'id') continue ;
      if ($field === 'flags' || $field === 'locales') {
        $parameters['casts'][$field] = 'bits';
      }
      if ($type === 'date') {
        $parameters['casts'][$field] = 'date';
      }
      if ($type === 'datetime' || $type === 'timestamp') {
        $parameters['casts'][$field] = 'datetime';
      }
      if (strpos($type, 'float') !== false) {
        $parameters['casts'][$field] = 'float';
      }
      $columns[] = $table.'.'.$field.' AS '.$model.'_'.$field;
      $fields[] = $field;
    }

    if (count($columns) < 1) {
      S('log')->error('no columns for model ['.$model.']', __METHOD__);
      return ;
    }

    $parameters['fields'] = $fields;
    $parameters['schema'] = join(', ', $columns);

    if (!empty($file)) {
      $ret  = '<?php'."\n\n";
      $ret .= '$parameters = '.var_export($parameters, true).';'."\n";
      file_put_contents($file, $ret);
    }

    return $parameters;

  }

  public static function DBCacheBuild() {
    try {
      $content  = '<?php'."\n\n";
      $data = Parameter::asCache();
      $content .= '$parameters = '.var_export($data, true).';'."\n\n";
      $data = Action::asCache();
      $content .= '$actions = '.var_export($data, true).';'."\n\n";
      $data = Redirection::asCache();
      $content .= '$redirections = '.var_export($data, true).';'."\n\n";
      $data = Extension::exists('performance') ? Goal::asCache() : array();
      $content .= '$goals = '.var_export($data, true).';'."\n\n";
      $data = Extension::exists('community') ? Privilege::asCache() : array();
      $content .= '$middle = '.var_export($data, true).';'."\n\n";
    }
    catch (Exception $e) {
      S('log')->error($e, __METHOD__);
      $content = '<?php'."\n\n";
    }
    $file = ETC_PATH.'/'.Model::PATH.'/'.self::DBCACHE;
    file_put_contents($file, $content);
    $stat = Shell::stat();
    chown($file, $stat['uid']);
    chgrp($file, $stat['gid']);
  }

  private static function trace($msg) {
    if (self::$trace < 1) return ;
    S('log')->trace('step : '.$msg);
  }

}
