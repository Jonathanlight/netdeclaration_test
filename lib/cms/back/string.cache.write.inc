<?php

try {

  String::CacheWrite();

  $res->sendMessage("Les dictionnaires ont bien été générés.");

}
catch (Exception $e) { $err->add($e); }
