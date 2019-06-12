<?php

class Forfait extends ActiveRecord {

  public function asFinderHash($hash) {
    $hash['services'] = implode("<br />", $this->getServices(array('order' => array('name' => 'asc')))->asSet('name'));
    return $hash;
  }

}