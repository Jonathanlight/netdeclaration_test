<?php

try { 

  if (!$user->hasFile($req->image)) {
    throw new Exception('file unknown ['.$req->image.']');
  }

  $user->getFile($req->image)
    ->getImg()
    ->setSize(36, 36)
    ->rename('_a.jpg');

  $user->setFlag(User::FLAG_IMAGE);

}
catch (Exception $e) { 
  $log->error($e); 
  $err->add(l('error.upload.image'));
}
