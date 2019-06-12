<?php

class Comment extends ActiveRecord 
{
  const FLAG_SPAM = 1;
  const FLAG_SHADY = 2;
  const FLAG_AGGRESSIVE = 4;
  const FLAG_GOOD = 8;
  const FLAG_BAD = 16;

  public static $flags = array(self::FLAG_SPAM => 'spam',
                               self::FLAG_SHADY => 'suspect',
                               self::FLAG_AGGRESSIVE => 'agressif',
                               self::FLAG_GOOD => 'bon',
                               self::FLAG_BAD => 'mauvais');

  const STATUS_REFUSED = -10;
  const STATUS_PENDING = 1;
  const STATUS_ACCEPTED = 20;

  public static $statuses = array(self::STATUS_ACCEPTED => 'accepté',
                                  self::STATUS_PENDING => 'en attente',
                                  self::STATUS_REFUSED => 'refusé');

  private static $colors = array(self::STATUS_REFUSED => 'red',
                                 self::STATUS_PENDING => 'yellow',
                                 self::STATUS_ACCEPTED => 'green');

  public function asFinderHash($hash) {
    $hash['_color'] = self::$colors[$this->status];
    try {
      $item = $this->getItem();
      $comment = '<a href="javascript:void(0)" onclick="new Kwo.Preview(this)" data-url="'.$item->asUrl().'" title="ID '.$item->getId().'">'.$item.'</a> : ';
      $content = strip_tags($this->content);
      $comment .= $content;
      $hash['comment'] = $comment;
    }
    catch (Exception $e) { 
      $hash['comment'] = '['.$this->model_id.':'.$this->record_id.']';
      $this->destroy();
    }
    return $hash;
  }

  public function destroy() {
    $this->setStatus(self::STATUS_REFUSED);
    $this->getItem()->onRelationDestroy($this);
    $this->getItem()->decrementMeta('comment');
  }

  public function accept() {
    if ($this->status == self::STATUS_ACCEPTED) return ;
    $this->setStatus(self::STATUS_ACCEPTED);
  }

  public static function models() {
    $where = '';
    if (Extension::exists('social')) {
      $where = ' WHERE model_id<>'.I('message');
    }
    $rs = S('dbo')->query('SELECT DISTINCT model_id'
                          .' FROM '.T('comment').$where);
    $hash = array();
    foreach ($rs as $row) {
      $model_id = $row['model_id'];
      $hash[$model_id] = N($model_id);
    }
    return $hash;
  }

  public function onCollect($finder) {
    $collection = $finder->getCollection();
    if (Extension::exists('social')) {
      $collection->filters['|<>|model_id'] = I('message');
    }
  }

}