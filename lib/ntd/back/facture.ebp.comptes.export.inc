<?php

try {

  $begin_at = Date::toDb($req->begin_at);
  $end_at = Date::toDb($req->end_at);
  $file = ExportEBP::exportComptes($begin_at, $end_at);
  $res->sendData($file);

}
catch (Exception $e) {
  $err->add($e);
}
