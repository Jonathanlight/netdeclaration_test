<?php

try {

  $opts = array('filters' => array('status' => Declaration::STATUS_BROUILLON));

  $declarations = Declaration::collect($opts);

  foreach ($declarations as $declaration) { 
    $declaration->destroy();
  }

} catch (Exception $e) { $err->add($e); }
