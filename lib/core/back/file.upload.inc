<?php

if ($req->isXhr()) {
  
  try { 

    //    $req->debug(true);
    
    $filename = $req->getHeader('x-file-name');
    $path = $req->getHeader('x-file-destination');

    $filename = File::NameClean($filename);
    $path = Folder::PathClean($path); 

    if (empty($path) || !is_dir($path)) {
      if (!empty($path)) {
        $log->error('['.$path.'] path unknown');
      }
      $path = DOC_PATH;
    }
    
    $file_path = $path.'/'.$filename; 
    
    //    $req->debug(true);

    $in = @fopen($req->getBodyStream(), 'r');
    if (!is_resource($in)) {
      throw new Exception('invalid input');
    }
    $out = fopen($file_path, 'w');
    if (!is_resource($out)) {
      throw new Exception('invalid output');
    }
    while (!feof($in)) {
      fwrite($out, fread($in, 8192));
    }
    fclose($out);
    fclose($in);
    
  }
  catch (Exception $e) { 
    $log->error($e);
    $err->add($e); 
  }
  
  return ;
}


try { 

  $folder = Folder::getInstance($req->destination);
  UploadManager::back($folder);
  $res->close();
  $res->write('<script>parent.Kwo.getDialog().onUploadCompleted();</script>');

}
catch (Exception $e) { 
  $res->write('<script>'
              .' alert("Attention ! '.addslashes(ucfirst($e->getMessage())).'.");'
              .'</script>');  
}


