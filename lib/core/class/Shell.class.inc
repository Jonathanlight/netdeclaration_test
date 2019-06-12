<?php

/***

file_put_contents('compress.zlib://gzipfile.gz', 'DATA');
readfile('compress.zlib://gzipfile.gz');

readfile('php://filter/read=string.strip_tags/resource=http://digg.com');

COMMAND LINE INPUT
file_get_contents('php://stdin');
POST DATA
file_get_contents('php://input');
***/

class Shell
{ 

  const PHP_BIN = '/usr/bin/php -d mbstring.func_overload=7';

  public static $bins = array('cat'      => '/bin/cat',
                              'chown'    => '/bin/chown',
                              'colrm'    => '/usr/bin/colrm',
                              'cp'       => '/bin/cp',
                              'cut'      => '/bin/cut',
                              'du'       => '/usr/bin/du',
                              'file'     => '/usr/bin/file',
                              'grep'     => '/bin/grep',
                              'htpasswd' => '/usr/bin/htpasswd',
                              'id'       => '/usr/bin/id',
                              'kexec'    => 'inc/opt/bin/kexec',
                              'killall'  => '/usr/bin/killall',
                              'ls'       => '/bin/ls',
                              'mv'       => '/bin/mv',
                              'rm'       => '/bin/rm',
                              'service'  => '/sbin/service',
                              'setquota' => '/usr/sbin/setquota',
                              'sort'     => '/bin/sort',
                              'tail'     => '/usr/bin/tail',
                              'useradd'  => '/usr/sbin/useradd',
                              'userdel'  => '/usr/sbin/userdel',
                              'usermod'  => '/usr/sbin/usermod',
                              'wc'       => '/usr/bin/wc');

  public static function exec($cmd) {
    $clean_cmd = escapeshellcmd($cmd);
    if ($cmd != $clean_cmd) {
      S('log')->error($clean_cmd, __METHOD__);
      return ;
    }
    //    S('log')->trace($clean_cmd);
    $ret = 0;
    $line = system($clean_cmd, $ret);
    if ($line === false) return false;
    return array('last_line' => $line, 
                 'return_var' => $ret);
  }

  public static function du($path) {
    $hash = self::exec(self::$bins['du'].' -sh '.$path);
    list ($a, $b) = explode("\t", $hash['last_line']);
    return $a;
  }
  
  public static function confirm($msg, $default_yes=false) {
    $y = $default_yes === true ? 'Y' : 'y';
    $n = $default_yes === false ? 'N' : 'n';
    S('res')->write($msg.' ? ['.$y.'/'.$n.'] ');
    $ret = fgets(STDIN);
    $ret = trim($ret);
    if ($default_yes === true && strlen($ret) === 0) return true;
    if (strtolower($ret) === 'y') return true;
    return false;
  }
  
  public static function prompt($msg, $default=null) {
    $msg = $default !== null ? $msg.' ['.$default.']' : $msg;
    S('res')->write($msg.' ');
    $ret = fgets(STDIN);
    $ret = trim($ret);
    $ret = empty($ret) && $default !== null ? $default : $ret;
    return $ret;
  }

  public static function readLine($s) {
    S('res')->write($s);
    $ret = fgets(STDIN);
    $ret = trim($ret);
    return $ret;
  }

  public static function stat() {
    return stat(APP_PATH);
  }

  public static function daemonize() {
    $pid = pcntl_fork();
    if ($pid == -1) {
      throw new Exception('cannot fork');
    }
    if ($pid > 0) {
      return $pid;
    }
    fclose(STDIN);
    fclose(STDOUT);
    fclose(STDERR);
    return false;
  }

  public static function removeDir($path) {
    $path = trim($path);
    if (strlen($path) < 3 || 
	$path[0] == '/' || 
	!is_dir($path) ||
	!is_writable($path) ||
	in_array($path, array(APP_PATH, ETC_PATH, LIB_PATH,
                              PUB_PATH, VAR_PATH)) ||
	strpos($path, '..') !== false ||
	strpos($path, '~') !== false) {
      S('log')->error('invalid path ['.$path.']', __METHOD__);
      throw new Exception('invalid path ['.$path.']', __METHOD__);
    }
    $cmd = 'rm -r '.$path;
    self::exec($cmd);
    S('log')->trace($cmd);
  }

  public static function chownDir($path) {
    $path = trim($path);
    $parent = substr($path, 0, 3);
    if (strlen($path) < 3 || 
	$path[0] == '/' || 
	!is_dir($path) ||
	!is_writable($path) ||
	!in_array($parent, array(APP_PATH, ETC_PATH, LIB_PATH,
                                 PUB_PATH, VAR_PATH)) ||
	strpos($path, '..') !== false ||
	strpos($path, '~') !== false) {
      S('log')->error('invalid path ['.$path.']', __METHOD__);
      throw new Exception('invalid path ['.$path.']');
    }
    $user = System::getApacheUser();
    $user = $user['name'];
    if (strlen($user) < 2) {
      S('log')->error('invalid user ['.$user.']', __METHOD__);
      throw new Exception('invalid user ['.$user.']');
    }
    $cmd = 'chown -R '.$user.':'.$user.' '.$path;
    self::exec($cmd);
//    S('log')->trace($cmd);
  }

}
