<?php

try {

  $log->enable();
  $req->debug();
  $res->close();
  Method::callback();

}
catch (Exception $e) {
  $err->add($e);
  $log->error($e);
}
