<?php

class Action extends ActiveRecord {

  public static function extensions($filter=false) {
    $extensions = $set = array();
    if ($filter == true) {
      $set = S('dbo')->asSet('SELECT DISTINCT extension_id FROM '.T('action'));
    }
    foreach (Extension::all() as $extension) {
      if ($filter === true && !in_array($extension['id'], $set)) continue ;
      $extensions[$extension['id']] = $extension['name'];
    }
    return $extensions;
  }

  protected function onAfterCommit($hash) {
    ConfigManager::DBCacheBuild();
  }

  protected function onAfterDestroy() {
    ConfigManager::DBCacheBuild();
  }
  
  public static function asCache() {
    $rs = S('dbo')->query('SELECT id, extension_id, name FROM '.T('action'));
    $hash = array();
    foreach ($rs as $row) {
      $key = Extension::name($row['extension_id']).'.'.$row['name'];
      $hash[$key] = $row['id'];
    }
    return $hash;
  }
  
  public static function asHash() {
    return $GLOBALS['actions'];
  }

}