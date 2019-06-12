<?php

class Snippet extends ActiveRecord 
{
  public function onAfterStore() {
    $this->syncAttributes();
  }

  public function syncAttributes() {
    $locales = array();
    $rs = $this->dbo->query('SELECT value, locale'.
                            ' FROM '.Item::TABLE_PROPERTY
                            .' WHERE model_id='.$this->getModelId()
                            .  ' AND record_id='.$this->getId()
                            .' ORDER BY locale ASC');
    $cache = '';
    foreach ($rs as $row) {
      if (empty($row['value'])) continue ;
      $cache .= $row['value']."\n";
      if (!in_array($row['locale'], $locales)) $locales[] = $row['locale'];
    }
    $attrs = array('cache' => $cache,
                   'locales' => array_sum($locales));
    $this->setAttributes($attrs);    
  }

  protected function onBeforeCommit(&$attrs) {
    if (isset($attrs['code'])) {
      $attrs['name'] = $attrs['code'];
    }
  }

  public static function extensions() {
    $rs = S('dbo')->query('SELECT DISTINCT extension_id'
                          .         ' FROM '.T('snippet'));
    $hash = array();
    foreach ($rs as $row) {
      $extension_id = $row['extension_id'];
      $hash[$extension_id] = Extension::name($extension_id);
    }
    asort($hash);
    return $hash;
  }

  public function getName($locale=null) {
    return $this->code;
  }

  public function getTitle($bindings=null) {
    return $this->content($bindings, 'title');
  }

  public static function get($code) {
    return Snippet::getInstance($code,
                                array('properties' => array('title', 
                                                            'content')));
  }

  public static function content($code, $bindings=null, $property='content') {
    $locale = S('res')->getLocale();
    $msg = null;
    try {
      $snippet = Snippet::getInstance($code, array('ignore' => true));
      $msg = $snippet->getProperty($property, $locale);
    }
    catch (Exception $e) {  }
    if ($msg === false || $msg === null) {
      S('log')->error('snippet ['.$code.'] ('.$locale.')', __METHOD__);
      return $code;
    }
    $patterns = array();
    $bindings = (array) $bindings;
    foreach ($bindings as $key => $value) {
      $patterns[] = '(('.$key.'))';
    }
    $msg = str_replace($patterns, $bindings, $msg);
    return $msg;
  }

  public function asView($view) {
    $icon_view = '<img src="/app/core/pix/action/view.png" style="margin-right: 5px; vertical-align: text-bottom;" /> ';
    if ($this->code == HomepageHelper::SNIPPET_SERVICES_CODE) {
      return $icon_view . 'Fragment "Tous nos services"';
    }
    elseif ($this->code == HomepageHelper::SNIPPET_INTRODUCTION_CODE) {
      return $icon_view . 'Fragment "Vous êtes ...';
    }
    elseif ($this->code == HomepageHelper::SNIPPET_PARTENAIRES_CODE) {
      return $icon_view . 'Fragment "Partenaires"';
    }
    elseif ($this->code == HomepageHelper::SNIPPET_PAIEMENT_CODE) {
      return $icon_view . 'Fragment "Paiement"';
    }
    elseif ($this->code == HomepageHelper::SNIPPET_FORWHO_CODE) {
      return $icon_view . 'Fragment "Pour qui"';
    }
    return parent::asView($view);
  }

}