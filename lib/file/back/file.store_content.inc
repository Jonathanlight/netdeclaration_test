<?php

try {
  $file = new File($req->file_path, 'w');
  $file->write($req->content);
  $res->sendRedirect('/back/file/content_edit', 
                 array('file_path' => $file->getName()));
}
catch (Exception $e) { $log->error($e); }



