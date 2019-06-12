<?php

class Policy extends ActiveRecord {

  protected function onBeforeDestroy() {
    if ($this->getAdmins()->numRows() >= 1) {
      throw new ActiveRecordException('Opération impossible, certains administrateurs sont associés à ce groupe.');
    }
  }

  protected function onBeforeCommit(&$hash) {
    if (is_array($hash['extensions'])) {
      $hash['extensions'] = join(',', $hash['extensions']);
    }
    if (isset($hash['actions'])) {
      $hash['actions'] = join(',', $hash['actions']);
    }
  }

  public function getActions() {
    $actions = array();
    if ($this->getId() == 1) return $actions;
    foreach (Extension::all() as $name => $extension) {
      if (!is_array($extension['back']) || count($extension['back']) === 0) continue ;
      foreach ($extension['back'] as $label => $url) {
        list ($url, ) = explode('?', $url);
        if (strpos($url, '/') === false) {
          $url = '/back/'.$name.'/'.$url;
        }
        //        error_log($url);
        $actions[$url] = '<strong>'.$name.'</strong> &gt; '.$label;
      }
    }
    return $actions;
  }

  public function hasNoAction() {
    return strlen($this->actions) < 3;
  }

}