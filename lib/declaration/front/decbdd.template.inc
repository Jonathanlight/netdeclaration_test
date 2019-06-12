<?php

try {

  $template_path = 'app/declaration/templates/'.$req->template.'.psp';
  if(is_file($template_path)) {
    $res->setFormat(Response::FORMAT_TEXT);
    $res->resetTemplates();
    $res->write(file_get_contents($template_path));
  }

}
catch (Exception $e) {
  $err->add($e);
}