<?php

try { 

  $remote_file_path = trim($req->remote_file_path, '/');
  
  $folder = new Folder($req->path);
  if (!$folder->isWritable($req->path)) {
    throw new Exception('écriture impossible dans ce répertoire.');
  }

  $sep = strpos($remote_file_path, '\\') !== false ? '\\' : '/';
  
  $parts = explode($sep, $remote_file_path);
  
  $remote_file_path = $parts[count($parts) - 1];
  $remote_file_path = File::NameClean(basename($remote_file_path));
  
  if (!File::isValidName($remote_file_path)) { 
    throw new Exception("cette extension n'est pas authorisée.");
  }
  
  $ctx->has_file = (int) $folder->hasFile($remote_file_path);
  
}
catch (Exception $e) { $err->add($e); }


