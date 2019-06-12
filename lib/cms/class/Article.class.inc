<?php

class Article extends ActiveRecord {

  public function onBeforeCommit(&$hash) {
    if (isset($hash['content'])) {
      $hash['content'] = String::tidy($hash['content']);
    }
    if (isset($hash['description'])) {
      $hash['description'] = String::tidy($hash['description']);
    }
  }

  public function onAfterCreate() {
    $heading = $this->getHeading();
    if ($heading->forum_id >= 1) {
      $forum = $heading->getForum();
      $content = $this->content.'<br/><a href="'.$this->asUrl().'">lire l\'article</a>'; 
      $topic = $forum->addTopic(array('name' => $this->name,
                                      'content' => $content,
                                      'user_id' => 1));
      $this->commit(array('topic_id' => $topic->getId()));
    }
  }

  public function asDocumentHash($locale) {
    $hash = parent::asDocumentHash($locale);
    $hash['name'] = $this->getHeading()->name.' - '.$this->name;
    $opts = array('order' => array('position', 'name'));
    foreach ($this->getChapters($opts) as $chapter) {
      $hash['content'] .= '<h3>'.$chapter->name.'</h3>';
      $hash['content'] .= $chapter->content;
		}
    return $hash;
  }

  public function asSearchHash($locale) {
    $hash = parent::asSearchHash($locale);
    $hash['title'] = $this->getHeading()->name.' : '.$this->name;
    if ($this->heading_id == 1) {
      $hash['image'] = '/app/search/pix/logo_articles.png';
    } 
    else {
      $hash['image'] = '/app/search/pix/logo_headings.png';
    }
    return $hash;
  }

  public function asUrl(){
    return '/'.I18n::$locales[$this->locale].'/article-'.String::urlify($this->name).'-'.$this->getId();
  }

}