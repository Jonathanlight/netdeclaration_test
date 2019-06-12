<?php

class Faq extends ActiveRecord {

  const FLAG_CONTACT = 1;

  protected function onAfterCommit($hash) {
    if (!isset($hash['position'])) return ;
    $n = $this->dbo->fetchValue('SELECT COUNT(id)'
                                .' FROM '.T('faq')
                                .' WHERE position='.$this->position
                                .' GROUP BY position');
    if ($n <= 1) return ;
    $this->dbo->exec('UPDATE '.T('faq')
                     .' SET position=position+1'
                     .' WHERE id<>'.$this->getId()
                     .  ' AND position>='.$this->position);
  }

  public static $flags = array(self::FLAG_CONTACT => 'dans contact');

}