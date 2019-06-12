<?php

class NtdMiddleManager {

  const MODULE_HOME = 'home';
  const MODULE_SERVICE = 'service';
  const MODULE_FACTURE = 'facture';
  const MODULE_SUIVI = 'suivi';
  const MODULE_DECLARATION = 'declaration';
  const MODULE_ADHERENT = 'adherent';
  const MODULE_IBAN_SECONDARY = 'iban.secondary';
  const MODULE_IBAN_PRIMARY = 'iban.primary';
  const MODULE_DEVIS = 'devis';
  const MODULE_GREFFE = 'greffe';

  public static $modules = array(
    self::MODULE_HOME => array('url' => 'home',
                               'title' => 'Tableau de bord'),
    self::MODULE_DECLARATION => array('url' => 'declarations',
                                      'title' => 'Déclarations'),
    self::MODULE_SUIVI => array('url' => 'suivi',
                                'title' => 'Télétransmissions',
                                'actions' => array('suivi')),
    self::MODULE_SERVICE => array('url' => 'services',
                                  'title' => 'Services'),
    self::MODULE_FACTURE => array('url' => 'factures',
                                  'title' => 'Factures'),
    self::MODULE_ADHERENT => array('url' => 'adherent',
                                   'title' => 'Coordonnées'),
    self::MODULE_IBAN_SECONDARY => array('url' => 'ibans',
                                         'title' => 'IBANS - Impôts'),
    self::MODULE_DEVIS => array('url' => 'devis',
                                'title' => 'Devis'),
    self::MODULE_GREFFE => array('url' => 'greffe',
                                'title' => 'Greffe'),
    /*self::MODULE_IBAN_PRIMARY => array('url' => 'iban.primary',
                                       'title' => 'IBAN (NTD)'),*/
  );

  public static $pages = array(
    'account.nos-videos',
    'account.partenaire.oga',
    'account.partenaire.bnf',
    'account.partenaire.urssaf',
    'account.partenaire.irc',
    'account.transfert.teleprocedures'
  );

  private static $current_module_code = null;

  public static function getCurrentModule($attr = null) {
    $current_module = self::$modules[self::$current_module_code];
    if ($attr !== null) {
      if ($attr == 'code') return self::$current_module_code;
      return $current_module[$attr];
    }
    return $current_module;
  }

  public static function setCurrentModule($module_code) {
    if (!isset(self::$modules[$module_code])) {
      throw new Exception('module does not exists');
    }
    self::$current_module_code = $module_code;
  }

  public static function isModuleAllowed($module_code){
    if($module_code == self::MODULE_DEVIS) {
      return S('req')->getUser()->hasFlag(User::FLAG_ACCESS_MODULE_DEVIS);
    }

    return true;
  }

  public static function onMiddleStart() {
    $module_snippet = self::getPageSnippet();
    if ($module_snippet) {
      self::setPageTitle($module_snippet->getProperty('title'));
      S('ctx')->_skeleton_middle_description = $module_snippet->getProperty('content');
    }
  }

  public static function setBreadCrumb($breadcrumb = true) {
    $breadcrumb = (array) $breadcrumb;
    if ($breadcrumb[0] === true) { // only for root module
      unset($breadcrumb[0]);
      $breadcrumb = array_reverse($breadcrumb, true);
      $breadcrumb[self::getPageSnippet(self::getCurrentModule('url'))->getProperty('title')] = self::getCurrentModule('url');
      $breadcrumb = array_reverse($breadcrumb, true);
    }
    S('res')->setBreadcrumb(array_merge(array('Accueil' => '/',
                                              'Espace Adhérent' => '/middle'),
                                        $breadcrumb));
  }

  public static function useTemplate($include_skeleton = true) {
    $template = S('req')->action();
    $templates = array(null);
    if ($include_skeleton) {
      $templates[] = 'skeleton.front';
      $templates[] = 'skeleton.middle';
    }
    $templates[] = 'app/ntd/templates/middle/' . $template . '.psp';
    S('res')->useTemplates($templates);
  }

  public static function getPageSnippet($action = null) {
    $action = $action ?: S('req')->action();
    $snippet_code = 'middle.page.' . $action;
    if (!Snippet::exists($snippet_code)) {
      return null;
    }
    return Snippet::getInstance($snippet_code);
  }


  public static function setPageTitle($title) {
    S('ctx')->_skeleton_middle_title = $title;
  }

  public static function setSEO($title = null) {
    if (!$title) {
      $snippet = self::getPageSnippet();
      if ($snippet) {
        $title = $snippet->getProperty('title');
      }
    }
    S('res')->setSeo(array('title' => S('ctx')->_current_adherent->company . ' - ' . $title));
  }

  public static function getNavPages() {
    return Page::collect(array('filters' => array('|IN|code' => self::$pages),
                               'order' => array('name' => 'ASC')));
  }


  // ----- ACTIONS Specific
  public static function actionDeclarerURL($opts) {
    $url = '/middle/declarer';
    if ($opts['service_id']) {
      $url .= '?service_id=' . $opts['service_id'];
    }
    return $url;
  }

  public static function actionPaiementURL($facture_id) {
    return '/middle/payment/-/facture_id/' . $facture_id;
  }


}
