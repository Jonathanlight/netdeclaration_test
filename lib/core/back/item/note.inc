<?php

try {

  $item = Item::getInstance(MODEL, (int) $req->id);

  $hash = $dbo->fetchHash('SELECT comment, content'
                          .' FROM '.Item::TABLE_NOTE
                          .' WHERE model_id='.$item->getModelId()
                          .  ' AND record_id='.$item->getId());
  
  $ctx->comment = $hash['comment'];
  $ctx->content = $hash['content'];

  $res->useXml();

}
catch (Exception $e) { $err->add($e); }