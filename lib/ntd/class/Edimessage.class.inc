<?php

class Edimessage extends ActiveRecord {

  protected function onAfterCommit($attrs) {
    if ($this->suivi_id < 1) {
      $this->setAttribute('suivi_id', Suivi::exists(array('ref_message' => $this->ref_message)));
    }
  }

}