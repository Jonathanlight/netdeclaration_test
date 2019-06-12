<?php

try {

  foreach ($dbo->getTables(E('search', 'table_prefix')) as $table) {
    $table->truncate();
    S('log')->trace($table);
  }

}
catch (Exception $e) { $err->add($e); }