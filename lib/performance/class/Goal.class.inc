<?php

class Goal extends ActiveRecord {

  const TYPE_VISIT = 1;
  const TYPE_EVENT = 2;

  public static $types = array(self::TYPE_VISIT => 'visit',
                               self::TYPE_EVENT => 'event');

  protected function onBeforeCommit(&$hash) {
    if ($hash['type'] == self::TYPE_EVENT) {
      if (empty($hash['value'])) {
        throw new ActiveRecordException('valeur invalide');
      }
      $ret = preg_match($hash['value'], 'test');
      if ($ret === false) {
        throw new ActiveRecordException('valeur invalide');
      }
    }
  }

  public function destroy() {
    $this->setStatus(0);
    ConfigManager::DBCacheBuild();
  }

  protected function onAfterCommit($hash) {
    ConfigManager::DBCacheBuild();
  }

  /*  protected function onAfterDestroy($hash) {
    
  }*/

  public static function asCache() {
    $rs = S('dbo')->query('SELECT id, value'
                          .' FROM '.T('goal')
                          .' WHERE type='.self::TYPE_EVENT
                          .  ' AND status>0');
    $hash = array();
    foreach ($rs as $row) {
      $hash[$row['id']] = $row['value'];
    }
    return $hash;
  }

  public static function asHash() {
    return $GLOBALS['goals'];
  }

  public static function achieve($date) {
    $dbo = S('dbo');
    $rs = $dbo->query('SELECT *'
                       .' FROM '.T('goal')
                       .' WHERE status>0'
                       .  ' AND type='.self::TYPE_VISIT);
    if ($rs->isEmpty()) return ;
    $dbo->exec('DELETE FROM '.T('conversion')
               .    ' WHERE model_id='.Model::id('goal')
               .      ' AND record_id in ('.join(',', $rs->asSet('id')).')'
               .      ' AND DATE(created_at)="'.$date.'"');
    foreach ($rs as $row) {
      if ($row['value'] <= 0) continue ; 
      if ($row['code'] == 'visit.number') {
        $field = 'number';
        $ope = '=';
      }
      elseif ($row['code'] == 'visit.depth') {
        $field = 'depth';
        $ope = '>=';
      }
      elseif ($row['code'] == 'visit.duration') {
        $field = 'duration';
        $ope = '>=';
      }
      $fields = array('model_id' => Model::id('goal'),
                      'record_id' => $row['id'],
                      'user_id' => '`user_id`',
                      'visit_id' => '`id`',
                      'created_at' => '`created_at`');
      $dbo->exec('INSERT INTO '.T('conversion')
                 .  ' ('.join(',', array_keys($fields)).')'
                 .   ' SELECT '.join(',', $fields)
                 .     ' FROM '.Visit::TABLE
                 .    ' WHERE DATE(created_at)="'.$date.'"'
                 .      ' AND '.$field.$ope.$row['value']);
      $dbo->debug();
    }
  }
  
}