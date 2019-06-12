<?php

class Affiliate extends ActiveRecord {

  const STATUS_ONLINE = 10;
  const STATUS_PENDING = 0;
  const STATUS_OFFLINE = -10;

  public static $statuses = array(self::STATUS_ONLINE => 'en ligne',
                                  self::STATUS_PENDING => 'en attente de validation',
                                  self::STATUS_OFFLINE => 'refus');

  protected function onAfterCommit($attrs) {
    if ($this->user_id >= 0) {
      try {
        $user = User::getInstance((int) $this->user_id);
        if (!$user->hasFlag(User::FLAG_AFFILIATE)) {
          $user->setFlag(User::FLAG_AFFILIATE);
        }
      }
      catch (Exception $e) { S('log')->error($e, __METHOD__); }
    }
  } 

}