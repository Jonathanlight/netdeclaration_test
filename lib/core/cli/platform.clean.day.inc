<?php

Cache::clean();
UploadManager::clean();

$files = glob('var/apache/*/*/*/*.*');
$files = $files ? $files : array();
$ts = time();
$ttl = 6 * 60 * 60;
foreach ($files as $file) {
  if (!file_exists($file)) continue ;
  $fts = filemtime($file);
  if (($ts - $fts) > $ttl) {
    unlink($file);
  }
}