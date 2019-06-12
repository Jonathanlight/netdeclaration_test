<?php

try {

  $file = new File($req->file_path, 'w');
  $content = $file->getContent();
  $enc = String::detectEncoding($content);
  if ($enc != 'UTF-8') {
    $file->write(iconv($enc, 'UTF-8', $content));
  }
  $ctx->file_path = $file->getName();

}
catch (Exception $e) { $err->add($e); }
