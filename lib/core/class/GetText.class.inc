<?php

class GetText
{
  private static $strings = array();

  public static function dict($code, $bindings=null, $locale=0) {
    $locale = $locale >= 1 ? $locale : S('res')->getLocale();
    $prefix = substr($code, 0, 8);
    if ($prefix === 'snippet:') {
      $code = substr($code, 8);
      try {
        $snippet = Snippet::getInstance($code, array('ignore' => true));
      }
      catch (Exception $e) { return ''; }
      $msg = $snippet->getProperty('content', $locale);
      if ($msg === false) {
        S('log')->error('snippet ['.$code.']('.$locale.')', __METHOD__);
        $msg = $code;
      }
    }
    else {
      if (strpos($code, ':') >= 2) {
        S('log')->trace('character ":" is deprecated ('.$code.')', __METHOD__);
        list ($extension, $code) = explode(':', $code);
      }
      if (self::$strings[$locale] === null) {
        $extension = P('app.extension');
        include APP_PATH.'/'.$extension.'/locales/messages_'.I18N::code($locale).'.inc';
        self::$strings[$locale] = $strings;
      }
      $msg = self::$strings[$locale][$code];
      if ($msg === null) {
        S('log')->error('unknown ['.$code.']('.$locale.')', __METHOD__);
        $msg = $code.' ('.$locale.')';
      }
    }
    if (is_array($bindings) && count($bindings) >= 1 && strlen($msg) > 3) {
      $patterns = array();
      foreach ($bindings as $key => $value) {
        $patterns[] = '(('.$key.'))';
      }
      $msg = str_replace($patterns, $bindings, $msg);
    }
    return $msg;
  }

  /*  private static $extensions = array();
   private static $words = array();*/
  /*  private static function merge($extension, $locale) {
    self::$extensions[$extension][$locale] = true;
    if (strlen($extension) <= 1) return;
    include APP_PATH.'/'.$extension.'/locales/messages_'.I18N::lang($locale).'.inc';
    if (!is_array($words)) return ;
    self::$words[$locale] = array_merge((array) self::$words[$locale], $words);
    }*/

}
