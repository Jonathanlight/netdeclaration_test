<?php

class Servicetype extends ActiveRecord {

  public function asUrl($locale_id = null){
    return NetDeclarationManager::url(array('item' => $this), $locale_id);
  }

}