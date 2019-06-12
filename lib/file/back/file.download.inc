<?php

try { 

  if ($req->hasAttribute('filepath')) {
    $filepath = $req->filepath;
  }
  else {
    $filepath = $req->file_path;
  }

  $res->sendData(File::getInstance($filepath, 'r'));

}
catch (Exception $e) { $err->add($e); }
