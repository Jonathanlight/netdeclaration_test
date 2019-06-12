<?php

try {

  $file = new File($req->filepath);

  $file->unlink();

  $ctx->path = $file->getPath();

}
catch (Exception $e) { $err->add($e); }
