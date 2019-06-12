<?php

try {

  if (!$admin->isSuperAdmin()) return ;

  $datas = array();
  $dbo->connect();
  $result = mysql_query('SHOW TABLE STATUS', $dbo->link());
  while ($row = mysql_fetch_array($result)) { 
    $total_size = ($row['Data_length'] + $row['Index_length']) / 1048576;
    $datas[$row['Name']] = sprintf('%.2f', $total_size).' M ('.$row['Rows'].')';
  }
  
  $ctx->datas = $datas;

  $res->useXml();

}
catch (Exception $e) { $err->add($e); }
