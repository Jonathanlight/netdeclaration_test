<?php

$directories = array(APP_PATH, DOC_PATH, ETC_PATH,
                     LIB_PATH, PUB_PATH, USR_PATH);

$user = 'apache';

try {

  if (!Shell::confirm('Change owner to <'.$user.'>')) return ;

  if (posix_getpwnam($user) === false) {
    throw new Exception('user unknown');
  }

  Shell::exec('chown -Rv '.$user.': '.join(' ', $directories));

  if (is_dir('mysql')) {
    $user = 'mysql';
    Shell::exec('chown -Rv '.$user.': mysql');
  }

}
catch (Exception $e) { $err->add($e); }