<?php

try {

  $file = new File($req->file_path);
  $zip  = new ZipArchive();
  $ret = $zip->open($file->getName());
  if ($ret!=true) throw new Exception('can not open zip');

  $files_arr = array();
  for ($i = 0; $i < $zip->numFiles; $i++) {
    $details_arr = $zip->statIndex($i);
    if (!File::isValidName($details_arr['name'])) {
      $bad_arr[] = basename($details_arr['name']); 
    }
    elseif (!preg_match('/\/$/i',$details_arr['name'])) {
      $filename = basename($details_arr['name']);
      $zip->renameIndex($i, $filename);
      $log->error($filename);
      $files_arr[] = $filename;
    }
  }

  if (count($bad_arr) >= 1) {
     $err->add('Cette archive contient un/des fichier(s) interdit(s) : '.join(',',$bad_arr));
     return;
  }
  
  $ret = $zip->extractTo($file->getPath(), $files_arr);
  if ($ret === false) {
    $err->add('extraction impossible');
    return;
  }
  $zip->close();
  $file->unlink();

}
catch (Exception $e) { $err->add($e); }
