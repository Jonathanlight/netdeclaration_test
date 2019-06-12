<?php

try { 

  //$req->debug();

  $item = null;

  if ($req->item) {
    $item = Item::getInstanceByKey($req->item);
    define(MODEL, $item->getModel());
  }
  elseif ($req->item_key) {
    S('log')->trace('item_key deprecated');
    $item = Item::getInstanceByKey($req->item_key);
    define(MODEL, $item->getModel());
  }

  if ($item === null) {
    $arg = true;
    if ($req->id >= 1) {
      $arg = (int) $req->id;
    }
    elseif (Model::isProfile(MODEL) && $req->getBranchValue('user_id') >= 1) {
      $id = $dbo->fetchValue('SELECT id'
                             .' FROM '.T(MODEL)
                             .' WHERE user_id='.$req->getBranchValue('user_id'));
      $arg = $id >= 1 ? (int) $id : true;
    }
    $item = Item::getInstance(MODEL, $arg); 
  }

  $hash = array();
  $branch = $req->getBranch();
  foreach ($branch as $key => $value) {
    $hash[$key] = $value;
  }
  
  $label = Model::label($item);
  if ($item->isLoaded()) {
    $hash = (array) $item->_nucleus;
    $hash['is_loaded'] = true;
    $title = $item->getName();
    $title = strlen($title) > 60 ? substr($title, 0, 60) . '&hellip;' : $title;
    $hash['fieldset_label'] = $label.' [ <b>'.$title.'</b> ]';
    if (!is_numeric($title)) {
      $hash['fieldset_label'] .= ' <small>( <b>'.$item->getId().'</b> )</small>';
      }
    $ret = $dbo->fetchValue('SELECT COUNT(*)'
                            .' FROM '.Item::TABLE_NOTE
                            .' WHERE model_id='.$item->getModelId()
                            .  ' AND record_id='.$item->getId());
    $hash['fieldset_label'] .= $ret ? ' *' : '';
  }
  else {
    $hash['is_loaded'] = false;
    $hash['fieldset_label'] = 'nouvel élément : <b>'.ucfirst($label).'</b>';
  }
  
  $hash['is_not_loaded'] = !$hash['is_loaded'];

  if (method_exists($item, 'asEditHash')) {
    $tmp = $item->asEditHash();
    $tmp = is_array($tmp) ? $tmp : array();
    foreach ($tmp as $key => $value) {
      $hash[$key] = $value;
    }
  }
  
  if (!(Model::isProfile(MODEL) && $req->getBranchValue('user_id') >= 1) &&
      !TreeManager::isNode($item) && $hash['disable_home'] != true) {
    $hash['fieldset_label'] .= ' <img src="/app/core/pix/action/home-search.png"'
                              .' onclick="Kwo.F(\''.$item->getModel().'\').onHome(this);"'
                              .' onload="if (!$(this).inModal()) { $(this).show(); }"'
                              .' style="display:none;"'
                              .' title="retour à liste" />';
  }


  if (TreeManager::isTree($item) && $item->isLoaded()) { 
    $columns = TreeManager::columns($item);
    $node_model = TreeManager::nodeModel($item);
    $hash['columnview'] = Template::render('//columns',
                                           array('columns' => $columns,
                                                 'tree_id' => $item->getId(),
                                                 'tree_model' => $item->getModel(),
                                                 'node_model' => $node_model));
  }

  if (Model::hasField(MODEL, 'app') && empty($hash['app']) && 
      !in_array(MODEL, array('parameter', 'pagelet', 'style', 'carrier',
                             'string', 'snippet', 'letter', 'notice'))) { 
    $hash['app'] = S('app')->getName();
  }

  $ctx->setAttributes($hash); 

  $ctx->item = $item;

  $res->useXml(MODEL.'.edit');

}
catch (Exception $e) { $err->add($e); }
