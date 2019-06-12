<?php

class Search extends ActiveRecord {

  const TABLE_HIT = 'sys_search_hit';
  const TABLE_HOP = 'sys_search_hop';

  const MAX_SIZE = 2000;

  private $limit = 0;
  private $offset = 0;

  private $cache = array();

  public function refresh($is_new=false) {
    $this->cache = array();
    $callback = explode(':', $this->callback);
    $opts = unserialize($this->opts);
    $hash = call_user_func($callback, $opts);
    $model_id = $this->model_id;
    $items = '';
    if (count($hash['items']) > 0) {
      $items = array_slice($hash['items'], 0, self::MAX_SIZE);
      foreach ($items as &$value) {
        $value = $model_id > 0 ? $value[1] : join(':', $value);
      }
      if ($is_new === false) {
        $old = trim($this->items, ',');
        $old = explode(',', $old);
        $diff = array_diff($items, $old);
        $row = array('search_id' => $this->id,
                     'added_on' => Date::today());
        foreach ($diff as $item) {
          $item = $model_id > 0
                ? array($model_id, $item)
                : explode(':', $item);
          $row['model_id'] = $item[0];
          $row['record_id'] = $item[1];
          S('dbo')->insert(self::TABLE_HOP, $row,
                           array('IGNORE'));
        }
      }
      $items = ','.join(',', $items).',';
    }
    $attributes = array('found_rows' => (int) $hash['found_rows'],
                        'metas' => serialize($hash['metas']),
                        'refreshed_at' => Date::now(),
                        'items' => $items);
    $this->setAttributes($attributes);
  }

  public function getPagination($opts=null) {
    $opts = (array) $opts;
    $opts += array('limit' => $this->limit,
                   'offset' => $this->offset,
                   'found_rows' => $this->getFoundRows());
    return new Pagination($opts);
  }

  protected function hasItems() {
    return strlen($this->items) >= 1;
  }

  public function getItems($page=1, $limit=10) {
    if (!isset($this->cache['items'])) {
      $items = trim($this->items, ',');
      $items = explode(',', $items);
      $model_id = $this->model_id;
      foreach ($items as &$value) {
        $value = $model_id > 0
               ? array($model_id, $value)
               : explode(':', $value);
      }
      $this->cache['items'] = $items;
    }
    $items = $this->cache['items'];
    $page = $page < 1 ? 1 : $page;
    $page = $page - 1;
    $this->offset = $page * $limit;
    $this->limit = $limit;
    $items = array_slice($items, $this->offset, $this->limit);
    foreach ($items as &$item) {
      if (intval($item[1]) < 1) continue;
      $item = Item::getInstance($item[0], $item[1]);
    }
    $req = S('req');
    if ($this->offset < 1 && $req->isFront()) {
      S('dbo')->insert(self::TABLE_HIT,
                       array('search_id' => $this->id,
                             'visit_id' => $req->getId()),
                       array('IGNORE'));
    }
    return $items;
  }

  public function getFoundRows() {
    return (int) $this->found_rows;
  }

  public function getMetas() {
    if (empty($this->metas)) return array();
    return unserialize($this->metas);
  }

  public static function factory($opts, $callback=null) {
    if (is_numeric($opts)) {
      return Search::getInstance((int) $opts);
    }

    foreach (array('limit', 'offset') as $key) {
      unset($opts[$key]);
    }
    $opts['callback'] = join(':', $callback);
    $opts['model_id'] = (int) $opts['model_id'];
    $opts['query'] = String::clean($opts['query']);

    $crc = Hash::crc($opts);

    $id = (int) Search::id(array('crc' => $crc));
    if ($id >= 1) {
      return Search::getInstance($id);
    }

    $row = array('callback' => $opts['callback'],
                 'crc' => $crc,
                 'latitude' => $opts['latitude'],
                 'longitude' => $opts['longitude'],
                 'model_id' => $opts['model_id'],
                 'opts' => serialize($opts),
                 'radius' => $opts['radius'],
                 'query' => $opts['query']);
    $id = (int) S('dbo')->insert(T('search'), $row);
    $search = Search::getInstance($id);
    $search->refresh(true);
    return $search;
  }

  public static function invalidate($item) {
    $model_id = $item->getModelId();
    $record_id = $item->getId();
    $str = ','.$model_id.':'.$record_id.',';
    S('dbo')->query('UPDATE '.T('search')
                    . ' SET found_rows=found_rows-1,'
                    .     ' status=0,'
                    .     ' items=REPLACE(items, "'.$str.'", ",")'
                    .' WHERE items LIKE "%'.$str.'%"');
    S('dbo')->query('UPDATE '.T('search')
                    . ' SET found_rows=found_rows-1,'
                    .     ' status=0,'
                    .     ' items=REPLACE(items, ",'.$record_id.',", ",")'
                    .' WHERE items LIKE "%,'.$record_id.',%"'
                    .  ' AND model_id='.$model_id);
  }

}
