<?php

class Paragraph extends ActiveRecord {

  protected function onBeforeCreate(&$hash) {
    if (empty($hash['title'])) {
      $hash['title'] = $hash['name'];
    }
  }

  protected function onBeforeCommit(&$hash) {
    if (isset($hash['name']) && empty($hash['name'])) {
      throw new ActiveRecordException('le nom est obligatoire');
    }
    if (isset($hash['content']) && strlen($hash['content']) >= 3) {
      $hash['content'] = String::tidy($hash['content']);
    }
  }

}