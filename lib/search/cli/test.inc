<?php

try {

  error_log(ini_get('mbstring.internal_encoding'));

  $GLOBALS['parameters']['extension.search.models'] = array(Model::id('page'), 
                                                            Model::id('topic'));

  $tables = array(Document::TABLE,
                  Engine::TABLE_BUCKET,
                  Engine::TABLE_STEM);

  foreach ($tables as $table) {
    $dbo->getTable($table)->truncate();
  }

  $topic = Topic::getInstance(17);
  $topic->markAsChanged();

  //  print($topic);

  //  Document::crawl();

}
catch (Exception $e) { $err->add($e); }
