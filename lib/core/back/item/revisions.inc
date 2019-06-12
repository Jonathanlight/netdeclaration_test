<?php

try {

  $item = Item::getInstance(MODEL, (int) $req->id);

  $rs = $dbo->query('SELECT *'
                    .' FROM '.Item::TABLE_REVISION
                    .' WHERE model_id='.$item->getModelId()
                    .  ' AND record_id='.$item->getId()
                    .' ORDER BY created_at DESC'
                    .' LIMIT 200');

  $rows = array();
  foreach ($rs as $row) {
    $row['attributes'] = unserialize($row['attributes']);
    $row['creator'] = Model::label($row['creator_model_id']);
    try {
      $creator = Item::getInstance((int) $row['creator_model_id'],
                                   (int) $row['creator_record_id']);
      $row['creator'] .= ' : '.$creator;
    }
    catch (Exception $e) { $err->log($e); }
    $rows[] = $row;
  }

  $ctx->rows = $rows;

  $res->useTemplates('//revisions');

}
catch (Exception $e) { $err->add($e); }
