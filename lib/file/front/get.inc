<?php

try {

  $path = $req->path;
  
  if ($req->hasAttribute('item_key')) {
    $item = Item::getInstanceByKey($req->item_key);
    $item->track(Intent::TYPE_DOWNLOAD);
    if (empty($path)) {
      $path = $item->file;
    }
  }
  
  $file = File::getInstance($path, 'r');
  $req->track($file->getPath(), 'download');
  $res->sendData($file);

}
catch (Exception $e) { 
  $req->track($path.' / download', Tracker::CATEGORY_ERROR);
  $err->add($e); 
}
