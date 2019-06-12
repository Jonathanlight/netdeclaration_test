<?php

class Body extends ActiveRecord 
{
  protected function onBeforeCommit(&$hash) {
    if (isset($hash['content'])) {
      $hash['content'] = String::tidy($hash['content'], 
                                      array('wrap' => 900));
    }
  }
}