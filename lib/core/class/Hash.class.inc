<?php

final class Hash 
{
  public static function crc($input) {
    $crc = array();
    array_walk_recursive($input, array(self, 'getCrcCallback'), $crc); 
    sort($crc); 
    $str = join('', $crc); 
    //    S('log')->debug($str);
    return String::crc32($str);
  }

  protected static function getCrcCallback($value, $key, $crc) { 
    $str = '';
    if (!empty($value) && is_scalar($value)) {
      if (!empty($key) && !is_numeric($key)) {
        $str .= $key;
      }
      $str .= $value;
    }
    if (!empty($str)) {
      $crc[] = $str;
    }
  }

  public static function crush(&$input) {
    if (!is_array($input)) return ;
    foreach ($input as $key => &$value) {
      $value = is_array($value) ? serialize($value) : $value;
    }
  }

  public static function duplicate($hash) {
    //    return array_diff_key($hash, array());
    $out = $hash + array();
    return $out;
  }

  public static function isNumeric($hash) {
    foreach ($hash as $value) {
      if (!is_numeric($value)) return false;
    }
    return true;
  }

  public static function merge($old_arr, $new_arr) {
    $old_arr = (array) $old_arr;
    if (!is_array($new_arr)) $new_arr = @unserialize($new_arr);
    if (!is_array($new_arr)) return $old_arr;
    foreach ($new_arr as $k0 => $v0) {
      if (is_array($v0)) {
	if (!is_array($old_arr[$k0])) $old_arr[$k0] = array();
	foreach ($v0 as $k1 => $v1) {
	  if (is_array($v1)) {
	    if (!is_array($old_arr[$k0][$k1])) $old_arr[$k0][$k1] = array();
	    foreach ($v1 as $k2 => $v2) $old_arr[$k0][$k1][$k2] += (int) $v2;
	  }
	  else $old_arr[$k0][$k1] += (int) $v1;
	}
      }
      else $old_arr[$k0] += $v0;
    }
    return $old_arr;
  }
  
  public static function trim(&$input) {
    if (!is_array($input)) return ;
    foreach ($input as $key => $value) {
      if (is_array($value) || is_object($value)) continue ;
      $input[$key] = trim($value);
    }
    return $input;
  }

  public static function asAttributes($in, $protect=false) {
    if (!is_array($in) || empty($in)) return '';
    $out = array();
    if (is_array($in['on'])) {
      foreach ($in['on'] as $event => $value) {
        $in['on'.$event] = $value;
      }
      unset($in['on']);
    }
    if (is_array($in['data'])) {
      foreach ($in['data'] as $key => $value) {
        if (is_array($value) && ($key === 'values' || $key === 'args')) {
          $value = json_encode($value);
          $value = htmlspecialchars($value);
        }
        $in['data-'.$key] = $value;
      }
      unset($in['data']);
    }
    foreach ($in as $key => $value) {
      if (is_array($value)) {
        $value = join(($key == 'style' ? ';' : ' '),
                      $value);
      }
      if ($protect === true) {
        $value = h($value);
      }
      $out[] = $key.'="'.$value.'"';
    }
    return join(' ', $out);
  }

  public static function toXml($xw, $objects) {
    foreach ($objects as $key => $obj) {
      $xw->startElement('var');
      $xw->writeAttribute('name', $key);
      if (is_array($obj) || is_object($obj)) {
        if (is_object($obj)) {
          if ($obj instanceof ActiveRecord) { 
            $obj = $obj->getAttributes(); 
          }
          elseif ($obj instanceof Collection) {
            $xw->writeAttribute('type', 'array');
            self::toXml($xw, $obj->asArray());
            return ; 
          }
        }
        $xw->writeAttribute('type', 'hash');
        foreach ($obj as $k => $v) {
          $xw->startElement('key');
          $xw->writeAttribute('name', $k);
          $xw->text(htmlspecialchars($v), ENT_COMPAT, 'UTF-8');
          $xw->endElement();
        }
        $obj = join(',', (array) $obj);
      }
      else {
        $xw->text(htmlspecialchars($obj), ENT_COMPAT, 'UTF-8');
      }
      $xw->endElement();
    }
  }

  public static function back($arr,$id) {
    $arr = (array) $arr;
    if (count($arr)<=1) return $arr;
    $id_arr = array();
    $i = 0;
    $pos = null;
    foreach ($arr as $k => $v) {
      $id_arr[] = $k;
      if ($k==$id) $pos = $i;
      $i++;
    }
    if ($pos===null || $pos===0) return $arr;
    $tmp = $id_arr[$pos-1];
    $id_arr[$pos-1] = $id_arr[$pos];
    $id_arr[$pos] = $tmp;
    foreach ($id_arr as $v) $ret_arr[$v] = $arr[$v];
    return $ret_arr;
  }

  public static function forward($arr,$id) {
    $arr = (array) $arr;
    if (($n=count($arr))<=1) return $arr;
    $id_arr = array();
    $i = 0;
    $pos = null;
    foreach ($arr as $k => $v) {
      $id_arr[] = $k;
      if ($k==$id) $pos = $i;
      $i++;
    }
    if ($pos===null || $pos===($n-1)) return $arr;
    $tmp = $id_arr[$pos+1];
    $id_arr[$pos+1] = $id_arr[$pos];
    $id_arr[$pos] = $tmp;
    foreach ($id_arr as $v) $ret_arr[$v] = $arr[$v];
    return $ret_arr;
  }

  public static function moveCell($in_arr, $index, $way='right', $cycle=true) {
    $in_arr = (array) $in_arr;
    if (($n=count($in_arr)) <= 1) return $in_arr;

    $keys_arr = array_keys ($in_arr);
    $pos = array_search ($index, $keys_arr);
    if ($pos===false) return $in_arr;

    $from = $pos;
    if ($pos===($n-1)) {
      $to = 0;
    }
    else {
      $to = $pos + 1;
    }

    $tmp = $keys_arr[$to];
    $keys_arr[$to] = $keys_arr[$from];
    $keys_arr[$from] = $tmp;
    foreach ($keys_arr as $key) {
      $out_arr[$key] = $in_arr[$key];
    }

    return $out_arr;
  }

  public static function hasKey($input_arr, $keys_arr) {
    $input_arr = (array) $input_arr;
    $keys_arr = (array) $keys_arr;
    foreach ($keys_arr as $key) {
      if (in_array($key, $input_arr)) return true;
    }
    return false;
  }

  public static function decode($str) {
    $str = trim($str);
    if (empty($str)) return array();
    $ret = (array) @unserialize($str);
    return $ret;
  }

  public static function encode($arr) {
    if (!is_array($arr)) return serialize(array());
    return serialize($arr);
  }

  public static function concat() {
    $result = array();
    foreach (func_get_args() as $arr) {
      $arr = (array) $arr;
      foreach ($arr as $v) $result[] = $v;
    }
    return $result;
  }

  public static function asSql($input, $protect=true) {
    if (empty($input)) $output = '1';
    $pairs = array();
    foreach ($input as $key => $value) {
      if ($protect === true) {
        $value = S('dbo')->protect($value);
      }
      $pairs[] = '`'.$key.'` = '.$value;
    }
    return join(' AND ', $pairs);
  }

  public static function asSet($input, $sep=',', $replace_space_flag=false) {
    if (!is_array($input)) { 
      if ($replace_space_flag === true) {
        $input = str_replace(array(' '), array(','), $input);
      }
      $input = String::asSet($input);
    }
    return join($sep, $input);
  }

  public static function toSet($hash, $enclose=false) {
    if (!is_array($hash)) {
      $hash = String::asSet($hash);
    }
    return $enclose === false ? join(',', $hash) : "'".join("','", $hash)."'";
  }

  public static function match($arr1, $arr2) {
    $arr1 = (array) $arr1;
    $arr2 = (array) $arr2;
    foreach ($arr1 as $v) {
      if (!in_array($v, $arr2)) return $v;
    }
    return true;
  }

  public static function insert(&$hash, $item, $index) {
    if ($index < 1) {
      array_unshift($hash, $item);
      return ;
    }
    if ($index >= count($hash)) {
      array_push($hash, $item);
      return ;
    }
    $hash = array_merge(array_slice($hash, 0, $index), 
                        array($item), 
                        array_slice($hash, $index));
  }


}


