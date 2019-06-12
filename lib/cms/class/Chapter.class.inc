<?php

class Chapter extends ActiveRecord {

  protected function onAlter() {
    parent::onAlter();
    $this->getArticle()->setMetas(array('updated_at' => Date::now()));
  }

}