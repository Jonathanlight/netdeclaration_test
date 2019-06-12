<?php

class Response
{
  const ENCODING_UTF8  = 1;

  const FORMAT_HTTP    = 1;
  const FORMAT_JSON    = 2;
  const FORMAT_PHP     = 3;
  const FORMAT_TEXT    = 4;
  const FORMAT_XML     = 5;
  const FORMAT_XMLRPC  = 6;
  const FORMAT_JSONRPC = 7;
  const FORMAT_SOAP    = 8;

  public static $formats = array('text' => self:: FORMAT_TEXT,
                                 'jsonrpc' => self:: FORMAT_JSONRPC,
                                 'json' => self:: FORMAT_JSON,
                                 'xmlrpc' => self:: FORMAT_XMLRPC,
                                 'php' => self:: FORMAT_PHP,
                                 'xml' => self:: FORMAT_XML,
                                 'soap' => self:: FORMAT_SOAP,
                                 'http' => self:: FORMAT_HTTP);

  private $attributes       = array();
  private $cache_key        = null;
  private $cache_ttl        = null;
  private $content          = null;
  private $country_id       = null;
  private $ctx              = null;
  private $debug_level      = false;
  private $encoding         = null;
  private $err              = null;
  public  $feeds            = array();
  private $format           = null;
  private $http_headers     = array();
  private $http_status_code = 0;
  private $is_buffered      = false;
  private $is_closed        = false;
  public  $lang             = null;
  public  $links            = array();
  private $locale           = 0;
  public  $metas            = array();
  private $partial_content  = null;
  private $req              = null;
  public  $scripts          = array();
  public  $space            = null;
  public  $styles           = array();
  private $xml_file         = null;
  private $templates        = array();
  private $master_templates = array();

  public function __construct() {

    $this->open();

    $this->ctx = S('ctx');
    $this->req = S('req');
    $this->err = S('err');

    $this->setFormat(self::FORMAT_TEXT);

    $req = $this->req;

    $this->locale = $req->getParameter('res_locale') >= 1
                  ? $req->getParameter('res_locale')
                  : $req->getLocale();

    if ($req->isCli()) {
      $this->close();
      return ;
    }

    $this->ctx->setAttribute('_locale', I18N::lang($this->locale));
    $this->ctx->setAttribute('_locale_id', $this->locale);
    $this->ctx->setAttribute('_country_id', Country::FR);

    if ($req->hasSession()) {
      $session = $req->getSession();
      if ($session->hasAttribute('flash')) {
        $this->ctx->_flash = $session->getAttribute('flash');
        $session->removeAttribute('flash');
        if ($session->isEmpty()) {
          $session->invalidate();
        }
      }
    }

    if ($req->isApi()) {
      $format = $req->getAttribute('api_format');
      if ($format == Request::FORMAT_XMLRPC) {
        $this->setFormat(self::FORMAT_XMLRPC);
      }
      elseif ($format == Request::FORMAT_JSONRPC) {
        $this->setFormat(self::FORMAT_JSONRPC);
      }
      elseif ($format == Request::FORMAT_SOAP) {
        $this->setFormat(self::FORMAT_SOAP);
      }
      if ($req->hasAttribute('kof', true)) {
        $this->setFormat($req->getAttribute('kof'));
      }
      else {
        $this->setFormat(self::FORMAT_JSONRPC);
      }
      return ;
    }

    if ($req->isFront() || $req->isAccount()) {
      $this->setMasterTemplates(P('front.template'));
    }
    elseif ($req->isMiddle()) {
      $this->setMasterTemplates(P('middle.template'));
    }
    elseif ($req->isBack()) {
      $this->setMasterTemplates('//back');
    }

    if ($req->hasHeader('x-requested-with')) {
      $this->resetTemplates();
      if ($req->isXhr()) {
        if ($req->isXhr(Request::XHR_UPDATE)) {
          $this->setContentType('txt', 'utf-8');
          $this->setFormat(self::FORMAT_TEXT);
        }
        else {
          $this->setContentType('js');
          $this->setFormat(self::FORMAT_JSON);
        }
      }
      else {
        $this->setContentType('txt');
        $this->setFormat(self::FORMAT_TEXT);
      }
    }

    if ($req->hasAttribute('kof', true)) {
      $this->setFormat($req->getAttribute('kof'));
    }
    elseif ($req->isHttp() && $req->hasHeader('x-knx-kof')) {
      $this->setFormat($req->getHeader('x-knx-kof'));
    }

    if (P('front.breadcrumb') === true) {
      $this->breadcrumb = array();
    }

    if ($req->hasParameter('noindex')) {
      $this->addMeta('robots', 'NOINDEX');
    }

  }

  private function open() {
    $this->is_buffered = ob_start();
  }

  public function render() {

    if ($this->isClosed() || !$this->isBuffered()) return ;

    $type = null;
    if ($this->format == self::FORMAT_JSON ||
        $this->format == self::FORMAT_JSONRPC) {
      $type = 'js';
    }
    elseif ($this->format == self::FORMAT_XML ||
            $this->format == self::FORMAT_XMLRPC ||
            $this->format == self::FORMAT_SOAP) {
      $type = 'xml';
    }
    elseif ($this->format == self::FORMAT_PHP) {
      $type = 'txt';
    }
    if ($type != null) {
      $this->setContentType($type);
    }

    $this->content = ob_get_clean();

    switch ($this->format) {
      case self::FORMAT_TEXT:    $this->renderText(); break;
      case self::FORMAT_HTTP:    $this->renderHttp(); break;
      case self::FORMAT_JSON:    $this->renderJson(); break;
      case self::FORMAT_XMLRPC:  $this->renderXmlRpc(); break;
      case self::FORMAT_JSONRPC: $this->renderJsonRpc(); break;
      case self::FORMAT_XML:     $this->renderXml(); break;
      case self::FORMAT_PHP:     $this->renderPhp(); break;
      case self::FORMAT_SOAP:    $this->renderSoap(); break;
      default:
	S('log')->trace('no format', __METHOD__);
	$this->renderText();
    }
  }

  private function renderText() {
    if ($this->xml_file !== null && $this->err->count() < 1) {
      $this->setContent(UiManager::getInstance($this->xml_file)->render());
    }
    $this->partial_content = $this->getContent();
    $this->ctx->setContent($this->partial_content);
    if ($this->err->count() >= 1) {
      $req = $this->req;
      $this->ctx->_error_msg .= join('<br/>', $this->err->getMessages());
      if ($req->isFront() || $req->isAccount() || $req->isMiddle()) {
        $this->setSeo('Attention !');
        if ($req->isFront()) {
          $template = P('template.error') ?: '/error';
        }
        else {
          $template = 'community:account.error';
        }
        $this->useTemplates($template);
      }
      elseif ($req->isBack()) {
        $this->useTemplates('//error');
      }
    }
    if (!empty($this->templates)) {
      $this->partial_content = Template::render($this->templates, true);
    }
    if (empty($this->master_templates)) {
      $content = $this->partial_content;
    }
    else {
      $this->ctx->setContent($this->partial_content);
      $content = Template::render($this->master_templates, true);
    }
    return $this->commit($content);
  }

  private function renderJson() {
    $results = array();
    $error_code = $this->err->getCode();
    if ($error_code != 0) {
      $results['msg'] = $this->err->getMessages();
    }
    foreach ($this->ctx->getPublicAttributes() as $key => $obj) {
      $results[$key] = is_object($obj) ? get_object_vars($obj) : $obj;
    }
    $hash = array('error' => $error_code,
                  'result' => $results);
    $out = json_encode($hash);
    if ($this->req->hasAttribute('callback')) {
      $out = $this->req->callback.'('.$out.')';
      S('log')->trace($out);
    }
    $this->commit($out);
  }

  private function renderXmlRpc() {
    $error_code = $this->err->getCode();
    if ($error_code != 0) {
      $response = xmlrpc_encode(array('faultCode' => $error_code,
                                      'faultString' => join(',', $this->err->getMessages())));
      $response = str_replace(array('<fault>','</fault>'),
                              array("<methodResponse>\n<fault>","</fault>\n</methodResponse>"),
                              $response);
    }
    else {
      $response = xmlrpc_encode($this->ctx->getPublicAttributes());
      $response = str_replace(array('<params>','</params>'),
                              array("<methodResponse>\n<params>","</params>\n</methodResponse>"),
                              $response);
    }
    $this->commit($response);
  }

  private function renderJsonRpc() {
    $hash = array('jsonrpc' => '2.0');
    $error_code = $this->err->getCode();
    if ($error_code != 0) {
      $hash['error'] = array('code' => $error_code,
                             'message' => $this->err->getMessage());
      $hash['id'] = null;
    }
    else {
      $hash['result'] = $this->ctx->getPublicAttributes();
      $hash['id'] = $this->req->getParameter('api_request_id');
    }
    $response = json_encode($hash);
    $this->commit($response);
  }

  private function renderXml() {
    if ($this->err->count() >= 1) {
      $xml = new xmlWriter();
      $xml->openMemory();
      $xml->startDocument('1.0','UTF-8');
      $xml->startElement('knx-xml-response');
      $xml->writeAttribute('stat', 'fail');
      $xml->startElement('err');
      $xml->writeAttribute('code', $this->err->code);
      $xml->text(join('|', $this->err->getMessages()));
      $xml->endElement();
      $xml->endElement();
      $xml->endDocument();
      $this->commit($xml->outputMemory(true));
      return ;
    }
    $xml = new xmlWriter();
    $xml->openMemory();
    $xml->startDocument('1.0','UTF-8');
    $xml->startElement('knx-xml-response');
    $xml->writeAttribute('stat', 'ok');
    Hash::toXml($xml, $this->ctx->getPublicAttributes());
    $xml->endElement();
    $xml->endDocument();
    $this->commit($xml->outputMemory(true));
  }

  private function renderPhp() {
    $this->commit(Hash::encode($this->ctx->getPublicAttributes()));
  }

  private function renderSoap() {
    $this->commit('');
  }

  private function renderHttp() {
    $this->processHeaders();
  }

  public function setContentType($type, $charset=null) {
    $type = strtolower($type);
    if (in_array($type, array('css', 'rss', 'xml'))) {
      $this->resetTemplates();
    }
    $type = strlen($type) <= 4 ? Mime::$registry[$type]['mime'] : $type;
    if (!empty($charset)) {
      $type .= '; charset='.$charset;
    }
    $this->setHeader('Content-Type', $type);
    return $this;
  }

  public function setEncoding($encoding) {
    $this->encoding = $encoding;
  }

  public function getFormat() {
    return $this->format;
  }

  public function isFormat($format) {
    return $this->format == $format;
  }

  public function setFormat($format) {
    if (!is_numeric($format)) {
      $format = strtolower($format);
      $format = (int) self::$formats[$format];
    }
    else {
      $format = (int) $format;
      if (!in_array($format, self::$formats)) {
        $format = 0;
      }
    }
    if ($format < 1) {
      S('log')->error('invalid response format ['.$format.']', __METHOD__);
      return ;
    }
    $this->format = $format;
  }

  public function setHead($item=null) {
    return $this->setSeo($item);
  }

  public function setSeo($item=null) {
    if ($item === null || $item instanceof Action) {
      if (is_null($item)) {
        try {
          $actions = Action::asHash();
          $key = $this->req->extension().'.'.$this->req->action();
          $action_id = (int) $actions[$key];
          if ($action_id < 1) {
            return $this;
          }
          $item = Action::getInstance($action_id);
        }
        catch (Exception $e) { return $this; }
      }
    }
    if ($item instanceof ActiveRecord) {
      $hash = $item->asHeadHash($this->getLocale());
      foreach ($hash as $key => $value) {
        if (empty($value)) {
          unset($hash[$key]);
        }
      }

      if (!empty($hash)) {
        $title = $hash['title'];
        $description = $hash['description'];
        $keywords = $hash['keywords'];
        $url = $hash['url'];
        $latitude = $hash['latitude'];
        $longitude = $hash['longitude'];
        $metas = $hash['metas'];
      }
      else {
        $title = (string) $item->getName();
      }
    }
    elseif (is_array($item)) {
      $title = $item['title'];
      $description = $item['description'];
      $keywords = $item['keywords'];
      $url = $item['url'];
      $latitude = $hash['latitude'];
      $longitude = $hash['longitude'];
      $metas = $hash['metas'];
    }
    elseif (is_string($item)) {
      $title = $item;
    }
    if (!empty($title)) {
      $this->metas['title'] = $title;
    }
    if (!empty($description)) {
      $this->metas['description'] = ucfirst($description);
    }
    if (!empty($keywords)) {
      $this->metas['keywords'] = is_array($keywords)
                               ? join(', ', $keywords)
                               : $keywords;
    }
    if (strpos($this->metas['title'], '’') !== false) {
      $this->metas['title'] = preg_replace('/’/u', "'", $this->metas['title']);
    }
    if (!empty($url)) {
      $this->setLink('canonical', array('href' => $url));
    }
    if ($latitude != 0 || $longitude != 0) {
      $this->metas['geo.position'] = $latitude.';'.$longitude;
    }
    if (!empty($metas)) {
      foreach ($metas as $key => $value) {
        $this->metas[$key] = $value;
      }
    }
    return $this;
  }

  public function setLang($lang) {
    $lang = is_numeric($lang) ? I18N::$metas[$lang] : $lang;
    $this->lang = $lang;
  }

  public function setLink($rel, $hash=array()) {
    if ($rel instanceof ActiveRecord) {
      $hash = array('href' => $rel->asUrl());
      $rel = 'canonical';
    }
    $this->links[] = array('rel' => $rel) + $hash;
    return $this;
  }

  public function getLocale() {
    return $this->locale;
  }

  public function setFlash($str) {
    if ($this->req->isCli()) {
      S('log')->error('operation forbidden', __METHOD__);
      return ;
    }
    $this->req->getSession()->setAttribute('flash', $str);
  }

  public function setBreadcrumb(array $hash) {
    if ($this->breadcrumb === null) return ;
    $breadcrumb = array();
    foreach ($hash as $label => $url) {
      if ($url === null) {
        $breadcrumb = array();
        continue ;
      }
      $breadcrumb[$label] = $url;
    }
    $this->ctx->setAttribute('_breadcrumb', $breadcrumb);
  }

  public function setMenu($name=null) {
    if (is_null($name)) {
      $name = array($this->req->extension(),
                    $this->req->action());
    }
    elseif (func_num_args() > 1) {
      $name = func_get_args();
    }
    else {
      $name = (array) $name;
    }
    $this->ctx->setAttribute('_menu', $name);
  }

  public function setSpace($name=null) {
    $this->space = $name ? $name : $this->req->extension();
  }

  public function setTitle($title) {
    $title = $title instanceof ActiveRecord ? $title->getTitle() : $title;
    $this->ctx->setAttribute('_title', $title);
  }

  public function setWarning($msg) {
    $this->ctx->_warnings[] = $msg;
  }

  public function setHeader($key, $value) {
    if ($this->isClosed()) {
      header($key.': '.$value);
      return ;
    }
    $this->http_headers[$key] = $value;
  }

  public function resetHeader($key) {
    $this->setHeader($key, '');
  }

  public function useTemplate($template=true) {
    $action = $this->req->action();
    if ($this->req->isBack()) {
      $this->templates[] = $template === true ? $action : $template;
      return ;
    }
    if ($template !== true) {
      $this->useTemplates($template);
      return ;
    }
    $templates = P('front.templates');
    $template = $templates[$this->req->extension()][$action];
    $this->templates = array_merge($this->templates,
                                   (array) ($template ? $template : $action));
  }

  public function useTemplates() {
    $templates = func_num_args() >= 1 && is_array(func_get_arg(0))
               ? func_get_arg(0)
               : func_get_args();
    foreach ($templates as $template) {
      if ($template === null) {
        $this->resetTemplates();
        continue ;
      }
      elseif ($template === true || empty($template)) {
        $action = $this->req->action();
        $hash = P('front.templates');
        $template = $hash[$this->req->extension()][$action];
        $template = $template ?: $action;
      }
      $this->templates[] = $template;
    }
    return $this;
  }

  public function setMasterTemplates($templates) {
    $this->master_templates = (array) $templates;
  }

  public function resetTemplates() {
    $this->master_templates = array();
    $this->templates = array();
  }

  public function useXml($filename=null) {
    $this->xml_file = $filename ?: $this->req->action();
  }

  public function addClass($class_name) {
    $tmp = $this->ctx->getAttribute('_body_class');
    $tmp .= ' '.$class_name;
    $this->ctx->setAttribute('_body_class', $tmp);
  }

  public function addScript($script) {
    $this->scripts[] = $script;
  }

  public function addFeed($name, $url) {
    $this->feeds[] = array('name' => $name, 'url' => $url);
  }

  public function addStyle($style) {
    $this->styles[] = $style;
  }

  public function addMeta($name, $value) {
    $this->metas[$name] = $value;
  }

  public function close() {
    if ($this->isBuffered()) {
      ob_end_clean();
    }
    $this->is_buffered = false;
    $this->is_closed = true;
  }

  public function isClosed() {
    return $this->is_closed;
  }

  public function isBuffered() {
    return $this->is_buffered;
  }

  public function write($content) {
    if (is_object($content)) {
      if (method_exists($content, 'asHtml')) {
        $content = $content->asHtml($this->getLocale());
      }
      else if (method_exists($content, 'asText')) {
        $content = $content->asText($this->getLocale());
      }
    }
    //    if ($this->isClosed()) {
    if ($this->isClosed() || $this->isBuffered()) {
      print($content);
      return ;
    }
    /*    if ($this->is_buffered === true) {
      print($content);
      return ;
      }*/
    $this->appendContent($content);
  }

  public function reset() {
    $this->resetTemplates();
    $this->setContent('');
  }

  private function getContent() {
    return $this->content;
  }

  private function setContent($content) {
    $this->content = $content;
  }

  private function appendContent($content) {
    $this->content .= $content;
    //S('log')->trace($this->content, __METHOD__);
  }

  public function isCached($opts=null) {
    if (P('cache.disabled') == 1 || $this->err->count() >= 1) return false;
    $req = $this->req;
    $item = null;

    if ($opts instanceof ActiveRecord) {
      $item = $opts;
      $ttl = true;
      $opts = array();
    }
    else {
      $opts = (array) $opts;
      $ttl = $opts['ttl'];
      $ttl = is_null($ttl) ? true : $ttl;
      if (intval($ttl) <= 0) return false;
      $item = $opts['item'];
    }

    if (!empty($opts['key'])) {
      $key = $opts['key'];
    }
    else {
      $key = '';
      if ($item) {
        if (is_array($item)) {
          $item = Item::getInstance((int) $item['model_id'],
                                    (int) $item['record_id']);
        }
        $key = $item->getModelId().':'.$item->getId().':'.$item->getMeta('state').':';
      }
      $key .= $req->extension().'.'.$req->action();
      $key .= ':'.$req->getChecksum();
      //      $key .= ':'.intval(P('cache.state'));
      $key .= ':'.$this->getLocale();
      if ($opts['ugc'] === true) {
        $user_id = (int) $this->ctx->_user['id'];
        if ($user_id >= 1) {
          $key .= ':'.$user_id;
        }
      }
    }

    $content = S('stg')->get($key);
    $this->cache_key = $key;
    $this->cache_ttl = $ttl;
    //    S('log')->debug($content, $key);
    if ($content !== false) {
      if (false) {
        $this->setHeader('X-Kwo-Cache-Key', $this->cache_key);
        $this->setHeader('X-Kwo-Cache-Ttl', $this->cache_ttl);
      }
      else {
        $this->setHeader('X-Kwo-Cache', 1);
      }
      $this->write($content);
      return true;
    }
    return false;
  }

  private function commit($content) {
    if (Platform::hasSingleton('session')) {
      S('session')->sync();
    }
    if (!$this->req->isCli() && !$this->isClosed()) {
      $this->processHeaders();
    }
    if (in_array($this->http_status_code, array(301, 303))) {
      return ;
    }
    if ($this->req->isRpc()) {
      print($content);
      return ;
    }

    if (!empty($this->cache_key) && $this->err->count() < 1) {
      $partial_content = $this->partial_content ?: $content;
      //      error_log($this->cache_key."\n".substr($partial_content, 0, 64));
      S('stg')->set($this->cache_key, $partial_content, $this->cache_ttl);
    }
    if (Tracker::$disabled === false && LOAD_LEVEL < 1 &&
        $this->req->isFront() && $this->format == self::FORMAT_TEXT &&
        strpos(substr($content, 0, 16), '<!DOCTYPE') !== false) {
      Item::log();
    }
    print($content);
  }

  private function processHeaders() {
    if (headers_sent($file, $line) === true) {
      S('log')->error('headers already sent (file='.$file.', line='.$line.')',
                        __METHOD__);
      return false;
    }
    if ($this->req->isFront() && $this->err->count() >= 1 &&
        !$this->req->isXhr() && !$this->req->isRpc()) {
      $this->http_status_code = 404;
    }
    if ($this->http_status_code > 0) {
      header('HTTP/1.1'.' '.
             $this->http_status_code.' '.
             self::$http_status_codes[$this->http_status_code],
             true,
             $this->http_status_code);
    }
    foreach (Cookie::$stack as $cookie_name => $cookie) {
      $cookie->commit();
    }
    foreach ($this->http_headers as $key => $value) {
      header($key.':'.$value);
    }
  }

  public function sendData($input, $opts=array()) {
    $this->close();
    $this->processHeaders();
    if ($input instanceof Iterator || is_array($input)) {
      $as_hash = false;
      if (is_object($input)) {
        $as_hash = $input instanceof Collection && !$input->isMapped();
        $fields = $input->getFields();
      }
      else {
        $elt = current($input);
        $fields = array_keys($elt);
      }
      $filename = $opts['filename'] ? $opts['filename'] : (string) $input;
      $csv = CsvWriter::getInstance(array('filename' => $filename,
                                          'columns' => $fields));
      foreach ($input as $row) {
        $row = $as_hash ? $row->asHash() : $row;
        $csv->append($row);
      }
      return ;
    }
    DownloadManager::file($input, $opts);
  }

  public function sendMessage($msg) {
    $this->ctx->setAttribute('callback_message', $msg);
  }

  public function sendRedirect($url='/', $args=null, $opts=null) {
    $req = $this->req;
    $opts = (array) $opts;
    if (Platform::hasSingleton('session')) {
      S('session')->sync();
    }
    $url = $url instanceof ActiveRecord ? $url->asUrl() : $url;
    $url = empty($url) ? '/' : $url;
    if ($req->isXhr()) {
      $this->ctx->callback_url = $url;
      return ;
    }
    $this->setFormat(self::FORMAT_HTTP);
    if ($req->isBack() && strstr($url, '/') === false) {
      $url = '/'.$req->scope().'/'.$req->extension().'/'.$url;
    }
    if (is_array($args) && !empty($args)) {
      $url .= '?'.http_build_query($args);
    }
    $this->setHeader('Location', $url);
    $this->http_status_code = $opts['permanent'] === true ? 301 : 303;
  }

  public function sendOk() {
    $this->setFormat(self::FORMAT_HTTP);
    $this->http_status_code = 204;
  }

  public function sendHttpNotModified($etag) {
    $this->setFormat(self::FORMAT_HTTP);
    $this->resetHeader('Expires');
    $this->resetHeader('Cache-Control');
    $this->setHeader('Etag', $etag);
    $this->http_status_code = 304;
  }

  public function cache($opts=null) {
    $opts = (array) $opts;
    $ttl = $opts['ttl'] > 1 ? $opts['ttl'] : 300;
    $etag = (time() + $ttl).'-'.intval($this->ctx->_user['id']);
    $this->setHeader('Etag', $etag);
    $this->setHeader('Cache-Control', 'max-age='.$ttl);
    $this->setHeader('Expires', gmdate('r', time() + $ttl));
  }

  public function setExpireTime($ttl=3600) {
    $this->resetHeader('Pragma');
    $this->setHeader('Cache-Control', 'max-age='.$ttl.', must-revalidate');
    $this->setHeader('Expires', gmdate('D, d M Y H:i:s', (time() + $ttl))." GMT");
  }

  public function debug() { $this->debug_level = true; }
  public function trace() { S('log')->trace($this->http_status_code, __METHOD__); }

  private function setAttribute($key, $val) { $this->attributes[$key] = $val; }
  private function getAttribute($key) { return $this->attributes[$key]; }
  private function hasAttribute($key) { return array_key_exists($key, $this->attributes); }

  public function __destruct() {
    if ($this->debug_level === true) {
      S('log')->debug(apache_response_headers(), __METHOD__);
      if ($this->http_status_code !== null) {
        S('log')->trace('http status code : '.$this->http_status_code,
                          __METHOD__);
      }
    }
  }

  public static function getInstance() {
    if (Platform::hasSingleton('res')) return ;
    Platform::addSingleton('res', new Response());
  }

  private static $http_status_codes = array(100 => 'Continue',
                                            101 => 'Switching Protocols',
                                            200 => 'OK',
                                            201 => 'Created',
                                            202 => 'Accepted',
                                            203 => 'Non-Authoritative Information',
                                            204 => 'No Content',
                                            205 => 'Reset Content',
                                            206 => 'Partial Content',
                                            300 => 'Multiple Choices',
                                            301 => 'Moved Permanently',
                                            302 => 'Found',
                                            303 => 'See Other',
                                            304 => 'Not Modified',
                                            305 => 'Use Proxy',
                                            307 => 'Temporary Redirect',
                                            400 => 'Bad Request',
                                            401 => 'Unauthorized',
                                            402 => 'Payment Required',
                                            403 => 'Forbidden',
                                            404 => 'Not Found',
                                            405 => 'Method Not Allowed',
                                            406 => 'Not Acceptable',
                                            407 => 'Proxy Authentication Required',
                                            408 => 'Request Time-out',
                                            409 => 'Conflict',
                                            410 => 'Gone',
                                            411 => 'Length Required',
                                            412 => 'Precondition Failed',
                                            413 => 'Request Entity Too Large',
                                            414 => 'Request-URI Too Large',
                                            415 => 'Unsupported Media Type',
                                            416 => 'Requested range not satisfiable',
                                            417 => 'Expectation Failed',
                                            500 => 'Internal Server Error',
                                            501 => 'Not Implemented',
                                            502 => 'Bad Gateway',
                                            503 => 'Service Unavailable',
                                            504 => 'Gateway Time-out');

}
