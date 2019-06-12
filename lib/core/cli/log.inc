<?php

if ($req->full == 'yes') {
  $cmd  = 'tail -n 200 -f '.Logger::ERR_FILE.' '.Logger::URL_FILE;
}
else {
  $cmd  = 'tail -n 200 -f '.Logger::ERR_FILE;
}

Shell::exec($cmd);