<?php

class Controller 
{ 
  public function __construct() { }

  public function exec() {

    $ctx = S('ctx');
    $dbo = S('dbo');
    $err = S('err');
    $log = S('log');
    $req = S('req');
    $res = S('res');

    if (!$req->isCli()) {
      try {
        $tracker = Tracker::getInstance(); 
        Platform::addSingleton('tracker', $tracker);        
      }
      catch (Exception $e) {}
    }

    if (($req->isFront() || $req->isAccount() || $req->isMiddle())) { 
      if (AuthManager::onStartUp() === false) return ;
      if ($req->isCached() && count($err) < 1) return ;
    }
     
    if ($req->isBack()) {
      $admin = S('admin');
      foreach ($req->getBranch() as $key => $value) {
        if ($ctx->hasAttribute($key)) continue ;
        $ctx->setAttribute($key, $value);
      }
      if ($req->hasAttribute('branches')) {
        foreach ($req->getAttribute('branches') as $key => $value) {
          if ($ctx->hasAttribute($key)) continue ;
          $ctx->setAttribute($key, $value);
        }
      }
      if ($ctx->getAttribute('_auth') == 1) {
        $admin->track(Intent::TYPE_AUTH);
      }
    }
    elseif ($req->isAccount()) {
      $user = $ctx->getAttribute('user');
    }
    elseif ($req->isMiddle()) {
      $ctx->setAttribute('_modules', P('middle.modules'));
      $user = $ctx->getAttribute('user');
      S('app')->hook('onMiddleStart');
    }

    $ctx->setAttribute('_scope', $req->scope());
    $ctx->setAttribute('_extension', $req->extension());
    $ctx->setAttribute('_action', $req->action());

    if (P('front.offline')
        && !S('req')->isCli()
        && !in_array($req->getClient('address'), P('front.allowed.ips'))
        && $req->action() != 'offline') {
      S('log')->trace($req->getClient('address'), 'Redirect offline');
      S('res')->sendRedirect('/offline');
      return;
    }

    include $req->getController();

    if ($req->isAccount()) {
      if (!$req->isXhr(Request::XHR_EXEC)) {
        if (($req->isXhr() || $req->isPhp())) {
          if($ctx->_keep_templates !== true) {
            $res->useTemplate();
          }
        }
        else {
          AccountManager::init();
          $res->setSeo($ctx->getAttribute('_title').' | '.ucfirst(P('app.label')));
          $template = P('account.template') ?: 'community:account';
          if ($err->count() >= 1) {
            $res->useTemplates($template);
          }
          else {
            if($ctx->_keep_templates !== true) {
              $res->useTemplates($template, true);
            }
          }
        }
      }
      if (!$req->isPhp()) {
        $req->track($req->action(), 'account');
      }
    }
    elseif ($req->isMiddle()) {
      $req->track($req->action(), 'middle');
    }

  } 

  public static function getInstance() { 
    $class = __CLASS__;
    return new $class; 
  }
  
}
