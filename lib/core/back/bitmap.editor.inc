<?php

try {

  $file_path = $req->file_path;

  if (strpos($file_path, '://') > 1) {
    $file_path = parse_url($file_path, PHP_URL_PATH);
  }

  $file_path = trim($file_path, '/');

  if (!file_exists($file_path)) {
    throw new Exception('['.$file_path.'] invalid path');
  }

  $ctx->file_path = $file_path;
  $ctx->file_size = String::toSize(filesize($file_path));

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
