<?php

if (!file_exists('ip-to-country.csv')) {

  $cmd = 'wget -nv -q "http://ip-to-country.webhosting.info/downloads/ip-to-country.csv.zip"';
  Shell::exec($cmd);
  
  if (!file_exists('ip-to-country.csv.zip')) {
    die('ZIP not found');
  }
  
  $cmd = 'unzip -qq ip-to-country.csv.zip';
  Shell::exec($cmd);
  
  unlink('ip-to-country.csv.zip');
   
}

if (!file_exists('ip-to-country.csv')) {
  die('CSV not found');
}

$cmd = 'chmod 644 ip-to-country.csv';
Shell::exec($cmd);

$dbo->exec("CREATE TABLE IF NOT EXISTS tmp_ip2country (
  from_ip int(10) unsigned NOT NULL default '0',
  to_ip int(10) unsigned NOT NULL default '0',
  country_code varchar(2) collate latin1_general_ci NOT NULL,
  PRIMARY KEY (from_ip,to_ip)
)");

$dbo->exec("TRUNCATE TABLE `tmp_ip2country`");

$dbo->exec("LOAD DATA LOCAL INFILE './ip-to-country.csv'"
           ." INTO TABLE tmp_ip2country fields terminated by ',' enclosed by '\"' (from_ip, to_ip, country_code)");

/** lines terminated by '\r\n' **/

$dbo->exec("CREATE TABLE IF NOT EXISTS sys_country_ip (
  from_ip int(10) unsigned NOT NULL,
  to_ip int(10) unsigned NOT NULL,
  country_id smallint(5) unsigned NOT NULL,
  PRIMARY KEY (from_ip,to_ip)
)");

$dbo->exec("TRUNCATE TABLE `sys_country_ip`");

$dbo->exec("INSERT INTO sys_country_ip"
           ." SELECT tmp_ip2country.from_ip,"
           .       " tmp_ip2country.to_ip,"
           .       " C.id"
           ." FROM tmp_ip2country"
           .     " JOIN ".T('country')." AS C ON (tmp_ip2country.country_code=C.code)");

$dbo->getTable('sys_country_ip')->optimize();

unlink('ip-to-country.csv');

$dbo->exec("DROP TABLE `tmp_ip2country`");

