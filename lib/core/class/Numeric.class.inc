<?php

class Numeric 
{
  public static function asFileSize($size, $type='auto') {
    $type = strtolower($type);
    if ($type === 'auto') {
      if ($size > 1048576) $type = 'm';
      elseif ($size > 1024) $type = 'k';
      else $type = 'o';
    }
    if ($type === 'k') $size = number_format($size / 1024,1, '.', '');
    elseif ($type === 'm') $size = number_format($size / 1048576,1, '.', '');
    else $size = number_format($size, 0, '', '');
    return $size.' '.strtoupper($type);
  }

  protected static $romans = array('', 
                                   'I', 'II', 'III', 'IV', 'V',
                                   'VI', 'VII', 'VIII', 'IX', 'X');

  protected static $roman = array('M' => 1000, 'CM' => 900, 'D' => 500, 'CD' => 400,
                                  'C' => 100, 'XC' => 90, 'L' => 50, 'XL' => 40,
                                  'X' => 10, 'IX' => 9, 'V' => 5, 'IV' => 4, 'I' => 1);
  
  public static function asRoman($num) {
    $n = intval($num);
    if ($num <= 10) {
      return self::$romans[$num];
    }
    $result = '';
    foreach (self::$roman as $roman => $value) {
      $matches = intval($n / $value);
      $result .= str_repeat($roman, $matches);
      $n = $n % $value;
    }
    return $result;
  }

}