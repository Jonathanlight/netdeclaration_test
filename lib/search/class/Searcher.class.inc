<?php

/****

IFNULL(MD1.value, 0)
distance en miles

****/

class Searcher
{
  private $dbo = null;
  private $distance = null;
  private $engine = null;
  private $exclude = null;
  private $indexes = array();
  private $locale = 0;
  private $latitude = null;
  private $limit = 10;
  private $longitude = null;
  private $metas = null;
  private $model = 0;
  private $models = null;
  private $records = null;
  private $offset = 0;
  private $order = null;
  private $page_count = 10;
  private $parent = 0;
  private $partial = false;
  private $partial_query = false;
  private $query = '';
  private $stem_count = 0;
  private $tables = null;
  private $where = '';

  public function __construct($opts=null) {
    $opts = (array) $opts;
    $this->dbo = S('dbo');
    foreach ($opts as $key => $value) {
      if ($value === null) continue;
      $this->{$key} = is_array($value) ? $value : trim($value);
    }
    $this->partial = (bool) $this->partial;

    if ($this->query === '*') $this->query = '';

    $this->models = (array) $this->models;
    foreach ($this->models as &$value) {
      $value = Model::id($value);
    }
    $this->model = (int) $this->model;
    $this->offset = (int) $this->offset;
    $this->limit = $this->limit >= 1 ? $this->limit : 1;
    $this->locale = $this->locale >= 1 ? $this->locale : S('res')->getLocale();

    if ($this->latitude !== null && $this->longitude !== null && $this->distance < 1) {
      $this->distance = 10;
    }
    $this->engine = Engine::factory();
    $this->metas = is_array($this->metas) ? $this->metas : array();
    $this->tables = (array) $this->tables;
    S('app')->hook('onSearch', array('searcher' => $this));
  }

  private function getResultSet() {

    if (empty($this->query)) {
      $sql = 'SELECT id FROM '.Document::TABLE.' WHERE 0';
      return $this->dbo->query($sql);
    }
    
    $tables = $this->tables;

    $select = 'SELECT d.id, d.size, d.model_id, d.record_id';
    $tables[Document::TABLE] = 'd';
    $where = ' WHERE d.status>=1 AND d.locale='.intval($this->locale);
    $group_by = '';
    $having = '';
    $order = '';
    $limit = ' LIMIT '.$this->limit;
    $offset = ' OFFSET '.$this->offset * $this->limit;

    $bindings = array();

    if ($this->model >= 1) {
      $where .= ' AND d.model_id='.$this->model.' AND d.record_id='.T($this->model).'.id';
    }
    elseif (!empty($this->models)) {
      $where .= ' AND d.model_id IN ('.implode(',', $this->models).')';
    }

    if (!empty($this->records)) {
      $where .= ' AND d.record_id IN ('.implode(',', $this->records).')';
    }

    if (!empty($this->exclude)) {
      foreach ($this->exclude as $model => $record) {
        $where .= ' AND NOT(d.model_id='.intval($model).' AND d.record_id='.intval($record).')';
      }
    }

    if (!empty($this->where)) {
      $where .= ' '.$this->where;
    }

    if (empty($this->order)) {
      $this->order = 'doc_weight DESC';
    }
    
    $order = ' ORDER BY '.$this->order;

    $first = substr($this->query, 0, 1);
    $last = substr($this->query, -1);

    if ($this->engine->hasFlag(Engine::FLAG_FULLTEXT) && $first == '"' && $last == '"') {
      $tables[Engine::TABLE_INDEX] = 'i';
      $select .= ', (d.ranking) as doc_weight';
      $where .= ' AND i.document_id=d.id';
      $where .= ' AND MATCH (i.content) AGAINST (\'"#query#"\' IN BOOLEAN MODE)';
      $bindings['#query#'] = str_replace('"', '', $this->query);
    }
    else {
      $select .= ', (SUM(b.weight) + d.ranking + COUNT(d.id)) as doc_weight'; 
      //        $select .= ', COUNT(d.id) AS word_count';
      $tables[Engine::TABLE_BUCKET] = 'b';
      $where .= ' AND b.document_id=d.id';
      $where .= ' AND b.stem_id IN ([stems])';
      $stems = $this->query2ids();
      if (count($stems) < 1) $stems[] = 0;
      $bindings['[stems]'] = $stems;
      if ($this->partial_query === false) {
        //          $having = ' HAVING word_count>='.$this->stem_count;
      }
      $group_by = ' GROUP BY b.document_id';
    }
    
    if (count($this->metas) > 0) {
      $tables[Meta::TABLE] = 'md';
      $where .= ' AND d.model_id=md.'.Meta::FIELD_MODEL.' AND d.record_id=md.'.Meta::FIELD_RECORD;
      //      $select .= ', md.created_at';
      foreach ($this->metas as $meta => $value) {
        $where .= ' AND md.`'.$meta.'`=:'.$meta.':';
        $bindings[':'.$meta.':'] = $value;
      }
    }
    
    if (count($this->indexes) > 0) {
      $tables[Engine::TABLE_INDEX] = 'i';
      $where .= ' AND d.id=i.id';
      foreach ($this->indexes as $index => $value) {
        $where .= ' AND i.`'.$index.'`=:'.$index.':';
        $bindings[':'.$index.':'] = $value;
      }
    }

    if ($this->model > 0) {
      //      $tables[T($this->model)] = 'm';
    }
    
    if ($this->latitude !== null && $this->longitude !== null && $this->distance !== null) {
      $tables[Meta::TABLE] = 'md';
      $longitude1 = $this->longitude - $this->distance / abs(cos(deg2rad($this->latitude)) * 69);
      $longitude2 = $this->longitude + $this->distance / abs(cos(deg2rad($this->latitude)) * 69);
      $latitude1 = $this->latitude - ($this->distance / 69);
      $latitude2 = $this->latitude + ($this->distance / 69);
      $select .= ',7912*ASIN(SQRT(POWER(SIN(('.$this->latitude.'-md.latitude)*0.00872664625997),2)+COS('.$this->latitude.'*0.0174532925)*cos(md.latitude*0.0174532925)*POWER(SIN(('.$this->longitude.'-md.longitude)*0.00872664625997),2))) as distance';
      $where .= ' AND md.longitude BETWEEN '.$longitude1.' AND '.$longitude2.' AND md.latitude BETWEEN '.$latitude1.' AND '.$latitude2;
      $order = ' ORDER BY distance';
    }
    
    foreach ($tables as $key => &$value) {
      $value = $key.' AS '.$value;
    }
    $from = ' FROM '.join(', ', $tables);

    $sql = $select.$from.$where.$group_by.$having.$order.$limit.$offset;
    $modifiers = array('SQL_CACHE', 'SQL_CALC_FOUND_ROWS');
    $rs = $this->dbo->query($sql, $bindings, $modifiers);

    //    $this->dbo->debug();

    return $rs;
  }

  private function query() {

    $rs = $this->getResultSet();

    $this->found_rows = $rs->foundRows();

    if (strlen($this->query) > 1 && $this->offset < 1) {
      $category = $rs === false || $rs->numRows() < 1 ? 'search.empty' : 'search';
      if (is_array($this->models) && count($this->models) == 1) {
        $category = Model::name($this->models[0]).'.'.$category;
      }
      S('req')->track($this->query, $category);
      $id = Tracker::str2id($this->query, Tracker::STR_QUERY);
      $this->dbo->insert(Tracker::TABLE_SEARCH,
                         array('query_id' => $id,
                               'visit_id' => S('req')->getId(),
                               'found_rows' => $this->found_rows,
                               'created_on' => Date::today()),
                         array('IGNORE'));
    }
    return $rs;
  }

  public function asArray() {
    $items = array();
    $rs = $this->query();
    foreach ($rs as $row) {
      $items[] = array('model_id' => (int) $row['model_id'],
                       'record_id' => (int) $row['record_id']);
    }
    return $items;
  }

  public function asItems() {
    $items = array();
    $rs = $this->query();
    foreach ($rs as $row) {
      $items[] = Item::getInstance((int) $row['model_id'],
                                   (int) $row['record_id']);
    }
    return $items;
  }

  public function asSet() {
    $set = array();
    $rs = $this->query();
    foreach ($rs as $row) {
      $set[] = $row['record_id'];
    }
    return $set;
  }

  public function getPagination($opts=null) {
    $opts = $opts ?: array();
    $opts['found_rows'] = $this->found_rows;
    $opts['limit'] = $this->limit;
    $opts['offset'] = $this->offset;
    return Pagination::getInstance($opts);
  }

  public function asSql() {
    $rs = $this->query();
    return $rs->asSql();
  }

  public function asHash() {
    $rs = $this->query();
    $search['results'] = array();
    $metas = array('created_at', 'updated_at');
    
    foreach ($rs as $i => $hash) {
      try {
        $item = Item::getInstance((int) $hash['model_id'],
                                  (int) $hash['record_id'],
                                  array('metas' => $metas));
        $document = $item->asSearchHash($this->locale); 
        //        $search['items'][] = $item;
      }
      catch (Exception $e) {
        Document::remove(array((int) $hash['model_id'],
                               (int) $hash['record_id']));
        continue ;
      }
      $document['index'] = $this->offset * $this->limit + $i + 1;
      $document['rate'] = strlen($hash['rate']) >= 5 ? Hash::decode($hash['rate']) : null;
      $document['subscriptions'] = (int) $hash['subscriptions'];
      $document['doc_weight'] = $hash['doc_weight'];
      $search['results'][] = $document;
    }
    $search['query'] = empty($this->query) ? '*' : $this->query;
    $search['action'] = $this->action;
    $search['found_rows'] = $this->found_rows;
    $search['limit'] = $this->limit;
    $search['start'] = ($this->offset * $this->limit) + 1;
    $search['end'] = ($this->offset + 1) * $this->limit;
    $search['offset'] = $this->offset;
    if ($search['end'] > $this->found_rows) {
      $search['end'] = $this->found_rows;
    }
    return $search;
  }

  public static $stopwords = array();

  private function query2ids() {
    $query = strtolower($this->query); 
    $locale = $this->locale;
    $words = Engine::tokenize(Indexer::normalize($query)); 
    $stems = array();
    if (self::$stopwords[$locale] === null) {
      self::$stopwords[$locale] = Indexer::getStopWords($locale);
    }
    $dbo = $this->dbo; 
    $check_synonyms = $this->engine->hasFlag(Engine::FLAG_SYNONYM);
    foreach ($words as $word) {
      if (strlen($word) < 2 || in_array($word, self::$stopwords[$locale])) {
        continue;
      } 
      $stem = Indexer::extractStem($word, $locale);
      $stems[$stem]++; 
      $this->stem_count++;
      if (!$check_synonyms) continue ;
      $synonym = $dbo->fetchValue('SELECT synonym'
                                  .' FROM '.T('synonym')
                                  .' WHERE name=:word:'
                                  .  ' AND locale='.$this->locale,
                                  array(':word:' => $word));
      if (!empty($synonym)) {
        $stem = Indexer::extractStem($synonym, $locale);
        $stems[$stem]++;
      }
    }
    $stems = array_keys($stems); 
    if (count($stems) < 1) return array();
    $parts = $bindings = array();
    foreach ($stems as $i => $stem) {
      $bindings[':name'.$i.':'] = $stem;
      $parts[] = 'name=:name'.$i.':';
    }
    $where = join(' OR ', $parts);
    $results = $dbo->asSet('SELECT id'
                           .' FROM '.Engine::TABLE_STEM
                           .' WHERE '.$where,
                           $bindings);
    if (count($results) < 1 && $this->partial === true && count($words) === 1) {
      $bindings = array('#name#' => $words[0]);
      $results = $dbo->asSet('SELECT id'
                             .' FROM '.Engine::TABLE_STEM
                             .' WHERE name LIKE "%#name#%"',
                            $bindings);
      $this->partial_query = true;
    }
    //S('dbo')->debug();
    //S('log')->debug($result);
    return $results;
  }
  
  public static function getInstance($opts) {
    $class = __CLASS__;
    return new $class($opts);
  }
  
}
