<?php

try {

  $params = $req->getAttributes(); 
  $params['limit'] = -1;
  $finder = Finder::getInstance($params);
  $sql = $finder->getCollection()->asSql();

  if ($req->direction == 'prev') {
    $operator = '>';
    $order = 'ASC';
  }
  else {
    $operator = '<';
    $order = 'DESC';
  }

  $id = (int) $dbo->fetchValue('SELECT t.id'
                               .' FROM ('.$sql.') AS t'
                               .' WHERE t.id '.$operator.' '.$req->id
                               .' ORDER BY t.id '.$order
                               .' LIMIT 1');

  $ctx->sibling_id = $id;

}
catch (Exception $e) { $err->add($e); }
