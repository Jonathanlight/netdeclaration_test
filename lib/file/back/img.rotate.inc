<?php

try {
  $file = new Img($req->file_path);
  $ret = $file->rotate($req->angle);
  $res->write("Kwo.File.view('".$file->getName()."');");
}
catch (Exception $e) { $err->add($e); }