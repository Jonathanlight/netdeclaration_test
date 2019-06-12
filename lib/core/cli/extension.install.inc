<?php

try {

  Extension::getInstance($req->name)->install();

}
catch (Exception $e) { $err->add($e); }