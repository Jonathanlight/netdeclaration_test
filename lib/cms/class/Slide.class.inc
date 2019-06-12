<?php

class Slide extends ActiveRecord {

  protected function onBeforeCreate(&$attrs) {
    if (empty($attrs['position'])) {
      $position = $this->dbo->fetchValue('SELECT MAX(position)'
                                         .' FROM '.T('slide')
                                         .' WHERE slideshow_id='.$attrs['slideshow_id']);
      $attrs['position'] = intval($position) + 1;
    }
  }

}