<?php

$dialog = 'top.Kwo.getDialog()';

try {
  
  $files = $req->getUser()->receive();
  
  //  error_log(var_export($files,true));
  
  if (count($files) < 1) throw new Exception('no file found');
  
  foreach ($files as $file) {
    
    $extension = strtolower($file->getExtension());
    
    $upload_settings = P('upload.settings');
    
    if (!empty($upload_settings) && 
        !empty($upload_settings['image_max_size']) && 
        ($extension == 'jpg' || $extension == 'jpeg' || $extension == 'gif' || $extension == 'png')) {
      $img = $file->getImg();
      if ($img->getWidth() > $upload_settings['image_max_size']['width'] || 
          $img->getHeight() > $upload_settings['image_max_size']['height']) {
        $ratio = $img->getWidth() / $img->getHeight();
        $width = 1600;
        $height = round(1600 / $ratio);
        if ($height > 1200) {
          $width = round(1200 * $ratio);
          $height = 1200;
        }
        $img->setSize($width, $height);
      }
    }
  }
  
  $req->track('upload', 'account');
  
  $res->write('<script>'.$dialog.'.onUploadCompleted("'.$file->getName().'")</script>');
  
}
catch (Exception $e) { 
  $res->write('<script>'.
              'alert("Attention ! '.addslashes(ucfirst($e->getMessage())).'.");'.
              $dialog.'.refresh();'.
              '</script>');
}
