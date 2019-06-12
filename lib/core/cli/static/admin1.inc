<?php

$file_path = 'http://download.geonames.org/export/dump/admin1CodesASCII.txt';

$countries = $dbo->asHash('SELECT fips_code, id'
                          .' FROM '.T('country'));

$handle = fopen($file_path, 'r');

if ($handle === false) {
  throw new Exception('can not open file');
}

$dbo->getTable('knx_admin1')->truncate();

while (($data = fgetcsv($handle, 1000, "\t")) !== false) {
  list($fips_code, $code) = explode('.', $data[0]);
  if ($countries[$fips_code] < 1) continue ;
  $dbo->insert('knx_admin1',
               array('id' => $data[3],
                     'country_id' => $countries[$fips_code],
                     'code' => sprintf('%u', crc32($code)),
                     'name' => $data[1])); 
}
fclose($handle);

$dbo->getTable('knx_admin1')->optimize();

$rewrites = array(3030293 => 'Bretagne',
                  3023519 => 'Corse');

foreach ($rewrites as $key => $value) {
  $dbo->update('knx_admin1',
               array('name' => $value),
               array('filters' => array('id' => $key),
                     'limit' => 1));
}

$dbo->query('UPDATE knx_admin1 SET name=REPLACE(name, "Region ", "") WHERE country_id='.Country::FR);
$dbo->query('UPDATE knx_admin1 SET name=REPLACE(name, "Région ", "") WHERE country_id='.Country::FR);

/*

CREATE TABLE IF NOT EXISTS `knx_admin1` (
  `id` mediumint(8) unsigned NOT NULL default '0',
  `code` int(10) unsigned NOT NULL default '0',
  `country_id` smallint(5) unsigned NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `name` (`country_id`,`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

*/