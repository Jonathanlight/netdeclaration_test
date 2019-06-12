<?php

/* no underscore in subdomain */

class Cookie 
{
  const NAME = 'storage';

  private $attrs = array();
  private $domain = null;
  private $expire = null;
  private $is_altered = false;
  private $is_new = false;
  private $is_removed = false;
  private $name = '';
  private $path = '/';
  private $value = null;

  public static $stack = array();

  public function __construct($name, $expire=null) {
    $this->name = $name;
    $parts = explode('.', S('req')->getServer('host'));
    if (count($parts) >= 2) {
      $parts = array_slice($parts, -2);
      $this->domain = '.' . join('.', $parts);
      if (strpos($this->domain, ':') !== false) {
        list ($this->domain, ) = explode(':', $this->domain, 2);
      }
    }
    if (isset($_COOKIE[$this->name])) {
      $this->value = $_COOKIE[$this->name];
      if (empty($this->value)) {
        $this->attrs = array();
      }
      else {
        list ($checksum, $datas) = explode("\t", $this->value, 2); 
        if ($checksum == $this->getChecksum($datas)) {
          $this->attrs = Hash::decode($datas);
          if (empty($this->attrs)) {
            $this->is_altered = true;
          }
        }
        else {
          $this->is_altered = true;
          $this->attrs = array();
          S('log')->error('invalid checksum ['.$this->value.']', __METHOD__);
        }
      }
    }
    else {
      $this->value = '';
      $this->attrs = array();
    }
    $this->setMaxAge($expire ?: time() + 31536000);
  }

  public function getName() {
    return $this->name;
  }

  private function setMaxAge($expire) {
    $this->expire = (int) $expire;
  }

  public function setPath($path) {
    $this->path = $path;
  }

  public function setSecure($value) {
    $this->secure = $value;
  }

  public function hasAttribute($key, $check_value=false) {
    if (!array_key_exists($key, $this->attrs)) return false;
    if ($check_value === true && 
        ($this->attrs[$key] === null || 
         $this->attrs[$key] === '')) return false;
    return true;
  }

  public function hasAttributes() {
    $attrs = is_array(func_get_arg(0)) ? func_get_arg(0) : func_get_args();
    if (is_bool($attrs[count($attrs) - 1])) {
      $check_content = array_pop($attrs);
    }
    else {
      $check_content = false;
    }
    foreach ($attrs as $attr) {
      if ($check_content === true && empty($attr)) return false; 
      if (!array_key_exists($attr, $this->attrs)) return false; 
    }
    return true;
  }
  
  public function setAttributes($hash) {
    foreach ($hash as $key => $value) {
      $this->setAttribute($key, $value);
    }
  }

  public function setAttribute($key, $value) {
    if (is_scalar($value) && $this->attrs[$key] == $value) {
      return false;
    }
    $this->is_altered = true;
    $this->attrs[$key] = $value;
    return true;
  }

  public function getAttribute($key) {
    return $this->attrs[$key];
  }

  public function getAttributes() {
    return $this->attrs;
  }

  public function removeAttribute($key) {
    if (!array_key_exists($key, $this->attrs)) {
      return false;
    } 
    $this->is_altered = true;
    $ret = $this->attrs[$key];
    unset($this->attrs[$key]);
    return $ret;
  }

  public function remove() {
    $this->is_altered = true;
    $this->is_removed = true;
  }

  public function commit() {
    if ($this->is_altered === false) {
      return false;
    }
    if ($this->is_removed === true) {
      $value = '';
      $expire = time() - 3600;
    }
    else {
      if (empty($this->value) && empty($this->attrs)) {
        return false;
      }
      $expire = $this->expire;
      $value = $this->getRawValue();
    }
    setcookie($this->name, $value, $expire, $this->path, 
              $this->domain, false, true);
    return true;
  }

  public function asString() {
    return $this->name.'='.urlencode($this->getRawValue());
  }

  private function getChecksum($str) {
    $str = $this->name . $str;
    $str = sprintf('%u', crc32($str));
    return substr($str, 0, 8);
  }

  private function getRawValue() {
    if (empty($this->attrs)) return '';
    $value = Hash::encode($this->attrs);
    $value = $this->getChecksum($value)."\t".$value;
    return $value;
  }

  public function debug() { 
    S('log')->debug('name='.$this->name);
    S('log')->debug($this->attrs);
  }

  public function __set($key, $value) { $this->setAttribute($key, $value); }

  public function __get($key) { return $this->getAttribute($key); }

  public function __isset($key) { return $this->hasAttribute($key); }

  public function __toString() { $this->getName(); }

}
