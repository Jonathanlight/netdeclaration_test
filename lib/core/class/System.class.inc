<?php

class System 
{

  public static function pwd() {
    return realpath($_SERVER['PWD']);
  }

  public static function fork($shellCmd) {
    exec("nice $shellCmd > /dev/null 2>&1 &");
  }

  public static function getApacheUser() {
    if (self::getOsType() === 'windows') return null;
    $users = array('apache', '_www', 'www-data', 'www', 
                   'wwwrun', 'httpd');
    foreach ($users as $user) {
      exec('id -u '.$user.' 2>&1', $uid, $ret);
      $uid = (int) $uid[0];
      if ($ret == Platform::EXIT_STATUS_SUCCESS && $uid > 0) {
        exec('id -g '.$user.' 2>&1', $gid, $ret);
        $gid = (int) $gid[0];
        if ($gid < 1) continue ;
        return array('uid' => $uid,
                     'gid' => $gid,
                     'user' => $user,
                     'name' => $user);
      }
    }
    return null;
  }

  public static function getOsType() {
    // windows, linux, osx
    $system = php_uname('s');
    $system = strtolower($system); 
    if ($system == 'linux') return 'linux';
    if (strpos($system, 'osx') !== false ||
        strpos($system, 'darwin') !== false) return 'osx';
    if (strpos($system, 'windows') !== false) return 'windows';
    S('log')->trace($system, __METHOD__);
    return 'unknown';
  }

  public static function getMysqlUser() {
    if (self::getOsType() === 'windows') return null;
    $users = array('mysql', '_mysql');
    foreach ($users as $user) {
      exec('id -u '.$user.' 2>&1', $uid, $ret);
      $uid = (int) $uid[0];
      if ($ret == Platform::EXIT_STATUS_SUCCESS && $uid > 0) {
        exec('id -g '.$user.' 2>&1', $gid, $ret);
        $gid = (int) $gid[0];
        if ($gid < 1) continue ;
        return array('uid' => $uid,
                     'gid' => $gid,
                     'user' => $user);
      }
    }
    return null;
  }

  public static function getLoadAvg() {
    $data = shell_exec('cat /proc/loadavg'); 
    $arr = explode(' ',$data);
    $arr[0] = $arr[0] * 100;
    return $arr[0];
  }

  public static function getUsedMemory() {
    
  }

}