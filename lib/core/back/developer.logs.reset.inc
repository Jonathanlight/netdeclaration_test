<?php

try {

  if (!$admin->isSuperAdmin()) return ;

  Logger::clean();

  $res->sendMessage('opération réalisée avec succès.');

}
catch (Exception $e) { $err->add($e); }
