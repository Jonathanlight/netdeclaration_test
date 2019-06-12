<?php

// ALTER TABLE `abuse` CHANGE `model_id` `model_id` SMALLINT UNSIGNED NOT NULL  

foreach ($dbo as $table) {
  try {
    $dbo->exec("ALTER TABLE `".$table."` CHANGE `lang_id` `locale` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT '48'");
  }
  catch (Exception $e) {}
  $dbo->getTable($table)->optimize();
}