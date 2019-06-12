<?php

try {

  $file = new File($req->file_path);
  $file->rename($req->new_filename);
  $ctx->file_path = $file->getName();

}
catch (Exception $e) { $err->add($e); }
