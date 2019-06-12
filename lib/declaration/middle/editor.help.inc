<?php

try {

  $res->resetTemplates();   
  $res->useTemplate();
  
}
catch (Exception $e) {
  $err->add($e);
}