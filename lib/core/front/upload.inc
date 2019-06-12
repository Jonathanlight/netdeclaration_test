<?php

$dialog = 'top.Kwo.getDialog()';

try {

  if ($req->isAuthenticated()) {
    $user = $req->getUser();
    $files = $user->receive();
    if (count($files) < 1) {
      throw new Exception('no file found');
    }
    $category = 'account';
  }
  else {
    $file = UploadManager::anonymous('file');
    $category = 'events';
  }

  if ($req->filter === 'image') {
    $metas = @getimagesize($file->getName());
    if ($metas === false ||
        !in_array($metas[2],
                  array(IMAGETYPE_GIF, IMAGETYPE_JPEG, IMAGETYPE_PNG))) {
      $log->error('invalid image (size)', $file->getName());
      $file->unlink();
      throw new Exception(l('error.image'));
    }
    if ($metas['channels'] == 4) {
      $log->error('CMYK image', $file->getName());
      $file->unlink();
      throw new Exception(l('error.image.channels'));
    }
  }

  $req->track('file.upload', $category);

  $script = $dialog.'.onUploadCompleted("'.$file->getName().'");';

}
catch (Exception $e) {

  $json = json_encode(array('error' => ucfirst($e->getMessage())));
  $script = 'args = '.$json.';'.$dialog.'.refresh(args);';

}

$res->write('<script>'.$script.'</script>');