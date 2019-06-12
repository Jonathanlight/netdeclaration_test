<?php

try {
  
  $res->write("\n".'Kwo Instance Factory : '."\n\n");

  $root_password = Shell::prompt(' + Password mysql root ?');
  $dbm = new DataBaseObject(array('login' => 'root', 
                                  'password' => $root_password, 
                                  'name' => 'mysql'));
  //  $dbm = new DataBaseObject(DB_SERVER, 'root', $root_password, 'mysql');
  $dbm->query('SELECT * FROM user LIMIT 1');

  $project = Shell::prompt(' + Project ?');
  if (strlen($project) < 3 || strlen($project) > 11 || 
      !Valid::isAlphanum($project, true)) {
    throw new Exception('invalid name ['.$project.'] (alplanum only, length between 3 and 11)');
  }
  if (file_exists('/var/web/'.$project)) {
    throw new Exception('directory exists [/var/web/'.$project.']');
  }
  if (file_exists('/etc/kernix/http/'.$project.'.conf')) {
    throw new Exception('virtualhost exists [/etc/kernix/http/'.$project.'.conf]'); 
  }

  $host = 'www.'.$project.'.pulsar';

  $db_name = Shell::prompt(' + DB name ?', $project);
  if (strlen($db_name) < 3 || strlen($db_name) > 11 || !Valid::isAlphanum($db_name, true)) {
    throw new Exception('invalid name ['.$db_name.'] (alphanum only, length between 3 and 11)');
  }
  if (file_exists('/var/lib/mysql/'.$db_name)) {
    throw new Exception('db exists [/var/lib/mysql/'.$db_name.']');
  }

  $rs = $dbm->query('SELECT Host FROM user WHERE User=:name:', array(':name:' => $db_name));
  if ($rs->foundRows() >= 1) throw new Exception('User ['.$db_name.'] exists in mysql:user');

  $rs = $dbm->query('SELECT Host FROM db WHERE Db=:name:', array(':name:' => $db_name));
  if ($rs->foundRows() >= 1) throw new Exception('Db ['.$db_name.'] exists in mysql:db');

  $db_password = Shell::prompt(' + DB password ?', String::password());

  do {
    $conf = Shell::prompt(' + App ?', $project.'.conf.inc');
    $conf = strpos($conf, '.') === false ? $conf.'.conf.inc' : $conf;
  } 
  while (!is_file('etc/applications/'.$conf));

  list ($app, ) = explode('.', $conf);

  $app = App::asHash($app);

  $path = '/var/web/'.$project;

  $res->write("\n".'Details : '."\n\n");
  $res->write(' - project : '.$project."\n");
  $res->write(' - path : '.$path."\n");
  $res->write(' - host : '.$host."\n");
  $res->write(' - app : '.$conf."\n");
  $res->write(' - db_name : '.$db_name."\n");
  $res->write(' - db_password : '.$db_password."\n");

  $db_user = $db_name;

  if (!Shell::confirm("\n".'Continue', true)) return ;

  $dbo->ping();
  $dbm->ping();

  $res->write("\n");

  try {
    $dbm->flush();
  }
  catch (Exception $e) { $log->error($e); }

  system('cp -a /var/web/kwo '.$path);
  if (!is_dir($path)) throw new Exception('copy failed');
  notify('copy tree');

  $ret = $dbm->exec("INSERT INTO db"
                    .   " VALUES ('localhost', '".$db_name."', '".$db_user."',"
                    .           " 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y',"
                    .           " 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y')");
  if ($ret === false) throw new Exception('can not insert into mysql:db');
  
  $ret = $dbm->exec("INSERT INTO user (Host, User, Password)"
                    .   " VALUES ('localhost', '".$db_name."', password('".$db_password."'))");
  if ($ret === false) throw new Exception('can not insert into mysql:user');

  $dbm->exec('flush privileges');

  system('ln -s '.$path.'/mysql /var/lib/mysql/'.$db_name);
  system('replace -s kwo '.$project.' dbpassword '.$db_password
         .' -- '.$path.'/'.Platform::BOOTSTRAP);
  notify('db setup');

  $dbr = new DataBaseObject(array('login' => 'root', 
                                  'password' => $root_password, 
                                  'name' => $db_name));

  $dbr->exec('DELETE FROM '.T('string')
             .    ' WHERE app<>""'
             .      ' AND app<>"'.$app['app.name'].'"');
  notify('string cleaning'); 

  system('replace -s "ServerAlias       *.kwo" "" www.test.kwo '.$host.' kwo '.$project
         .' -- '.$path.'/'.ETC_PATH.'/virtualhost.conf');
  system('ln -s '.$path.'/'.ETC_PATH.'/virtualhost.conf'
         .     ' /etc/kernix/http/'.$project.'.conf');
  notify('virtualhost setup');
    
  foreach (glob($path.'/'.ETC_PATH.'/applications/*.conf.inc') as $file) {
    if (basename($file) != $conf) unlink($file);
  }
  notify('app conf cleaning');
  
  system('replace -s .kwo .pulsar'
         .' -- '.$path.'/'.ETC_PATH.'/applications/'.$conf);
  notify('app conf setup');

  if (is_dir($path.'/'.DOC_PATH.'/.trash')) {
    system('rm -r '.$path.'/'.DOC_PATH.'/.trash');
  }
  foreach (glob($path.'/'.DOC_PATH.'/*') as $file) {
    if (basename($file) === $project) continue ;
    system('rm -r '.$file);
  }
  notify('doc cleaning');

  remote_exec($path, 'build');
  notify('build');

  remote_exec($path, 'var.clean');
  notify('var clean');

  if (is_dir($path.'/usr')) {
    system('rm -r '.$path.'/usr/*');
    notify('usr remove');
  }

  if (is_dir($path.'/tmp')) {
    system('rm -r '.$path.'/tmp');
    notify('tmp remove');
  }

  if (is_dir($path.'/pub')) {
    system('rm -r '.$path.'/pub');
    notify('pub remove');
    system('mkdir -p '.$path.'/pub/tmp');
    system('chown -R apache:apache '.$path.'/pub/tmp');
    notify('pub/tmp creation');
  }

  remote_exec($path, 'build');
  notify('build');

  remote_exec($path, 'item.clean',
              array('full' => 'yes'));
  notify('item clean');
  
  $included_extensions = array();

  foreach (Extension::all() as $name => $extension) {
    if (is_dir($path.'/'.LIB_PATH.'/'.$name.'/infos')) {
      system('rm -r '.$path.'/'.LIB_PATH.'/'.$name.'/infos');
    }
    if (in_array($name, array('tracker', 'comment', CORE, 'file', 'abuse'))) {
      remote_exec($path, 'extension.reset', 
                  array('name' => $name));
      continue ;
    }
    if (in_array($name, array('test', 'answer', 'calendar'))) {
      remote_exec($path, 'extension.uninstall', 
                  array('name' => $name, 
                        'confirm' => 'no'));
      remote_exec($path, 'build');
      continue ;
    }
    $res->write("\n".'[ Extension <'.$name.'> ]'."\n");
    if (Shell::confirm('. Install', true)) {
      $included_extensions[] = $name;
      remote_exec($path, 'extension.install', array('name' => $name));
      if (Shell::confirm('. Reset')) {
        remote_exec($path, 'extension.reset', array('name' => $name));
      }
    }
    else {
      remote_exec($path, 'extension.uninstall', 
                  array('name' => $name,
                        'confirm' => 'no'));
    }
    remote_exec($path, 'build');
  }

  $res->write("\n");

  foreach ($dbr->getTables('knx') as $table) {
    $table->drop();
  }
  $dbr->resetTables();

  foreach ($dbr->getTables() as $table) {
    try {
      $table->repair()->optimize();
    }
    catch (Exception $e) { $log->error($e); }
  }

  $tables = array(Intent::TABLE, Suggestion::TABLE_HIT,
                  Item::TABLE_LOG, Item::TABLE_PING, Item::TABLE_REVISION,
                  Captcha::TABLE, 
                  T('search'), Search::TABLE_HIT, Search::TABLE_HOP,
                  T('task'), T('url'),
                  Smtp::TABLE);
  foreach ($tables as $table) {
    if (!$dbr->hasTable($table, false)) continue ;
    $dbr->getTable($table)->truncate();
  }

  notify('table cleaning');

  remote_exec($path, 'build');
  notify('build');

  $res->write("\n");

  system('service httpd graceful');

  $res->write("\n");

}
catch (Exception $e) {
  $res->write("\n\n".$e->getMessage()."\n\n");
}

function notify($str) {
  S('res')->write(' # '.str_pad($str.' ', 32, '.').' OK'."\n");
}

function remote_exec($path, $str, $args=array()) {
  if (strlen($path) < 8) throw new Exception('bad path');
  system('cd '.$path.' && php '.Platform::BOOTSTRAP.' log.trace message="'.$str.' '.json_encode($args).'"');
  $cmd = 'cd '.$path.' && php '.Platform::BOOTSTRAP.' '.$str;
  foreach ($args as $key => $value) {
    $cmd .= ' '.$key.'='.$value;
  }
  system($cmd);
}