<?php

function uid2name($uid) {
  $hash = posix_getpwuid($uid);
  return $hash['name'];
}

if (!Net::isPrivateAddress($_SERVER['REMOTE_ADDR'])) {
  S('log')->error($_SERVER['REMOTE_ADDR']);
  return ;
}

$res->resetTemplates();

$hash = array('server_version' => apache_get_version(),
              'server_user_name' => get_current_user(),
              'server_user_id' => getmyuid(),
              'var_user_name' => uid2name(fileowner(DOC_PATH)),
              'var_user_id' => fileowner(DOC_PATH),
              'php_version' => phpversion(),
              'php_display_errors' => ini_get('display_errors'),
              'php_register_globals' => ini_get('register_globals'),
              'php_safe_mode' => ini_get('safe_mode'),
              'php_magic_quotes_gpc' => get_magic_quotes_gpc(),
              'php_magic_quotes_runtime' => get_magic_quotes_runtime());

$res->write(serialize($hash));