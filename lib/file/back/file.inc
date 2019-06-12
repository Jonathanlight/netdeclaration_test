<?php

try {

  $file = File::isImage($req->file_path)
        ? new Img($req->file_path)
        : new File($req->file_path);

  $ctx->file = $file;

  $info_arr["nom"] = wordwrap(basename($file->getBaseName()), 22, "<br/>", 1);
  $info_arr["chemin"] = '/'.wordwrap($file->getPath(), 22, "<br/>", 1);
  $info_arr["date"] = date('d/m/Y G:i', $file->getCtime());
  $info_arr["taille"] = Numeric::asFileSize($file->getSize());
  if (File::isImage($file)) {
    $info_arr["dim"] = $file->getWidth().' x '.$file->getHeight();
  }
  $ctx->info_arr = $info_arr;

  $res->useTemplates('skeleton', true);

  $res->setTitle($file->getFolder()->getHtmlPath());
  $res->setSeo($file->getFolder()->getHtmlPath());

}
catch (Exception $e) { return $err->add($e); }
