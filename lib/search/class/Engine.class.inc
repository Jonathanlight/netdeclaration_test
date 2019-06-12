<?php

class Engine extends ActiveRecord {

  const TABLE_BUCKET = 'sch_bucket';
  const TABLE_INDEX = 'sch_index';
  const TABLE_STEM = 'sch_stem';

  const FLAG_FULLTEXT = 1;
  const FLAG_SYNONYM = 2;

  public static $flags = array(self::FLAG_FULLTEXT => 'fulltext',
                               self::FLAG_SYNONYM => 'synonymes');

  public function getDetails() {
    $n = S('dbo')->fetchValue('SELECT COUNT(*) FROM '.Document::TABLE);
    return array('nbre de documents indexés' => $n);
  }
  
  public static $singletons = array();
  
  public static function factory() {
    if (self::$singletons['engine'] === null) {
      self::$singletons['engine'] = Engine::getInstance(1);
    }
    return self::$singletons['engine'];
  }
  
  public static function getIndexer() {
    $indexer = self::$singletons['indexer'];
    if ($indexer === null) {
      $indexer = new Indexer();
      $indexer->setEngine(self::factory());
    }
    return $indexer;
  }

  public static function query($opts=null) {
    return Searcher::getInstance($opts);
  }
  
  public static function tokenize($content) {
    $tokens = preg_split('/[\W\s]+/u', $content);
    $tokens = empty($tokens) ? array() : $tokens;
    return $tokens;
  }
  
  public static function crawl() {
    if (ini_get('mbstring.func_overload') < 1) {
      S('log')->warn('mbtring.func_overlaod should be 7');
    }
    $opts = array('filters' => array('|<|status' => Document::STATUS_ONLINE),
                  'group' => array('model_id', 'record_id'));
    $n = 0;
    foreach (ResultSet::getInstance(Document::TABLE, $opts) as $row) {
      try {
        $item = Item::getInstance((int) $row['model_id'], 
                                  (int) $row['record_id']);
        $item->index();
        $n++;
      }
      catch (Exception $e) { Document::remove($row); } 
    }
    return $n;
  }

}