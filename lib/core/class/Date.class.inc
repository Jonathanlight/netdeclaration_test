<?php

final class Date 
{
  const MIN_YEAR = 1600;
  const DATE_MYSQL = 'Y-m-d H:i:s';
  const DATE_NULL = '0000-00-00 00:00:00';
  
  public static function asHash($date) {
      $date = is_array($date) ? $date[0] : $date;
    if (strlen($date) < 6 || substr($date, 0, 2) === '00') {
      return null;
    }
    $hash = array();
    if ($date[2] === '/' || $date[1] === '/' ) {
      list ($hash['date'], $hash['time']) = explode(' ', $date);
      list ($hash['day'], $hash['month'], $hash['year']) = explode('/', $hash['date']);
      list ($hash['hour'], $hash['min'], $hash['sec']) = explode(':', $hash['time']);
    }
    elseif ($date[4] === '-') {
      list ($hash['date'], $hash['time']) = explode(' ', $date);
      list ($hash['year'], $hash['month'], $hash['day']) = explode('-', $hash['date']);
      list ($hash['hour'], $hash['min'], $hash['sec']) = explode(':', $hash['time']);
    }
    elseif (strlen($date) == 10 && is_numeric($date)) { 
      $date = (int) $date;
      $hash['date'] = date('Y-m-d', $date);
      $hash['year'] = date('Y', $date);
      $hash['month'] = date('m', $date);
      $hash['day'] = date('d', $date);
      $hash['time'] = date('H:i:s', $date);
      $hash['hour'] = date('H', $date);
      $hash['min'] = date('i', $date);
      $hash['sec'] = date('s', $date);
    }
    if ($hash['year'] < self::MIN_YEAR) {
      S('log')->trace('bad input ('.$date.')', __METHOD__);
      return false;
    }
    $hash['ts'] = mktime((int) $hash['hour'], (int) $hash['min'], (int) $hash['sec'],
                         (int) $hash['month'], (int) $hash['day'], (int) $hash['year']);
    return $hash;
  }

  public static function asTimestamp($date) {
    if (strlen($date) < 6 || substr($date, 0, 2) === '00') {
      S('log')->trace('bad input ('.$date.')', __METHOD__);
      return null;
    }
    $hash = self::asHash($date); 
    return $hash['ts'];
  }
  
  public static function isBetween($from, $to, $date=null) {
    if (Date::isNull($from) && Date::isNull($to)) return true;
    $date = $date === null ? time() : self::asTimestamp($date);
    if (!Date::isNull($from) && $date < self::asTimestamp($from)) {
      return false;
    }
    if (!Date::isNull($to) && $date > self::asTimestamp($to)) {
      return false;
    }
    return true;
  }
  
  public static function toDb($date=null, $include_time = true) {
    $time = null;
    $date = trim($date);
    if (self::isNull($date)) {
      return '0000-00-00';
    }
    if (is_numeric($date) && $date > 100000) {
      return $include_time ? date(self::DATE_MYSQL, $date) : date('Y-m-d', $date);
    }
    if (strpos($date, ':') !== false) {
      list ($date, $time) = explode(' ',$date);
    }
    if (strpos($date, '-') !== false) {
      list ($year, $month, $day) = explode('-', $date);
    }
    else {
      list ($day, $month, $year) = explode('/', $date);
    }
    if ($year <= self::MIN_YEAR || $month <= 0 || $day <= 0) {
      return '0000-00-00';
    }
    $ret = $year.'-'.$month.'-'.$day;
    if ($time != null && $include_time) $ret .= ' '.$time;
    return $ret;
  }

  public static function when($diff=0) {
    return date(self::DATE_MYSQL, (time() + $diff));
  }

  public static function now() {
    return date(self::DATE_MYSQL);
  }

  private static $today = null;

  public static function today() {
    if (is_null(self::$today)) {
      self::$today = date('Y-m-d');
    }
    return self::$today;
  }

  public static function yesterday() {
    $ts = mktime(0, 0, 0, date('m'), date('d') - 1, date('Y'));
    return date('Y-m-d', $ts);
  }
  
  public static function isToday($hash) {
    return (intval($hash['day']) == intval(date('d')) && 
            intval($hash['month']) == intval(date('m')) && 
            intval($hash['year']) == intval(date('Y')));
  }

  public static function isYesterday($hash) {
    return (intval($hash['day']) == intval(date('d') - 1) && 
            intval($hash['month']) == intval(date('m')) && 
            intval($hash['year']) == intval(date('Y')));
  }

  public static function isNull($date) {
    return (is_numeric($date) && $date == 0) || empty($date) || substr($date, 0, 2) === '00';
  }

  public static function min2hour($min) {
    return floor($min / 60) . 'h' . str_pad(($min % 60), 2, '0', STR_PAD_LEFT);
  }

  public static function isValid($date) {
    $h = self::asHash($date);
    if (!is_array($h)) return false;
    return checkdate($h['month'], $h['day'], $h['year']);
  }
}
