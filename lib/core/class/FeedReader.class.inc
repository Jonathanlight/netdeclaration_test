<?php

/***
 Fonctionne avec : 
 - http://es.noticias.yahoo.com/rss/internet.xml

copyright, description, image, items, language,
lastBuildDate, link, title, ttl   

 ***/

class FeedReader implements Iterator {

  public $items = null;
  private $timeout = 10;

  public function __construct($source=null, $opts=null) {
    if (strlen($source) < 5) {
      throw new Exception('invalid source  ['.$source.']');
    } 
    $opts = (array) $opts;
    foreach ($opts as $key => $value) {
      $this->{$key} = $value;
    }
    $xml = $this->fetchContent($source);
    if ($xml === false) {
      throw new Exception('invalid source ['.$source.']');
    }
    $doc = new DOMDocument();
    $doc->preserveWhiteSpace = false;
    if ($doc->loadXML($xml) === false) {
      throw new Exception('invalid xml in ['.$source.']');
    }
    $this->load($doc);
  }
  
  private function fetchContent($source) {
    $opts = array('http' => array('timeout' => $this->timeout));
    $context = stream_context_create($opts);
    return file_get_contents($source, false, $context);
  }

  private function load($doc) { 
    $channel = $doc->documentElement->firstChild;
    foreach ($channel->childNodes as $node) {
      if ($node->tagName === 'item') {
        $this->items[] = $this->node2hash($node);
      }
      else {
        $children = $node->childNodes;
        if ($children->length >= 2) {
          $this->{$node->tagName} = $this->node2hash($node);
        }
        else {
          //          $this->{$node->tagName} = utf8_decode($node->nodeValue);
          $this->{$node->tagName} = $node->nodeValue;
        }
      }
    }
  }

  private function node2hash($node) {
    $hash = array();
    foreach ($node->childNodes as $child) {
      //      $hash[$child->tagName] = utf8_decode($child->nodeValue);
      $hash[$child->tagName] = $child->nodeValue;
    }
    if (strlen($hash['pubDate']) >= 8) {
      $time = date_parse($hash['pubDate']);
      $time = mktime($time['hour'], $time['minute'], $time['second'], 
                     $time['month'], $time['day'], $time['year']);
      if ($time > time()) {
        $time = time();
      }
      $hash['pubDate'] = date(Date::DATE_MYSQL, $time);
    }
    return $hash;
  }

  public function rewind()  { reset($this->items); }
  public function current() { return current($this->items); }
  public function key()     { return key($this->items); }
  public function next()    { return next($this->items); }
  public function valid()   { return $this->current() !== false; }
  
  public function debug() {
    S('log')->debug($this);
  }

  public static function getInstance($source) {
    $class = __CLASS__;
    return new $class($source);
  }
  
}