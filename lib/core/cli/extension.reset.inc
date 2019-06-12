<?php

try {

  //  if ($req->confirm != 'no' && !Shell::confirm('Are you sure', true)) return ;
  if (!Extension::exists($req->name)) {
    throw new Exception('extension unknown ['.$req->name.']');
  }
  
  Extension::getInstance($req->name)->reset();

}
catch (Exception $e) { $err->add($e); }