<?php

/* TODO : propager l'auth avec un header spécial reconnu par AuthManager */

class Cache
{
  private static $trace = false;

  public static function request($action, $args=null, $opts=null) {
    $req = S('req');
    $opts = (array) $opts;

    $args = $args === true ? S('ctx')->getAttributes() : $args;

    $url = $action;
    if (!empty($args)) {
      $url .= '?'.http_build_query($args);
    }

    if (!empty($opts['key'])) {
      $key  = $opts['key'];
    }
    else {
      $crc = sprintf('%u', crc32($url));
      if (strpos($url, '://') > 3) {
        $key  = $opts['token'] ? $opts['token'] : $req->action();
        $key .= ':'.$crc;
      }
      else {
        $key = '';
        if ($opts['item']) {
          $item = $opts['item'];
          $key = $item->getModelId().':'.$item->getId().':'.$item->getMeta('state').':';
        }
        if (empty($opts['token'])) {
          $tmp = trim($action, '/');
          $tmp = str_replace('/', '.', $tmp);
          $key .= $tmp;
        }
        else {
          $key .= $opts['token'];
        }
        $key .= ':'.$crc;
        $key .= ':'.S('res')->getLocale();
        if ($opts['ugc'] === true && S('ctx')->_user['id'] >= 1) {
          $key .= ':'.intval(S('ctx')->_user['id']);
        }
      }
    }

    $data = S('stg')->get($key);
    if ($data !== false) {
      return $data;
    }

    $ttl = $opts['ttl'];

    $http = array('method' => 'GET');

    if ($opts['timeout'] >= 1) {
      /* timeout : 60 */
      $http['timeout'] = (int) $opts['timeout'];
    }

    // $http['ignore_errors'] = true;

    if (substr($url, 0, 7) != 'http://' && substr($url, 0, 8) != 'https://') {
      $url = H::url($url);
      $headers = array();
      $headers[] = 'Accept-Language: '.$_SERVER['HTTP_ACCEPT_LANGUAGE'];
      // $headers[] = 'Accept-Encoding: '.$_SERVER['HTTP_ACCEPT_ENCODING']; /* pb gzip */
      $headers[] = 'Accept: '.$_SERVER['HTTP_ACCEPT'];
      $headers[] = 'User-Agent: '.$_SERVER['HTTP_USER_AGENT'];
      $headers[] = 'X-Requested-With: php';
      $headers[] = 'X-Knx-Scope-From: '.$req->scope();
      $headers[] = 'X-Knx-Extension-From: '.$req->extension();
      $headers[] = 'X-Knx-Action-From: '.$req->action();
      $headers[] = 'X-Knx-Address-From: '.$req->getClient('address');
      $headers[] = 'X-Knx-Res-Locale: '.S('res')->getLocale();
      if (CLUSTER_NODE_ID > 0) {
        $headers[] = 'X-Cluster-Node-Id: '.CLUSTER_NODE_ID;
      }
      $cookies = array($req->getCookie(Cookie::NAME)->asString(true),
                       $req->getCookie(Tracker::COOKIE_NAME)->asString(true),
                       'SERVERID='.$_COOKIE['SERVERID'],
                       $req->getParameter('session_id'));
      $headers[] = 'Cookie: '.join('; ', $cookies);
      $authorization = $req->getHeader('authorization');
      if (!empty($authorization)) {
        $headers[] = 'Authorization: '.$authorization;
      }
      $http['header'] = join("\r\n", $headers)."\r\n";
      $opts['ignore'] = isset($opts['ignore']) ? $opts['ignore'] : true;
    }

    $context = stream_context_create(array('http' => $http));

    $stream = @fopen($url, 'r', false, $context);
    if ($stream === false) {
      if ($opts['ignore'] == false) {
        S('log')->trace('url unavailable ['.$url.']', __METHOD__);
      }
      return '';
    }

    $data = stream_get_contents($stream);

    // $metas = stream_get_meta_data($stream);

    fclose($stream);

    if (P('cache.disabled') != 1) {
      S('stg')->set($key, $data, $ttl);
    }

    return $data;
  }

  public static function clean() {
    S('stg')->flush();
  }

}
