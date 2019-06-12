<?php

try {

  $path = GreffeManager::getAmitelPath( GreffeManager::AMITEL_REPONSE_PATH );
  $files = glob($path . '/*_reponse.zip');

  foreach ($files as $file) {
    list($greffe_id,) = explode('_', basename($file));

    if (Greffe::exists((int)$greffe_id)) {
      $greffe = Greffe::getInstance((int)$greffe_id);

      if ($greffe->status == Greffe::STATUS_SENDED) {
        $zip = new ZipArchive();
        $zip->open($file);
        $filenames = array();
        for ($i = 0; $i < $zip->numFiles; $i++) {
          $filenames[] = $zip->getNameIndex($i);
        }

        $status = !in_array($greffe_id.'_rejet.pdf', $filenames) ? Greffe::STATUS_ACCEPTED : Greffe::STATUS_REFUSED;
        $greffe->commit(array('status'      => $status,
                              'documents'   => $filenames,
                              'response_at' => date('Y-m-d')));

        if (!file_exists(GreffeManager::getResponseDocumentPath())) {
          mkdir(GreffeManager::getResponseDocumentPath());
        }
        $dest_path = $greffe->getResponseDocumentPath();
        if (!file_exists($dest_path)) {
          mkdir($dest_path);
        }

        $zip->extractTo($dest_path);
        $zip->close();

        $zip_dest_path = $dest_path.'/documents.zip';
        rename($file, $zip_dest_path);
      }
    }
  }

}
catch (Exception $e) { $err->add($e); }