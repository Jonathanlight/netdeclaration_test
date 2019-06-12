<?php

$rs = $dbo->query('select * from tkr_visitor where counter>0');
foreach ($rs as $hash) {
  print($hash['created_at'].' '.Net::num2ip($hash['ip']).' '.gethostbyaddr(Net::num2ip($hash['ip']))."\n");
}