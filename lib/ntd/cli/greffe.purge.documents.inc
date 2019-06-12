<?php

try {

  $filters = array('status'    => Greffe::STATUS_ACCEPTED,
                   '|!&|flags' => Greffe::FLAG_DOCUMENTS_PURGED);
  $greffes = Greffe::collect(array('filters' => $filters));

  foreach ($greffes as $greffe) {
    $path = $greffe->getDocumentPath();
    if (!file_exists($path)) continue;

    $files = glob($path . '/*');
    foreach ($files as $file) {
      unlink($file);
    }
    rmdir($path);
    $greffe->setFlag(Greffe::FLAG_DOCUMENTS_PURGED);
  }

}
catch (Exception $e) { $err->add($e); }