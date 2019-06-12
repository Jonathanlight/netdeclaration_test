<?php

class Finder
{
  public  $actions = array();
  public  $branch = null;
  private $collection = null;
  public  $cols = array();
  public  $filters = array();
  public  $extra_filters = array();
  public  $has_checkbox = false;
  public  $has_user = false;
  public  $height = 580;
  public  $include = null;
  public  $limit = null;
  public  $metas = null;
  public  $model = null;
  public  $opts = null;
  public  $order = null;
  public  $order_reverse = false;
  public  $orders = null;
  public  $overlay = null;
  private $params = null;
  private $resetted = false;
  private $session_key = null;

  public function __construct($params) {

    $req = S('req');
    //$req->debug();

    $this->model = $params['model'] ?: MODEL;
    $this->branch = (array) $params['branch'];
    unset($this->branch[$this->model.'_id']);

    $this->height -= count($this->branch) * 68;

    $this->resetted = $params['reset'] == 1;
    $this->limit = $params['limit'];

    $session = $req->getSession();
    $this->session_key = $this->branch;
    ksort($this->session_key);
    $this->session_key = $this->model.'-finder-'.http_build_query($this->session_key);
    $this->session_key = rtrim($this->session_key, '-');

    if ($this->isResetted()) {
      $params = array();
      $session->setAttribute($this->session_key, $params);
    }
    elseif ($params['submit'] == 1) {
      $session->setAttribute($this->session_key, $params);
    }
    else {
      $params = $session->getAttribute($this->session_key);
      if (empty($params)) {
        $this->resetted = true;
      }
    }

    $this->params = $params;

    $this->loadXml();

    $this->opts = $this->getCollectionOpts();

    $this->adapt();

    if ($this->limit != -1 && $this->isResetted() && !S('admin')->hasFlag(Admin::FLAG_AUTOLIST)) {
      $this->collection = null;
    }
    else {
      $this->collection = Item::collect($this->model, $this->opts);
      //      $this->collection->trace();
    }

  }

  public function isResetted() {
    return $this->resetted === true;
  }

  public function onFind() {
    $class = Item::getInstance($this->model);
    $class->onCollect($this);
    if ($this->collection) {
      $class->onFind($this);
    }
    return $this;
  }

  public function getCollection() {
    return $this->collection;
  }

  private function adapt() {
    $invalid_keys = array();
    foreach ($this->filters as $key => &$filter) {
      if (isset($this->branch[$key]) && $this->branch[$key] >= 1) {
        $filter['type'] = 'hidden';
        $filter['value'] = $this->branch[$key];
      }
      elseif (in_array($filter['type'], array('checkbox', 'radio', 'select')) &&
              empty($filter['options'])) {
        $invalid_keys[] = $key;
      }
    }
    foreach ($invalid_keys as $key) unset($this->filters[$key]);
    $relations = (array) M($this->model, 'belongs_to');
    if (count($this->branch) < 1) return ;
    foreach ($relations as $model => $relation) {
      $key = $relation['foreign_key'];
      if (isset($this->branch[$key]) && $this->branch[$key] >= 1) {
        if (empty($this->params['filters'][$key])) {
          $this->opts['filters'][T($this->model).'.'.$key] = $this->branch[$key];
        }
        if (isset($this->cols[$model.'_name'])) {
          unset($this->cols[$model.'_name']);
        }
      }
    }
    if (Model::hasOwner($this->model)) {
      $branch_keys = array();
      foreach ($this->branch as $key => $value) {
        if ($value < 1) continue ;
        $branch_keys[] = $key;
      }
      $model_key = $branch_keys[0];
      list ($model, ) = explode('_', $model_key);
      if ($this->branch[$model_key] >= 1) {
        $this->opts['filters']['model_id'] = Model::id($model);
        $this->opts['filters']['record_id'] = $this->branch[$model_key];
      }
    }
  }

  private function getCollectionOpts() {
    $opts = array();

    $filters = array();

    if ($this->limit != -1) {
      if (strlen($this->params['limit']) >= 1) {
        $opts['limit'] = (int) $this->params['limit'];
      }
      else {
        $opts['limit'] = 50;
      }
      if (strlen($this->params['offset']) >= 1) {
        $opts['offset'] = (int) $this->params['offset'];
      }
    }
    if ($this->include == 'visit') {
      $opts['tables'] = array(Visit::TABLE => 'v');
      $opts['cols'] = array('v.medium', 'v.source', 'v.term', 'v.campaign');
      $filters[] = 'visit_id=v.id';
    }
    else {
      $opts['include'] = strlen($this->include) >= 1 ? String::asSet($this->include) : null;
    }
    $opts['metas'] = String::asSet($this->metas);
    if (isset($this->cols['created_at']) && !Model::hasField($this->model, 'created_at')) {
      $opts['metas'][] = 'created_at';
    }
    if (isset($this->cols['updated_at']) && !Model::hasField($this->model, 'updated_at')) {
      $opts['metas'][] = 'updated_at';
    }

    $order = strlen($this->params['order']) >= 1 ? $this->params['order'] : $this->order;
    $this->order = $order;
    $this->order_reverse = (bool) $this->params['order_reverse'];
    $opts['order'] = array();
    if (strlen($order) >= 1) {
      $chunks = (array) explode(',', $order);
      foreach ($chunks as $chunk) {
        $chunk = trim($chunk);
        list ($field, $direction) = explode(' ', $chunk);
        $direction = trim(strtoupper($direction));
        $direction = $direction === 'DESC' ? $direction : 'ASC';
        if ($this->order_reverse == true) {
          $direction = $direction == 'ASC' ? 'DESC' : 'ASC';
        }
        $opts['order'][$field] = $direction;
      }
    }

    $metas = array('created_at', 'updated_at');
    foreach ($metas as $meta) {
      if (strpos($this->order, $meta) && !in_array($meta, $opts['metas'])) {
        $opts['metas'][] = $meta;
      }
    }

    $opts['filters'] = $this->getCollectionFilters($filters);

    return $opts;

  }

  /*
   Les différentes filters de cette classe :
   - $filters : filtres pour la collection
   - $this->params['filters'] : filtres transmis dans la requete
   - $this->filters : filtres pour construire l'UI (filtres XML)
  */

  private function getCollectionFilters($filters) {

    $values = array();

    $dbo = S('dbo');
    $this->params['filters'] = (array) $this->params['filters'];

    foreach ($this->params['filters'] as $name => $value) {

      $this->filters[$name]['value'] = $value;

      if (!(is_array($value) || strlen($value) >= 1)) continue ;      
      if (substr($name, 0, 4) === '|%%|' && !is_array($value) && strpos($value, ' ') !== false) {
        $value = explode(' ', $value);
      }
      if (!is_array($value)) {
        if ($value[0] == '%' && $name[0] != '|') {
          $name = '|%%|'.$name;
          $value = trim($value, '%');
        }
        elseif (substr($value, -1) == '%' && $name[0] != '|') {
          $name = '|%|'.$name;
          $value = rtrim($value, '%');
        }
      }
      $casts = (array) M($this->model, 'casts');
      if ($casts[$name] === 'bits' && $name[0] != '|') {
        if ($this->filters[$name]['type'] == 'hbits') {
          $name = '|hbits|'.$name;
        }
        else {
          $name = '|&|'.$name;
        }
      }
      $key = $name;
      $filters[$key] = $value;
      $values[$name] = $value;
    }

    $has_many = (array) M($this->model, 'has_many');
    foreach ($has_many as $name => $relation) {
      $key = $relation['foreign_key'];
      if (!isset($this->params['filters'][$key])) continue ;
      if (!is_array($this->params['filters'][$key])) continue ;
      if (count($this->params['filters'][$key]) < 1) continue ;
      $through = $relation['through'];
      $col = empty($through) ? 'id' : $this->model.'_id';
      $set = $dbo->asSet('SELECT '.$col
                         .' FROM '.$through
                         .' WHERE '.$key.' IN ('.join(',', $this->params['filters'][$key]).')');
      unset($filters[$key]);
      $filters['|=|id'] = $set;
      unset($filters['id']);
    }

    $this->extra_filters = (array) $this->params['extra_filters'];

    if ($this->model == 'conversion') {
      $h = array('source' => Tracker::STR_SOURCE,
                 'term' => Tracker::STR_TERM,
                 'campaign' => Tracker::STR_CAMPAIGN);
      foreach ($filters as $key => $value) {
        if ($h[$key] === null || empty($value)) continue ;
        $value = Tracker::str2id($value, $h[$key], false);
        $filters[$key] = $value < 1 ? -1 : $value;
      }
      if (!empty($filters['ip'])) {
        $filters['ip'] = Net::ip2num($filters['ip']);
      }
    }

    if (!empty($this->extra_filters['user_value'])) {
      $field = $this->extra_filters['user_field'];
      $value = $this->extra_filters['user_value'];
      if ($field == 'id' && strpos($value, ',') >= 1) {
        $value = str_replace(' ', '', $value);
        $value = explode(',', $value);
      }
      elseif ($field == 'email' || $field == 'name') {
        $set = $dbo->asSet('SELECT id'
                           .' FROM '.T('user')
                           .' WHERE '.$field.' LIKE "'.$value.'%"');
        $value = $set;
      }
      elseif ($field == 'last_name') {
        $profile = P('profile.user');
        $set = $dbo->asSet('SELECT user_id'
                           .' FROM '.T($profile)
                           .' WHERE last_name LIKE "'.$value.'%"');
        $value = $set;
      }
      if (is_array($value) && count($value) == 1) $value = $value[0];
      $filters[T($this->model).'.user_id'] = $value;
    }

    if (false) {
      S('log')->debug($filters, '$filters');
      S('log')->debug($this->params, '$this->params');
      S('log')->debug($this->filters, '$this->filters');
    }
    // S('log')->debug($values);

    foreach ($this->filters as $name => &$filter) {
      if (isset($values[$name])) {
        $filter['value'] = $values[$name];
      }
    }

    return $filters;

  }

  public function getItemHash($item, $cols) {
    $hash = array();
    $hash['_color'] = 'green';
    if ($item->hasAttribute('status') && $item->status < 1) {
      $hash['_color'] = 'red';
    }
    foreach ($cols as $col) {
      $key = $col['name'];
      $value = $item->hasAttribute($key) ? $item->getAttribute($key) : ' - ';
      if (isset($col['model'])) {
        if ($col['model'] == 'heading') {
          try {
            if ($item->heading_id < 1) {
              $value = '-';
            }
            else {
              $heading = Heading::getInstance($item->heading_id);
              $value = $heading->code.' <small>'.$heading->app.'</small>';
            }
          }
          catch (Exception $e) {
            S('log')->error($e, __METHOD__);
            $value = '** heading '.$item->heading_id.' **';
          }
        }
        else {
          $value = Item::name($col['model'], $value);
        }
      }
      elseif (substr($key, -3) == '_at') {
        $value = H::datetime($value);
        list ($day, $hour) = explode(' ', $value);
        $value = $day.' <small>'.$hour.'</small>';
      }
      elseif (substr($key, -3) == '_on') {
        $value = H::date($value);
      }
      elseif ($key == 'user') {
        if ($item->user_id >= 1) {
          try {
            $user = User::getInstance($item->user_id, array('ignore' => true));
            $value = '<span title="'.$user.' ('.$user->id.')">'.$user->email.'</span>';
          }
          catch (Exception $e) { $value = '** user_id '.$item->user_id.' **'; }
        }
        else {
          $value = '* Anonymous *';
        }
      }
      elseif ($key == 'item') {
        try {
          $i = $item->getItem();
          $value = $i->getName();
        }
        catch (Exception $e) {
          if (Model::exists($item->model_id)) {
            $value = '** '.N($item->model_id).' ('.$item->record_id.') **';
          }
          else {
            $value = '** '.$item->model_id.' ('.$item->record_id.') **';
          }
        }
      }
      elseif ($key == 'extension_id') {
        $value = Extension::name($value);
      }
      elseif ($key == 'status') {
        $value = $item::$statuses[$value];
      }
      elseif ($key == 'type') {
        $value = $item::$types[$value];
      }
/*      elseif ($key == 'heading_id') {
        try {
          if ($item->heading_id < 1) {
            $value = '-';
          }
          else {
            $heading = Heading::getInstance($item->heading_id);
            $value = $heading->code.' ('.$heading->app.')';
          }
        }
        catch (Exception $e) {
          S('log')->error($e, __METHOD__);
          $value = '** heading '.$item->heading_id.' **';
        }
      }*/
      /*else*/if ($key == 'model_id') {
        $value = ucfirst(Model::label($value));
      }
      elseif ($key == 'locale') {
        $value = '<img src="/'.PIX_PATH.'/lang/'.I18N::lang($value).'.png" />';
      }
      elseif ($key == 'locales') {
        $str = '';
        foreach (I18N::$locales as $locale => $code) {
          //          if ($value > $locale) break ;
          if ($value & $locale) $str .= ', '.$code;
        }
        $value = ltrim($str, ', ');
      }
      $hash[$key] = $value;
    }
    try {
      if (method_exists($item, 'asFinderHash')) {
        $hash = $item->asFinderHash($hash);
      }
      return $hash;
    }
    catch (Exception $e) {
      S('log')->error($e.' ('.$item->getId().')', __METHOD__);
      return $hash;
    }
  }

  private function loadXml() {

    $doc = new DOMDocument();
    $doc->preserveWhiteSpace = false;

    $extension = M($this->model, 'extension');
    $file = LIB_PATH.'/'.$extension.'/xml/'.$this->model.'.finder.xml';
    if (!file_exists($file)) {
      $file = LIB_PATH.'/'.CORE.'/xml/item/finder.xml';
    }

    if ($doc->load($file) === false) {
      throw new Exception();
    }

    $finders = $doc->documentElement->getElementsByTagName('finder');
    $finder = $finders->item(0);

    $attributes = self::node2hash($finder);
    foreach ($attributes as $key => $value) {
      $this->{$key} = $value;
    }

    $date_suffixes = array('_at', '_on');

    $labels = array('name' => 'nom',
                    'id' => 'ID',
                    'status' => 'statut');


    $relation = M($this->model, 'belongs_to');

    $foreign_keys = array();
    if (!empty($relation)) {
      foreach ($relation as $mdl => $hash) {
        $foreign_keys[$hash['foreign_key']] = $mdl;
      }
    }

    foreach ($finder->childNodes as $node) {
      if ($node->nodeName == 'filters') {
        foreach ($node->childNodes as $child) {
          $type = $child->getAttribute('type');
          $name = $child->getAttribute('name');
          if (empty($type)) {
            if ($name == 'flags') {
              if ($this->model == 'abuse') {
                $child->setAttribute('type', 'hbits');
              }
              else {
                $child->setAttribute('type', 'checkbox');
              }
              $child->setAttribute('name', 'flags');
              $child->setAttribute('options', ucfirst($this->model).'::$flags');
            }
            elseif ($name == 'status') {
              $child->setAttribute('type', 'checkbox');
              $child->setAttribute('options', ucfirst($this->model).'::$statuses');
            }
            elseif ($name == 'locale') {
              $child->setAttribute('type', 'checkbox');
              $child->setAttribute('options', "I18N::locales()");
            }
            elseif ($name == 'type') {
              $child->setAttribute('type', 'select');
              $child->setAttribute('options', ucfirst($this->model).'::$types');
            }
            elseif ($name == 'heading_id') {
              $child->setAttribute('type', 'select');
              $child->setAttribute('options', "Model::headings('".$this->model."')");
              $child->setAttribute('label', 'rubrique');
            }
            elseif (substr($name, -3) == '_id' && Model::exists(substr($name, 0, -3))) {
              $child->setAttribute('type', 'select');
//              $mdl = $foreign_keys[$name];
              $child->setAttribute('options', "Model::asHash('".substr($name, 0, -3)."')");
              if (!$child->hasAttribute('label')) {
                $child->setAttribute('label', substr($name, 0, -3));
              }
            }
            elseif ($name == 'app') {
              $child->setAttribute('type', 'select');
              $child->setAttribute('options', 'App::names(true)');
              $child->setAttribute('label', 'App');
            }
            elseif ($child->hasAttribute('options')) {
              $child->setAttribute('type', 'select');
            }
            else {
              $type = 'text';
              $child->setAttribute('type', $type);
            }
          }
          if ($type === 'user') {
            $this->has_user = true;
            continue;
          }
          elseif ($type === 'tag') {
            $child->setAttribute('type', 'text');
            $child->setAttribute('name', '|TAG|');
            $child->setAttribute('label', 'tag');
          }
          elseif ($type === 'interest') {
            $child->setAttribute('type', 'select');
            $child->setAttribute('name', '|INTEREST|');
            $child->setAttribute('label', 'thèmes');
            $child->setAttribute('options', "Model::asHash('interest')");
          }
          elseif (isset($foreign_keys[$name])) {
            $child->setAttribute('type', 'select');
            $mdl = $foreign_keys[$name];
            $child->setAttribute('options', "Model::asHash('".$mdl."')");
            if (!$child->hasAttribute('label')) {
              $child->setAttribute('label', $mdl);
            }
          }
          $name = $child->getAttribute('name');
          if (!$child->hasAttribute('label')) {
            $label = $labels[$name] ? $labels[$name] : $name;
            $child->setAttribute('label', $label);
          }
          /*          if ($name[0] != '|' &&
              !in_array($name, array('id', 'state', 'status', 'type')) &&
              substr($name, -3) != '_id' && substr($name, -5) != '_type') {
            //            $name = '|%|'.$name;
            $child->setAttribute('name', $name);
            }*/
          $this->filters[$name] = self::node2hash($child);
          if (isset($this->params['filters'])) unset($this->filters[$name]['value']);
        }
      }
      elseif ($node->nodeName == 'cols') {
        foreach ($node->childNodes as $child) {
          $name = $child->getAttribute('name');
          if (in_array(substr($name, -3), $date_suffixes)) {
            $child->setAttribute('format', 'date');
            $child->setAttribute('width', '120px');
            if (!$child->hasAttribute('label')) {
              $child->setAttribute('label', 'date');
            }
          }
          elseif (substr($name, -3) == '_id') {
            $model = substr($name, 0, -3);
            if (Model::exists($model) && !$child->hasAttribute('label')) {
              $child->setAttribute('label', N($model));
              $child->setAttribute('model', $model);
              $child->setAttribute('width', '150px');
            }
          }
          if (!$child->hasAttribute('label')) {
            if (isset(self::$labels[$name])) {
              $child->setAttribute('label', self::$labels[$name]);
            }
            else {
              $child->setAttribute('label', $name);
            }
          }
          if (!$child->hasAttribute('width') && isset(self::$widths[$name])) {
            $child->setAttribute('width', self::$widths[$name].'px');
          }
          $this->cols[$name] = self::node2hash($child);
        }
      }
      elseif ($node->nodeName == 'actions') {
        foreach ($node->childNodes as $child) {
          $hash = self::node2hash($child);
          $hash['global'] = $hash['global'] == true || $hash['name'] == 'export';
          if ($hash['global'] === true) {
            if ($hash['name'] == 'download') {
              $hash['icon'] = $hash['name'].'.png';
              $hash['confirm'] = 'êtes vous sûr de vouloir procéder à l’export ?';

            }
          }
          else {
            $this->has_checkbox = true;
          }
          $this->actions[$hash['name']] = $hash;
        }
      }
      elseif ($node->nodeName == 'orders') {
        foreach ($node->childNodes as $child) {
          $hash = self::node2hash($child);
          $this->orders[$hash['cols']] = $hash;
        }
      }
      elseif ($node->nodeName == 'overlay') {
        $this->overlay = $node->nodeValue;
      }
    }
    //S('log')->debug($this->cols);
    //S('log')->debug($this->filters);
  }

  public static $widths = array('phone' => 100,
                                'app' => 160,
                                'country_id' => 50,
                                'locale' => 30,
                                'locales' => 60,
                                'model_id' => 140,
                                'extension_id' => 100,
                                'heading_id' => 150,
                                'code' => 230,
                                'status' => 190,
                                'type' => 150,
                                'position' => 90);

  public static $labels = array('phone' => 'tel',
                                'country_id' => 'pays',
                                'locale' => 'L',
                                'locales' => 'Trad',
                                'heading_id' => 'rubrique',
                                'model_id' => 'modèle',
                                'extension_id' => 'extension',
                                'name' => 'nom',
                                'title' => 'titre');

  public static function node2hash($node) {
    $map = $node->attributes;
    $hash = array();
    $convert = array('options', 'value');
    foreach ($map as $index => $attributes) {
      $hash[$attributes->name] = $attributes->value;
      if (in_array($attributes->name, $convert)) {
        $hash[$attributes->name] = self::evalString($hash[$attributes->name]);
      }
    }
    return $hash;
  }

  public static function evalString($str) {
    eval('$ret = '.$str.';');
    return $ret;
  }

  public function __toString() {
    try {
      $template = '//finder';
      $args = array();
      $args['finder'] = $this;
      $args['collection'] = $this->getCollection();
      $args['page_count'] = $args['collection'] ? $args['collection']->getPageCount() : 0;
      $html = Template::render($template, $args);
      return $html;
    }
    catch (Exception $e) {
      S('req')->getSession()->removeAttribute($this->session_key);
      S('log')->error($e, __METHOD__);
    }
    return 'error';
  }

  public function debug() {
    S('log')->debug($this->opts);
  }

  public static function getInstance($params=null) {
    if ($params === null) {
      $params = S('req')->getAttributes();
    }
    return new Finder($params);
  }

}

