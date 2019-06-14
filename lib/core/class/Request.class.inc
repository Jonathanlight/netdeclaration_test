<?php

class Request
{
  private static $parameters = array();
  
  const FORMAT_XMLRPC  = 1;
  const FORMAT_JSONRPC = 2;
  const FORMAT_SOAP    = 3;
  const FORMAT_REST    = 4;
  
  const XHR_EXEC   = 1;
  const XHR_UPDATE = 2;
  
  public function __construct() {}

  public function getBody() {
    return file_get_contents('php://input');
  }

  public function getBodyStream() {
    return 'php://input';
  }
  
  public function isAccount() { return $this->scope() === 'account'; }
  public function isApi() { return $this->scope() === 'api'; }
  public function isBack() { return $this->scope() === 'back'; }
  public function isCli() { return $this->scope() === 'cli'; }
  public function isFront() { return $this->scope() === 'front'; }
  public function isMiddle() { return $this->scope() === 'middle'; }
  
  public function isIe($version=null) {
    $regex = $version ? 'MSIE '.strval($version) : 'MSIE';
    return stripos($_SERVER['HTTP_USER_AGENT'], $regex) !== false;
  }
  
  public function isHttp() { return strlen($_SERVER['HTTP_HOST']) > 1; }
  
  public function isXhr($type=null) { 
    $ret = $this->hasHeader('x-prototype-version'); 
    if ($ret = false) {
      return stripos($_SERVER['HTTP_X_REQUESTED_WITH'], 'XMLHttpRequest') !== false;
    } 
    if ($type !== null) { 
      if ($type === self::XHR_UPDATE) {
        return $this->getHeader('x-kwo-request') === 'update';
      }
      else {
        return $this->getHeader('x-kwo-request') === 'exec';
      }
    }
    return true;
  }
  
  public function isPhp() {
    return $this->getHeader('x-requested-with') === 'php'; 
  }

  public function isRpc() { 
    return $this->getParameter('api_version') >= 1 
         ? $this->getParameter('api_version')
         : false; 
  }

  public function hasValidCaptcha() {
    try {
      Captcha::check();
      return true;
    }
    catch (Exception $e) {
      $this->track('captcha', Tracker::CATEGORY_ERROR);
      return false;
    }
  }

  public function getChecksum($type='CRC32') {
    if ($this->hasParameter('hash')) {
      return $this->getParameter('hash');
    }
    $attributes = $this->getAttributes();
    ksort($attributes);
    //    $location = strtr(trim($this->getPath(), '/'), '/.-[]()', '_______');
    //    $location 
    //    $location = empty($location) ? 'index' : $location;
    $data  = $this->scope().$this->extension().$this->action();
    $data .= Hash::encode($attributes);
    if ($type === 'MD5') {
      $hash = hash('md5', $data);
    }
    else {
      $hash = sprintf('%u', crc32($data));
    }
    $this->setParameter('hash', $hash);
    return $hash;
  }
  
  public function getHeader($key) {
    $key = strtolower($key);
    $headers = $this->getParameter('headers');
    if (!is_array($headers)) return false;
    return array_key_exists($key, $headers) ? $headers[$key] : false;
  }
  
  public function getHeaders() { 
    return $this->getParameter('headers'); 
  }

  public function hasHeader($key) { 
    $headers = $this->getParameter('headers');
    return is_array($headers) && array_key_exists(strtolower($key), $headers); 
  }

  public function scope() { 
    return $this->getParameter('scope'); 
  }

  public function extension() {
    return $this->getParameter('extension'); 
  }

  public function action() { 
    return $this->getParameter('action'); 
  }

  public function isPreview() {
    return $this->hasAttribute('p') && $this->p === 'y';
  }

  public function setErrorController() {
    return $this->setController('front', CORE, 'server.error');
  }

  public function setController($scope, $extension, $action, $path=null) {
    $this->setParameter('scope', $scope);
    $this->setParameter('extension', $extension);
    $this->setParameter('action', $action);
    $controller = $path ?: LIB_PATH.'/'.$extension.'/'.$scope.'/'.$action.'.inc';
    $this->setParameter('controller', $controller);
    return $controller;
  }

  public function getController() {
    return $this->getParameter('controller');
  }

  public function getLocale() { 
    if ($this->getParameter('locale') >= 1) {  
      return $this->getParameter('locale'); 
    }
    $locales = S('app')->getLocales();
    if (count($locales) === 1 || $this->isCli()) {
      $locale = $locales[0];
    }
    elseif ($this->hasCookie() && 
            $this->getCookie()->hasAttribute('locale')) { 
      $locale = $this->getCookie()->locale; 
    }
    elseif ($this->hasAttribute('request_locale')) {
      $locale = $this->getAttribute('request_locale');
    }
    else {
      $hal = $_SERVER['HTTP_ACCEPT_LANGUAGE']; 
      $locale = 0;
      foreach ($locales as $locale) {
        if ($locale == I18N::LOCALE_FR && 
            (strpos($hal, 'fr') !== false || 
             strpos($hal, 'be') !== false || 
             strpos($hal, 'ch') !== false)) { 
          $locale = I18N::LOCALE_FR; break ; 
        }
        elseif ($locale == I18N::LOCALE_ES && strpos($hal, 'es') !== false) { 
          $locale = I18N::LOCALE_ES; break ; 
        }
        elseif ($locale == I18N::LOCALE_IT && strpos($hal, 'it') !== false) { 
          $locale = I18N::LOCALE_IT; break ; 
        }
        elseif ($locale == I18N::LOCALE_DE && 
                (strpos($hal, 'de') !== false || 
                 strpos($hal, 'at') !== false)) { 
          $locale = I18N::LOCALE_DE; break ; 
        }
        elseif ($locale == I18N::LOCALE_EN && strpos($hal, 'en') !== false) { 
          $locale = I18N::LOCALE_EN; break ; 
        } else {
          $locale = I18N::LOCALE_FR; break ;
        }
      }
    }
    settype($locale, 'int');
    $locale = in_array($locale , $locales) ? $locale : $locales[0];
    $this->setParameter('locale', $locale);
    if ($this->hasCookie()) { 
      $cookie = $this->getCookie();
      if ($cookie->locale != $locale) { 
        $cookie->setAttribute('locale', $locale);
      }
    } 
    return $locale;
  }

  public function isSecure() {
    return $_SERVER['HTTP_X_FORWARDED_PORT'] == 'on' ||
           $_SERVER['HTTP_X_FORWARDED_PROTO'] === 'https';
  }

  public function getServer($key) { 
    if ($key === 'host') {
      // ServerAlias
      $host = $this->isCli() 
            ? $_SERVER['HOSTNAME']
            : $_SERVER['HTTP_HOST'];
      return strtolower($host);
    }
    if ($key === 'port') {
      if (strlen($_SERVER['HTTP_X_FORWARDED_PORT'], '.') >= 1) {
        return $_SERVER['HTTP_X_FORWARDED_PORT'];
      }
      return $_SERVER['SERVER_PORT'];
    }
    if ($key === 'port') {
      if (strlen($_SERVER['HTTP_X_FORWARDED_PORT'], '.') >= 1) {
        return $_SERVER['HTTP_X_FORWARDED_PORT'];
      }
      return $_SERVER['SERVER_PORT'];
    }
    $hash = array();
    $hash['host'] = $this->getServer('host');
    return $hash;
  }

  public function getClient($key=null) {
    if ($key === 'agent') {
      if (!$this->hasParameter('client_agent')) {
        $agent = IS_CLI ? 'shell' : strtolower($_SERVER['HTTP_USER_AGENT']);
        $this->setParameter('client_agent', $agent);
      }
      return $this->getParameter('client_agent');
    }
    if ($key === 'host') {
      if (!$this->hasParameter('client_host')) {
        $this->setParameter('client_host',
                            gethostbyaddr($this->getClient('address')));
      }
      return $this->getParameter('client_host');
    }

    if ($key === 'address') { 
      if ($this->hasParameter('client_address')) {
        return $this->getParameter('client_address');
      }
      $this->setParameter('client_address', '?');
      if ($this->isPhp()) { 
        $address = $this->getHeader('x-knx-address-from'); 
      }
      elseif (!empty($_SERVER['HTTP_CLIENT_IP'])) {
        $address = $_SERVER['HTTP_CLIENT_IP'];
      }
      elseif (strpos($_SERVER['HTTP_X_FORWARDED_FOR'], '.') > 1) {
        $this->setParameter('client_is_proxied', true);
        $address = $_SERVER['HTTP_X_FORWARDED_FOR'];
        if (strpos($address, ',') > 1) {
          S('log')->trace('  [XFF='.$_SERVER['HTTP_X_FORWARDED_FOR'].']'
                          .' [CIP='.$_SERVER['HTTP_CLIENT_IP'].']',
                          __METHOD__);
          $addresses = explode(',', $address);
          //          $address = array_pop($addresses);
          $address = array_shift($addresses);
          $address = trim($address);
        }
        if (Net::isPrivateAddress($address)) {
          $address = '';
        }
      }
      elseif (!empty($_SERVER['HTTP_X_CLUSTER_CLIENT_IP'])) {
        $address = $_SERVER['HTTP_X_CLUSTER_CLIENT_IP'];
        S('log')->trace('cluster ['.$address.']', __METHOD__);
      }
      $address = trim($address);
      if (empty($address)) {
        $address = $_SERVER['REMOTE_ADDR'];
      }
      else {
        $this->setParameter('client_is_proxied', true);
      }
      $this->setParameter('client_address', $address);
      return $this->getParameter('client_address');
    }
    if ($key === 'ip') {
      if (!$this->hasParameter('client_ip')) {
        $this->setParameter('client_ip',
                            Net::ip2num($this->getClient('address')));
      }
      return $this->getParameter('client_ip');
    }
    if ($key === 'referer') {
      if (!$this->hasParameter('referer')) {
        $referer = $this->hasHeader('x-kwo-referer')  
                 ? $this->getHeader('x-kwo-referer') 
                 : $_SERVER['HTTP_REFERER'];
        $referer = strtolower($referer);
        $this->setParameter('referer', $referer);
      }
      return $this->getParameter('referer');
    }
    if ($key === 'country') {
      if (!$this->hasParameter('client_country')) {
        $this->setParameter('client_country',
                            Net::ip2country($this->getClient('address')));
      }
      return $this->getParameter('client_country');
    }
    if ($key === 'login') {
      return $_SERVER['PHP_AUTH_USER']; 
    }
    if ($key === 'password') {
      return $_SERVER['PHP_AUTH_PW']; 
    }
    $hash = array();
    if (IS_CLI) return array();
    $hash['address'] = $this->getClient('address');
    $hash['host']    = $this->getClient('host');
    $hash['agent']   = $this->getClient('agent');
    $hash['referer'] = $this->getClient('referer');
    if ($this->isAuthenticated()) {
      $user = $this->getUser();
      $hash['user'] = $user.' ('.$user->getId().')';
      $hash['email'] = $user->email;
    }
    return $hash;
  }

  public function getMethod() { 
    return $_SERVER['REQUEST_METHOD']; 
  }

  public function getUrl() { 
    // ex : http://www.bk.pulsar.inerd/back/core/sys.infos?toto=titi
    $url = $_SERVER['SCRIPT_URI'];
    if (!empty($_SERVER['QUERY_STRING'])) {
      $url .= '?'.$_SERVER['QUERY_STRING'];
    }
    return $url; 
  }

  public function getUri() { 
    // ex : /back/sys/sys.infos?test=ixi
    return $_SERVER['REQUEST_URI']; 
  }

  public function getPath() { 
    // ex: /back/core/sys.infos
    return $_SERVER['SCRIPT_URL']; 
  }

  public function match($regex) { 
    return (bool) preg_match('#'.$regex.'#i', $this->getPath()); 
  }

  public function comesFrom($regex) {
    return (bool) preg_match('#'.$regex.'#i', $this->getClient('referer'));
  }

  public function getQueryString($as_hash=false) { 
    return $as_hash === true ? $_GET : $_SERVER['QUERY_STRING'];
  }

  public function getSession() { 
    if (Platform::hasSingleton('session')) {
      return S('session');
    }
    if ($this->isCli()) {
      S('log')->error('no session in CLI mode', __METHOD__);
      throw new Exception('no session in CLI mode');
    }
    return Platform::addSingleton('session', new Session());
  }

  public function hasSession($name=Session::COOKIE_NAME) {
    return $this->hasCookie($name);
  }

  /*** AUTH ***/
  
  public function isAuthenticated() {
    $ctx = S('ctx'); 
    if (!is_array($ctx->getAttribute('_user'))) {
      AuthManager::getInstance();
    }
    return $ctx->_user['id'] >= 1;
  }

  public function getUserId() {
    $ctx = S('ctx');
    if (!is_array($ctx->getAttribute('_user'))) {
      //      S('log')->warn('new instanciation of AuthManager', __METHOD__);
      AuthManager::getInstance();
    }
    if ($ctx->_user['id'] < 1) {
      throw new AuthException('authentication failure');
    }
    return (int) $ctx->_user['id'];
  }

  public function getUser() {
    if ($this->getParameter('user') === null) {
      $user = User::getInstance($this->getUserId());
      if ($user->status < 1) {
        throw new AuthException('authentication failure');
      }
      $this->setParameter('user', $user);
    }
    return $this->getParameter('user');
  }

  public function isModerator() { 
    return $this->hasPrivilege(Privilege::MODERATOR);
  }

  public function hasPrivilege($id) {
    if (!$this->isAuthenticated()) return false;
    $session = $this->getSession();
    $user = $session->user;
    return ($user['privileges'] & B($id)) > 0;
  }

  public function invalidate() {
    $ctx = S('ctx');
    $ctx->_user['id'] = 0;
    $this->setParameter('user', null);
    if ($this->hasSession()) {
      $this->getSession()->logout();
    }
  }

  /*** /AUTH ***/

  public function isCached() {
    if ($this->isCli()) return false;
    $etag = $this->getHeader('if-none-match');
    if (strpos($etag, '-') < 4) return false;
    list ($expire, $user_id) = explode('-', $etag);
    if (time() <= $expire && intval($user_id) == intval(S('ctx')->_user['id'])) {
      S('res')->sendHttpNotModified($etag);
      return true;
    }
    return false;
  }

  public function getCookie($name=Cookie::NAME, $ttl=null) {
    if (isset(Cookie::$stack[$name])) {
      return Cookie::$stack[$name];
    }
    $cookie = new Cookie($name, $ttl);
    Cookie::$stack[$name] = $cookie;
    return $cookie;
  }
  
  public function hasCookie($name=Cookie::NAME) { 
    return array_key_exists($name, $_COOKIE); 
  }

  public function removeCookies() {
    foreach ($_COOKIE as $k => $v) {
      $cookie = $this->getCookie($k);
      $cookie->remove();
    }
    return count(Cookie::$stack);
  }
 
  public function track($action=true, $category=null) {
    if (LOAD_LEVEL > 0) return ;
    if (!Platform::hasSingleton('tracker') || 
        $action === null) {
      return ; 
    }
    $default = $this->isXhr() ? Tracker::CATEGORY_EVENT : Tracker::CATEGORY_PAGE;
    if ($action instanceof ActiveRecord && ($visit_id = $this->getId()) > 0) {
      $obj = $action;
      $action = $obj->getName(). ' / '.$obj->getModel();
    }
    elseif ($action === true) {
      if ($category) {
        $action = $this->action();
      }
      else {
        $action = $this->action().' / '.$this->extension();
        $category = $default;
      }
    }
    $category = $category ?: $default;
    $action = str_replace(array('<', '>', '"'),
                          array(' ', ' ', ' '),
                          $action);
    $action = trim($action);
    $category = strtolower($category);
    $category = trim($category);
    S('tracker')->track($action, $category);
    $this->setParameter('is_tracked', true);
  }

  public function isTracked() {
    return $this->getParameter('is_tracked') === true;
  }

  public function isBot() {
    return $this->getParameter('is_bot') === true;
  }

  public function getId() { 
    return (int) $this->getParameter('visit_id'); 
  }

  public function getVisit() {
    $id = $this->getId();
    if ($id < 1) {
      S('log')->error('invalid visit : '.$id, __METHOD__);
      throw new Exception('invalid visit');
    }
    return Visit::getInstance($id);
  }

  public function isNewVisitor() { 
    return $this->getParameter('is_new_visitor') === true; 
  }
  
  public function isNewVisit() {
    return $this->getParameter('is_new_visit') === true; 
  }

  public function trace() {
    //    $str  = $_SERVER['HTTP_HOST'];
    $str = $_SERVER['SCRIPT_URI'];
    if (!empty($_SERVER['QUERY_STRING'])) {
      $str .= '?'.$_SERVER['QUERY_STRING'];
    }
    S('log')->trace($str);
  }

  public function debug($full=false) { 
    if ($full === false) {
      S('log')->debug($this->getAttributes(), __METHOD__); 
      return ;
    }
    $hash = array('PARAMETERS' => $this->getParameters(),
                  'ATTRIBUTES' => $this->getAttributes());
    if (!empty($_FILES)) {
      $hash['_FILES'] = $_FILES;
    }
    //    $hash['_SERVER'] = $_SERVER;
    if ($this->hasCookie()) {
      $hash['COOKIE'] = $this->getCookie()->getAttributes();
    }
    $hash['CLIENT'] = $this->getClient();
    $hash['URL'] = $this->getUrl();
    S('log')->debug($hash, __METHOD__);
  }

  public function getBranches() {
    return (array) $this->getAttribute('branches');
  }

  public function getBranch() {
    return (array) $this->getAttribute('branch');
  }

  public function getBranchValue($key, $bubble=false) {
    $branch = (array) $this->getAttribute('branch');
    if ($branch[$key]) {
      return $branch[$key];
    }
    if ($bubble === false) return null;
    $branches = (array) $this->getAttribute('branches');
    if ($branches[$key]) {
      return $branches[$key];
    }
    return null;
  }

  public function hasParameter($key) { 
    return array_key_exists($key, self::$parameters); 
  }

  public function setParameter($key, $value) { 
    self::$parameters[$key] = $value; 
  }
  
  public function getParameter($key) { 
    return self::$parameters[$key]; 
  }
  
  public function getParameters() {
    return self::$parameters; 
  }

  public function hasAttribute($key, $has_content_flag=false) {
    if (!property_exists($this, $key)) return false;
    $value = $this->getAttribute($key);
    return ($has_content_flag === true && empty($value)) ? false : true;
  }

  public function hasAttributes() {
    $keys = is_array(func_get_arg(0)) ? func_get_arg(0) : func_get_args();
    if (is_bool($keys[count($keys) - 1])) {
      $check_content_flag = array_pop($keys);
    }
    else {
      $check_content_flag = false;
    }
    foreach ($keys as $key) {
      if (!$this->hasAttribute($key)) return false;
    }
    return true;
  }

  public function getAttribute($key) { 
    return $this->{$key}; 
  }
  
  public function getAttributes() {
    $args = func_get_args();
    $result = array();
    if (empty($args)) {
      $result = get_object_vars($this);
      return $result;
    }
    $keys = is_array($args[0]) ? $args[0] : $args;
    foreach ($args as $key) {
      $result[$key] = $this->$key;
    }
    return $result;
  }
  
  public function setAttribute($key, $value) { 
    $this->{$key} = $value;
  }
  
  public static function getInstance() {
    if (Platform::hasSingleton('req')) {
      return Platform::getSingleton('req');
    }
    $req = new Request();
    Platform::addSingleton('req', $req);
    $router = Router::getInstance();
    $router->dispatch($req);
    $router = null;
  }
  
}
 












