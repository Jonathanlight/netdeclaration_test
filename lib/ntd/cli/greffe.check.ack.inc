<?php

try {

  $path = GreffeManager::getAmitelPath( GreffeManager::AMITEL_ACK_PATH );
  $files = glob($path . '/*_accuse.ack');

  foreach ($files as $file) {
    list($greffe_id,) = explode('_', basename($file));

    if (Greffe::exists((int)$greffe_id)) {
      $greffe = Greffe::getInstance((int)$greffe_id);

      if ($greffe->status == Greffe::STATUS_VALID) {
        $content = file_get_contents($file);
        $pattern = '#([0-9]{4})([0-9]{2})([0-9]{2})\-([0-9]{2}):([0-9]{2}):([0-9]{2})#'; // YYYYMMJJ-hh:mm:ss
        if (preg_match($pattern, trim($content), $datetime)) {
          unset($datetime[0]);
          $datetime = array_chunk($datetime, 3);
          $date = implode('-', $datetime[0]);
          $time = implode(':', $datetime[1]);
          $ack_date = $date.' '.$time;

          $greffe->commit(array('status'  => Greffe::STATUS_SENDED,
                                'send_at' => $ack_date));
          unlink($file);

          $demande_path = GreffeManager::getAmitelPath( GreffeManager::AMITEL_DEMANDE_PATH );
          $demande_file = $demande_path . '/' . (int)$greffe_id . '_demande.zip';
          if (file_exists($demande_path))
            unlink($demande_file);
        }
        else {
          S('log')->error('Erreur de validation pour le dépôt '.$greffe_id, __METHOD__);
        }
      }
    }
  }

}
catch (Exception $e) { $err->add($e); }