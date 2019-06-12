<?php

class Item 
{
  const TABLE_DATA = 'sys_item_data';
  const TABLE_LOG = 'sys_item_log';
  const TABLE_NOTE = 'sys_item_note';
  const TABLE_PING = 'sys_ping';
  const TABLE_PROPERTY = 'sys_item_property';
  const TABLE_REVISION = 'sys_item_revision';
  const TABLE_SEO = 'sys_item_seo';
  const TABLE_TAG = 'sys_item_tag';

  const STATUS_OFFLINE = 0;
  const STATUS_ONLINE = 1;

  const LOG_TYPE_VIEW = 1;
  const LOG_TYPE_CLICK = 2;
  const LOG_TYPE_DOWNLOAD = 4;

  const DATA_ATTRIBUTES = 1;
  const DATA_TWEET_ID = 101;
  const DATA_TUMBLR_ID = 102;

  const DATA_CUSTOM1 = 241;
  const DATA_CUSTOM2 = 242;
  const DATA_CUSTOM3 = 243;
 
  public static function log($item=null, $type=null) {
    if (LOAD_LEVEL > 0) return ;
    $type = $type > 1 ? $type : self::LOG_TYPE_VIEW;
    if (is_null($item)) {
       $model_id = $record_id = 0;
    }
    else {
      if ($item instanceof ActiveRecord) { 
        $model_id = $item->getModelId();
        $record_id = $item->getId();
      }
      elseif (is_array($item)) {
        $model_id = $item['model_id'];
        $record_id = $item['record_id'];
      }
      if ($model_id < 1 || $record_id < 1) {
        S('log')->error('invalid values', __METHOD__);
        return ;
      }
    }
    $type = $type >= 1 ? $type : 1;
    $dbo = S('dbo');
    $ret = $dbo->exec('UPDATE IGNORE '.self::TABLE_LOG
                      .' SET counter=counter+1'
                      .' WHERE model_id='.$model_id
                      .  ' AND record_id='.$record_id
                      .  ' AND type='.$type
                      .  ' AND created_on=CURDATE()'); 
    if ($ret < 1) {
      $dbo->insert(self::TABLE_LOG,
                   array('model_id' => $model_id,
                         'record_id' => $record_id,
                         'counter' => 1,
                         'type' => $type,
                         'created_on' => Date::now()),
                   array('IGNORE'));
    }
  }
 
  public static function getPropertiesById($item, $locale=null) {
    $where = $locale ? ' AND locale='.intval($locale) : '';
    $rs = $item->dbo->query('SELECT *'
                            .' FROM '.Item::TABLE_PROPERTY
                            .' WHERE model_id='.$item->getModelId()
                            .  ' AND record_id='.$item->getId()
                            .$where);
    $properties = array();
    foreach ($rs as $hash) {
      $properties[$hash['locale']][$hash['property_id']] = $hash['value'];
    }
    return $properties;
  }

  public static function getInstanceByKey($item_key, array $opts=array()) {
    if (strpos($item_key, '-') < 1) {
      S('log')->trace('invalid key ['.$item_key.']', __METHOD__);
      throw new ClassRecordException('invalid key');
    }
    list ($model_id, $record_id, $hash) = explode('-', $item_key);
    if ($model_id < 1 || $record_id < 1 || 
        $hash != String::crypt($model_id . $record_id)) {
      S('log')->trace('invalid key ['.$item_key.']', __METHOD__);
      throw new ClassRecordException('invalid key');
    }
    $model = N($model_id);
    return self::factory($model, $record_id, $opts);
  }
  
  public static function getInstance($model, $args=true, array $opts=array()) {
    if (is_numeric($model)) { 
      $model = N($model);
      if ($model === null) {
        S('log')->error('invalid model_id ('.$model.') ['.gettype($model).']',
                        __METHOD__);
        throw new ClassRecordException('invalid model');
      }
    }
    else {
      $model = strtolower($model);
    }
    return self::factory($model, $args, $opts);
  }

  public static function collect($model, $opts=null) {
    //return new Collection($model, $opts);
    return Collection::getInstance($model, $opts);
  }

  public static function id($model, $elt) {
    return (int) self::exists($model, $elt);
  }



  public static $names = array();
  public static function name($model, $id) {
    if ($id < 1) return '-';
    $model_id = Model::id($model);
    $id = (int) $id;
    $key = $model_id.'-'.$id;
    $name = self::$names[$key];
    if ($name) {
      return $name;
    }
    $name = S('dbo')->fetchValue('SELECT name'
                                 .' FROM '.T($model)
                                 .' WHERE id='.$id
                                 .' LIMIT 1');
    if ($name != false && $name != null) {
      self::$names[$key] = $name;
      if (count(self::$names) >= 200) {
        S('log')->warn('item names cache is growing too much ['.$model.']',
                       __METHOD__);
      }
    }
    return $name;
  }

  public static function exists($model, $elt) {
    if (is_array($elt)) {
      $bindings = array();
      $where = '1';
      foreach ($elt as $key => $value) {
        $where .= ' AND '.$key.'=:'.$key.':';
        $bindings[':'.$key.':'] = $value;
      }
    }
    elseif (preg_match('/^\d*$/', $elt) == 1) {
      $where = 'id='.intval($elt);
      $bindings = null;
    }
    else {
      $where = 'code=:code:';
      $bindings = array(':code:' => $elt);
    }
    $id = S('dbo')->fetchValue('SELECT id'
                               .' FROM '.T($model)
                               .' WHERE '.$where
                               .' LIMIT 1',
                               $bindings);
    return $id > 0 ? intval($id) : false;
  }

  public static function factory($model, $args=true, array $options=array()) { 
    if (func_num_args() < 1) {
      S('log')->error('arguments required', __METHOD__);
      throw new ClassRecordException('arguments required');
    }
    
    if (empty($args)) {
      S('log')->error('invalid argument ['.$model.']', __METHOD__);                  
      S('log')->debug($args, __METHOD__);
      throw new ClassRecordException('invalid argument');
    }

    if (empty($model)) {
      throw new ClassRecordException('empty class');
    }
    
    $classname = ucfirst($model);
    $instance = new $classname;
    $instance->_model = $model;
    $params = Model::parameters($model);
    if ($params === null) {
      S('log')->error('model not found ['.$model.']', __METHOD__);
      throw new ClassRecordException('model not found');
    }
    
    $instance->_model_id = $params['id'];
    $instance->_table = $params['table'];
    
    foreach (array('belongs_to', 'has_one', 'has_many') as $relation) {
      $instance->{'_'.$relation} = (array) $params[$relation];
    }
    
    $instance->_foreign_key = isset($params['foreign_key'])
                            ? $params['foreign_key']
                            : $model.'_id';
    
    $instance->_opts = array('include' => array(),
                             'exclude' => array(),
                             'properties' => array(),
                             'metas' => array());
    
    if (count($options) >= 1) {
      if (isset($options['ignore'])) { 
        $instance->_verbose = ! (bool) $options['ignore'];        
      }
      $instance->_opts['include'] = (array) $options['include'];
      if (Model::hasProperties($model) && isset($options['properties'])) {
        $instance->_opts['properties'] = $options['properties'];
      }
      $instance->_opts['metas'] = $options['metas'] === true
                                ? array('*')
                                : (array) $options['metas']; 
      $instance->_locale = (int) $options['locale'];
    }
    if (!is_array($args) && !is_bool($args)) {
      if (is_int($args) || preg_match('/^\d*$/', $args) == 1) {
        $args = (int) $args;
        if ($args < 1) {
          S('log')->error('invalid numeric argument ('.$args.') ['.$model.']',
                          __METHOD__);
          throw new ClassRecordException('invalid numeric argument');
        }
        $args = array('id' => $args);
      }
      elseif (is_string($args) && !empty($args)) {
        $args = array('code' => $args);
      }
    }
    if (is_array($args) && count($args) >= 1) {
      $instance->setArguments($args);
      $instance->instantiate();
    }
    if (is_object($options['nucleus'])) {
      $instance->_setNucleus($options['nucleus']);
    }
    return $instance;
  }

  public static function asRelationRows($item, $models, $table) {
    $dbo = S('dbo');
    $models = String::asSet($models);
    $rels = array();
    $sortable = false;
    $order = '';
    $rel_table = $dbo->getTable($table);
    $rel_fields = $rel_table->getFields(); 
    $cleanable = !in_array('id', $rel_fields);
    if (in_array('position', $rel_fields)) {
      $sortable = true;
      $order = ' ORDER BY position';
    }
    $mixed = false;
    if (substr($table, -5) != '_item') {
      $model = $models[0];
      $key = T($model) == $table ? 'id' : $model.'_id';
      $rows = $dbo->query('SELECT *'
			  .' FROM '.$table
			  .' WHERE '.$item->getModel().'_id='.$item->getId()
			  .$order);
      foreach ($rows as $row) {
        $rels[] = array('item' => array($model, $row[$key]),
			'row' => $row);
      }
    }
    else {
      $mixed = true;
      $rows = $dbo->query('SELECT *'
			  .' FROM '.$table
			  .' WHERE '.$item->getModel().'_id='.$item->getId()
			  .$order);
      foreach ($rows as $row) {
        $rels[] = array('item' => array($row['model_id'], $row['record_id']),
			'row' => $row);
      }
    }
    foreach ($rels as $index => $rel) {
      try {
	//	S('log')->debug($rel);
	$o = Item::getInstance($rel['item'][0], $rel['item'][1],
			       array('ignore' => true));
	$rels[$index]['item'] = $o; 
      }
      catch (Exception $e) {
	S('log')->error('['.$item->getModel().'] '.
			'('.$item->getId().') : '.
			'invalid relation '.
			'['.N($rel['item'][0]).'] '.
			'('.$rel['item'][1].') | '.
			$table,
			__METHOD__);
	if ($cleanable) {
	  if ($mixed) {
	    $where = 'model_id='.I($rel['item'][0])
	      .' AND record_id='.$rel['item'][1];
	  }
	  else {
	    $field  = N($rel['item'][0]);
	    $field .= '_id';
	    $where = $field.'='.$rel['item'][1];
	  }
	  $dbo->exec('DELETE FROM '.$table
		     .    ' WHERE '.$item->getModel().'_id='.$item->getId()
		     .      ' AND '.$where
		     .' LIMIT 1');
	  $dbo->debug();
	}
	$rel['item'] = null;
      }
    }
    if (count($rels) < 1) return '';
    if (count($rels) === 1) $sortable = 1; 
    $html = '<ul class="sortable" id="att-'.$item->getKey().'">';
    $attrs = array('id' => '', 'class' => '',
                   'data' => array('model' => '', 'item' => ''));
    foreach ($rels as $rel) {
      if ($rel['item'] === null) continue ; 
      $attrs['id'] = 'xxx_'.$rel['item']->getKey();
      $attrs['data']['model'] = $rel['item']->getModel();
      $attrs['data']['item'] = $rel['item']->getKey();
      $attrs['class'] = $rel['item']->isOnline() ? null : 'offline';
      $html .= H::elt('li', null, $attrs);
      $html .= '<span class="destroy">x</span>';
      if ($sortable === true) {
        $html .= '<span class="handle" draggable="true">=</span> ';
      }
      $str  = $mixed ? ucfirst($rel['item']->getModel()).' : ' : '';
      $str .= $item->asRelationRow($rel['item'], $rel['row']);
      $html .= '<span class="content">'.$str.'</span>';
      $html .= '</li>';
    }
    $html .= '</ul>';
    return $html;
  }

  // http://www.hixie.ch/specs/pingback/pingback
  // http://wordpress.org/development/
  public static function ping($item) {
    $doc = new DOMDocument();
    @$doc->loadHTML($item->content);
    $nodes = $doc->getElementsByTagName('A');
    if ($nodes->length < 1) return ;
    $opts = array('http' => array('method' => 'HEAD'));
    $context = stream_context_create($opts);
    foreach ($nodes as $node) {
      $url = $node->getAttribute('href');
      if (!Valid::isUrl($url)) continue ;
      if (!($handle = @fopen($url, 'r', false, $context))) continue ;
      $metas = stream_get_meta_data($handle);
      $headers = (array) $metas['wrapper_data'];
      $ping_url = null;
      foreach ($headers as $header) {
        list ($name, $value) = explode(': ', $header);
        if ($name == 'X-Pingback') $ping_url = $value;
      }
      if (empty($ping_url)) {
        $html = stream_get_contents($handle);
        $page = new DOMDocument();
        $page->preserveWhiteSpace = false;
        @$page->loadHTML($item->content);
        $links = $page->getElementsByTagName('link');
        if ($nodes->length >= 1) {
          foreach ($nodes as $node) {
            if ($node->hasAttribute('rel') && 
                $node->hasAttribute('href') && 
                $node->getAttribute('href') == 'pingback') {
              $ping_url = $node->getAttribute('href');
            }
          }
        }
      }
      // si vide vérifier dans <HEAD> : <link rel="pingback" href="http://bob.example.net/xmlrpcserver">
      if ($ping_url === null) continue ; 
      $client = RpcClient::getInstance($ping_url);
      $client->call('pingback.ping', 
                    array('sourceURI' => H::url($item->asUrl()),
                          'targetURI' => $url));
      fclose($handle);
    }
  }

  public static function clean($models=null) {
    if (empty($models)) return ;
    $dbo = S('dbo');
    foreach (P('item_tables') as $table) {
      if (!$dbo->hasTable($table, false)) continue ;
      $column = $table === Meta::TABLE ? Meta::FIELD_MODEL : 'model_id';
      try {
        $dbo->exec('DELETE FROM '.$table
                   .    ' WHERE '.$column.' IN ('.join(',', $models).')');
      }
      catch (Exception $e) { S('log')->error($e, __METHOD__); }
    }
  }

  public static function asSourceName($source) {
/*    if (is_numeric($source)) {
      $source = S('dbo')->fetchValue('SELECT name FROM '.Tracker::TABLE_STRING
                                     .         ' WHERE id='.$source);
    } */
    if ($source[0] != '|') return $source;
    list (, $model, $id) = explode('|', $source); 
    if (!Model::exists($model)) return $source;
    try {
      $item = Item::getInstance($model, (int) $id, array('ignore' => true));
      if (method_exists($item, 'asSourceName')) {
        $name = $item->asSourcetName();
      }
      else {
        $name = $item->getName().' ('.$id.')';
      }
      return $name;
    }
    catch (Exception $e) { 
      return '** '.$model.' ('.$id.') **';
    }
  }

  public static function asSource($item) {
    $medium = self::asMedium($item);
    $id = S('dbo')->fetchValue('SELECT id'
                               .' FROM '.Tracker::TABLE_STRING
                               .' WHERE name="|affiliate|'.$item->getId().'"'
                               .  ' AND type='.Tracker::STR_SOURCE);
    if ($id < 1) {
      $row = array('name' => '|affiliate|'.$item->getId(),
                   'type' => Tracker::STR_SOURCE);
      $id = S('dbo')->insert(Tracker::TABLE_STRING, $row);
    }
    return $id;
  }

  public static function asMedium($item) {
    $medium = '';
    switch ($item->getModel()) {
      case 'affiliate':
        $medium = Tracker::MEDIUM_AFFILIATE;
        break;
      case 'campaign':
        $medium = Tracker::MEDIUM_CAMPAIGN;
        break;
      case 'user':
        $medium = Tracker::MEDIUM_USER;
        break; 
    }
    return $medium;
  }

  public static function edit($item, $opts=null) {
    $opts = (array) $opts;
    
    $tag = $opts['tag'] ?: 'a';
    $attrs = array('data' => array('item' => $item->getKey()),
                   'on' => array('click' => 'kwo.ux.onItemEdit(this)'));
    if ($opts['callback']) {
      $attrs['data']['callback'] = $opts['callback'];
    }
    else {
      if ($opts['container']) {
        $attrs['data']['container'] = $opts['container'];
      }
      $view = $opts['view'] ?: 'preview';
      $attrs['data']['view'] = $view;
    }
    $html = (isset($opts['html'])) ? $opts['html'] : $item->asView($view);
    if (empty($html)) {
      $attrs['data']['on'] = null;
      $html = '** '.c(N($item)).' ('.$item->getId().') **';
    }
    return H::elt($tag, $html, $attrs);
  }

}



//insert into sys_item_log (model_id, record_id, created_on) values (0,0,'2011-09-16') on duplicate key update counter=counter+1