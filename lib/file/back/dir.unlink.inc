<?php

try {

  $dir = Folder::getInstance($req->path);
  $file_path = $dir->getParentPath();
  $dir->hide();

  $ctx->path = $file_path;

}
catch (Exception $e) { $err->add($e); }
