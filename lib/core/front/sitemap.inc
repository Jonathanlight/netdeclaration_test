<?php

try {

  $res->setContentType('xml');

  if ($res->isCached()) return ;

  $file = basename($req->getPath(), '.xml');

  list (, $type) = explode('-', $file); 

  $set = array();
  if (S('app')->hasManager()) {
    if (method_exists(S('app')->getManager(), 'sitemap')) {
      $sitemap = call_user_func(array(S('app')->getManager(), 'sitemap'), $type);
      $res->write($sitemap);
    }
  }
  
}
catch (Exception $e) { $err->add($e); }
