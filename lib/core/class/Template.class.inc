<?php

class Template
{
  private $current = null;
  private $sources = array();
  private $tiles = array();
  private $used_tiles = array();

  const PATH = 'templates';

  public function __construct() { }

  private function loadSource($name) {
    if (array_key_exists($name, $this->sources)) return true;
    $src = @file_get_contents($this->tiles[$name]);
    if ($src === false || strlen($src) < 1) {
      if ($src === false) {
        S('log')->error('error [name='.$name.' path='.$this->tiles[$name].']',
                        __METHOD__);
      }
      $src = '';
    }
    $this->sources[$name] = $src;
  }

  private function _addTile($name, $path=null) {
    if ($path === null) {
      if (strpos($name, '/') === false) {
        if (strpos($name, ':') === false) {
          $req = S('req');
          $extension = $req->extension();
          if ($req->isFront() || $req->isMiddle() || $req->isAccount()) {
            $path = APP_PATH.'/'.$extension.'/'.self::PATH.'/'.$name.'.psp';
          }
          else {
            $path = LIB_PATH.'/'.$extension.'/'.self::PATH.'/'.$name.'.psp';
          }
        }
        else {
          list($ext, $file) = explode(':', $name);
          $path = APP_PATH.'/'.$ext.'/'.self::PATH.'/'.$file.'.psp';
        }
      }
      else {
        if ($name[0] === '/') {
          if ($name[1] != '/') {
            $path = APP_PATH.'/'.CORE.'/'.self::PATH.'/'.substr($name, 1).'.psp';
          }
          else {
            $path = LIB_PATH.'/'.CORE.'/'.self::PATH.'/'.substr($name, 1).'.psp';
          }
        }
        else {
          $path = $name;
        }
      }
    }
    else $path = trim($path, '/');
    $this->tiles[$name] = $path;
  }

  public function _setTile($name, $src) {
    $this->tiles[$name] = $src;
    $this->sources[$name] = $src;
  }

  public function _useTiles() {
    $this->used_tiles = array();
    $args = is_array(func_get_arg(0)) ? func_get_arg(0) : func_get_args();
    foreach ($args as $tile) {
      if ($tile === null) {
      	$this->used_tiles = array();
      	continue;
      }
      if (!array_key_exists($tile, $this->tiles)) {
        $this->_addTile($tile);
      }
      if (!array_key_exists($tile, $this->sources)) {
        $this->loadSource($tile);
      }
      $this->used_tiles[] = $tile;
    }
  }

  public function apply($container_obj=null) {
    $out = '';
    if ($container_obj instanceof Context ||
	$container_obj instanceof ActiveRecord) {
      $container_obj = $container_obj->getAttributes();
    }
    elseif (is_object($container_obj)) {
      $container_obj = get_object_vars($container_obj);
    }
    elseif (!is_array($container_obj)) {
      $container_obj = array();
    }

    extract($container_obj, EXTR_SKIP);
    unset($container_obj);

    $this->used_tiles = array_reverse($this->used_tiles);
    //    error_log(E_ALL & ~(E_NOTICE | E_WARNING));
    $original_handler = set_error_handler(array($this, 'onTemplateError'),
                                          E_ALL & ~E_NOTICE);
    foreach ($this->used_tiles as $tile) {
      $this->current = $tile;
      ob_start();
      if (eval('?>'.$this->sources[$tile].'<?php ') === false) {
        $hash = error_get_last();
        S('log')->error($hash['message']
                        .' on line '.$hash['line']
                        .' ['.$hash['type'].']',
                        $this->tiles[$this->current]);
      }
      $_content = ob_get_clean();
    }
    restore_error_handler();
    $out = $_content;
    return $out;
  }

  public function onTemplateError($errno, $errstr, $errfile, $errline) {
    if ($errno & E_WARNING) return ;
    S('log')->error($this->tiles[$this->current]
                    .' (line='.$errline.':err='.$errno.')'
                    .' '.trim($errstr), 
                    __METHOD__);
    return true;
  }

  /*** STATIC ***/

  private static $_singleton = null;

  public static function render($templates, $bindings=null) {
    if (empty($templates)) {
      S('log')->error('invalid template', __METHOD__);
      return '';
    }
    if ($bindings === true) {
      $bindings = S('ctx')->getAttributes();
    }
    elseif ($bindings instanceof Context || $bindings instanceof ActiveRecord) {
      $bindings = $bindings->getAttributes();
    }
    $template = self::getInstance();
    $template->_useTiles((array) $templates);
    return $template->apply($bindings);
  }

  public static function addTile($name, $code) {
    self::getInstance()->_setTile($name, $code);
  }

  public static function getInstance() {
    if (self::$_singleton === null) {
      $class = __CLASS__;
      self::$_singleton = new $class;
    }
    return self::$_singleton;
  }

}

