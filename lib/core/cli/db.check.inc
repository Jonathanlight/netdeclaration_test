<?php

try {

  if (System::getOsType() === 'osx') {
    $password = '';
  }
  else {
    $password = Shell::prompt('Password mysql root ?');
  }
 
  $db = new DataBaseObject(array('login' => 'root', 
                                 'password' => $password, 
                                 'name' => 'mysql')); 
  
  $n = $db->fetchValue('SELECT COUNT(*)'
                       .' FROM db'
                       .' WHERE User=:user:'
                       .  ' AND Db=:db:', 
                       array(':user:' => DB_LOGIN, 
                             ':db:' => DB_NAME));
  
  if ($n < 1 && Shell::confirm('Insert ['.DB_NAME.'] into table <mysql.db> ?')) {
    $table = $db->getTable('db');
    $fields = $table->getFields();
    $row = array();
    foreach ($fields as $field) {
      $row[$field] = 'Y';
    }
    $row['Host'] = 'localhost';
    $row['Db'] = DB_NAME;
    $row['User'] = DB_LOGIN;
    $cols = array('Grant_priv', 'Create_view_priv', 
                  'Create_routine_priv', 'Alter_routine_priv',
                  'Execute_priv');
    foreach ($cols as $col) {
      if (!in_array($col, $fields)) continue ;
      $row[$col] = 'N';
    }
    $db->insert('db', $row);
  }
  
  $n = $db->fetchValue('SELECT COUNT(*) FROM user WHERE User=:user:', 
                       array(':user:' => DB_LOGIN));
  
  if ($n < 1 && Shell::confirm('Insert ['.DB_LOGIN.'] into table <mysql.user> ?')) {
    $db->exec('INSERT INTO user (Host, User, Password)'
              .        ' VALUES ("localhost", :user:, password(:password:))',
              array(':user:' => DB_LOGIN, 
                    ':password:' => DB_PASSWORD));
  }
  
  $db->exec('flush privileges');

}
catch (Exception $e) { $err->add($e); }
