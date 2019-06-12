<?php

try {

  $dbo->query('DELETE FROM '.AuthManager::TABLE_ATTEMPT
              .    ' WHERE TIMESTAMPDIFF(DAY, created_at, NOW()) > 1'); 
  
}
catch (Exception $e) { $err->add($e); }
