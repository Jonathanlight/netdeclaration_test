<?php

try {
  $dbo->query('TRUNCATE TABLE '.AuthManager::TABLE_ATTEMPT);
  $ctx->callback_notification = 'Toutes les tentatives de connexion ont été supprimées';
}
catch (Exception $e) { $err->add($e); }