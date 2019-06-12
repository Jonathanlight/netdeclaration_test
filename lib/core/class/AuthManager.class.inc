<?php

class AuthManager 
{
  const AUTH_FORM = 1;
  const AUTH_COOKIE = 2;
  const AUTH_TOKEN = 3;
  const AUTH_HTTP = 4;
  const AUTH_OAUTH = 5;
  const AUTH_IP = 6;

  public static $auth_types = array(self::AUTH_FORM => 'form',
                                    self::AUTH_COOKIE => 'cookie',
                                    self::AUTH_TOKEN => 'token',
                                    self::AUTH_HTTP => 'http',
                                    self::AUTH_OAUTH => 'oauth',
                                    self::AUTH_IP => 'ip');
  private $ctx = null;
  private $dbo = null;
  private $req = null;
  private $max_auth_attempt = 20;

  const TABLE_ATTEMPT = 'cty_auth_attempt';

  public function __construct() {
    $this->dbo = S('dbo');
    $this->ctx = S('ctx');
    $this->req = S('req');

    switch ($this->req->scope()) {
    case 'front':
    case 'middle':
    case 'account':
      $this->handleFront();
      break;
    }
  }
  
  private function handleFront() { 
    $this->ctx->setAttribute('_user', array('id' => 0));

    if ($this->req->hasSession()) { 
      $session = $this->req->getSession(); 
      if ($session->hasAttribute('user') && $session->user['id'] >= 1) {
        $this->ctx->setAttribute('_user', $session->getAttribute('user'));
        if ($this->req->isNewVisit()) {
          self::onUserAuth($this->ctx->_user['id']);
        }
        return ;
      }
    }
    
    if (!$this->checkRemote()) {
      $this->ctx->setAttribute('_auth_errors', l('error.access.denied'));
      return ;
    }

    $req = $this->req;
    $cookie = $req->getCookie();
    $bindings = array();  

    $identity = P('auth.identity') ?: 'email';

    $method = 'web';
    $auth_type = 0;

    if ($req->hasAttributes('login', 'password')) {
      $where = $identity.'=:login: AND password=MD5(:password:)'; 
      $bindings[':login:'] = $req->login;
      $bindings[':password:'] = $req->password;
      $auth_type = self::AUTH_FORM;
    }
    elseif ($req->hasAttribute('credential')) {
      list($md5, $id, $time) = explode('-', $req->getAttribute('credential'));
      if ((time() - $time) > (2 * 3600)) {
        S('log')->trace('credential expired : user ('.$id.')', __METHOD__);
        $this->ctx->setAttribute('_auth_errors', l('error.access.expired'));
        return ;
      }
      $where = 'id=:id: AND MD5(CONCAT(id, password, :time:))=:md5:';
      $bindings[':id:'] = $id;
      $bindings[':time:'] = $time;
      $bindings[':md5:'] = $md5;
      $method = 'credential';
      $auth_type = self::AUTH_TOKEN;
    }
    elseif ($cookie->hasAttributes('user_id', 'user_secret', true)) {
      $where = 'id=:user_id: AND SUBSTRING(password, 3, 8)=:user_secret:';
      $bindings[':user_id:'] = (int) $cookie->getAttribute('user_id');
      $bindings[':user_secret:'] = $cookie->getAttribute('user_secret');
      $method = 'cookie';
      $auth_type = self::AUTH_COOKIE;
    }
    elseif (false && isset($_SERVER['PHP_AUTH_USER']) && isset($_SERVER['PHP_AUTH_PW'])) {
      $where = $identity.'=:login: AND password=MD5(:password:)'; 
      $bindings[':login:'] = $_SERVER['PHP_AUTH_USER'];
      $bindings[':password:'] = $_SERVER['PHP_AUTH_PW'];
      $auth_type = self::AUTH_HTTP;
    }
    /*    elseif ($req->hasAttribute('eauth')) {
      try {
        list($id, $md5) = explode('-', $req->getAttribute('eauth'));
        $tmp = hash('md5', strval($id) . KWO_SEED);
        if ($md5 != substr($tmp, -8)) {
          return ;
        }
        $email = Email::getInstance($id);
        $where = $identity.'=:login:'; 
        $bindings[':login:'] = $email->email;
      }
      catch (Exception $e) { return ; }
      }*/
    
    if (count($bindings) <= 0) return;

    $rs = $this->dbo->query('SELECT * FROM '.T('user').' WHERE '.$where, 
                             $bindings);
    if ($rs === false || $rs->numRows() !== 1) {
      $this->dbo->insert(self::TABLE_ATTEMPT, 
                         array('ip' => $this->req->getClient('ip'))); 
      $req->track('login', Tracker::CATEGORY_ERROR);
      $cookie->removeAttribute('user_secret');
      $this->ctx->setAttribute('_auth_errors', l('error.access.denied'));
      $msg = 'login failure';
      if ($req->hasAttribute('login', true)) {
        $msg .= ' ['.$req->login.']';
      }
      S('log')->error($msg, __METHOD__);
      return ; 
    }

    $this->dbo->query('DELETE FROM '.self::TABLE_ATTEMPT
                      .    ' WHERE ip='.$this->req->getClient('ip')); 
    
    $obj = $rs->fetchObject(); 
    
    if ($obj->status < User::STATUS_PENDING) {
      S('log')->error('invalid account ('.$obj->id.')', __METHOD__);
      $this->ctx->setAttribute('_auth_errors', l('error.account.closed'));
      return ;
    }

    $cookie->setAttribute('user_id', $obj->id);

    if ($auth_type != self::AUTH_COOKIE && $cookie->hasAttribute('user_secret')) {
      $cookie->removeAttribute('user_secret');
    }

    if ($req->hasAttribute('remember_me') || 
        (!$req->hasAttribute('remember_me') && P('auth.sso') === true)) {
      $cookie->user_secret = substr($obj->password, 2, 8);
    }

    $user = User::getInstance((int) $obj->id);
    $user->setInformations(array('auth_at' => Date::now(),
                                 'auth_count' => $user->getInformation('auth_count') + 1));
        
    if (($method === 'credential' || $req->knxm === Tracker::MEDIUM_MAIL) && 
        $user->status == User::STATUS_PENDING) {
      $user->setAttribute('status', User::STATUS_CONFIRMED);
    }

    self::onUserAuth($user, $auth_type);

  }
    
  private function checkRemote() {
    $auth_count = $this->dbo->fetchValue('SELECT COUNT(*)'
                                         .' FROM '.self::TABLE_ATTEMPT
                                         .' WHERE ip='.$this->req->getClient('ip'));
    if ($auth_count < $this->max_auth_attempt) return true;
    S('log')->error('max auth attempts reached', __METHOD__);
    return false;
  }

  public static function onStartUp() {
    $ctx = S('ctx');
    $req = S('req');

    if (P('auth.login') !== null && !$req->isPhp() &&
        (strpos($req->action(), 'webservice.') === false) &&
        (strpos($req->action(), 'paiement.callback') === false) &&
        !($req->getClient('login') == P('auth.login') &&
          $req->getClient('password') == P('auth.password'))) {
      header('WWW-Authenticate: Basic realm="Welcome"');
      header('HTTP/1.0 401 Unauthorized');
      exit ;
    }

    if ((Extension::exists('community') && P('auth.level') >= 1) || 
        $req->isAccount() || $req->isMiddle()) { 
      AuthManager::getInstance();
    }

    $public = array('admin.signin', 'admin.login', 'paiement.callback',
                    'captcha', 'snippet', 'user.signup', 'signup', 
                    'password.send', 'email.confirm', 'smtp');
    if ($req->isAccount() || $req->isMiddle() || 
        (P('auth.level') === 2 && !in_array($req->action(), $public) &&
         $req->extension() != 'push')) {
      try {
        $user = $req->getUser();
        if ($req->isMiddle() && !$user->hasAnyPrivilege(Privilege::middle())) {
          throw new AuthException('need middle privilege');
        }
        $ctx->user = $user;
      }
      catch (AuthException $e) {
        S('log')->error($e, __METHOD__);
        User::signup();
        return false;
      }
    }
    return true;
  }

  public static function onUserAuth($user, $auth_type=0) {
    $auth_type = $auth_type > 1 ? $auth_type : self::AUTH_FORM;
    if (is_numeric($user)) {
      if ($user < 1) {
        S('log')->error('user_id ('.intval($user).')',
                        __METHOD__);
      }
      $user = User::getInstance($user);
    }
    $req = S('req');
    $session = $req->getSession();
    $session->auth($user);
    $visit_id = $req->getId();
    $user->track(Intent::TYPE_AUTH, 
                 array('value' => $auth_type));
    if ($visit_id > 0) {
      $dbo = S('dbo');
      $dbo->exec('UPDATE '.Intent::TABLE
                 .' SET user_id='.$user->getId()
                   .' WHERE visit_id='.$visit_id
                   .  ' AND user_id=0');
      /*      if (Extension::exists('kda')) {
        $dbo->exec('UPDATE '.KDA::TABLE_LOG
                   .' SET user_id='.$user->getId()
                   .' WHERE visit_id='.$visit_id
                   .  ' AND user_id=0');    
                   }*/
      if (Model::exists('conversion')) {
        $dbo->exec('UPDATE '.T('conversion')
                   .' SET user_id='.$user->getId()
                   .' WHERE visit_id='.$visit_id
                   .  ' AND user_id=0');    
      }
      if (Platform::hasSingleton('tracker')) {
        $dbo->exec('UPDATE '.Visit::TABLE
                   .' SET user_id='.$user->getId()
                   .' WHERE id='.$visit_id
                   .' LIMIT 1');
      }
    }
    if ($req->getParameter('visit_number') >= 3) {
      $user->setFlag(User::FLAG_ACCUSTOMED);
    }
    S('app')->hook('onUserAuth', array('user' => $user));
  }

  public static function getInstance() { 
    $class = __CLASS__;
    return new $class; 
  }

}
