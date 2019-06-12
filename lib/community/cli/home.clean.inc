<?php

try {

  User::clean();

}
catch (Exception $e) { $err->add($e); }
