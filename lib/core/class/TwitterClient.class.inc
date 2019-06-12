<?php

/* 

consumer_key
consumer_secret
oauth_token
oauth_token_secret


$client = TwitterClient::getInstance();
$client->post('/statuses/update', 
              array('status' => 'cool'));

*/

  // si pb "Read-only application cannot POST problem" : reset des tokens

  //$consumer_key, $consumer_secret, $oauth_token = NULL, $oauth_token_secret = NULL

  // out-of-band mode OAuth

class TwitterClient 
{
  private $opts = null;
  
  private $format = 'json';

  private $oauth = null;

  const HOST = 'http://api.twitter.com/1';
  
  public function __construct($opts) {
    $ts = time();
    $this->oauth = array_merge(array('version' => '1.0',
                                     'nonce' => md5($ts),
                                     'timestamp' => $ts,
                                     'signature_method' => 'HMAC-SHA1'),
                               $opts);
  }
  
  public function post($url, $params=null) {
    $params = (array) $params;
    $response = $this->fetch($url, 'POST', $params);
    return json_decode($response, true);
  }
  
  public function fetch($url, $method, $parameters) {
    $url = self::HOST . $url . '.'. $this->format;

    $oauth = array('oauth_consumer_key' => $this->oauth['consumer_key'],
                   'oauth_nonce' => $this->oauth['nonce'],
                   'oauth_signature_method' => $this->oauth['signature_method'],
                   'oauth_token' => $this->oauth['access_token'],
                   'oauth_timestamp' => $this->oauth['timestamp'],
                   'oauth_version' => $this->oauth['version']);
    $args = array_merge($oauth, $parameters);

    $this->oauth['signature'] = $this->getSignature($url, $method, $args);
    $content = self::build_http_query($parameters);

    $headers[] = 'User-Agent: Kwo OAuth Client';
    $headers[] = 'Content-Type: application/x-www-form-urlencoded';
    $headers[] = 'Authorization: '.$this->getAuthorizationHeader();

    $headers = join("\r\n", $headers)."\r\n";

    $opts = array('method' => $method,
                  'timeout' => 5,
                  'content' => $content,
                  'ignore_errors' => true,
                  'header' => $headers);
      
    $context = stream_context_create(array('http' => $opts));

    $stream = @fopen($url, 'r', false, $context);
    if ($stream === false) {
      // en cas d'erreur d'api ... regarder le json
      S('log')->trace('url unavailable ['.$url.']', __METHOD__);
      return false;
    }
    $response = stream_get_contents($stream);
    fclose($stream);
    return $response;
  }

  public function getAuthorizationHeader() {
    $parts = array('oauth_nonce' => $this->oauth['nonce'],
                   'oauth_signature_method' => $this->oauth['signature_method'],
                   'oauth_timestamp' => $this->oauth['timestamp'],
                   'oauth_consumer_key' => $this->oauth['consumer_key'],
                   'oauth_token' => $this->oauth['access_token'],
                   'oauth_signature' => $this->oauth['signature'],
                   'oauth_version' => $this->oauth['version']);
    foreach ($parts as $key => &$value) {
      $value = $key.'='.'"'.$value.'"';
    }
    $header = 'OAuth '.join(', ', $parts);
    return $header;
  }

  public function getSignature($url, $method, $parameters) {
    $signature = hash_hmac('SHA1', 
                           $this->getBaseString($method, $url, $parameters),
                           $this->getKey(),
                           true);
    $signature = base64_encode($signature);
    $signature = rawurlencode($signature);
    return $signature;
  }

  private function getBaseString($method, $url, $parameters) {
    $params = $parameters;
    if (isset($params['oauth_signature'])) {
      unset($params['oauth_signature']);
    }
    $params = self::build_http_query($params);

    $parts = array(strtoupper($method), $url, $params);
    $base_string = $this->encode($parts);
    return $base_string;
  }

  private function getKey() {
    $parts = array($this->oauth['consumer_secret'],
                   $this->oauth['access_token_secret']);
    $key = $this->encode($parts);
    return $key;
  }

  public function publish($item) {
    if ($item->hasBit(Meta::BIT_TWEETED)) return ;
    if (method_exists($item, 'asTweet')) {
      $msg = $item->asTweet();
    }
    else {
      $msg = $item->getName().' '.$item->asUrl();
    }
    $msg = substr($msg, 0, 140);
    $ret = (array) $this->post('/statuses/update', 
                               array('status' => $msg,
                                     'trim_user' => 't'));
    if (isset($ret['id'])) {
      $item->setBit(Meta::BIT_TWEETED);
    }
    else {
      S('log')->error($ret, __METHOD__);
    }
  }

  public static function getInstance($opts=null) {
    return new TwitterClient($opts);
  }

  private function encode($input) {
    foreach ($input as &$value) {
      $value = rawurlencode($value);
    }
    $str = implode('&', $input);
    return $str;
  }

  private static function build_http_query($params) {
    if (!$params) return '';
    
    $tmp = array();
    foreach ($params as $key => $value) {
      $key = rawurlencode($key);
      $value = rawurlencode($value);
      $tmp[$key] = $value;
    }

    $params = $tmp;
   
    uksort($params, 'strcmp');
    
    $pairs = array();
    foreach ($params as $key => $value) {
      if (is_array($value)) {
        natsort($value);
        foreach ($value as $duplicate_value) {
          $pairs[] = $key . '=' . $duplicate_value;
        }
      }
      else {
        $pairs[] = $key . '=' . $value;
      }
    }
    return implode('&', $pairs);
  }

  public static function tagify($tag) {
    $tag = String::urlify($tag);
    $tag = str_replace('-', ' ', $tag);
    $tag = mb_convert_case($tag, MB_CASE_TITLE, 'UTF-8');
    $tag = str_replace(' ', '', $tag);
    return '#'.$tag;
  }

}

