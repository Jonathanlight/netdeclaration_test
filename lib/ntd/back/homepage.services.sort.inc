<?php

try {

  $opts = array('limit' => 1);
  $position = 1;
  foreach (String::asSet($req->ids) as $service_id) {
    $opts['filters'] = array('id' => $service_id);
    $dbo->update(T('Service'), array('position' => $position), $opts);
    $position++;
  }

}
catch (Exception $e) { $err->add($e); }
