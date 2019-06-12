<?php

  /*
CREATE TABLE tkr_agent (
  id int(10) unsigned NOT NULL auto_increment,
  ip varchar(15) character set utf8 collate utf8_bin NOT NULL,
  flag tinyint(3) unsigned NOT NULL default '0',
  `name` varchar(500) NOT NULL,
  visitor_id int(10) unsigned NOT NULL default '0',
  created_at timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (id),
  KEY `name` (`name`(333))
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;
  */

$where = 1;
if ($req->hasAttribute('exclude', true)) {
  $exclude = str_replace(',', '|', $req->exclude);
  $where = 'name NOT REGEXP "'.$exclude.'"';
 }

$total = $dbo->fetchValue('SELECT COUNT(*) FROM tkr_agent');

$rs = $dbo->query('SELECT name, COUNT(*) as n'
                  .' FROM tkr_agent'
                  .' WHERE '.$where
                  .' GROUP BY name'
                  .' HAVING n > 2 '
                  .' ORDER BY n DESC');

$hash = $rs->asHash();
print('Total : '.$total."\n");
print('Sub total : '.array_sum($hash)."\n\n");
print_r($hash);

