<?php

try { //$req->debug();

  $folder = new Folder($req->path);
  UploadManager::back($folder);

  if ($req->hasAttribute('type')) {
    $res->close();
    if ($req->type === 'multi') {
      $res->write('<script>parent.onComplete();</script>');
    }
    else {
      $res->write('<script>parent.Kwo.panel.onRefresh(); parent.$("upload-form").enable().reset();</script>'); 
    }
  }
  else {
    $res->sendRedirect('/back/file/dir', 
                   array('path' => trim($req->path, '/'), 
                         'time' => time()));
  }
}
catch (Exception $e) { 
  $res->write('<script>'
              .' alert("Attention ! '.addslashes(ucfirst($e->getMessage())).'.");'
              .' parent.Kwo.getDialog().refresh({path: "'.$req->path.'"})'
              .'</script>');  
}
