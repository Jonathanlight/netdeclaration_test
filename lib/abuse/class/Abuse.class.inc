<?php

class Abuse extends ActiveRecord 
{
  const FLAG_ILLICIT = 1;
  const FLAG_ANSWERED = 2;

  public static $flags = array(self::FLAG_ILLICIT => 'illégitime',
                               self::FLAG_ANSWERED => 'défendu');

  const STATUS_PENDING = 0;
  const STATUS_PROCESSING = 1;
  const STATUS_PROCESSED = 2;

  public static $statuses = array(self::STATUS_PROCESSED => 'traité',
                                  self::STATUS_PROCESSING => 'en cours',
                                  self::STATUS_PENDING => 'en attente');

  public function asEditHash() {
    $details['motif'] = (string) $this->getMotive();
    try {
      $item = $this->getItem();
      $details['objet cible'] = Item::edit($item, array('view' => 'item'));
    }
    catch (Exception $e) {
      $this->log->error($e, __METHOD__);
    }
    try {
      $user = $this->getUser();
      $details['origine'] = Item::edit($user);
    }
    catch (Exception $e) { }
    if (!empty($this->full_name)) {
      $details['nom'] = h($this->full_name);
    }
    if (!empty($this->email)) {
      $details['email'] = h($this->email);
    }
    $hash['details'] = $details;
    return $hash;
  }
  
  public function onComment($comment) { 
    $this->setFlag(self::FLAG_ANSWERED);
  }
  
  public function asFinderHash($hash) {
    $hash['content'] = H::ellipse($hash['content']);
    return $hash;
  }


}