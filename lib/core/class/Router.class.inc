<?php

class Router 
{
  const MAX_URI_PARAMS = 5;

  private $req = null;

  public function __construct() {}

  public function dispatch($req) {

    $this->req = $req;

    try {
      $this->detectRoute(); 
    }
    catch (Exception $e) { 
      S('log')->error($e, __METHOD__);
      $this->traceError();
      if (IS_CLI) {
        die('action unknown');
      }
      $this->req->setErrorController();
    }
 
    try {
      $this->loadAttributes();
      $this->loadParameters();
    }
    catch (Exception $e) { 
      S('log')->error($e, __METHOD__); 
    }

    if ($req->isBack()) {
      try { 
        $this->handleBack(); 
      }
      catch (Exception $e) { 
        S('log')->error('auth failure : '.$this->req->getUri(),
                        __METHOD__); 
        $this->req->setErrorController();
      }
    }

  }
  
  private function handleBack() {
    $req = $this->req;
    $session = $req->getSession();
    $cookie = $req->getCookie();
    $admin_token = $session->getAttribute('admin_token');
    if (!empty($admin_token)) {
      list ($admin_id, $secret) = explode('-', $admin_token);
      if ($secret != String::crypt($admin_id)) {
        $req->setController('front', CORE, 'admin.redirect');
        return ;
      }
      $admin_id = (int) $admin_id;
      $admin = Admin::getInstance($admin_id, array('include' => 'policy'));
      Platform::addSingleton('admin', $admin);
    }
    elseif ($cookie->getAttribute('back.access') == 1) {
      $req->setController('front', CORE, 'admin.redirect');
    }
    else {
      throw new Exception();
    }
  }

  private function detectRoute() { 

    $req = $this->req;

    if (IS_CLI) { 
      $uri = $_SERVER['argv'][1];
    }
    else { 
      $uri = $_SERVER['REQUEST_URI'];
      foreach (Redirection::asHash() as $regex => $hash) {
        if (preg_match('#'.$regex.'#u', $uri)) { 
          $req->setController('front', CORE, 'redirection');
          S('ctx')->redirection = $hash;
          return ;
        }
      }
      $uri = $_SERVER['SCRIPT_NAME'];
    }

    $uri = str_replace('//', '/', $uri);
    $uri = trim($uri, '/');
    
    if ($uri === Admin::url()) {
      $req->setController('front', CORE, 'admin.signin');
      return ;
    }

    if ($uri[2] === '/' || $uri[1] === '/' || strlen($uri) === 2) {
      $str = substr($uri, 0, 2);
      $str = trim($str, '/');
      if (is_numeric($str)) {
        $req->setParameter('api_version', (int) $str);
        $uri = ltrim(substr($uri, 2), '/');
      }
      elseif (in_array($str, array('fr', 'en', 'it', 'es', 'de', 'nl', 'pt', 'ru'))) {
        $req->setParameter('res_locale', I18N::lang($str));
        $uri = ltrim(substr($uri, 2), '/');
      }
      
    }
    
    list ($uri, $params) = explode('/-/', $uri, 2);

    if (strlen($params) >= 3) {
      $pairs = (array) explode('/', $params);
      $pairs = array_slice($pairs, 0, (self::MAX_URI_PARAMS * 2));
      $n = count($pairs) - 1;
      if ($n % 2 === 0) $n++;
      for ($i = 0; $i < $n; $i += 2) {
        $req->setAttribute($pairs[$i], (string) $pairs[$i + 1]);
      }
    }

    list ($scope, $extension, $action) = explode('/', $uri);

    if ($req->getParameter('api_version') > 0) {
      $action = $extension;
      $extension = $scope;
      $scope = 'api';
    }

    $routes = P('front.routes');
    if ($scope != 'back' && $scope != 'account' && $scope != 'middle' && $scope != 'api' && 
        IS_CLI === false && is_array($routes)) { 
      foreach ($routes as $regex => $route) {  
        $matches = array(); 
        $regex = ltrim($regex, '/');
        if (preg_match('#^'.$regex.'#u', $uri, $matches)) {
          $scope = 'front';
          $extension = $route[0];
          $action = $route[1];
          foreach ($matches as $key => $value) {
            if (is_int($key)) continue ;
            $req->setAttribute($key, $value);
          }
          if (is_array($route[2])) {
            foreach ($route[2] as $key => $value) {
              if (!is_string($key)) continue ;
              if (strpos($key, '[') >= 1) {
                $pair = explode('[', trim($key, ']'));
                $req->{$pair[0]}[$pair[1]] = $value; 
              }
              else {
                $req->setAttribute($key, $value);
              }
            }
          }
          break ;
        }
      }
    }

    if ($this->isValid($scope.$extension.$action) === false) {
      S('log')->error($scope.$extension.$action, __METHOD__);
      throw new Exception('url format', 
                          Error::CODE_INVALID_URL);
    }

    if (IS_CLI) {
      if ($scope != 'cli') {
        if (empty($extension) && empty($action)) {
          $action = $scope;
          $extension = CORE;
        }
        else {
          $action = $extension;
          $extension = $scope;
        }
        $scope = 'cli';
      }
    }
    elseif ($scope === 'api') {
      if ($action === 'services.xml') { 
        $req->setParameter('api_format', Request::FORMAT_XMLRPC); 
        $method = '';
        list ($api_request_params) = xmlrpc_decode_request($req->getBody(), $method);
        $req->setParameter('api_request_method', $method);
        $req->setParameter('api_request_params', $api_request_params); 
        /***
         S('log')->debug($req->getBody());
         S('log')->debug($req->getParameter('api_request_params'));
         S('log')->debug($method);
        ***/
        if ($method === 'pingback.ping') {
          $extension = CORE;
          $action = 'item.ping';
        }
        else {
          list ($extension, $action) = explode('.', $method, 2);
          if (!Extension::exists($extension)) {
            $action = $method;
            $extension = Model::extension($extension);
          }
        }
      }
      elseif ($action === 'services.json') {
        $req->setParameter('api_format', Request::FORMAT_JSONRPC);
        $json = json_decode($req->getBody());
        $req->setParameter('api_request_method', $json->method);
        $req->setParameter('api_request_params', $json->params);
        $req->setParameter('api_request_id', $json->id);
        $req->setParameter('api_format_version', $json->version);
        /***
        S('log')->debug($req->getBody());
        S('log')->debug($req->getParameter('api_request_params'));
        S('log')->debug($method);
        ***/
        $method = $json->method;
        list ($extension, $action) = explode('.', $method, 2);
        if (!Extension::exists($extension)) {
          $action = $method;
          $extension = Model::extension($extension);
        }
      }
      elseif ($action === 'services.soap') {
        $req->setParameter('api_format', Request::FORMAT_SOAP);
      }
      $scope = 'api';
    }
    elseif ($scope === 'account') {
      if ($extension === null || $action === null) {
	$scope = 'front';
	$extension = 'community';
	$action = 'account';
      }
    }
    elseif ($scope === 'middle') { 
      if (empty($extension)) {
        $modules = P('middle.modules');
        $module = reset($modules);
        $action = $module['action'];
      }
      elseif (empty($action)) {
        $action = $extension;
      }
      $extension = P('app.extension');
    }
    elseif ($scope === 'back') {
      
    }
    else {
      if (strlen($scope) < 1 || $scope === '-') { 
        $extension = P('app.extension');
        $action = P('front.home');
      }
      elseif (strlen($extension) <= 1) { 
	$action = $scope;
        if (strpos($action, 'sitemapindex') === 0) { 
          $action = 'sitemapindex';
          $extension = CORE;
        }
        elseif (strpos($action, 'sitemap') === 0) { 
          $action = 'sitemap';
          $extension = CORE;
        }
        else { 
          $extension = P('app.extension');
        }
      }
      elseif ($scope != 'front') {
        $action = $extension;
	$extension = $scope;
      }
      $scope = 'front';
    }
    
    $req->setController($scope, $extension, $action);

    if ($scope === 'back') {
      $controller = $req->getController(); 
      $virtuals = array('item', 'developer', 'editor', 'file', 'folder', 'bitmap');
      list ($model, $method) = explode('.', $action, 2); 
      if (!file_exists($controller) || $method == 'item') {
        $controller_found = false;
        if (Model::exists($model)) {
          $extension = Model::extension($model); 
          $controller = LIB_PATH.'/'.$extension.'/back/'.$model.'.'.$method.'.inc'; 
          if (file_exists($controller)) {
            $req->setController($scope, $extension, $model.'.'.$method, $controller);
            $controller_found = true;
          } 
        }
        if ($controller_found === false) {
          $req->setController($scope, $extension, $action,
                              LIB_PATH.'/'.CORE.'/back/item/'.$method.'.inc'); 
        }
      }
      if (!empty($method) && $model != 'item') {
        define('MODEL', strtolower($model));
        S('ctx')->setAttribute('_is_model', Model::exists(MODEL));
      }
    }
    elseif (IS_CLI) {
      S('app')->hook('onRequestDispatch', array('req' => $req));
    }
    
    $controller = $req->getController(); 

    if (!Extension::exists($req->extension())) { 
      throw new Exception('invalid extension ['.$req->extension().']', 
                          Error::CODE_INVALID_EXTENSION);
    } 

    if (!file_exists($controller)) {
      throw new Exception('invalid controller ['.$controller.']',
                          Error::CODE_INVALID_CONTROLLER);
    }

  }

  private function loadAttributes() {
    $req = $this->req;
    if ($req->isCli()) {
      foreach ($_SERVER['argv'] as $key => $value) {
	if ($key <= 1) continue ;
	$pair = explode('=', $value);
	$req->setAttribute($pair[0], trim($pair[1]));
      }
      return ;
    }
    if ($req->isApi() && $req->hasParameter('api_request_params')) {
      foreach ($req->getParameter('api_request_params') as $key => $value) {
        $req->setAttribute($key, $value);
      }
      return ;
    }
    $attributes = array();
    $attributes += $_POST + $_GET;
    $encoding = null;
    if ($req->isXhr()) {
      $encoding = 'utf8';
    }
    elseif (array_key_exists('kie', $attributes)) {
      $encoding = $attributes['kie'];
    }
    array_walk_recursive($attributes, array($this, 'filterParams'), $encoding);
    foreach ($attributes as $key => $value) {
      if ($key === '__token') continue ;
      $req->setAttribute($key, $value); 
    }
  }

  private function filterParams(&$value, $key, $encoding) {
    $value = trim($value); 
  }

  private function loadParameters() {

    $req = $this->req;

    if (!IS_CLI) {
      $headers = apache_request_headers();
      $headers = array_change_key_case($headers, CASE_LOWER);
      $req->setParameter('headers', $headers);
    }

    $locales = S('app')->getLocales();
    if (count($locales) === 1) {
      $res_locale = $locales[0];
    }
    elseif ($req->hasParameter('res_locale')) {
      $res_locale = $req->getParameter('res_locale');
    }
    elseif ($req->hasHeader('x-knx-res-locale')) {
      $res_locale = $req->getHeader('x-knx-res-locale');
    }
    elseif ($req->hasAttribute('res_locale')) {
      $res_locale = $req->getAttribute('res_locale');
    }
    $req->setParameter('res_locale', $res_locale);

    $action = $req->action();
    $parts = explode('.', $action);
    $tail = array_pop($parts);
    if ($req->hasHeader('x-requested-with') ||
//        substr($action, 0, 8) === 'service.' ||
        $req->extension() === CORE ||
        $req->dnt == 1 ||
        $action[0] == '_' ||
        in_array($tail, array('rss', 'feed', 'atom', 'js', 'json', 'css',
                              'ping', 'jump', 'xml', 'service'))) {
      Tracker::$disabled = true;
    }

    if ($req->hasAttribute('knxm')) {
      $req->setParameter('noindex', true);
    }

  }

  private function traceError() {
    if (LOAD_LEVEL > 0) return ;
    if (IS_CLI) {
      $url = join(' ', $_SERVER['argv']);
    }
    else {
      $url  = '['.Date::now().']'."\t";
      $url .= $_SERVER['HTTP_X_FORWARDED_FOR'] ?: $_SERVER['REMOTE_ADDR']."\t";
      $url .= $_SERVER['SCRIPT_URI'];
      if (!empty($_SERVER['QUERY_STRING'])) {
        $url .= '?'.$_SERVER['QUERY_STRING'];
      }
      if (false) {
        $url .= "\n".' * '.$_SERVER['HTTP_USER_AGENT'];
        $url .= "\n".' * '.$_SERVER['HTTP_REFERER'];
      }
    }
    $fp = fopen(Logger::URL_FILE, 'a');
    fwrite($fp, $url."\n");
    fclose($fp);
  }

  public function isValid($path) {
    return (empty($path) || (strlen($path) < 64 && preg_match('/^(\w|\.|-)+$/', $path)));
  }

  public static function getInstance() {
    $class = __CLASS__;
    return new $class;
  }

}