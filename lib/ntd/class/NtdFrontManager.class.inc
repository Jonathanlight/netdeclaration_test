<?php

class NtdFrontManager {

  public static $routes = array(
    'signup' => '/signup',
    'user.signup' => '/user.signup',
    'login' => '/login',
    'search.results' => '/search/results',
  );

  public static function route($route) {
    if (!isset(self::$routes[$route])) {
      S('log')->error('route not exists [' . $route . ']', __METHOD__);
    }
    return self::$routes[$route];
  }

} 