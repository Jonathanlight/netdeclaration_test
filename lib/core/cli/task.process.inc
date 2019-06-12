<?php

try {

  Task::process();

}
catch (Exception $e) { $err->add($e); }
