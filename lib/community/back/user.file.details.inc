<?php

try {

  $file = File::getInstance($req->filepath);
  $details = $file->getDetails();
  $details['size'] = Numeric::asFileSize($details['size']);
  $details['ctime'] = date('Y-m-d G:i:s', $details['ctime']);
  if ($details['ctime'] != $details['mtime']) {
    $details['mtime'] = date('Y-m-d G:i:s', $details['mtime']);
  }
  if (isset($details['width'])) {
    $details['width'] .= ' px';
    $details['height'] .= ' px';
  }

  $ctx->file = $file;
  $ctx->details = $details;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
