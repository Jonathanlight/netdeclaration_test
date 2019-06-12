<?php

/*** definir un hook pour l'ajout d'objet
onProductCreate($product)
get_called_class
 ***/

class ActiveRecord
{
  protected $dbo = null;
  protected $log = null;

  public $_args = array();
  public $_belongs_to = array();
  public $_cache = array();
  public $_changes = array();
  public $_foreign_key = null;
  public $_has_many = array();
  public $_has_one = array();
  public $_is_destroyed = false;
  public $_is_new = false;
  public $_locale = 0;
  public $_model = null;
  public $_model_id = null;
  public $_nucleus = null;
  public $_opts = array();
  public $_parts = null;
  public $_table = null;
  public $_verbose = true;

  public function __construct() {
    $this->dbo = S('dbo');
    $this->log = S('log');
    $this->_cache['objects'] = array();
  }

  public function instantiate() {
    $this->onBeforeInstantiate();
    if ($this->getArguments() === null) return ;
    $where = '1';
    $bindings = array();
    if (count($this->_args) === 1 && key($this->_args) === 'id') {
      $where = $this->_table.'.id='.intval(current($this->_args));
      $bindings = null;
    }
    else {
      foreach ($this->getArguments() as $key => $value) {
        $col = strpos($key, '.') === false ? $this->_table.'.`'.$key.'`' : $key;
        if (is_int($value) || is_float($value)) {
          $where .= ' AND '.$col.'='.$value;
        }
        else {
          $where .= ' AND '.$col.'=:'.$key.':';
          $bindings[':'.$key.':'] = $value;
        }
      }
    }
    if ($this->_parts === null) {
      $this->_parts = $this->_getSqlParts(self);
    }
    $group = empty($this->_parts['group']) ? '' : ' GROUP BY '.$this->_parts['group'];
    if (!empty($this->_parts['where'])) {
      $where .= ' AND '.$this->_parts['where'];
    }
    $nucleus = $this->dbo->fetchObject('SELECT '.$this->_parts['cols']
                                       .' FROM '.$this->_parts['from']
                                       .' WHERE '.$where
                                       .$group
                                       .' LIMIT 1',
                                       $bindings);
    if ($nucleus === false) {
      $this->_nucleus = null;
      if ($this->_verbose === true) {
        //        S('log')->backtrace();
        $this->log->error('element not found ['.$this->getModel().'] ('.$this->getModelId().')',
                          __METHOD__);
        $this->log->debug($this->getArguments(), __METHOD__);
      }
      throw new UnknownRecordException();
    }
    $this->_setNucleus($nucleus);
    $this->onAfterInstantiate();
  }

  public function _setNucleus($obj) {
    $this->_nucleus = is_array($obj) ? (object) $obj : $obj;
    $casts = M($this->getModel(), 'casts');
    if (!is_array($casts)) return ;
    foreach ($casts as $key => $type) {
      $value = $this->_nucleus->{$key};
      if ($value === null) continue ;
      switch ($type) {
      case 'hash': $this->setNucleusValue($key, Hash::decode($value)); break;
      case 'array': $this->setNucleusValue($key, Hash::decode($value)); break;
      case 'set': $this->setNucleusValue($key, String::asSet($value)); break;
      }
    }
  }

  protected function castAttributes(&$input) {
    $hash = Hash::duplicate($input);
    $casts = M($this->getModel(), 'casts');
    if (!is_array($casts) || empty($hash)) {
      return $hash;
    }
    foreach ($casts as $key => $type) {
      if (!array_key_exists($key, $hash)) continue ;
      $value = $hash[$key];
      switch ($type) {
      case 'array': $hash[$key] = Hash::encode($value); break;
      case 'hash': $hash[$key] = Hash::encode($value); break;
      case 'set': $hash[$key] = Hash::toSet($value); break;
      case 'date':
      case 'datetime':
        if (strpos($value, '/') !== false) {
          $hash[$key] = Date::toDb($value);
        }
        elseif (empty($value)) {
          $hash[$key] = '0000-00-00';
          if ($type == 'datetime') {
            $hash[$key] .= ' 00:00:00';
          }
        }
        break;
      case 'float':
        $value = is_numeric($value) ? $value : str_replace(',', '.', $value);
        $hash[$key] = (float) $value;
        break;
      case 'bits':
        $value = is_array($value) ? array_sum($value) : (int) $value;
        $hash[$key] = $value;
        break;
      }
    }
    return $hash;
  }

  public function _getSqlParts($caller) {
    $group = '';
    $where = array();
    $from = $this->_table;
    $cols = $this->_table.'.*';

    if (is_array($this->_opts['metas']) && count($this->_opts['metas']) >= 1) {
      $cols .= ', md.'.join(', md.', $this->_opts['metas']);
      $from .= ' LEFT JOIN '.Meta::TABLE.' AS md'
                      .' ON (md.'.Meta::FIELD_MODEL.'='.$this->getModelId()
                      .' AND md.'.Meta::FIELD_RECORD.'='.$this->_table.'.id)';
    }

    if ($this->_opts['properties'] === true || count($this->_opts['properties']) >= 1) {
      $properties = M($this->getModel(), 'properties');
      $this->_opts['properties'] = $this->_opts['properties'] === true
                                 ? array_keys($properties)
                                 : $this->_opts['properties'];
      $locale = $this->_locale >= 1 ? $this->_locale : S('res')->getLocale();
      $i = 0;
      foreach ($this->_opts['properties'] as $name) {
        $i++;
        $id = $properties[$name];
        $cols .= ', p'.$i.'.value AS property_'.$name;
        $from .= ' LEFT JOIN '.Item::TABLE_PROPERTY.' AS p'.$i
                       .' ON (p'.$i.'.model_id='.$this->getModelId()
                       .' AND p'.$i.'.record_id='.$this->_table.'.id'
                       .' AND p'.$i.'.property_id='.intval($id)
                       .' AND p'.$i.'.locale IN (0, '.$locale.'))';
      }
    }

    foreach ($this->_opts['include'] as $index => $model) {
      if (!is_int($index)) {
        $relation = Model::parameters($index);
        $foreign_key = $model['foreign_key'];
        $model = $index;
      }
      else {
        $relation = Model::parameters($model);
        $foreign_key =& $relation['foreign_key'];
      }
      $table = T($model);
      //      $table = $relation['table'];
      if (isset($this->_belongs_to[$model])) {
        $from .= ' JOIN '.$table.' ON '.$table.'.id='.$this->_table.'.'.$foreign_key;
      }
      elseif (isset($this->_has_one[$model])) {
        $from .= ' JOIN '.$table.' ON '.$table.'.'.$foreign_key.'='.$this->_table.'.'.'id';
      }
      elseif (isset($this->_has_many[$model])) {
        $through = $this->_has_many[$model]['through'];
        if (strlen($through) < 1) {

          if (isset($relation['belongs_to'][$this->_model])) {
            $model_foreign_key = $relation['belongs_to'][$this->_model]['foreign_key'];
            $from .= ' JOIN '.$table.' ON '.$table.'.'.$model_foreign_key.'='.$this->_table.'.id';
          }else{            
            $from .= ' JOIN '.$table.' ON '.$table.'.id='.$this->_table.'.'.$foreign_key;
          }
        }

        else {
          $from .= ', '.$through.', '.$table;
          $where[] = $this->_table.'.id='.$through.'.'.$this->getModel().'_id AND '.$through.'.'.$model.'_id='.$table.'.id';
          if (!in_array($model, $this->_opts['exclude'])) {
            $cols .= ', '.$through.'.'.$model.'_id AS '.$model.'_id, '.$through.'.'.$this->getModel().'_id AS '.$this->getModel().'_id';
          }
        }
      }
      else {
        $from .= ' JOIN '.$table.' ON '.$table.'.id='.$this->_table.'.'.$foreign_key;
      }
      if (!in_array($model, $this->_opts['exclude'])) {
        $cols .= ', '.$relation['schema'];
      }
    }

    if (is_array($this->_opts['group']) && count($this->_opts['group']) >= 1) {
      $group = join(', ', $this->_opts['group']);
    }

    //S('log')->debug(array('from' => $from, 'cols' => $cols, 'group_by' => $group_by));

    return array('from' => $from, 'cols' => $cols, 'group' => $group, 'where' => implode(' AND ', $where));
  }

  public function setNucleusValue($key, $value) {
    $this->checkLoaded(__METHOD__);
    $this->_nucleus->{$key} = $value;
  }

  public function hook($method, $args) {
    if (!(method_exists($this, $method))) {
      return false;
    } 
    return call_user_func(array($this, $method), $args);
  }

  public function getDatas() {
    return S('dbo')->asHash('SELECT type, value'
                            .' FROM '.Item::TABLE_DATA
                            .' WHERE model_id='.$this->getModelId()
                            .  ' AND record_id='.$this->getId());
  }

  public function getData($key) {
    return S('dbo')->fetchValue('SELECT value'
                                .' FROM '.Item::TABLE_DATA
                                .' WHERE model_id='.$this->getModelId()
                                .  ' AND record_id='.$this->getId()
                                .  ' AND type='.intval($key));
  }

  public function hasData($key) {
    return S('dbo')->fetchValue('SELECT COUNT(*)'
                                .' FROM '.Item::TABLE_DATA
                                .' WHERE model_id='.$this->getModelId()
                                .  ' AND record_id='.$this->getId()
                                .  ' AND type='.intval($key)) > 0;
  }

  public function removeData($key) {
    $this->dbo->exec('DELETE FROM '.Item::TABLE_DATA
                     .' WHERE model_id='.$this->getModelId()
                     .  ' AND record_id='.$this->getId()
                     .  ' AND type='.intval($key)
                     .' LIMIT 1');
  }

  public function setData($key, $value) {
    $value = is_array($value) ? serialize($value) : $value;
    $dbo = S('dbo');
    $ret = $dbo->insert(Item::TABLE_DATA,
                        array('model_id' => $this->getModelId(),
                              'record_id' => $this->getId(),
                              'type' => $key,
                              'value' => $value),
                        array('IGNORE'));
    if ($dbo->affectedRows() < 1) {
      $filters = array('model_id' => $this->getModelId(),
                       'record_id' => $this->getId(),
                       'type' => $key);
      $dbo->update(Item::TABLE_DATA,
                   array('value' => $value),
                   array('filters' => $filters,
                         'limit' => 1));
    }
  }

  public function setDatas($hash) {
    if (!is_array($hash)) return false;
    foreach ($hash as $key => $value) {
      $this->setData($key, $value);
    }
    return true;
  }

  public function incrementMeta($key) {
    if (!$this->hasMetas()) return ;
    return Meta::increment($this, $key);
  }

  public function decrementMeta($key) {
    if (!$this->hasMetas()) return ;
    return Meta::decrement($this, $key);
  }

  public function getMetas() {
    if (!$this->hasMetas()) return array();
    $args = func_get_args();
    $this->checkLoaded(__METHOD__.'('.join(',', $args).')');
    $metas = $keys = array();
    foreach ($args as $key) {
      if ($this->hasAttribute($key)) {
        $metas[$key] = $this->getAttribute($key);
      }
      else {
        $keys[] = $key;
      }
    }
    $hash = Meta::get($this, $keys);
    foreach ($hash as $key => $value) {
      $this->setNucleusValue($key, $value);
      $metas[$key] = $value;
    }
    return $metas;
  }

  public function getMeta($key) {
    $this->checkLoaded(__METHOD__.'('.$key.')');
    if ($this->hasAttribute($key)) {
      $value = $this->getAttribute($key);
    }
    else {
      $value = Meta::get($this, $key);
      $this->setNucleusValue($key, $value);
    }
    return $value;
  }

  public function setVisit($visit) {
    $id = $visit instanceof Request ? $visit->getId() : (int) $visit;
    $this->setMeta('visit', $id);
  }

  public function setUser($user) {
    $this->checkLoaded(__METHOD__);
    $user = $user instanceof User
          ? $user
          : User::getInstance(intval($user));
    if ($this->hasAttribute('user_id')) {
      $this->setAttribute('user_id', $user->getId());
    }
    $this->setMeta('user', $user->getId());
    //    $user->setAttribute('action_count', $user->action_count + 1);
    return $this;
  }

  public function setMeta($key, $value) {
    if (!$this->hasMetas()) return ;
    $this->setMetas(array($key => $value));
  }

  public function setMetas($hash) {
    if (!$this->hasMetas()) return ;
    $this->checkLoaded(__METHOD__);
    if (isset($hash['updated_at'])) {
      $hash['updated_on'] = $hash['updated_at'];
    }
    foreach ($hash as $key => $value) {
      Meta::set($this, $key, $value);
      $this->setNucleusValue($key, $value);
    }
  }

  protected function hasMetas() {
    return Model::hasMetas($this->getModel());
  }

  /* http://en.wikipedia.org/wiki/Bit_manipulation */

  public function hasBit($bit) {
    if (!$this->hasMetas()) return false;
    $bit = is_array($bit) ? array_sum($bit) : $bit;
    //    return (intval($this->getMeta('bits')) & $bit) > 0;
    return (intval($this->getMeta('bits')) & $bit) >= $bit;
  }

  public function setBit($bit) {
    if (!$this->hasMetas()) return ;
    $bits = (int) $this->getMeta('bits');
    $bits = $bits | $bit;
    $this->setMeta('bits', $bits);
  }

  public function unsetBit($bit) {
    if (!$this->hasMetas()) return ;
    $bits = (int) $this->getMeta('bits');
    $bits = $bits & ~$bit;
    $this->setMeta('bits', $bits);
  }

  public function hasFlag($flag, $column='flags') {
    $flag = is_array($flag) ? array_sum($flag) : $flag;
    $flag = $flag instanceof ActiveRecord ? B($flag->getId()) : intval($flag);
    $flag = (int) $flag;
    return (intval($this->getAttribute($column)) & $flag) >= $flag;
  }

  public function toggleFlag($flag, $value, $column='flags') {
    $value = (bool) $value;
    if ($value === true) {
      $this->setFlag($flag);
    }
    else {
      $this->unsetFlag($flag);
    }
  }

  public function setFlag($flag, $column='flags') {
    if ($this->hasFlag($flag, $column)) return $this;
    $flag = $flag instanceof ActiveRecord ? B($flag->getId()) : intval($flag);
    $value = $this->getAttribute($column);
    $value = $value | $flag;
    $this->setAttribute($column, $value);
    return $this;
  }

  public function unsetFlag($flag, $column='flags') {
    if (!$this->hasFlag($flag, $column)) return $this;
    $flag = $flag instanceof ActiveRecord ? B($flag->getId()) : intval($flag);
    $value = $this->getAttribute($column);
    $value = $value & ~$flag;
    $this->setAttribute($column, $value);
    return $this;
  }

  public function getMask($column='flags', $decimal=false) {
    if (!$this->isItem()) return array();
    if (in_array($column, array('interests', 'locales'))) {
      $value = $this->getMeta($column);
      $decimal = true;
    }
    else {
      $value = $this->getAttribute($column);
    }
    $bits = array();
    if ($value <= 0) return $bits;
    for ($i = 0; $i <= 31; $i++) {
      $n = pow(2, $i);
      if ($n > $value) break ;
      if ($value & $n) $bits[] = $decimal ? ($i + 1) : $n;
    }
    return $bits;
  }

 /***
    qui a les notices 1 et 3
     select id from cty_user where notices=(1 + 4);
    qui a la seule notice 3
     select id from cty_user where notices=4;
    qui a la notice 3
     select id from cty_user where notices & 4 > 0;
    supprimer notice 3
     update cty_user set notices=notices-4
    ***/

  public function setMask($column, $bits, $dec=false) {
    if (is_object($bits) && $bits instanceof Collection) {
      $tmp = array();
      foreach ($bits as $item) {
        $tmp[] = B($item->getId());
      }
      $bits = $tmp;
    }
    elseif ($dec === true) {
      foreach ($bits as &$value) $value = B($value);
    }
    $value = array_sum($bits);
    if ($this->getAttribute($column) == $value) return ;
    return $this->setAttribute($column, $value);
  }

  public function getComments($opts=array()) {
    $this->checkLoaded(__METHOD__);
    $opts['include'] = 'user';
    $opts['metas'] = array('created_at');
    $opts['filters'] = (array) $opts['filters'];
    $opts['filters']['model_id'] = $this->getModelId();
    $opts['filters']['record_id'] = $this->getId();
    return new Collection('comment', $opts);
  }

  public function isA($model_id) {
    return $this->getModelId() == Model::id($model_id);
  }

  public function belongsTo($item) {
    if (!$this->isItem()) return false;
    if (!($this->hasAttribute('model_id') &&
          $this->hasAttribute('record_id'))) return false;
    return $this->model_id == $item->getModelId() &&
           $this->record_id == $item->getId();
  }

  public function isAvailable() {
    return $this->isOnline();
  }

  public function isOnline() {
    if (!$this->isItem()) return false;
    return !$this->hasAttribute('status') || $this->status >= 1;
  }

  public function setStatus($status) {
    $this->checkLoaded(__METHOD__);
    $this->commit(array('status' => (int) $status));
    return $this;
  }

  public function increment($key, $quantity=1) {
    $this->checkLoaded(__METHOD__);
    $this->setAttribute($key, ($this->getAttribute($key) + $quantity));
    return $this;
  }

  public function decrement($key, $quantity=1) {
    $this->checkLoaded(__METHOD__);
    $this->setAttribute($key, $this->getAttribute($key) - $quantity);
    return $this;
  }

  private function checkLoaded($method) {
    if ($this->isItem()) return true;
    $this->log->error('object not loaded', $this->getModel().'::'.$method);
    throw new ClassRecordException('object not loaded');
  }

  /*** pivot ***/
  public function getPrev($check_association=true) {
    if (!$this->isItem() ||
        ($this->_cache['prev'] === null && !$this->hasPrev($check_association))) return null;
    return $this->_cache['prev'];
  }

  public function getNext($check_association=true) {
    if (!$this->isItem() ||
        ($this->_cache['next'] === null && !$this->hasNext($check_association))) return null;
    return $this->_cache['next'];
  }

  public function hasPrev($check_association=true) {
    if (!$this->isItem() || $this->_cache['prev'] === false) return false;
    $field = null;
    /*if ($this->hasAttribute('parent')) {
      $field = 'parent';
    }*/
    if ($check_association && count($this->_belongs_to) >= 1) {
      $hash = current($this->_belongs_to);
      $field = $hash['foreign_key'];
    }
    $where = $this->hasAttribute('status') ? 'status>=1' : '1';
    if ($field !== null) {
      $where .= ' AND '.$field.'='.intval($this->getAttribute($field));
    }
    $order = '';
    if ($this->hasAttribute('position')) {
      $where .= ' AND id<>'.$this->getId();
      $where .= ' AND position<'.$this->position;
      $order = ' ORDER BY position DESC';
    }
    elseif ($this->hasAttribute('published_at')) {
      $where .= ' AND id<>'.$this->getId();
      $where .= ' AND published_at<=\''.$this->published_at.'\'';
      $order = ' ORDER BY published_at DESC, id DESC';
    }
 elseif ($this->hasAttribute('published_on')) {
      $where .= ' AND id<>'.$this->getId();
      $where .= ' AND published_on<=\''.$this->published_on.'\'';
      $order = ' ORDER BY published_on DESC, id DESC';
    }
    else {
      $where .= ' AND id<'.$this->getId();
      $order = ' ORDER BY id DESC';
    }
    $nucleus = $this->dbo->fetchObject('SELECT * FROM '.$this->_table
                                       .' WHERE '.$where.$order.' LIMIT 1');
    if ($nucleus === false) {
      $this->_cache['prev'] = false;
      return false;
    }
    $this->_cache['prev'] = clone $this;
    $this->_cache['prev']->_setNucleus($nucleus);
    return true;
  }

  public function hasNext($check_association=true) {
    if (!$this->isItem() || $this->_cache['next'] === false) return false;
    $field = null;
    /*if ($this->hasAttribute('parent')) {
      $field = 'parent';
    }*/
    $order = '';
    $where = $this->hasAttribute('status') ? 'status>=1' : '1';
    if ($check_association && count($this->_belongs_to) >= 1) {
      $hash = current($this->_belongs_to);
      $field = $hash['foreign_key'];
      $where .= ' AND '.$field.'='.intval($this->getAttribute($field));
    }
    if ($this->hasAttribute('position')) {
      $where .= ' AND id<>'.$this->getId();
      $where .= ' AND position>'.$this->position;
      $order = ' ORDER BY position ASC';
    }
    elseif ($this->hasAttribute('published_at')) {
      $where .= ' AND id<>'.$this->getId();
      $where .= ' AND published_at>\''.$this->published_at.'\'';
      $order = ' ORDER BY published_at ASC, id ASC';
    }
    elseif ($this->hasAttribute('published_on')) {
      $where .= ' AND id<>'.$this->getId();
      $where .= ' AND published_on>\''.$this->published_on.'\'';
      $order = ' ORDER BY published_on ASC, id ASC';
    }
    else {
      $where .= ' AND id>'.$this->getId();
      $order = ' ORDER BY id ASC';
    }
    $nucleus = $this->dbo->fetchObject('SELECT * FROM '.$this->_table
                                       .' WHERE '.$where.$order.' LIMIT 1');
    if ($nucleus === false) {
      $this->_cache['next'] = false;
      return false;
    }
    $this->_cache['next'] = clone $this;
    $this->_cache['next']->_setNucleus($nucleus);
    return true;
  }

  public function getItem($opts=array()) {
    if ($this->_cache['item'] instanceof ActiveRecord) return $this->_cache['item'];
    if (!($this->hasAttributes('model_id', 'record_id') &&
          $this->model_id >= 1 && $this->record_id >= 1)) {
      throw new ActiveRecordException('no item inside');
    }
    $opts['ignore'] = true;
    $this->_cache['item'] = Item::getInstance((int) $this->model_id,
                                              (int) $this->record_id,
                                              $opts);
    return $this->_cache['item'];
  }

  protected function getItemName($full_flag=false) {
    $ret = '';
    try {
      $item = $this->getItem();
      $ret .= $item->getName();
      if ($full_flag === true) {
        $ret .= ' ('.$item->getModel().')';
      }
    }
    catch (Exception $e) {
      if ($this->model_id >= 1) {
        $ret = '('.N($this->model_id).' ) ?';
      }
    }
    return $ret;
  }

  public function getUser() {
    if ($this->_cache['user'] instanceof ActiveRecord) return $this->_cache['user'];
    $user_id = $this->user_id >= 1 ? $this->user_id : $this->getMeta('user');
    if ($user_id < 1) {
      throw new Exception('no user');
    }
    $this->_cache['user'] = User::getInstance($user_id);
    return $this->_cache['user'];
  }

  public function getVisit() {
    $visit_id = $this->hasAttribute('visit_id')
              ? $this->getAttribute('visit_id')
              : $this->getMeta('visit');
    if ($visit_id < 1) {
      throw new Exception('no visit');
    }
    return Visit::getInstance($visit_id);
  }

  public function getThumbnail() {
    if ($this->hasAttribute('thumbnail')) return $this->thumbnail;
    if ($this->hasAttribute('image')) return $this->image;
    return null;
  }

  public function getImage() {
    if ($this->hasAttribute('image')) return $this->image;
    if ($this->hasAttribute('thumbnail')) return $this->thumbnail;
    return null;
  }

  public function getInterests() {
    return $this->isItem() ? $this->getMask('interests') : array();
  }

  public function setInterests($interests) {
    if (!is_array($interests)) return array();
    $this->checkLoaded(__METHOD__);
    $value = 0;
    foreach ($interests as $interest) {
      $value += B($interest);
    }
    $this->setMeta('interests', $value);
    //    Interest::set($this, $interests);
  }

  public function getFinderAttribute($key) {
    return $this->getAttribute($key);
  }

  public function setFinderAttribute($key, $value) {
    return $this->commit(array($key => $value));
  }

  public function hide() { }

  public function isRoot() {
    return !$this->isItem() || $this->ancestor_id < 1;
  }

  public function isDestroyed() {
    return $this->_is_destroyed;
  }

  public function isDestroyable() {
    return true;
  }

  public function destroy() {

    $this->checkLoaded(__METHOD__);

    if (!$this->isDestroyable()) {
      throw new ActiveRecordException('item can not be destroyed');
    }

    if ($this->hasBit(Meta::BIT_ETERNAL)) {
      $this->log->error('element not destroyable ['.$this->getModel().'] '.
                        '('.$this->getId().')', __METHOD__);
      throw new ActiveRecordException('élément protégé contre la suppression');
    }

    $this->onBeforeDestroy();

    $id = $this->getId();
    $uri = $this->getModelId();

    $models = array();
    if (is_array($this->_belongs_to)) {
      foreach ($this->_belongs_to as $model => $hash) {
        $models[] = Model::id($model);
        $item = $this->getOne($model);
        try {
          $item->onRelationDestroy($this);
        }
        catch (Exception $e) { $this->log->error($e, __METHOD__); }
      }
    }

    if ($this->hasAttributes('model_id', 'record_id') &&
        $this->model_id >= 1 && $this->record_id >= 1 &&
        !in_array($this->model_id, $models)) {
      try {
        $this->getItem()->onRelationDestroy($this);
      }
      catch (Exception $e) { $this->log->error($e, __METHOD__); }
    }

    foreach ($this->_has_many as $model => $hash) {
      if (strlen($hash['through']) >= 2) {
        try {
          $this->dbo->exec('DELETE FROM '.$hash['through']
                           .    ' WHERE `'.$this->_foreign_key.'`='.$id);
        }
        catch (Exception $e) { $this->log->error($e, __METHOD__); }
      }
      elseif ($hash['dependent'] === true) {
        $filters = array($this->_foreign_key => $id);
        /*        if ($hash['structure'] === 'tree') {
          $filters['ancestor_id'] = 0;
          }*/
        $opts = array('filters' => $filters);
        $collection = new Collection($model, $opts);
        foreach ($collection as $object) {
          $object->destroy();
        }
      }
    }

    $this->markAsChanged();

    $ret = $this->dbo->exec('DELETE FROM '.$this->_table
                            .    ' WHERE id='.$id
                            .    ' LIMIT 1');

    if ($ret < 1) {
      $this->log->error('failure ['.$this->getModel().' ('.$uri.')] ('.$id.')', _METHOD__);
      throw new ActiveRecordException('{'.$this->getModel().'} can not delete ('.$id.')');
    }

    $this->_is_destroyed = true;

    /*    $this->log->trace('[M='.$uri.':R='.$id.'] '
                      .strtoupper($this->getModel())
                      .' ['.$this.']', __METHOD__);*/

    foreach (P('item_tables') as $table) {
      try {
        if ($table == Meta::TABLE) {
          S('dbo')->exec('DELETE FROM '.$table
                         .    ' WHERE model='.$uri
                         .      ' AND record='.$id);
        }
        else {
          S('dbo')->exec('DELETE FROM '.$table
                         .' WHERE model_id='.$uri
                         .  ' AND record_id='.$id);
        }
      }
      catch (Exception $e) {
        S('log')->error('[M='.$uri.':R='.$id.'] '.$e->getMessage(), __METHOD__);
      }
    }

    try {
      $this->onAfterDestroy();
    }
    catch(Exception $e) { $this->log->error($e, __METHOD__); }

    try {
      $this->onAlter();
    }
    catch(Exception $e) { $this->log->error($e, __METHOD__); }

    S('app')->hook('onItemDestroy', 
                   array('item' => $this));

  }

  public function getDescription($locale=null) {
    $this->checkLoaded(__METHOD__);
    $out = '';
    if ($this->hasAttribute('description')) {
      $out = $this->description;
    }
    return $out;
  }

  public function getName($locale=null) {
    if ($this->_cache['name'] !== null) {
      return $this->_cache['name'];
    }
    if ($locale === null && $this->hasAttribute('name')) {
      $this->_cache['name'] = $this->getAttribute('name');
    }
    elseif ($this->hasAttribute('name')) {
      $this->_cache['name'] = $this->getAttribute('name');
    }
    elseif ($this->hasAttribute('title')) {
      $this->_cache['name'] = $this->getAttribute('title');
    }
    elseif ($this->hasAttribute('code')) {
      $this->_cache['name'] = $this->getAttribute('code');
    }
    else {
      $this->_cache['name'] = $this->getId();
    }
    return $this->_cache['name'];
  }

  public function getTitle($locale=null) {
    $this->checkLoaded(__METHOD__);
    return $this->hasAttribute('title') ? $this->title : $this->getName($locale);
  }

  public function setTags($tags, $locale=null) {
    $this->checkLoaded(__METHOD__);
    Tag::set($this, $tags, $locale);
    $this->markAsChanged();
  }

  public function getTags($locale=null) {
    if (!$this->isItem()) return array();
    $locale = $locale ?: $this->_locale();
    return $this->dbo->asSet('SELECT t.name'
                             .' FROM '.Item::TABLE_TAG.' AS i'
                             .' JOIN '.T('tag').' as t'
                             .  ' ON (t.id=i.tag_id)'
                             .' WHERE i.model_id='.$this->getModelId()
                             .  ' AND i.record_id='.$this->getId()
                             .  ' AND i.locale='.$locale);
  }


  public function asText($locale=null) {
    $fields = array('title', 'name', 'label',
                    'description', 'summary', 'content');
    $out = '';
    foreach ($fields as $field) {
      if (!$this->hasAttribute($field) ||
          strlen($this->getAttribute($field)) < 1) continue ;
      $out .= $this->getAttribute($field)."\n";
    }
    $tags = $this->getTags($locale);
    if (!empty($tags)) {
      $out .= join(', ', $tags);
    }
    return $out;
  }


  public function asDocument($locale) {
    $document = new Document($this, $locale);
    return $document;
  }

  public function asDocumentHash($locale) {
    $this->checkLoaded(__METHOD__);
    if (Model::hasProperties($this)) {
      $name  = $this->getProperty('title', $locale);
      $name .= $this->getProperty('name', $locale);
      $name .= $this->getProperty('label', $locale);
      $description = $this->getProperty('description', $locale);
      $content = $this->getProperty('content', $locale);
    }
    else {
      $name  = $this->title;
      $name .= $this->name;
      $name .= $this->label;
      $description = $this->description;
      $content = $this->content;
    }
    $h = array('model_id' => $this->getModelId(),
               'record_id' => $this->getId(),
               'name' => $name,
               'description' => $description,
               'content' => $content,
               'keywords' => $this->getTags($locale),
               'indexes' => array(),
               'word_count' => 0);
    return $h;
  }

  public function asExportHash() {
    return $this->getAttributes();
  }

  public function asSuggestionHash($locale) {
    $this->checkLoaded(__METHOD__);
    $locale = $locale ?: $this->getLocale();
    return array('name' => $this->getName($locale),
                 'label' => $this->getName($locale),
                 'locale' => $locale,
                 'content' => $this->asText($locale),
                 'attributes' => array('item' => $this->getKey()));
  }

  public function asIdentityHash($locale, $type=null, $options=null) {
    return array('name' => $this->getName($locale),
                 'description' => $this->getDescription($locale),
                 'image' => $this->getThumbnail());
  }

  public function asView($view) {
    if ($view == 'id') return $this->getId();
    if ($view == 'item') {
      return c(N($this)).' ('.$this->getId().')</br>'.$this->getName();
    }
    return $this->getName();
  }

  public function asSearchHash($locale) {
    $h = array();
    $h['title'] = $this->getTitle();
    if ($this->hasAttribute('description')) {
      $h['description'] = $this->description;
    }
    if ($this->hasAttribute('thumbnail', true)) {
      $h['image'] = $this->thumbnail;
    }
    elseif ($this->hasAttribute('image', true)) {
      $h['image'] = $this->image;
    }
    $h['updated_at'] = $this->getMeta('updated_at');
    $h['created_at'] = $this->getMeta('created_at');
    $h['url'] = $this->asUrl();
    return $h;
  }

  public function asHeadHash($locale) {
    $h = $this->dbo->fetchHash('SELECT title, description, keywords' //, canonical_url as url'
                                  .' FROM '.Item::TABLE_SEO
                                  .' WHERE model_id='.$this->getModelId()
                                  .  ' AND record_id='.$this->getId()
                                  .  ' AND locale IN ('.$locale.', 0)'
                                  .' ORDER BY locale DESC'
                                  .' LIMIT 1');
    return $h;
  }

  public function asRelationRow($relation, $row) {
    return $relation->getName();
  }

  public function asConversionName() {
    return $this->getModel().' ('.$this->getId().') : '.$this->getName();
  }

  public function asPickerHash() {
    return array('id' => $this->getId(),
                 'record_id' => $this->getId(),
                 'model_id' => $this->getModelId(),
                 'model' => $this->getModel(),
                 'name' => $this->getName(),
                 'key' => $this->getKey(),
                 'url' => $this->asUrl());
  }

  public function asPickerRow() {
    $out = '';
    if (!empty($this->code)) {
      $out = $this->code.' : ';
    }
    $out .= $this->getName();
    return $out;
  }

  public function isIndexable() {
    return $this->isItem() && $this->isOnline();
  }

  public function index() {
    if (!Extension::exists('search') || !$this->isItem()) return ;
    Engine::getIndexer()->index($this);
    //Engine::index($this);
  }

  public function markAsChanged() {
    if (!$this->isItem()) return ;
    $models = (array) P('extension.search.models');
    foreach ($models as &$model) {
      $model = I($model);
    }
    if (Extension::exists('search') &&
        in_array($this->getModelId(), $models)) {
      try {
        Document::setStatus($this);
      }
      catch (Exception $e) { $this->log->error($e, __METHOD__); }
    }
    $this->onChange();
    $this->markAsEvolved();
  }

  public function markAsEvolved() {
    if (!$this->isItem()) return ;
    $this->incrementMeta('state');
    //    Cache::remove($this);
  }

  public function duplicate() {
    $h = $this->getAttributes();
    $this->onBeforeDuplicate($h);
    foreach (array('id') as $field) {
      unset($h[$field]);
    }
    $item = Item::getInstance((int) $this->getModelId());
    $item->commit($h);
    $rs = $this->dbo->query('SELECT *'
                            .' FROM '.Item::TABLE_PROPERTY
                            .' WHERE model_id='.$this->getModelId()
                            .  ' AND record_id='.$this->getId());
    foreach ($rs as $h) {
      $h['record_id'] = $item->getId();
      $this->dbo->insert(Item::TABLE_PROPERTY, $h);
    }
    $this->onAfterDuplicate($item);
    return $item;
  }

  public function hasLocale($locale) {
    if ($this->hasAttribute('locales')) {
      return ($this->locales & $locale) >= $locale;
    }
    if ($this->hasAttribute('locale')) {
      return $this->locale == $locale;
    }
    return false;
  }

  public function getLocale() {
    return $this->hasAttribute('locale')
         ? (int) $this->getAttribute('locale')
         : S('app')->getLocale();
  }

  public function getLocales() {
    $this->checkLoaded(__METHOD__);
    $locales = array();
    if ($this->hasAttribute('locales')) {
      $locales = $this->locales > 0 ? $this->getMask('locales') : array();
    }
    elseif ($this->hasAttribute('locale')) {
      $locales = array($this->locale);
    }
    return $locales;
  }

  public function onComment($comment) {}
  
  protected function onPriceChange() {
    if ($this instanceof Purchasable) {
      Discount::applyCatalogDiscounts($this);
    }
  }

  public function onRelationCreate($item) {}
  public function onRelationUpdate($item) {}
  public function onRelationDestroy($item) {}

  public function onResourceCreate($resource) {}
  public function onResourceUpdate($resource) {}
  public function onResourceDestroy($resource) {}

  public function onCollect($finder) {}
  public function onExport($finder) {}
  public function onFind($finder) {}

  public function onLetterSend() {}
  public function onTrack($type, $opts) {}
  public function onChange() {}

  protected function onBeforeDuplicate(&$attrs) {}
  protected function onAfterDuplicate($new_item) {}

  protected function onAdd(ActiveRecord $item) {}
  protected function onAlter() {}
  protected function onRemove(ActiveRecord $item) {}

  protected function onOnline() {}
  protected function onOffline() {}

  protected function onBeforeCommit(&$attrs) {}
  protected function onAfterCommit($attrs) {}

  protected function onBeforeCreate(&$attrs) {}
  protected function onAfterCreate() {}

  protected function onBeforeDestroy() {}
  protected function onAfterDestroy() {}

  protected function onBeforeInstantiate() {}
  protected function onAfterInstantiate() {}

  protected function onBeforeUpdate(&$attrs) {}
  protected function onAfterUpdate(&$attrs) {}

  protected function onBeforeStatusChange(&$attrs) {}
  protected function onAfterStatusChange($old) {}


  public function hasChanged() {
    return count($this->_changes) >= 1;
  }

  public function prior($key) {
    return $this->_changes[$key];
  }

  public function changes() {
    return $this->_changes;
  }

  public function commit($attrs) {
    if (empty($attrs)) {
      $attrs = array();
    }
    $model = $this->getModel();
    $this->onBeforeCommit($attrs);
    if (isset($attrs['id'])) { unset($attrs['id']); }
    $old_status = null;
    if (isset($attrs['status']) && (!$this->isItem() || $attrs['status'] != $this->status)) {
      $old_status = $this->status;
      $this->onBeforeStatusChange($attrs);
    }
    $price_change = false;
    if (isset($attrs['price']) || isset($attrs['original_price'])) {
      if (!$this->isItem()) $price_change = true;
      else {
        if (isset($attrs['price']) && $attrs['price'] != $this->price) {
          $price_change = true;
        }
        if (isset($attrs['original_price']) && $attrs['original_price'] != $this->original_price) {
          $price_change = true;
        }
      }
    }
    if (strlen($attrs['image']) >= 5 &&
        isset($attrs['thumbnail']) && empty($attrs['thumbnail']) &&
        preg_match('#^/'.DOC_PATH.'/#u', $attrs['image'])) {
      try {
        $thumbnail_name = 'thumb-'.basename($attrs['image']);
        $thumb = Img::getInstance($attrs['image'])->copyTo($thumbnail_name, true);
        $box_size = P('thumbnail.box.size') ?: 50;
        $thumb->setBox($box_size);
        $attrs['thumbnail'] = '/'.$thumb->getName();
      }
      catch (Exception $e) { }
    }
    $metas = array('updated_at' => Date::now(),
                   'updated_on' => Date::now());
    if ($this->isItem()) { 
      $is_online = $this->isOnline(); 
      /*      if (isset($attrs['locales'])) {
        if ((is_array($attrs['locales']) && array_sum($attrs['locales']) < 1) ||
            $attrs['locale'] < 1) {
          $attrs['locales'] = S('app')->getLocale();
        }
      }
      else */
      if (isset($attrs['locale']) && $attrs['locale'] < 1) {
        $attrs['locale'] = S('app')->getLocale();
      }
      
      $this->onBeforeUpdate($attrs);
      $row = $this->castAttributes($attrs); 
      $ret = $this->dbo->update($this->_table, $row,
                                array('filters' => array('id' => $this->getId()),
                                      'limit' => 1)); 
      $alterations = array();
      foreach ($row as $key => $value) {
        $old = $this->getAttribute($key);
        $this->_changes[$key] = $old;
        if ($value != $old) {
          $alterations[$key] = array($old, $value);
        }
        $this->_nucleus->{$key} = $value;
      }
      $this->_is_new = false;
      $this->saveVersion($alterations);
      $this->setArguments(array('id' => $this->getId()));
      $this->instantiate();
      $this->onAfterUpdate($attrs);
    }
    else {
      $is_online = false;
      if (Model::hasField($model, 'published_at') && empty($attrs['published_at'])) {
        $attrs['published_at'] = Date::now();
      }
      if (Model::hasField($model, 'published_on') && empty($attrs['published_on'])) {
        $attrs['published_on'] = Date::now();
      }
      /*      if (Model::hasField($model, 'locales') && $attrs['locales'] < 1) {
        $attrs['locales'] = S('app')->getLocale();
      }
      else*/ 
      if (Model::hasField($model, 'locale') && $attrs['locale'] < 1) {
        $attrs['locale'] = S('app')->getLocale();
      }
      if (TreeManager::isNode($this)) {
        TreeManager::onNodeCreate($this, $attrs);
      }
      $this->onBeforeCreate($attrs);
      foreach ($this->_belongs_to as $relation) {
        if ($attrs[$relation['foreign_key']] < 1) {
          $this->log->error('creation failure ['.$model.'],'
                            .' foreign_key missing ['.$relation['foreign_key'].']', __METHOD__);
          throw new ClassRecordException('creation failure : foreign_key missing');
        }
      }

      $id = $this->dbo->insert($this->_table,
                               $this->castAttributes($attrs)); 
      if ($id === DataBaseObject::ERROR_DUPLICATION) {
        throw new DuplicateRecordException('duplicate record ['.$model.'] '."\n");//.var_export($attrs, true));
      }
      if ($id === false) {
        $this->log->error('insert failure ['.$model.']', __METHOD__);
        throw new ClassRecordException('insertion failure');
      }
      $this->_is_new = true;
      $this->setArguments(array('id' => $id)); 
      $this->instantiate();
      $this->onAfterCreate($attrs);
      $metas['created_on'] = Date::now();
    }

    $models = array();
    if (is_array($this->_belongs_to)) {
      $relation = reset($this->_belongs_to);
      if ($attrs[$relation['foreign_key']] >= 1) {
        $metas['parent'] = (int) $attrs[$relation['foreign_key']];
      }
      foreach ($this->_belongs_to as $model => $attrs) {
        $models[] = Model::id($model);
        try {
          $item = $this->getOne($model);
          if ($this->_is_new === true) {
            $item->onRelationCreate($this);
          }
          else {
            $item->onRelationUpdate($this);
          }
        }
        catch (Exception $e) { $this->log->error($e, __METHOD__); }
      }
    }

    if ($this->hasAttributes('model_id', 'record_id') &&
        $this->model_id >= 1 && $this->record_id >= 1 &&
        !in_array($this->model_id, $models)) {
      try {
        $item = $this->getItem();
        if ($this->_is_new === true) {
          $item->onRelationCreate($this);
        }
        else {
          $item->onRelationUpdate($this);
        }
      }
      catch (Exception $e) { $this->log->error($e, __METHOD__); }
    }

    foreach (array('flags', 'status', 'user_id') as $field) {
      if (!isset($attrs[$field])) continue ;
      $field = $field === 'user_id' ? 'user' : $field;
      $metas[$field] = is_array($attrs[$field])
                     ? array_sum($attrs[$field])
                     : (int) $attrs[$field]; 
    }
    foreach (array('latitude', 'longitude') as $field) {
      if (!isset($attrs[$field])) continue ;
      $metas[$field] = (float) $attrs[$field];
    }
    if (isset($attrs['locales'])) {
      $metas['locales'] = is_array($attrs['locales'])
                        ? array_sum($attrs['locales'])
                        : (int) $attrs['locales'];
    }
    elseif (isset($attrs['locale'])) {
      $metas['locales'] = (int) $attrs['locale']; 
    }
    $this->setMetas($metas);
    $this->incrementMeta('revision');
    $this->onAfterCommit($attrs);
    if ($old_status !== null) {
      $this->onAfterStatusChange($old_status);
    }
    if ($price_change === true) {
      $this->onPriceChange();
    }
    if ($this->hasAttribute('status')) {
      if ($is_online === false && $this->isOnline()) {
        $this->onOnline();
      }
      elseif ($is_online === true && !$this->isOnline()) {
        $this->onOffline();
      }
    }
    $this->markAsChanged();
    $this->onAlter();
    S('app')->hook('onAfterCommit',
                   array('item' => $this,
                         'attrs' => $attrs));
    return $this;
  }

  protected function saveVersion($attrs) {
    if (empty($attrs)) return ;
    if (M($this, 'revision') != true) {
      return ;
    }
    try {
      $req = S('req');
      $record = array('model_id' => $this->getModelId(),
                      'record_id' => $this->getId());
      if ($req->isBack()) {
        $record['creator_model_id'] = Model::id('admin');
        $record['creator_record_id'] = S('admin')->getId();
      }
      else {
        $record['creator_model_id'] = Model::id('user');
        if ($req->isAuthenticated()) {
          $record['creator_record_id'] = $req->getUserId();
        }
      }
      $record['action'] = S('req')->getPath();
      $record['attributes'] = serialize($attrs);
      $this->dbo->insert(Item::TABLE_REVISION, $record);
    }
    catch (Exception $e) {
      $this->log->error($e, __METHOD__);
    }
  }

  public function asChannel() {
    $channel = array();
    $channel['id'] = $this->getKey();
    $channel['title'] = (string) $this;
    $channel['description'] = (string) $this->description;
    $channel['link'] = $this->asUrl();
    $channel['copyright'] = P('copyright');
    $channel['ttl'] = 240;
    if ($this->hasAttribute('image')) {
      $channel['image'] = $this->image;
    }
    $channel['updated_at'] = $this->getMeta('updated_at');
    return $channel;
  }


  public function asFeed($entries=null) {
    $opts = array();
    if (!$this->isOnline()) {
      $this->log->error('offline item ['.$this->getModel().']'
                        .           ' ('.$this->getId().')',
                        __METHOD__);
      throw new Exception(l('error.item.invalid'));
    }
    if ($entries === null) {
      if (method_exists($this, 'getEntries')) {
        $entries = $this->getEntries();
      }
      elseif (count($this->_has_many)) {
        $model = key($this->_has_many);
        $opts['last'] = 10;
        if (Model::hasField($model, 'status')) {
          $opts['filters'] = array('|>|status' => 0);
        }
        $entries = $this->getItems($model, $opts);
      }
      else {
        $entries = $this->getComments(array('last' => 10));
      }
    }
    return new FeedWriter($this, $entries);
  }

  public function asFeedHash() {
    $feed = array();
    $feed['id'] = $this->getId();
    $feed['title'] = $this->getName();
    if ($this->hasAttribute('description')) {
      $feed['description'] = $this->description;
    }
    elseif ($this->hasAttribute('content')) {
      //      $feed['description'] = $this->content;
      $feed['description'] = H::ellipse($this->content,
                                        array('length' => 200));
    }
    if ($this->hasAttribute('author')) {
      $feed['author'] = $this->author;
    }
    elseif ($this->hasAttribute('user_id') && $this->user_id >= 1) {
      $feed['author'] = $this->getUser()->name;
    }
    elseif ($this->hasAttribute('author_id') && $this->author_id >= 1) {
      $feed['author'] = $this->getAuthor()->name;
    }
    $feed['link'] = $this->asUrl().'?knxm='.Tracker::MEDIUM_RSS.'&knxt='.urlencode($feed['title']);
    $feed['guid'] = $this->getModelId().'-'.$this->getId();
    $feed['category'] = join(',', $this->getTags());
    $feed['updated_at'] = $this->getMeta('updated_at');
    return $feed;
  }

  public function asAutocompleteName($from=null) {
    return $this->getName();
  }

  public function convert($opts=null) {
    if (!Model::exists('conversion')) return ;
    Conversion::add($this, $opts);
  }

  public function track($intent=Intent::TYPE_DISPLAY, $value=0) {
    return Intent::track($this, $intent, $value);
  }

  public function log($type=null) {
    return Item::log($this, $type);
  }

  public function getId() {
    return $this->getAttribute('id');
  }

  public function getBit() { 
    return B($this->getAttribute('id')); 
  } 

  public function getKey() {
    $h = String::crypt($this->getModelId().$this->getId());
    return join('-', array($this->getModelId(),
                           $this->getId(),
                           $h));
  }

  public function getModel() { return $this->_model; }

  public function getModelId() { return (int) $this->_model_id; }

  public function getUrn() { 
    return 'urn::item::'.$this->_model_id.'::'.$this->getId(); 
  }

  /** 2083 characters max **/
  public function asUrl() {
    return '/'.M($this, 'extension').'/'.$this->getModel().
           '/-/id/'.$this->getId();
  }

  public function debug() { $this->log->debug($this->getAttributes()); }

  public function isBoughtBy($user) {
    if (!Model::exists('order')) return false;
    $user_id = $user instanceof User ? $user->getId() : (int) $user;
    $id = S('dbo')->fetchValue('SELECT p.id'
                               .' FROM '.T('purchase').' AS p,'
                               .     ' '.T('order').' AS o'
                               .' WHERE p.model_id='.$this->getModelId()
                               .  ' AND p.record_id='.$this->getId()
                               .  ' AND p.order_id=o.id'
                               .  ' AND o.user_id='.$user_id
                               .  ' AND o.status>='.Order::STATUS_PAID);
    return $id >= 1;
  }

  public function isItem() { return $this->_nucleus !== null; }
  public function isLoaded() { return $this->_nucleus !== null; }

  public function isNew() { return $this->_is_new === true; }

  public function getResources($opts=null) {
    if (!$this->isItem()) throw new ActiveRecordException();
    $opts = (array) $opts;
    if (!isset($opts['order'])) {
      $opts['order'] = array('position' => 'asc');
    }
    $opts['filters']  = (array) $opts['filters'];
    if (empty($opts['filters']['|>=|status'])) {
      $opts['filters']['|>=|status'] = Resource::STATUS_ONLINE;
    }
    $opts['filters'] += array('model_id' => $this->getModelId(),
                              'record_id' => $this->getId());
    return Item::collect('resource', $opts);
  }

  public function setProperty($key, $value, $locale=null) {
    $locale = $this->_locale($locale);
    return $this->setProperties(array($key => $value), $locale);
  }

  public function setProperties($h, $locale=null) {
    $locale = $this->_locale($locale);
    $properties = $this->getPropertiesById();
    $row = array('model_id' => $this->getModelId(),
                 'record_id' => $this->getId(),
                 'locale' => $locale);
    foreach ($h as $name => $value) {
      $property_id = Model::property($this, $name);
      $row['property_id'] = $property_id;
      if (isset($properties[$locale][$property_id])) {
        $this->dbo->update(Item::TABLE_PROPERTY,
                           array('value' => $value),
                           array('filters' => $row));
      }
      else {
        $row['value'] = $value;
        $this->dbo->insert(Item::TABLE_PROPERTY, $row);
      }
    }
    $this->_cache['properties'][$locale] = null;
    $this->setMetas(array('updated_at' => Date::now()));
    $this->incrementMeta('revision');
    $this->markAsChanged();
    $this->onAlter();
    return $this;
  }

  public function getProperty($key, $locale=null) {
    $locale = $this->_locale($locale);
    if ($this->hasAttribute('property_'.$key)) {
      return $this->getAttribute('property_'.$key);
    }
    if ($this->_cache['properties'][$locale] === null) {
      $this->getProperties($locale);
    }
    return $this->_cache['properties'][$locale][$key];
  }

  public function getProperties($locale=null) {
    $locale = $this->_locale($locale);
    if ($this->_cache['properties'][$locale] === null) {
      $h = $this->dbo->asHash('SELECT p.name, ip.value'
                                 .' FROM '.Item::TABLE_PROPERTY.' AS ip'
                                 .' JOIN '.T('property').' AS p'
                                 .  ' ON (ip.property_id=p.id)'
                                 .' WHERE ip.model_id='.$this->getModelId()
                                 .  ' AND ip.record_id='.$this->getId()
                                 .  ' AND ip.locale='.intval($locale));
      $this->_cache['properties'][$locale] = $h;
    }
    return $this->_cache['properties'][$locale];
  }

  public function _locale($locale=null) {
    if ($locale >= 1) return $locale;
    if ($this->_locale >= 1) return $this->_locale;
    if ($this->hasAttribute('locale') && $this->locale >= 1) {
      return $this->locale;
    }
    return S('res')->getLocale();
  }

  public function getPropertiesById($locale=null) {
    $where = $locale ? ' AND locale='.intval($locale) : '';
    $rs = $this->dbo->query('SELECT *'
                            .' FROM '.Item::TABLE_PROPERTY
                            .' WHERE model_id='.$this->getModelId()
                            .  ' AND record_id='.$this->getId()
                            .$where);
    $properties = array();
    foreach ($rs as $h) {
      $properties[$h['locale']][$h['property_id']] = $h['value'];
    }
    return $properties;
  }

  public function hasAttribute($key, $check_length=false) {
    if (empty($key)) return false;
    $this->checkLoaded(__METHOD__ . '('.$key.')');
    $value = property_exists($this->_nucleus, $key);
    if ($value === false || $check_length === false) {
      return $value;
    }
    return strlen($this->getAttribute($key)) >= 1;
  }

  public function hasAttributes() {
    $attrs = is_array(func_get_arg(0))
           ? func_get_arg(0)
           : func_get_args();
    foreach ($attrs as $attr) {
      if (!$this->hasAttribute($attr)) return false;
    }
    return true;
  }

  public function getAttribute($key) {
    if (!$this->isItem() || empty($key)) return null;
    if (property_exists($this->_nucleus, $key)) {
      return $this->_nucleus->{$key};
    }
    if (property_exists($this->_nucleus, 'property_'.$key)) {
      return $this->_nucleus->{'property_'.$key};
    }
    //S('log')->debug(get_object_vars($this->_nucleus));
    return null;
  }

  public function getAttributes($prefix=null, $trim_flag=false) {
    if (!$this->isItem()) return array();
    if ($prefix === null) {
      return (array) $this->_nucleus;
    }
    $h = array();
    $prefix .= '_';
    $l = strlen($prefix);
    foreach ($this->_nucleus as $key => $value) {
      if (substr($key, 0, $l) != $prefix) continue;
      $key = $trim_flag === true ? substr($key, $l) : $key;
      $h[$key] = $value;
    }
    return $h;
  }

  public function setAttributes(array $row) {
    $this->checkLoaded(__METHOD__);
    $alterations = array();
    $row = $this->castAttributes($row);
    foreach ($row as $key => $value) {
      $old = $this->getAttribute($key);
      if ($value == $old) continue ;
      $alterations[$key] = array($old, $value);
      $this->_nucleus->{$key} = $value;
    }
    if (empty($alterations)) return $this;
    $this->saveVersion($alterations);
    $opts = array('filters' => array('id' => $this->getId()),
                  'limit' => 1);
    $ret = $this->dbo->update($this->_table, $row, $opts);
    if ($ret === -1) {
      $this->log->error('update failure ['.$this->getModel().']', __METHOD__);
      throw new ActiveRecordException('update failure');
    }
    return $this;
  }

  public function setAttribute($key, $value) {
    $this->checkLoaded(__METHOD__);
    if ($this->getAttribute($key) == $value) {
      return $this;
    }
    $this->setAttributes(array($key => $value));
    return $this;
  }

  public function __get($key) {
    return $this->getAttribute($key);
  }

  public function __set($key, $value) {
    S('log')->error('invalid operation : '.
		    '$'.$this->getModel().' ->'.$key.' = "val"; '.
                    'use commit() or setAttribute()',
                    __METHOD__);
  }

  public function __isset($key) { return $this->hasAttribute($key); }

  public function setArguments($args) { $this->_args = $args; }

  protected function getArguments() { return $this->_args; }

  protected function _count($model, $opts=array()) {
    return $this->getItems($model, $opts)->count();
  }

  public function __clone() {
    $this->_nucleus = null;
    $this->_cache = array('objects' => array());
    $this->_is_destroyed = false;
    $this->_is_new = false;
    $this->_opts = array('include' => array());
    $this->_changes = array();
    $this->_args = array('id' => (int) $this->id);
    // _locale
  }

  public function getOne($model, $opts=null) {
    $this->checkLoaded('get - '.$model);
    $opts = (array) $opts;

    if (isset($this->_cache['objects'][$model])) {

      return $this->_cache['objects'][$model];
    }
    if (isset($this->_has_one[$model]) || isset($this->_belongs_to[$model])) {      
      if (in_array($model, $this->_opts['include'])) {
        $this->_cache['objects'][$model] = Item::getInstance($model);
        $this->_cache['objects'][$model]->_setNucleus($this->getAttributes($model, true));
        return $this->_cache['objects'][$model];
      }
      $args = isset($this->_has_one[$model])
            ? array($this->_foreign_key => $this->getId())
            : $this->getAttribute($model.'_id');
      $this->_cache['objects'][$model] = Item::getInstance($model, $args, $opts);
      return $this->_cache['objects'][$model];
    }
    $foreign_key = $model.'_id';
    if (Model::hasField($this->getModel(), $foreign_key)) {
      if ($this->getAttribute($foreign_key) < 1) {
        $this->log->error('bad foreign key ('.$foreign_key.') ['.$model.']', __METHOD__);
      }

      $this->_cache['objects'][$model] = Item::getInstance($model,
                                                           $this->getAttribute($foreign_key),
                                                           $opts);
    }
    else {

      $this->_cache['objects'][$model] = Item::getInstance($model,
                                                           array($this->_foreign_key => $this->getId()),
                                                           $opts);
    }
    return $this->_cache['objects'][$model];
  }

  public function relation($model) {
    $model = $model instanceof ActiveRecord ? $model->getModel() : $model;
    if (isset($this->_has_many[$model])) return $this->_has_many[$model];
    if (isset($this->_belongs_to[$model])) return $this->_belongs_to[$model];
    if (isset($this->_has_one[$model])) return $this->_has_one[$model];
    return null;
  }

  public function getItems($model, $opts=null) {
    $this->checkLoaded(__METHOD__);
    $model = strtolower($model);
    $filters = array();
    $opts['filters'] = (array) $opts['filters'];

    $relation = $this->_has_many[$model];

    $through = $relation['through'];
    if (strlen($through) >= 2) {
      $filter = '';
      if (in_array($this->_foreign_key, $relation['through_cols'])) {
        $filter = $through.'.`'.$this->_foreign_key.'`='.$this->getId();
        if (in_array($model.'_id', $relation['through_cols'])) {
          $filter .= ' AND '.T($model).'.`id`='.$through.'.`'.$model.'_id`';
        }
        else {
          $filter .= ' AND '.T($model).'.`id`='.$through.'.`record_id`'.
                     ' AND '.$through.'.`model_id`='.Model::id($model);
        }
      }
      else {
        $filter  = $through.'.`record_id`='.$this->getId().' AND '.
	           $through.'.`model_id`='.$this->_model_id;
        $filter .= ' AND '.$through.'.`'.$model.'_id`='.T($model).'.`id`';
      }
      $filters[] = $filter;
      if (is_array($relation['cols'])) {
        $opts['cols'] = $relation['cols'];
      }
      $opts['tables'] = array($through);
    }
    elseif ($relation['foreign_key'] === true) {
      $filters['model_id'] = $this->getModelId();
      $filters['record_id'] = $this->getId();
    }
    else {
      $filters[$this->_foreign_key] = $this->getId();
    }
    if (!isset($opts['order'])) {
      if (is_array($relation['order'])) {
        $opts['order'] = $relation['order'];
      }
      else if (Model::hasField($model, 'position')) {
        $opts['order'] = array('position' => 'ASC');
      }
    }
    foreach (array('metas', 'include') as $key) {
      if (!isset($relation[$key])) continue ;
      $opts[$key] = array_merge((array) $opts[$key], 
				(array) $relation[$key]);
    }
    if (is_array($relation['filters'])) {
      foreach ($relation['filters'] as $key => $value) {
        $filters[$key] = $value;
      }
    }
    $opts['filters'] = empty($opts['filters'])
                     ? $filters
                     : array_merge(array($filters),
                                   array($opts['filters']));
    $collection = Item::collect($model, $opts);
    $collection->setTitle($this->getName());
    return $collection;
  }

  public function __call($method, $args=array()) {
    $_method = __METHOD__.'::'.$method;
    $method = strtolower($method);
    $snippet = substr($method, 0, 3);
    $is_plural = false;
    switch ($snippet) {
    case 'add':
      $this->checkLoaded($method);
      $model = substr($method, 3);
      if (substr($model, -1) === 's') {
        $model = Model::singularize($model);
        $is_plural = true;
      }
      if ($args[0] instanceof ActiveRecord || $args[0] instanceof Collection) {
        $model = $args[0]->getModel();
        $relation = $this->relation($model);
        if ($relation === null || $relation['through'] === null) {
          $this->log->error('no relation between '.
			    '['.$this->getModel().'] and '.
			    '['.$model.']', $_method);
          throw new ActiveRecordException('no relation');
        }
        $items = $args[0] instanceof Collection ? $args[0] : array($args[0]);
        $attributes = (array) $args[1];
        foreach ($items as $item) {
          $row  = $attributes;
          $row += array($this->_foreign_key => $this->getId(),
                        $item->_foreign_key => $item->getId());
          $this->dbo->insert($relation['through'], $row, array('IGNORE'));
          $item->onAdd($this);
        }
        return $args[0] instanceof ActiveRecord ? $args[0] : $this;
        break ;
      }
      $args[0][$this->_foreign_key] = $this->getId();
      $class = Item::getInstance($model);
      $class->_cache['objects'][$this->getModel()] = $this;
      $class->commit($args[0]);
      $commit = array();
      if ($this->hasAttribute($model.'_count')) {
        $commit[$model.'_count'] = $this->getAttribute($model.'_count') + 1;
      }
      if (count($commit) >= 1) {
        $this->commit($commit);
      }
      return $class;
      break ;
    case 'rem':
      $this->checkLoaded($method);
      if (!($args[0] instanceof ActiveRecord)) {
        $this->log->error('arg must be an ActiveRecord', $_method);
        return $this;
      }
      $item = $args[0];
      $model = $item->getModel();
      $relation = $this->relation($model);
      if ($relation === null || $relation['through'] === null) {
        $this->log->error('no relation between '.
			  '['.$this->getModel().'] and '.
			  '['.$item->getModel().']',
			  $_method);
        throw new ActiveRecordException('no relation');
      }
      /*      $row = array($this->_foreign_key => $this->getId(),
       $item->_foreign_key => $item->getId());*/
      $cols = $relation['through']['through_cols'];
      $where = '';
      if (in_array($this->_foreign_key, $relation['through_cols'])) {
        $where = $this->_foreign_key.'='.$this->getId();
        if (in_array($item->_foreign_key, $relation['through_cols'])) {
          $where .= ' AND '.$item->_foreign_key.'='.$item->getId();
        }
        else {
          $where .= ' AND model_id='.$item->_model_id.
                    ' AND record_id='.$item->getId();
        }
      }
      else {
        $where = 'model_id='.$this->_model_id
           .' AND record_id='.$this->getId()
           .' AND '.$item->_foreign_key.'='.$item->getId();
      }
      $this->dbo->exec('DELETE FROM '.$relation['through']
                       .    ' WHERE '.$where);
      $item->onRemove($this);
      return $this;
      break ;
    case 'has':
      $this->checkLoaded($method);
      if (substr($method, 0, 6) === 'hasany') {
        $model = strtolower(substr($method, 6));
        return call_user_func_array(array($this, '_count'),
                                    array($model, $args[0])) >= 1;
      }
      $model = strtolower(substr($method, 3));
      if ($args[0] instanceof ActiveRecord) {
        $item = $args[0];
        if ($item->getModel() != $model) {
          $this->log->error('invalid item model ['.$item->getModel().']', 
			    $_method);
          return $this;
        }
        $model_id = $item->getModelId();
        $record_id = $item->getId();
        $foreign_key = $this->_foreign_key;
      }
      elseif (is_numeric($args[0])) {
        $model_id = Model::id($model);
        $record_id = (int) $args[0];
        $foreign_key = $model.'_id';
      }
      else {
        $this->log->error('arg must be an ActiveRecord or a numeric', 
			  $_method);
        return $this;
      }
      $relation = Model::relation($this->getModel(), $model);
      if ($relation === null || $relation['through'] === null) {
        $this->log->error('no relation between '.
			  '['.$this->getModel().'] and '.
			  '['.$model.']',
			  $_method);
        throw new ActiveRecordException('no relation');
      }
      $where = '';
      if (in_array($this->_foreign_key, $relation['through_cols'])) {
        $where = $this->_foreign_key.'='.$this->getId();
        if (in_array($foreign_key, $relation['through_cols'])) {
          $where .= ' AND '.$foreign_key.'='.$record_id;
        }
        else {
          $where .= ' AND model_id='.$model_id.
                    ' AND record_id='.$record_id;
        }
      }
      else {
        $where = 'model_id='.$this->_model_id
           .' AND record_id='.$this->getId()
           .' AND '.$foreign_key.'='.$record_id;
      }
      return $this->dbo->fetchValue('SELECT COUNT(*)'
                                    .' FROM '.$relation['through']
                                    .' WHERE '.$where) >= 1;
      break ;
    case 'cou':
      $this->checkLoaded($method);
      $model = Model::singularize(substr($method, 5));
      return call_user_func_array(array($this, '_count'),
                                  array($model, $args[0]));
      break ;
    case 'get':
      $model = substr($method, 3);
      return substr($model, -1) === 's'
           ? $this->getItems(Model::singularize($model), $args[0])
           : $this->getOne($model, $args[0]);
      break ;
    default:
      S('log')->error('unknown method', $_method);
      throw new Exception('method unknown');
      break ;
    }
  }

  public function __toString() {
    if (!$this->isItem()) {
      S('log')->trace('DEPRECATED __toString sur un objet non loadé '.
		      '('.$this->getModel().')');
      S('log')->backtrace();
      return null;
    }
    return $this->getName();
  }

  //** STATIC **

  public static function collect($opts=null) {
    $model = strtolower(get_called_class());
    return Item::collect($model, $opts);
  }

  public static function id($elt) {
    $model = strtolower(get_called_class());
    return Item::id($model, $elt);
  }

  public static function name($id) {
    if ($id < 1) return '-';
    $model = strtolower(get_called_class()); 
    return Item::name($model, $id);
  }

  public static function exists($elt) {
    $model = strtolower(get_called_class());
    return Item::exists($model, $elt);
  }

  public static function getInstance($args=true, array $options=array()) {
    $model = strtolower(get_called_class());
    return Item::factory($model, $args, $options);
  }

  public static function getInstanceByKey($item_key, array $opts=array()) {
    $model = strtolower(get_called_class());
    $item = Item::getInstanceByKey($item_key, $opts);
    if (!$item->isA($model)) {
      throw new MaliciousException();
    }
    return $item;
  }

}
