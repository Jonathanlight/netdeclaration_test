<?php

class Component extends ActiveRecord {

  protected function onAfterCommit($hash) {
    if (!isset($hash['position'])) return ;
    $n = $this->dbo->fetchValue('SELECT COUNT(id)'
                                .' FROM '.T('component')
                                .' WHERE position='.$this->position
                                .  ' AND faq_id='.$this->faq_id
                                .' GROUP BY position');
    if ($n <= 1) return ;
    $this->dbo->exec('UPDATE '.T('component')
                     .' SET position=position+1'
                     .' WHERE id<>'.$this->getId()
                     .  ' AND faq_id='.$this->faq_id
                     .  ' AND position>='.$this->position);
  }

  public function getLocale() {
    return $this->getFaq()->getLocale();
  }

}