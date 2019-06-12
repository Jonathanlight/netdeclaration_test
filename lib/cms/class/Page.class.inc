<?php

class Page extends ActiveRecord {

  public function asUrl(){
    return '/'.I18n::$locales[$this->locale].'/page-'.String::urlify($this->title).'-'.$this->getId();    
  }

  public function asView($view) {
    $icon_view = '<img src="/app/core/pix/action/view.png" style="margin-right: 5px; vertical-align: text-bottom;" /> ';
    if ($this->heading_id == Heading::exists(array('code' => 'ntd.carousels'))) {
      return $icon_view . 'Page "' . $this->title . '"';
    }
    return parent::asView($view);
  }

}