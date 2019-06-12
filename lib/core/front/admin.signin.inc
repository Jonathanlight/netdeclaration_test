<?php

try {

  $url = Admin::url();
  $uri = trim($_SERVER['SCRIPT_NAME'], '/');

  if ($uri != $url) {
    S('log')->trace('bad admin auth');
  }

  $req->getCookie()->setAttribute('admin_url', $url);

  $path = APP_PATH.'/'.P('app.extension').'/pix/admin.banner.png'; 

  $ctx->banner = false;
  if (file_exists($path)) {
    $ctx->banner = '/'.$path;
  }
  
  $ctx->auth_url  = '/back/core/home';
  $ctx->login = $req->login;

  $res->resetTemplates();
  $res->useTemplates('//admin.signin');

}
catch (Exception $e) { $err->add($e); }
