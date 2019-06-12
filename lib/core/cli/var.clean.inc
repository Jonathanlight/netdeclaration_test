<?php

try {

  Logger::clean();
  UploadManager::clean();
  Session::clean();
  Cache::clean();
  Scheduler::clean();

}
catch (Exception $e) { $err->add($e); }
