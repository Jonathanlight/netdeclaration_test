<?php

class Intent
{
  const TABLE = 'sys_item_intent';

  const TYPE_IMPRESSION = 0;

  const TYPE_DISPLAY = 1;
  const TYPE_REDIRECT = 2;
  const TYPE_DOWNLOAD = 3;
  const TYPE_RATE = 4;
  const TYPE_VOTE = 5;
  const TYPE_LIKE = 6;
  const TYPE_DISLIKE = 7;
  const TYPE_PLAY = 8;
  const TYPE_SHARE = 9;
  const TYPE_FAVORITE = 10;
  const TYPE_FAN = 11;
  const TYPE_ABUSE = 12;
  const TYPE_SUBSCRIBE = 13;
  const TYPE_COMMENT = 14;
  const TYPE_CLIC = 15;
  const TYPE_SUBMIT = 16;
  const TYPE_SELECTION = 17;
  const TYPE_AUTH = 18;
  const TYPE_INVITE = 19;
  const TYPE_CREATION = 20;
  const TYPE_PRINT = 21;
  const TYPE_PURCHASE = 22;
  const TYPE_PAY = 23;
  const TYPE_CUSTOMIZE = 24;

  const STATUS_OFFLINE = 0;
  const STATUS_ONLINE = 1;

  public static $names = array(self::TYPE_IMPRESSION => 'affichage',
                               self::TYPE_DISPLAY => 'visualisation',
                               self::TYPE_REDIRECT => 'redirection',
                               self::TYPE_DOWNLOAD => 'téléchargement',
                               self::TYPE_RATE => 'note',
                               self::TYPE_VOTE => 'vote',
                               self::TYPE_LIKE => 'j’aime',
                               self::TYPE_DISLIKE => 'je n’aime pas',
                               self::TYPE_PLAY => 'lecture',
                               self::TYPE_SHARE => 'partage',
                               self::TYPE_FAVORITE => 'favoris',
                               self::TYPE_FAN => 'fan',
                               self::TYPE_ABUSE => 'abus',
                               self::TYPE_SUBSCRIBE => 'inscription',
                               self::TYPE_COMMENT => 'commentaire',
                               self::TYPE_CLIC => 'clic',
                               self::TYPE_SUBMIT => 'soumission',
                               self::TYPE_SELECTION => 'selection',
                               self::TYPE_AUTH => 'authentification',
                               self::TYPE_INVITE => 'invitation',
                               self::TYPE_CREATION => 'création',
                               self::TYPE_PRINT => 'impression',
                               self::TYPE_PURCHASE => 'commandé',
                               self::TYPE_PAY => 'payé',
                               self::TYPE_CUSTOMIZE => 'personnalisation');

  public static $type2meta = array(self::TYPE_ABUSE => 'abuse',
                                   self::TYPE_COMMENT => 'comment',
                                   self::TYPE_DISPLAY => 'display',
                                   self::TYPE_DOWNLOAD => 'download',
                                   self::TYPE_FAVORITE => 'favorite',
                                   self::TYPE_RATE => 'rate',
                                   self::TYPE_SHARE => 'share',
                                   self::TYPE_SUBSCRIBE => 'suscription',
                                   self::TYPE_DISLIKE => 'dislike',
                                   self::TYPE_LIKE => 'like');

  public static function track($item, $type=Intent::TYPE_DISPLAY, $opts=null) {
    $dbo = S('dbo');
    $req = S('req');
    $opts = (array) $opts;
    $visit_id = $opts['visit_id'] >= 1 ? $opts['visit_id'] : $req->getId();
    if ($visit_id < 1) return false;
    $arr = $dbo->fetchArray('SELECT medium, source'
                            .' FROM '.Visit::TABLE
                            .' WHERE id='.intval($visit_id)); //visit_id= ERREUR
    $medium = (int) $arr[0];
    $source = (int) $arr[1];
    $table = $dbo->getTable(self::TABLE);
    $row = array('model_id' => $item->getModelId(),
                 'record_id' => $item->getId(),
                 'type' => $type,
                 'medium' => $medium,
                 'source' => $source,
                 'visit_id' => $visit_id,
                 'created_on' => Date::today());
    if ($table->hasRow($row)) return false;
    $row['status'] = (int) $opts['status'];
    $row['value'] = (int) $opts['value'];
    $row['user_id'] = (int) $opts['user_id'];
    if ($req->isAuthenticated() && $row['user_id'] < 1) {
      $row['user_id'] = $req->getUserId();
      try {
        $user = User::getInstance($row['user_id']);
        $user->setFlag(User::FLAG_INTENT);
      }
      catch (Exception $e) { $log->error($e, __METHOD__); }
    }
    $dbo->insert(self::TABLE, $row);
    if ($dbo->affectedRows() >= 1) {
      $meta = self::$type2meta[$type];
      if (!empty($meta)) {
        $item->incrementMeta($meta);
      }
      try {
        $item->onTrack($type, $opts);
      }
      catch (Exception $e) { $log->error($e, __METHOD__); }
    }
    return $affected;
  }

  public static function count($item, $type) {
    return (int) S('dbo')->fetchValue('SELECT COUNT(*)'
                                      .' FROM '.self::TABLE
                                      .' WHERE model_id='.$item->getModelId()
                                      .  ' AND record_id='.$item->getId()
                                      .  ' AND type='.$type);
  }

}