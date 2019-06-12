<?php

try { 

  $n = Engine::crawl();

  $res->sendMessage($n.' document(s) indexé(s)');

}
catch (Exception $e) { $err->add($e); }
