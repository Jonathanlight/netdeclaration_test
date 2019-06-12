<?php

class Greffedossier extends ActiveRecord {

  const STATUS_PENDING = 0;
  const STATUS_CLOSED = 1;

  public static $statuses = array(
    self::STATUS_PENDING => 'En cours',
    self::STATUS_CLOSED  => 'Clôturé'
  );


  protected function onAfterCommit($hash) {
    if (empty($this->name)) {
      $this->setAttribute('name', 'Dossier #'.$this->getId());
    }
  }


  /** KWO **/

  public function asRelationRow($relation, $row) {
    $name = $relation->getName();

    if ($relation instanceof Greffe) {
      $name = 'Ref: '.$relation->getId().' - '.c(H::datenice($relation->getMeta('created_at')));
    }
    return $name;
  }

  public function asFinderHash($hash) {
    if ($this->status == self::STATUS_PENDING) {
      $hash['_color'] = 'orange';
    }
    else if ($this->status < self::STATUS_PENDING) {
      $hash['_color'] = 'red';
    }
    else {
      $hash['_color'] = 'green';
    }
    return $hash;
  }
}
