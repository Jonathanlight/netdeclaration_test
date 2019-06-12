<?php

try { 
  
  $params = $req->getAttributes();

  $finder = Finder::getInstance($params);

  $finder->onFind();
  
  if ($req->offset > 0) {
    $collection = $finder->getCollection();    
    if ($collection && $collection->foundRows() > 0 && count($collection) < 1) {
      $collection->setOffset(0);
    }
  }

  $res->write($finder);

}
catch (Exception $e) { $err->add($e); }