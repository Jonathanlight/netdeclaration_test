<?php

/*
code d’erreurs
http://xmlrpc-epi.sourceforge.net/specs/rfc.fault_codes.php
*/

class RpcClient {

  private $file = null;
  private $method = null;
  private $params = array();
  private $response = array();
  private $server = null;
  private $debug = false;
  private $type = null;

  public function __construct($server, $path=null, $type='xml') {
    $this->server = 'http://'.$server; 
    if ($path !== null) {
      $path = trim($path, '/');
      $this->server .= '/'.$path;
    }
    $this->type = $type;
  }

  public function call($method, $params) {
    return $this->type == 'xml'
                        ? $this->callXml($method, $params)
                        : $this->callJson($method, $params);
  }

  protected function callXml($method, $params) {
    $this->method = $method; 
    $this->params = $params; 
    $content = xmlrpc_encode_request($this->method, $this->params);
    
    $context = stream_context_create(array('http' => array('method' => 'POST',
                                                           'header' => 'Content-Type: text/xml; charset=utf-8',
                                                           'content' => $content)));
    
    $this->file = file_get_contents($this->server, false, $context);
    
    if ($this->file === false) {
      S('log')->error('can not connect server', __METHOD__);
      throw new Exception('can not connect server'); 
    }
    $this->response = xmlrpc_decode($this->file);
    
    if ($this->debug === true) {
      $log = S('log');
      $log->debug($this->server, 'server');
      $log->debug($this->params, 'params');
      $log->debug($content, 'content');
      $log->debug($this->file, 'file');
      $log->debug($this->response, 'response');
    }
    
    if (xmlrpc_is_fault($this->response)) {
      S('log')->error($this->response['faultCode'].'] '.$this->response['faultString'],
                      __METHOD__);
      throw new Exception('WebService Error');
    }
    return $this->response;
  }

  protected function callJson($method, $params) {
    
    $this->method = $method; 
    $this->params = $params;

    $hash = array('jsonrpc' => '2.0',
                  'method' => $method,
                  'params' => $params,
                  'id' => timestamp());
    $content = json_encode($hash);
    
    $context = stream_context_create(array('http' => array('method' => 'POST',
                                                           'header' => 'Content-Type: text/js; charset=utf-8',
                                                           'content' => $content)));
    
    $this->file = file_get_contents($this->server, false, $context);
    
    if ($this->file === false) {
      S('log')->error('can not connect server', __METHOD__);
      throw new Exception('can not connect server'); 
    }
    $this->response = json_decode($this->file, true);
    
    if ($this->debug === true) {
      $log = S('log');
      $log->debug($this->server, 'server'); 
      $log->debug($this->params, 'params');
      $log->debug($content, 'content');
      $log->debug($this->file, 'file');
      $log->debug($this->response, 'response');
    }
    
    if (isset($this->response['error'])) {
      S('log')->error($this->response['error']['code'].'] '.$this->response['error']['message'],
                      __METHOD__);
      throw new Exception('WebService Error');
    }
    return $this->response;
  }

  public static function getInstance($server, $path=null) {
    $class = __CLASS__;
    return new $class($server, $path);
  }



}