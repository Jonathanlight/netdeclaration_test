<?php

class Resource extends ActiveRecord {

  const PATH = 'doc/resources';

  const TYPE_IMAGE = 1;

  const STATUS_ONLINE = 1;

  public function asEditHash() {
    return array('disable_home' => true);
  }

  protected function onAfterCreate() {
    try {
      $this->getItem()->onResourceCreate($this);
    }
    catch (Exception $e) {
      $this->log->error($e, __METHOD__);
    }
  }

  protected function onAfterUpdate(&$hash) {
    try {
      $this->getItem()->onResourceUpdate($this);
    }
    catch (Exception $e) {
      $this->log->error($e, __METHOD__);
    }
  }
  
  protected function onBeforeDestroy() {
    try {
      $this->getItem()->onResourceDestroy($this);
    }
    catch (Exception $e) {
      $this->log->error($e, __METHOD__);
    }
  }

  public static function asRows($item) {
    if (!$item->isItem()) return '';
    $opts = array('filters' => array('|>=|status' => -128));
    $resources = $item->getResources($opts);
    if (count($resources) < 1)  return '';
    $html = '<ul id="'.$item->getKey().'">'."\n";
    foreach ($resources as $resource) {
      $html .= '<li data-id="'.$resource->getId().'" id="resource_'.$resource->getId().'">';
      if ($resource->isImage() && !empty($resource->path)) {
        $html .= '<img src="/'.$resource->path.'" />';
      }
      $class = 'handle'; 
      $class .= $resource->status < 1 ? ' offline' : '';
      $html .= '<strong class="'.$class.'">=</strong>';
      $attributes = array('data' => array('model' => 'resource',
                                          'record-id' => $resource->getId()));
      $name = $resource->getName();
      $name = empty($name) ? '** resource-'.$resource->getId().' **' : $name; 
      $html .= H::elt('a', $name, $attributes);
      $html .= '<div class="details">';
      $html .= '<span>supprimer</span>';
      $html .= '</div>';
      $html .= '<div class="clear"></div>';
      $html .= '</li>'."\n";
    }
    $html .= '</ul>'."\n";
    return $html;
  }

  public function isImage() {
    return $this->type == self::TYPE_IMAGE;
  }



}