<?php

class DecBdd {

  public static $ip_addresses = array(
    '127.0.0.1', // LAN : local
    '92.103.81.138', // Kernix : 15 rue cels
  );

  public static function manageWebServiceAccess() {
    if (P('app.domain') == 'dev.ntd-dev.li.kernix.net') return true;
    if (!in_array(long2ip(S('req')->getClient('ip')), self::$ip_addresses)) {
      throw new Exception('no access found');
    }
  }

  public static $apps = array(
    'dev'     => 'middle.dev.ntd-dev.li.kernix.net',
    'preprod' => 'middle.preprod-ntd.109.kernix.biz',
    'prod'    => 'middle.ntd.109.kernix.biz',
  );

  public static $models = array(
    'dectype',
    // 'dicoedi', // disable: too many data to sync
    'edimessagetype',
    'formulairetype',
    'ifield',
    'imodel',
    'itemplate',
    'letter',
    'millesime',
    'operation',
    'page',
    'rof',
    'service',
    'servicetype',
    'snippet',
    'suivipayant',
    'tarif',
  );

  public static function getAll($action, $params = null) {
    $exports = array();
    foreach (self::$apps as $name => $hostname) {
      if ($name == 'dev') {
        $exports[$name] = self::get($hostname, $action, $params, true);
      } else {
        $exports[$name] = self::get($hostname, $action, $params);
      }
    }
    return $exports;
  }

  public static function get($hostname, $action, $params = null, $ssl = false) {
    if ($ssl) {
        $protocol = 'https';
    } else {
        $protocol = 'http';
    }
    $response = H::get( $protocol . '://' . P('auth.login') . ':' . P('auth.password') . '@' . $hostname . '/' . $action, $params, array('ttl' => 0));
    $export = null;
    if(!empty($response)) {
      eval('$export = ' . $response . ';');
    }

    if (!is_array($export)) {
      S('log')->error($export, __METHOD__);
      return null;
    }
    return $export;
  }

  public static function post($hostname, $action, $params = null, $ssl = false){
    //$out = H::get(, $params, array('ttl' => 0));
    if ($ssl) {
        $protocol = 'https';
    } else {
        $protocol = 'http';
    }
    $url = $protocol . '://' . P('auth.login') . ':' . P('auth.password') . '@' . $hostname . '/' . $action;

    // use key 'http' even if you send the request to https://...
    $options = array(
      'http' => array(
        'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
        'method'  => 'POST',
        'content' => http_build_query($params),
      ),
    );
    $context  = stream_context_create($options);
    $result = file_get_contents($url, false, $context);

    $export = null;
    eval('$export = ' . $result . ';');
    if (!is_array($export)) {
      S('log')->error($export, __METHOD__);
      return null;
    }
    return $export;
  }

}
