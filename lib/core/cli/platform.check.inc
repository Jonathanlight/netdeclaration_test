<?php

/*
- mod_rewrite : apache_get_modules()
- droits d'execution à comparer avec var : get_current_user() 
- version apache : apache_get_version()
- version php
- répertoires session 
- bon fonctionnement de la basse de données
*/

try {

  $required_extensions = array('calendar', 'curl', 'date', 'dom', 'gd', 'hash',
                               'json', 'mbstring', 'mysql', 'openssl', 
                               'SimpleXML', 'SQLite', 
                               'tidy', 'zip', 'zlib');

  $diff = array_diff($required_extensions, get_loaded_extensions());
  if (count($diff) >= 1) {
    throw new Exception('extensions ['.join(', ', $diff).'] not found');
  }

  if (extension_loaded('gettext')) {
    throw new Exception('extension [gettext] must not be loaded');
  }

  if (!file_exists(Session::PATH)) {
    throw new Exception(Session::PATH.' not found');
  }
  
  $url = H::url('/core/server.ping');
  
  $str = file_get_contents($url);
  
  print_r(unserialize($str));

}
catch (Exception $e) {
  $res->write($e->getMessage());
}