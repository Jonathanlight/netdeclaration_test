<?php

$where = 1;
if ($req->hasAttribute('exclude', true)) {
  $exclude = str_replace(',', '|', $req->exclude);
  $where = 'robot NOT REGEXP "'.$exclude.'"';
}

$total = $dbo->fetchValue('SELECT COUNT(*) FROM tkr_robot');

$rs = $dbo->query('SELECT robot, COUNT(*) as n'
                  .' FROM tkr_robot'
                  .' WHERE '.$where
                  .' GROUP BY robot'
                  .' ORDER BY n DESC');

$hash = $rs->asHash();
print('Total : '.$total."\n");
print('Sub total : '.array_sum($hash)."\n\n");
print_r($hash);

