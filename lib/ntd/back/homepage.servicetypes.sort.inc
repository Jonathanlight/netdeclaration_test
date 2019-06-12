<?php

try {

  $opts = array('limit' => 1);
  $position = 1;
  foreach (String::asSet($req->ids) as $servicetype_id) {
    $opts['filters'] = array('id' => $servicetype_id);
    $dbo->update(T('Servicetype'), array('position' => $position), $opts);
    $position++;
  }

}
catch (Exception $e) { $err->add($e); }
