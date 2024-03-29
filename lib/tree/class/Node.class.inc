<?php

class Node extends ActiveRecord {

  public $_recursive = true;

  const FLAG_ALIAS = 1;
  const FLAG_MENU = 2;
  const FLAG_NODE_OFFLINE = 4;
  const FLAG_NODE_PROTECTED = 8;
  const FLAG_TREE_OFFLINE = 16;
  const FLAG_TREE_PROTECTED = 32;

  public static $flags = array(self::FLAG_ALIAS => 'alias',
                               self::FLAG_MENU => 'dans menu',
                               self::FLAG_NODE_OFFLINE => 'noeud caché',
                               self::FLAG_NODE_PROTECTED => 'noeud protégé',
                               self::FLAG_TREE_OFFLINE => 'branche cachée',
                               self::FLAG_TREE_PROTECTED => 'branche protégée');

  public function duplicate() {
    $tree = Tree::getInstance($this->tree_id);
    $hash = $this->getAttributes();
    unset($hash['id']);
    $hash = array_merge($hash,
                        TreeManager::nextChild('node',
                                               $tree->getId(),
                                               substr($this->path, 0, -2)));
    $hash['parent_path'] = substr($this->path, 0, -2);
    $hash['name'] .= ' (2)';
    $brother = Node::getInstance();
    $brother->commit($hash);
    $brother->import($this->path);
    return $brother;
  }

  public function import($path) {

    $cols = array_diff($this->dbo->getTable(T('node'))->getFields(),
                       array('id', 'path', 'ancestor_id'));

    $this->dbo->exec('INSERT IGNORE INTO '.T('node')
                     .' (path, #cols#)'
                     .' SELECT CONCAT(:path:, SUBSTRING(path, #length#)), #cols# '
                     .' FROM '.T('node')
                     .' WHERE path>:min: AND path<=:max:'
                     .  ' AND tree_id='.$this->tree_id,
                     array(':path:' => $this->path,
                           '#length#' => (strlen($path) + 1),
                           '#cols#' => join(',', $cols),
                           ':min:' => $path,
                           ':max:' => $path.'zz'));

    $rs = $this->dbo->query('SELECT id, path'
                            .' FROM '.T('node')
                            .' WHERE path BETWEEN :min: AND :max:'
                            .'   AND tree_id='.$this->tree_id
                            .' ORDER BY path',
                            array(':min:' => $this->path,
                                  ':max:' => $this->path.'zz'));

    $opts = array('filters' => array('tree_id' => $this->tree_id));
    $record = array('ancestor_id' => 0);
    while ($row = $rs->fetchHash()) {
      $opts['filters']['|%|path'] = $row['path'].'__';
      $record['ancestor_id'] = (int) $row['id'];
      $this->dbo->update(T('node'), $record, $opts);
    }
  }

  public function getBreadcrumb() {
    $n = strlen($this->path) / 2;
    $pathes = array();
    for ($i = 1; $i < $n; $i++) {
      $pathes[] = substr($this->path, 0, $i * 2);
    }
    $hash = $this->dbo->asHash('SELECT id, name'
                               .' FROM '.T('node')
                               .' WHERE tree_id='.$this->tree_id
                               .  ' AND path IN ([pathes])'
                               .' ORDER BY path',
                               array('[pathes]' => $pathes));
    $hash[$this->getId()] = $this->name;
    return $hash;
  }

  public function asEditHash() {
    if ($this->isItem()) {
      $tree_id = (int) $this->tree_id;
    }
    else {
      $tree_id = (int) S('ctx')->getAttribute('tree_id');
    }
    if ($tree_id < 1) {
      throw new Exception('unknown tree');
    }
    $tree = Tree::getInstance($tree_id);
    $hash['models'] = $tree->models; 
    $hash['has_model_id'] = strlen($tree->models) >= 1;
    if ($this->isLoaded()) {
      $hash['fieldset_label'] = 'Node <small>( id - <b>'.$this->getId().'</b> )</small>';
    };
    return $hash;
  }

  protected function onBeforeCommit(&$hash) {
    if (isset($hash['name']) && empty($hash['name'])) {
      throw new ActiveRecordException('le nom est obligatoire');
    }
    if (!empty($hash['record_id']) &&
        !Item::exists($hash['model_id'], $hash['record_id'])) {
      throw new ActiveRecordException('ID element associé invalide');
    }
  }

  /*  protected function onAfterDestroy() {
    $this->dbo->exec('DELETE FROM tre_item_node'
                     .' WHERE node_id='.$this->getId());
    if (strlen($this->path) < 2 ||
        $this->tree_id < 1 ||
        $this->_recursive === false) return ;
    $this->dbo->exec('DELETE FROM tre_item_node'
                     .    ' WHERE node_id IN (SELECT id'
                     .                        ' FROM '.T('node')
                     .                       ' WHERE tree_id='.$this->tree_id
                     .                         ' AND path BETWEEN :min: AND :max:)',
                     array(':min:' => $this->path,
                           ':max:' => $this->path.'zz'));
                           }*/

}
