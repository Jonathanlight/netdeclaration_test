<?php

class NtdAccountManager {

  const MODULE_PASSWORD = 'password';
  const MODULE_EMAIL = 'email';
  const MODULE_ADHERENTS = 'adherents';
  const MODULE_NEWSLETTERS = 'newsletters';
  const MODULE_RESILIATION = 'resiliation';

  public static $modules = array(
    self::MODULE_EMAIL => array('url' => 'email'),
    self::MODULE_PASSWORD => array('url' => 'password'),
    self::MODULE_ADHERENTS => array('url' => 'adherents'),
    self::MODULE_NEWSLETTERS => array('url' => 'newsletters'),
    self::MODULE_RESILIATION => array('url' => 'resiliate.form'),
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


  public static function onAccountStart() { }

  public static function setBreadCrumb($breadcrumb = true) {
    $breadcrumb = (array) $breadcrumb;
    if ($breadcrumb[0] === true) { // only for root module
      unset($breadcrumb[0]);
      $breadcrumb = array_reverse($breadcrumb, true);
      $breadcrumb[self::getPageSnippet(self::getCurrentModule('url'))->getProperty('title')] = self::getCurrentModule('url');
      $breadcrumb = array_reverse($breadcrumb, true);
    }
    S('res')->setBreadcrumb(array_merge(array('Accueil' => '/',
                                              'Mon Compte' => '/account'),
                                        $breadcrumb));
  }

  public static function useTemplate($include_skeleton = true) {
    $template = S('req')->action();
    $templates = array(null);
    if ($include_skeleton) {
      $templates[] = 'skeleton.front';
      $templates[] = 'skeleton.account';
    }
    $templates[] = 'app/ntd/templates/account/' . $template . '.psp';
    S('res')->useTemplates($templates);
    S('ctx')->_keep_templates = true;
  }

  public static function getPageSnippet($action = null) {
    $action = $action ? : S('req')->action();
    return Snippet::exists('account.page.' . $action) ? Snippet::getInstance('account.page.' . $action): null;
  }

}
