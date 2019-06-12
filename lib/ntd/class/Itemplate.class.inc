<?php

class Itemplate extends ActiveRecord {

  public static $statuses = array(0 => 'hors ligne', 1 => 'en ligne');

  public function getIfields($opts = array()) {
    if (!isset($opts['order'])) {
      $opts['order'] = array('name' => 'ASC');
    }
    return $this->getFormulairetype()->getIfieldsByMillesime($this->millesime_id, array(), $opts['order']);
  }

  /* ----- Hooks ----- */

  protected function onBeforeCommit(&$attrs) {
    if ($attrs['psp']) {
      if (strpos($attrs['psp'], 'formulaire-page') < 1) {
        throw new Exception('Ce n\'est pas le format template');
      }
    }
    if ($attrs['html']) {
      if (strpos($attrs['html'], 'editor-page') < 1) {
        throw new Exception('Ce n\'est pas le format éditeur');
      }
    }
    if ($attrs['millesime_id'] > 0 && $this->millesime_id > 0 && $this->millesime_id != $attrs['millesime_id']) {
      $attrs['version'] = '0';
    }
  }

  protected function onAfterCommit($attrs) {
    if ($this->version < 1) {
      $sql = 'SELECT MAX(version)
                FROM #table_template
               WHERE formulairetype_id = :formulairetype_id:
                 AND millesime_id = :millesime_id:';
      $last_version = (int) S('dbo')->fetchValue($sql,
                                                 array('#table_template' => T('Itemplate'),
                                                       ':formulairetype_id:' => $this->formulairetype_id,
                                                       ':millesime_id:' => $this->millesime_id));
      $this->setAttribute('version', 1 + $last_version);
    }

    if ($this->status == 1) {
      S('dbo')->update(T('Itemplate'),
                       array('status' => 0),
                       array('filters' => array('|!=|id' => $this->getId(),
                                                'formulairetype_id' => $this->formulairetype_id,
                                                'millesime_id' => $this->millesime_id)));
      $path = $this->getTemplatePath();
      $folder_path = dirname($path);
      if (!Folder::exists($folder_path)) {
        Folder::create($folder_path, true);
      }
      file_put_contents($path, $this->psp);
    }
  }

  public function getCode() {
    return $this->getFormulairetype()->name . '#' . $this->getMillesime()->name . '#' . $this->version;
  }

  public function asHtml($ctx = true) {
    return H::inc($this->getTemplatePath(), $ctx);
  }


  public function getTemplatePath() {
    return 'app/declaration/templates/' . $this->getFormulairetype()->getDocumentCode()
        . '/' . $this->getFormulairetype()->code . '_' . $this->getMillesime()->getId() . '.psp';
  }

  protected function onBeforeDuplicate(&$commit) {
    $commit['version'] = 0;
    $commit['status'] = 0;
    $commit['name'] .= ' (dupliqué)';
  }

  public function asEditHash() {
    $hash = array();
    if ($this->isLoaded()) {
      S('ctx')->setAttribute('editor_url', H::url('/middle/core/editor',
                                                  array('itemplate_id' => $this->getId()),
                                                  array('app' => App::getInstance('xmiddle'))));
    }
    return $hash;
  }

  public function renderPsp() {
    $editor = FormEditor::getInstance($this);
    $render = $editor->renderTemplate();
    $this->setAttribute('psp', $render['psp']);
  }

  public function getDetails() {
    $hash = array();
    $hash['Type de formulaire'] = Item::edit($this->getFormulairetype());
    $hash['Fichier'] = $this->getTemplatePath();
    return $hash;
  }

}
