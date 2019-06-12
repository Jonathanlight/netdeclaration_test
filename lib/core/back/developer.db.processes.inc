<?php

try {

  if (!$admin->isSuperAdmin()) return ;

  $datas = array();

  $dbo->connect();
  $result = mysql_list_processes($dbo->link());
  while ($row = mysql_fetch_assoc($result)){
    $datas[] = $row;
  }
  
  $ctx->datas = $datas;

  $res->useXml();

}
catch (Exception $e) { $err->add($e); }
