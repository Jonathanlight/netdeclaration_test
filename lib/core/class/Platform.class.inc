<?php

final class Platform 
{
  const BOOTSTRAP = 'init.php';
  const LOCKER = 'locker';

  const EXIT_STATUS_SUCCESS = 0;
  const EXIT_STATUS_FAILURE = 1;

  public function __construct() {}

  public function invoke() {
    Logger::getInstance();
    Error::getInstance();
    Context::getInstance();
    App::getInstance();
    DataBaseObject::getInstance();
    Request::getInstance();
    Response::getInstance();
    Storage::getInstance();
  }

  public function launch() {
    $app = self::getSingleton('app');
    $res = self::getSingleton('res');
    $req = self::getSingleton('req');
    try { 
      $app->hook('onAppStart');
      $scopes = P('app.scopes');
      $scopes[] = 'cli';
      if (!in_array($req->scope(), $scopes)) {
        S('log')->error('invalid scope');
        return self::EXIT_STATUS_FAILURE;
      }
      if (!$res->isFormat(Response::FORMAT_HTTP)) { 
        $this->execute(); 
      }
      $res->render();
      $app->hook('onAppStop');
      if (S('err')->count() > 0) {
        return self::EXIT_STATUS_FAILURE;
      }
    }
    catch (Exception $e) {
      error_log('[PLATFORM LEVEL]'
                .$e->getFile().':'
                .$e->getLine().' '
                .'['.$req->getClient('address').'] '
                .$e->getMessage());
     
      return self::EXIT_STATUS_FAILURE;
    }
    return self::EXIT_STATUS_SUCCESS;
  }

  private function execute() {
    $req = self::getSingleton('req');
    $log = self::getSingleton('log');
    $app = self::getSingleton('app');

    try {
      
      if ($req->isCli()) {
        if (file_exists('scheduler.stop')) {
          $log->warn('skipping ['.$req->action().']', __METHOD__);
          return ; 
        }
      }
      else {
        try {
          $app->hook('onActionStart');
        }
        catch (Exception $e) { $log->error($e, __METHOD__); } 
      }

      $controller = Controller::getInstance();
      $controller->exec();

      if (!$req->isCli()) {
        try {
          $app->hook('onActionStop');
        }
        catch (Exception $e) { $log->error($e, __METHOD__); } 
      }

    } 
    catch (Exception $e) {
      if ($req->isBack()) {
        if (!self::hasSingleton('admin')) {
          $elt = H::elt('img', null, 
                        array('on' => array('load' => "window.top.location='/".Admin::url()."';")));
          self::getSingleton('res')->write($elt);
          return ;
        }
        $log->error($e, __METHOD__);
        throw $e;
      }
      elseif ($req->isCli()) {
        S('err')->add($e);
        $log->error($e, __METHOD__);
        return ;
      }
      try { 
        if ($req->action() == 'server.error') return ;
        header('HTTP/1.0 404 Not Found', true, 404);
        $req->setErrorController();
        if ($req->isFront()) {
          $app->hook('onActionFail');
        }
        $this->execute();        
      }
      catch (Exception $e) { $log->error($e, __METHOD__); } 
    }
  }

  private static $singletons = array(); 

  public static function addSingleton($name, $obj) {
    if (!is_string($name) || !is_object($obj)) {
      self::$singletons['log']->error('failure ['.$name.']', __METHOD__);
      throw new Exception('singleton failure ['.$name.']');
    }
    self::$singletons[$name] = $obj;
    $GLOBALS['objects'][$name] = true;
    return $obj;
  }

  public static function getSingleton($name) {
    $ret = self::$singletons[$name];
    if ($ret === null) {
      self::$singletons['log']->error('failure ['.$name.']', __METHOD__);
    }
    return $ret;
  }

  public static function hasSingleton($name) {
    return is_object(self::$singletons[$name]);
  }

  public static function getInstance() {
    $platform = new Platform();
    $platform->invoke();
    $ret = $platform->launch();
    if (IS_CLI) {
      exit($ret);
    }
  }

}

final class MaliciousException extends Exception {
  public function __construct($msg='', $code=0) {
    S('log')->error($this, __CLASS__);
    S('req')->debug();
    $msg = empty($msg) ? 'malicious' : $msg;
    parent::__construct($msg, $code);                                             
  }
}

final class DataBaseException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class ActiveRecordException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class ClassRecordException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class UnknownRecordException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class DuplicateRecordException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class FileSystemException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class ProfileException extends Exception { 
  public $errors = array();
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class AuthException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class PrivilegeException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}

final class OrderException extends Exception { 
  public function __construct($msg='', $code=0) { parent::__construct($msg, $code); } 
}
