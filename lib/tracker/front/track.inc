<?php

try {

  $category = strlen($req->category) < 1) ? null : $req->category;
  $req->track($req->action, $category);
  
  if (!$req->isXhr()) {
    $res->close();
    String::spacer();
  }

}
catch (Exception $e) {
  $log->error($e);
}