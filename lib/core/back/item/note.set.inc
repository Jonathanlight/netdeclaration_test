<?php

try {

  $item = Item::getInstance(MODEL, (int) $req->id);
  
  $note = array('model_id' => $item->getModelId(),
               'record_id' => $item->getId(),
               'content' => $req->content,
               'comment' => $req->comment);

  $table = $dbo->getTable(Item::TABLE_NOTE);
  $row = array('model_id' => $item->getModelId(), 
               'record_id' => $item->getId());

  if ($table->hasRow($row)) {
    $opts = array('filters' => array('model_id' => $item->getModelId(),
                                     'record_id' => $item->getId()),
                  'limit' => 1);
    $dbo->update(Item::TABLE_NOTE, $note, $opts);
  }
  else {
    $dbo->insert(Item::TABLE_NOTE, $note);
  }

}
catch (Exception $e) { $err->add($e); }