<?php

try {

  $folder = new Folder($req->path);
  $folder->addChild($req->dir_name);
  $ctx->path = $folder->getPath();

}
catch (Exception $e) { $err->add($e); }
