<?php

try {

  $user_id = (int) $req->id;

  $rs = $dbo->query('SELECT *'
                    .' FROM '.ACL::TABLE
                    .' WHERE user_id='.$user_id
                    .' ORDER BY created_at DESC');

  $items = array();

  foreach ($rs as $row) {
    try {
      $items[$row['created_at']] = Item::getInstance($row['model_id'],
                                                     $row['record_id'],
                                                     array('ignore' => true));
    }
    catch (Exception $e) {
      /*      $dbo->exec('DELETE FROM '.ACL::TABLE
                 .' WHERE user_id='.$user_id
                 .' AND model_id='.$row['model_id']
                 .' AND record_id='.$row['record_id']
                 .' LIMIT 1'); */
      $log->error('item unknown ['.$row['model_id'].':'.$row['record_id'].']');
    }
  }

  $ctx->items = $items;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
