<?php

class App
{
  const PATH = 'applications';

  private $attributes = array();
  public $ts = null;

  public function __construct($register) {
    if (!is_array($register)) {
      $name = $register;
      $register = array();
      include ETC_PATH.'/'.self::PATH.'/'.$name.'.conf.inc';
    }
    $this->attributes = $register;
  }
  
  public function hasManager() { 
    $manager = $this->getManager();
    return !empty($manager);
  }
  
  public function getManager() {
    return $this->getAttribute('app.manager');
  }
  
  public function hook($method, $args=null) { 
    $manager = $this->getManager(); 
    if (!($this->hasManager() && method_exists($manager, $method))) {
      return false;
    } 
    call_user_func(array($manager, $method), $args);
  }
  
  public function getName() {
    return $this->getAttribute('app.name');
  }

  public function getLocale() {
    $locales = $this->getAttribute('app.locales');
    $locale = reset($locales); 
    return $locale ?: I18N::LOCALE_FR;
  }

  public function getLocales() {
    return $this->getAttribute('app.locales');
  }
  
  public function hasAttribute($key) { 
    return array_key_exists($key, $this->attributes);
  }
  
  public function getAttributes() {
    return $this->attributes;
  }
  
  public function getAttribute($key) { 
    return $this->attributes[$key]; 
  }
  
  public function debug() {
    S('log')->debug($this->attributes);
  }

  public static function all() {
    $apps = array();
    foreach (glob(ETC_PATH.'/'.self::PATH.'/*.inc') as $file) {
      $register = array();
      include $file;
      $apps[$register['app.name']] = $register;
    }
    return $apps;
  }
  
  public static function asAttributes($name) {
    $register = array();
    $file = ETC_PATH.'/'.self::PATH.'/'.$name.'.conf.inc';
    if (!file_exists($file)) {
      throw new Exception('invalid app name ['.$name.']', __METHOD__);
    }
    include $file;
    return $register;
  }

  public static function asHash($name) {
    $register = array();
    $file = ETC_PATH.'/'.self::PATH.'/'.$name.'.conf.inc';
    if (!file_exists($file)) {
      throw new Exception('invalid app name ['.$name.']', __METHOD__);
    }
    include $file;
    return $register;
  }
  
  public static function names($only_values=false) {
    $apps = array();
    if ($only_values === false) {
      $apps[''] = '--';
    }
    foreach (glob(ETC_PATH.'/'.self::PATH.'/*.inc') as $file) {
      $register = array();
      include $file;
      $apps[$register['app.name']] = $register['app.name'];
    }
    asort($apps);
    return $apps;
  }

  public static function number() {
    return (int) P('regexp');
  }

  public static function getInstance($name=null) {

    if (!is_null($name)) {
      return new App($name);
    }

    foreach (array('extensions', 'models', 'parameters', 'register') as $key) {
      $GLOBALS[$key] = (array) $GLOBALS[$key];
    }

    $regexp = $GLOBALS['register']['regexp'];
    $register = array();
    if (IS_CLI) {
      if (!file_exists(basename($_SERVER['argv'][0]))) {
        throw new Exception('Please changedir in the DocumentRoot directory.');
      }
      $env = $_ENV['KWO_APP'];
      if (count($regexp) >= 1 &&
          strlen($env) >= 2 &&
          file_exists(ETC_PATH.'/'.self::PATH.'/'.$env.'.conf.inc')) {
        include ETC_PATH.'/'.self::PATH.'/'.$env.'.conf.inc';
      }
      else {
        $files = glob(ETC_PATH.'/'.self::PATH.'/*.conf.inc');
        include $files[0]; 
      }
    } 
    else {
      $hostname = $_SERVER['HTTP_HOST'];
      if (count($regexp) === 1 || strlen($hostname) < 1) {
        include current($regexp); 
      }
      else {
        $flag = false;
        foreach ($regexp as $reg => $path) {
          if (preg_match($reg, $hostname) > 0) {
            $flag = true;
            include $path;
            break ;
          }
          }
        if ($flag === false) {
          include $path;
        }
      }
    }
      
    $app = new App($register);
        
    $GLOBALS['register'] += (array) $app->getAttributes();
    
    foreach ($GLOBALS['register'] as $key => $value) {
      if (isset($GLOBALS['parameters'][$key])) continue ;
      $GLOBALS['parameters'][$key] = $value;
    }
    
    unset($GLOBALS['register']);

    S('ctx')->setAttribute('_app', (string) $app->getName());
    
    $app->ts = time();

    Platform::addSingleton('app', $app);

  }
  
}
