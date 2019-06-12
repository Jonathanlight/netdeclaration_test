<?php

try {

  $dir = Folder::getInstance($req->path);
  $dir->compress();

  $ctx->path = $req->path;

}
catch (Exception $e) { $err->add($e); }

