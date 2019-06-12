<?php

  // TODO : taille : db, session, var/users

try {

  if (!$admin->isSuperAdmin()) return ;

  $datas = array();
  $datas['name'] = $_SERVER['SERVER_NAME'];
  $datas['IP'] = $_SERVER['SERVER_ADDR'];
  $datas['load avg'] = join(' &middot; ', sys_getloadavg());
  $datas['web server'] = $_SERVER['SERVER_SOFTWARE'];
  $datas['PHP version'] = phpversion();
  $datas['MySQL version'] = S('dbo')->version();

  $ctx->datas = $datas;

  $res->useXml();

}
catch (Exception $e) { $err->add($e); }

