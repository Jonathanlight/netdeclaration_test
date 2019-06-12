<?php

Class ResultSet implements Iterator, Countable 
{
  private $current_record = false;
  private $link = null;
  private $found_rows = null;
  private $index = 0;
  private $map = null;
  //  private $pagination = null;
  private $result = null;
  private $sql = null;
  private $title = null;
  
  public function __construct($result, $sql, $link) { 
    $this->result = $result;
    $this->sql = $sql;
    $this->link = $link;
    if (strpos($this->sql, 'SQL_CALC_FOUND_ROWS') >= 7) {
      $this->foundRows();
    }
  }

  public function asSql() {
    return $this->sql;
  }
  
  public function asHash($key_field=null, $value_field=null) {
    if ($key_field === null) {
      $fields = $this->getFields();
      $key_field = $fields[0];
      $value_field = $fields[1];
    }
    $hash = array();
    foreach ($this as $row) {
      $hash[$row[$key_field]] = $value_field ? $row[$value_field] : $row;
    }
    return $hash;
  }

  public function asArray($key=null) {
    $results = array();
    foreach ($this as $row) {
      if ($key === null) {
        $results[] = $row;
        continue ;
      }
      $results[$row[$key]] = $row; 
    }
    return $results;
  }

  public function asSet($field=null) {
    $set = array();
    foreach ($this as $row) {
      $set[] = $field ? $row[$field] : current($row);
    }
    return $set;
  }

  public function fetchFieldName($field_offset=0) {
    $obj = mysql_fetch_field($this->result, $field_offset);
    return $obj === false ? false : $obj->name;
  } 

  public function fetchArray() { return mysql_fetch_array($this->result, MYSQL_NUM); }

  public function fetchAttributes($sql, $bindings=null) {
    return $this->fetchHash($sql, $bindings);
  }

  public function fetchHash() { 
    $hash = mysql_fetch_array($this->result, MYSQL_ASSOC); 
    if ($hash === false) return false;
    if ($this->map !== null) {
      $tmp = array();
      foreach ($this->map as $from => $to) {
        $tmp[$to] = $hash[$from];
      }
      $hash = $tmp;
    }
    return $hash;
  }  

  public function fetchObject() { return mysql_fetch_object($this->result); }
  public function fetchValue() { return mysql_result($this->result, 0, 0); }


  public function foundRows() {
    if ($this->found_rows !== null) {
      return $this->found_rows;
    }
    $res = mysql_query('SELECT FOUND_ROWS()', $this->link);
    if ($res === false) {
      return $this->trace('found_rows failure '.$this->sql, __METHOD__);
    }
    $this->found_rows = mysql_result($res, 0, 0);
    return $this->found_rows;
  }

  public function free() { 
    // peut on detruire l'objet ResultSet ?
    return mysql_free_result($this->result);
  }

  public function getNext($result_type=MYSQL_ASSOC) { 
    return mysql_fetch_array($this->result, $result_type); 
  }

  public function isEmpty() { return $this->numRows() < 1; }

  public function numRows() {
    $ret = mysql_num_rows($this->result);
    if ($ret === false) {
      $this->trace($this->sql, __METHOD__);
      return 0;
    }
    return (int) $ret;
  }

  public function count() {
    return $this->numRows();
  }

  public function getFields() {
    if ($this->map !== null) {
      return array_values($this->map);
    }
    $fields = array();
    $i = 0;
    $n = mysql_num_fields($this->result);
    while ($i < $n) {
      $meta = mysql_fetch_field($this->result, $i);
      $fields[] = $meta->name;
      $i++;
    }
    return $fields;
  }

  public function numFields() {
    $ret = mysql_num_fields($this->result);
    return $ret === false ? $this->trace($this->sql, __METHOD__) : $ret;
  }

  public function result($row=0, $col=0) { 
    $ret = mysql_result($this->result, $row, $col); 
    return $ret === false ? $this->trace($this->sql, __METHOD__) : $ret;
  }

  public function sum($field) {
    $out = 0;
    foreach ($this as $row) {
      $out += $row[$field];
    }
    return $out;
  }

  public function map($map) {
    if (!is_array($map) || count($map) < 1) {
      S('log')->error('bad input', __METHOD__);
      S('log')->debug($map, 'mapping');
      throw new Exception('bad mapping');
    }
    $this->map = array();
    foreach ($map as $key => $value) {
      $key = is_int($key) ? $value : $key;
      $this->map[$key] = $value;
    }
    return $this;
  }

  public function unmap() {
    $this->map = null;
    return $this;
  }

  public function debug($prefix='') { 
    $prefix = empty($prefix) ? '' : ' : '.$prefix;
    S('log')->debug($prefix.$this->sql); 
  }

  private function trace($msg, $method, $trace_error=true) {
    S('log')->log->error($msg, $method); 
    if ($trace_error === true) {
      S('log')->log->error('['.mysql_errno($this->link).'] '
                           .mysql_error($this->link),
                           __METHOD__); 
    }
    return false;
  }

  public function goLast() {
    if ($this->numRows() < 1) return false;
    $ret = mysql_data_seek($this->result, ($this->numRows() - 1));
    if ($ret === false) return $this->trace($this->sql, __METHOD__);
    return $ret;
  }

  public function goFirst() { 
    if ($this->numRows() < 1) return ;
    $ret = mysql_data_seek($this->result, 0);
    if ($ret === false) return $this->trace($this->sql, __METHOD__);
    return $ret;
  }

  public function rewind() { 
    $this->current_record = false;
    if ($this->numRows() < 1) return ;
    $ret = mysql_data_seek($this->result, 0);
    if ($ret === false) return $this->trace($this->sql, __METHOD__);
    $this->current_record = $this->fetchHash();
    $this->index = 0;
    return $ret;
  }

  public function current() {
    return $this->current_record;
  }
  
  public function key() {
    return $this->index;
  }

  public function next() {
    $this->current_record = $this->fetchHash();
    $this->index++;
    return $this->current_record;
  }
  
  public function valid() {
    return $this->current_record !== false;
  }
  
  public function setTitle($title) {
    $this->title = $title;
  }

  public function hasPagination() {
    return $this->limit < 1 ? false : $this->foundRows() > $this->limit;
  }

  public function asCollection($model) {
    $hash = $this->getBoundaries();
    $opts = array('limit' => $hash['limit'], 
                  'offset' => $hash['offset']);
    $collection = Item::collect($model, $opts);
    $collection->setResultSet($this);
    $collection->setSql($this->sql);
    return $collection;
  }

  public function getBoundaries() {
    preg_match('/ LIMIT\s+(?<limit>\d+)\s+OFFSET\s+(?<offset>\d+)/i', $this->sql, $hash);
    $hash['limit'] = $hash['limit'] < 1 ? 50 : $hash['limit'];
    $hash['offset'] = intval($hash['offset'] / $hash['limit']);
    return $hash;
  }

  public function getPagination() {
    /** do not forget **/
    $hash = $this->getBoundaries();
    return new Pagination(array('limit' => $hash['limit'],
                                'offset' => $hash['offset'],
                                'found_rows' => $this->foundRows()));
  }

  public function __toString() {
    return $this->title === null ? mysql_field_table($this->result, 0) : $this->title;
  }

  public static function getInstance($table, array $opts=array()) {
    $dbo = S('dbo');
    $sql = 'SELECT';
    if (is_array($opts['modifiers'])) {
      $sql .= ' '.join(' ', $opts['modifiers']);
    }
    if (isset($opts['map'])) {
      $opts['map'] = (array) $opts['map'];
      foreach ($opts['map'] as $key => &$value) {
        $value = is_int($key) ? $value : $key.' AS '.$value;
      }
      $sql .= ' '.join(',', $opts['map']); 
    }
    else {
      $sql .= ' *';
    }
    $sql .= ' FROM '.$table;
    if (is_array($opts['filters'])) {
      $sql .= ' WHERE '.$dbo->hash2sql($opts['filters']);
    }
    if (is_array($opts['order'])) {
      $orders = array();
      foreach ($opts['order'] as $key => $value) {
        if (!preg_match('/^[\w\.]+$/', $key.$value)) {
          S('log')->error('invalid order ['.$key.'-'.$value.']', __METHOD__);
          continue ;
        }
        if (is_numeric($key)) {
          $orders[] = $value;
        }
        else {
          $orders[] = $key.(strtoupper($value) ===  'DESC' ? ' DESC' : '');
        }
      }
      $sql .= ' ORDER BY '.join(', ', $orders);
    }
    if ($opts['limit'] >= 1) {
      $sql .= ' LIMIT '.$opts['limit'];
    }
    $sql .= empty($opts['group']) ? '' : ' GROUP BY '.join(', ', $opts['group']);
    return $dbo->query($sql, null, $opts['modifiers']);
  }

}

