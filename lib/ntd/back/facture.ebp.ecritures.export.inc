<?php

try {

  $begin_at = Date::toDb($req->begin_at);
  $end_at = Date::toDb($req->end_at);
  $all = (int) $req->all;
  $export_types = (array) $req->export_types;  
  $file = ExportEBP::exportEcritures($begin_at, $end_at, $all, $export_types);
  $res->sendData($file);  

}
catch (Exception $e) {
  $err->add($e);
}
