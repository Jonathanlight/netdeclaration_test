<?php

class NetDeclaration {

  const HEADING_EZINE_CODE = 'ntd.articles';
  const COOKIE_FLASHINFO = 'flashinfo';
  const SNIPPET_FLASHINFO = 'flashinfo';
  const SNIPPET_FLASHINFO_DOMTOM = 'flashinfo.domtom';

  const NEWSLETTER_BASE_PUBLIC = 'ntd.public';
  const NEWSLETTER_BASE_CEC = 'ntd.cec';
  const NEWSLETTER_BASE_ENTREPRISE = 'ntd.entreprise';
  const NEWSLETTER_BASE_OGA = 'ntd.oga';
  const NEWSLETTER_BASE_PRO_SANTE = 'ntd.pro_sante';
  const NEWSLETTER_BASE_INTERNATIONNAL = 'ntd.internationnal';

  public static $newsletter_bases = array(
    self::NEWSLETTER_BASE_PUBLIC         => 'Netdeclaration',
    self::NEWSLETTER_BASE_CEC            => 'Cabinet Expert-Comptable & Avocat',
    self::NEWSLETTER_BASE_ENTREPRISE     => 'Entreprise',
    self::NEWSLETTER_BASE_OGA            => 'Organisme de Gestion Agréé',
    self::NEWSLETTER_BASE_PRO_SANTE      => 'Professionnel de la santé',
    self::NEWSLETTER_BASE_INTERNATIONNAL => 'International'
  );

  // ----- FlashInfo Manager
  public static function flashInfoClose() {
    $cookie = S('req')->getCookie();
    $cookie->setAttribute(self::COOKIE_FLASHINFO, Date::now());
  }

  public static function getSnippetFlashInfo($force = false) {
    $code = NetDeclarationManager::isDomtom() ? self::SNIPPET_FLASHINFO_DOMTOM : self::SNIPPET_FLASHINFO;
    if(!Snippet::exists($code)) {
      return null;
    }
    $snippet = Snippet::getInstance($code);
    if (!$force) {
      $cookie = S('req')->getCookie();
      $close_at = $cookie->getAttribute(self::COOKIE_FLASHINFO);
      if (strtotime($close_at) > strtotime($snippet->getMeta('updated_at'))) {
        return null;
      }
    }
    return $snippet;
  }


  // ----- Trees Manager
  public static function getTreeContent() {
    return self::getTree('ntd.content.'.I18n::$locales[S('req')->getLocale()]);
  }

  public static function getTreeFooter() {
    return self::getTree('ntd.footer.'.I18n::$locales[S('req')->getLocale()]);
  }

  public static function getTreeHeader() {
    return self::getTree('ntd.header.'.I18n::$locales[S('req')->getLocale()]);
  }

  public static function getTree($tree_id) {
    $stg = S('stg');
    try {
      $tree = $stg->get('tree.' . $tree_id);
      if (!$tree) $tree = self::onBuild(Tree::getInstance($tree_id));
      return $tree;
    } catch (Exception $e) {
      S('err')->add($e);
      return array();
    }
  }

  public static function onBuild($tree) {
    $stg = S('stg');

    $pointers = $struct = array();
    $rs = S('dbo')->query('SELECT LEFT(path, LENGTH(path) - 2) AS P,'
        . ' ' . T('node') . '.*'
        . ' FROM ' . T('node')
        . ' WHERE tree_id=' . $tree->getId()
        . ' ORDER BY P, position');
    foreach ($rs as $node) {
      if (($node['flags'] & Node::FLAG_NODE_OFFLINE) > 0) continue;
      $n = array('node' => $node,
                 'item' => null,
                 'children' => null);
      if ($node['model_id'] >= 1 && $node['record_id'] >= 1) {
        try {
          $item = Item::getInstance($node['model_id'], $node['record_id']);
          $n['item']['url'] = $item->asUrl();
          $n['item']['key'] = $item->getKey();
        }
        catch (Exception $e) {
          S('log')->error($e, __METHOD__);
        }
      }
      $n['item']['url'] = empty($n['item']['url']) ? $n['node']['url'] : $n['item']['url'];

      if ($node['ancestor_id'] < 1) {
        $struct[$node['path']] = $n;
        $pointers[$node['path']] = &$struct[$node['path']];
        continue;
      }
      $path = substr($node['path'], 0, -2);
      if ($pointers[$path]) {
        $pointers[$path]['children'][$node['path']] = $n;
        $pointers[$node['path']] = &$pointers[$path]['children'][$node['path']];
      }
    }
    $stg->set('tree.' . $tree->code, $struct, true);
    return $struct;
  }


  public static function getActualites($opts = array()) {
    $opts['order']['published_at'] = 'desc';
    $opts['include'][] = 'heading';
    $opts['filters']['sys_heading.code'] = self::HEADING_EZINE_CODE;
    $articles = Article::collect($opts);
    return $articles;
  }

  public static function asShellParams($params) {
    $str = null;
    foreach ($params as $key => $value) {
      $str .= ' '.(is_int($key) ? '' : $key.' ').$value;
    }
    return $str;
  }

  public static function getFlashInfos() {
    $opts = array();
    $opts['filters']['is_flash_infos'] = 1;
    return self::getActualites($opts);
  }

  public static function getAccountMenu($action, $menu, $selected_menu) {
    if (strpos($action, 'account.page') !== false) {
      $menu = array();
    }
    return array($menu, $selected_menu);
  }

  public static function setCurrentAdherent($adherent_id){
    $cookie = S('req')->getCookie();
    $cookie->setAttribute('current_adherent_id' ,$adherent_id);
  }

  public static function getCurrentAdherent() {
    $cookie = S('req')->getCookie();
    $adherent_id = (int) $cookie->getAttribute('current_adherent_id');
    if ($adherent_id > 0) {
      $adherent_args = array('user_id' => S('req')->getUser()->getId(),
                             'id' => $adherent_id);
      if (Adherent::exists($adherent_args)) {
        return Adherent::getInstance($adherent_args);
      }
    }
    return Adherent::getCurrentPrimaryAdherent();
  }

  public static function getMailFooter(){
    return l('snippet:letter.footer');
  }
  public static function getMailAdmin(){
    return P('app.domain') == 'dev.ntd-dev.li.kernix.net' ? 'shumbert@kernix.com' : 'direction@netdeclaration.net';
  }

  public static function getNewsletterBases() {
    $filters = array(
      '|IN|code' => array_keys(self::$newsletter_bases)
    );
    return Base::collect(array('filters' => $filters));
  }

  // ----- Helpers
  public static function datetime($date) {
    if (strlen($date) < 6 || substr($date, 0, 4) === '0000') return '';
    $hash = Date::asHash($date);
    $html = 'le ' . $hash['day'] . '/' . $hash['month'] . '/' . $hash['year'] . ' à ' . $hash['hour'] . ':' . $hash['min'];
    return $html;
  }

  public static function isMetropoleIP($ip) {
    $sql = ' SELECT id'
          .' FROM ntd_metropole_ip'
          .' WHERE from_ip <= '.$ip
          .' AND to_ip >= '.$ip;
    $is_metropole = S('dbo')->fetchValue($sql) > 0;
    return $is_metropole;
  }

}
