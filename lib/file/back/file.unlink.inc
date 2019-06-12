<?php

try {

  $file = new File($req->file_path);

  $file->unlink();

  $ctx->path = $file->getPath();

}
catch (Exception $e) { $err->add($e); }
