<?php

try {

  $name = $req->name;
  $new_name = $req->new_name;

  if (empty($name) || empty($new_name)) {
    throw new Exception('Usage: formulaire.duplicate.v1 <name> <new_name>');
  }

  if (!Formulairetype::exists(array('name' => $name))) {
    throw new Exception('Le formulaire n\'existe pas !');
  }

  if (Formulairetype::exists(array('name' => $new_name))) {
    throw new Exception('Le formulaire dupliqué existe déja !');
  }

  $ftype = Formulairetype::getInstance(array('name' => $name));
  $attributes = $ftype->getAttributes();

  unset($attributes['id']);
  $attributes['name'] = $new_name;

  $new_ftype = Formulairetype::getInstance();
  $new_ftype->commit($attributes);

  shell_exec('cp -a lib/ntd/data/form.'.$name.'.data.inc lib/ntd/data/form.'.$new_name.'.data.inc');
  shell_exec('sed -i "s/'.$name.'/'.$new_name.'/g" lib/ntd/data/form.'.$new_name.'.data.inc');

  shell_exec('cp -a app/ntd/templates/formulaires/formulaire.edit.'.$name.'.psp app/ntd/templates/formulaires/formulaire.edit.'.$new_name.'.psp');
  shell_exec('sed -i "s/'.$name.'/'.$new_name.'/g" app/ntd/templates/formulaires/formulaire.edit.'.$new_name.'.psp');

}
catch (Exception $e) { $err->add($e); }