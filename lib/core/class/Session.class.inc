<?php

class Session
{
  const PATH = 'var/session';

  const COOKIE_NAME = 'session';

  private static $parameters = array();

  public function __construct() {
    $this->start(__METHOD__);
    if (is_array($_SESSION)) {
      foreach ($_SESSION as $key => $value) {
        $this->{$key} = $value;
      }
    }
    $this->close();
    $this->setParameter('checksum', $this->getChecksum());
    S('req')->setParameter('session_id', 
                           $this->getParameter('name').'='.
                           $this->getParameter('id'));
  }

  private function start($method) {
    $this->setParameter('name', self::COOKIE_NAME);
    $this->setParameter('path', '/');
    $parts = explode('.', S('req')->getServer('host'));
    if (count($parts) >= 2) {
      $parts = array_slice($parts, -2);
      $domain = '.'.join('.', $parts);
      if (strpos($domain, ':') !== false) {
        list ($domain, ) = explode(':', $domain);
      }
      $this->setParameter('domain', $domain);
    }
    session_name($this->getParameter('name'));
    if ($this->getParameter('domain')) {
      session_set_cookie_params(0, $this->getParameter('path'), 
                                $this->getParameter('domain'), false, true);
    }
    else {
      session_set_cookie_params(0, $this->getParameter('path'));
    }
    session_start();
    $this->setParameter('id', session_id()); 
  }

  public function commit() {
    $this->start(__METHOD__);
    $_SESSION = $this->getAttributes();
    $this->close();
  }

  private function close() {
    session_write_close();
  }

  protected function getChecksum() {
    $attributes = $this->getAttributes();
    return crc32(serialize($attributes));
  }

  public function invalidate() {
    $this->start(__METHOD__);
    $expire = time() - 3600;
    if ($this->getParameter('domain')) {
      $ret = setcookie($this->getParameter('name'), '', $expire,
                       $this->getParameter('path'),
                       $this->getParameter('domain'), false, true);
    }
    else {
      $ret = setcookie($this->getParameter('name'), '', $expire, 
                       $this->getParameter('path'));
    }
    if ($ret === false) {
      S('log')->error('setcookie() failure, '.$this->getParameter('domain'),
                      __METHOD__);
    }
    if (session_destroy() === false) {
      S('log')->error('session_destroy() failure', __METHOD__);
    }
    return $this;
  }

  public function setAttribute($key, $value) {
    return $this->setAttributes(array($key => $value));
  }

  public function setAttributes($hash) {
    if (!is_array($hash)) {
      S('log')->error('invalid input type', __METHOD__);
      return $this;
    }
    foreach ($hash as $key => $value) {
      $this->{$key} = $value;
    }
    return $this;
  }

  public function increment($key) {
    $this->{$key} = (int) $this->{$key} + 1;
    return $this;
  }

  public function removeAttribute($key) {
    $this->setAttribute($key, null);
    return $this;
  }

  public function getAttribute($key) {
    return $this->{$key};
  }

  public function isEmpty() {
    $attributes = $this->getAttributes();
    foreach ($attributes as $key => $value) {
      if (!is_null($value)) return false;
    }
    return true;
  }

  public function auth($user) {
    $attributes = array('id' => $user->getId(),
                        'email' => $user->email,
                        'name' => $user->name,
                        'notices' => $user->notices,
                        'privileges' => $user->privileges);
    $this->setAttribute('user', $attributes);
    $attributes = array('_user' =>  array('id' => $user->getId(),
                                          'name' => $user->name));
    S('ctx')->setAttributes($attributes);
    return $this;
  }

  public function logout() {
    $this->removeAttribute('user');
  }

  public function getAttributes() {
    $hash = array();
    foreach (get_object_vars($this) as $key => $value) {
      if ($value !== null) $hash[$key] = $value;
    }
    return $hash;
  }

  public function hasAttribute($key) {
    return property_exists($this, $key) && !is_null($this->{$key});
  }

  public function hasAttributes() {
    foreach (func_get_args() as $attribute) {
      if (!$this->hasAttribute($attribute)) return false;
    }
    return true;
  }

  public function debug() {
    S('log')->debug('session_name: '.$this->getParameter('name'));
    S('log')->debug('session_id: '.session_id());
    S('log')->debug('session_save_path: '.session_save_path());
    S('log')->debug(session_get_cookie_params(), 'session_cookie_params');
    S('log')->debug($_SESSION, 'session');
  }

  public function sync() {
    if ($this->getChecksum() == $this->getParameter('checksum')) {
      //      S('log')->trace('no commit', __METHOD__);
      return ;
    }
    //    S('log')->trace('commit', __METHOD__);
    $this->commit();
  }

  private function getParameter($key) {
    return self::$parameters[$key];
  }

  private function setParameter($key, $value) {
    self::$parameters[$key] = $value;
  }

  public static function clean() {
    if (strlen(self::PATH) < 9 || !is_dir(self::PATH)) return ;
    $files = glob(self::PATH.'/*/*/sess_*');
    $files = $files ?: array();
    $ts = time();
    $ttl = 24 * 60 * 60;
    foreach ($files as $file) {
      if (!file_exists($file)) continue ;
      $fts = filemtime($file);
      if (($ts - $fts) > $ttl) {
        unlink($file);
      }
    }
  }

  public static function build() {
    $mode = 0777;
    $stat = Shell::stat();
    if (strlen(Session::PATH) < 4) return ;
    $level1 = array_merge(range(0, 9), range('a', 'v'));
    $level2 = array_merge(range(0, 9), range('a', 'v'));
    foreach ($level1 as $c1) {
      foreach ($level2 as $c2) {
        $path = Session::PATH.'/'.$c1.'/'.$c2;
        if (is_dir($path)) continue ;
        mkdir($path, $mode, true);
        chown($path, $stat['uid']);
        chgrp($path, $stat['gid']);
      }
    }
  }

}





  /*  private function start($method) {
    if (S('req')->isFront() || S('req')->isMiddle() || S('req')->isAccount()) {
      $this->_name = self::COOKIE_NAME;
      $this->_path = '/';
      $parts = explode('.', S('req')->getServer('host'));

      if (count($parts) > 2) {
        $parts = array_slice($parts, -2);
        $this->_domain = '.'.join('.', $parts);
        if (strpos($this->_domain, ':') !== false) {
          list ($this->_domain, ) = explode(':', $this->_domain);
        }
      }
    }
    else {
      $this->_name = 'back_session_id'; 
      $this->_path = '/back';
    }
    session_name($this->_name);
    if ($this->_domain) {
      session_set_cookie_params(0, $this->_path, 
                                $this->_domain, false, true);
    }
    else {
      session_set_cookie_params(0, $this->_path);
    }
    session_start();
    $this->_id = session_id(); 
    //    d(array($this->_id, $this->_name, $this->_path, $_SERVER['SCRIPT_URL']));
    }*/