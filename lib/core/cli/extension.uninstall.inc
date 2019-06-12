<?php

try {

  if ($req->all === 'yes') {
    foreach (Extension::all() as $name => $extension) {
      if (in_array($name, array(CORE, 'tracker', 'file'))) continue ;
      if (!Shell::confirm('['.$name.'] Are you sure', true)) continue ;
      Extension::getInstance($name)->uninstall();
    }
    return ;
  }
  
  if (!Extension::exists($req->name)) {
    throw new Extension('invalid name ['.$req->name.']');
  }

  if ($req->confirm != 'no' && !Shell::confirm('Are you sure', true)) return ;

  Extension::getInstance($req->name)->uninstall();

}
catch (Exception $e) { $err->add($e); }