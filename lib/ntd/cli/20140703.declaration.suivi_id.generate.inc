<?php

try {

  foreach (Declaration::collect() as $declaration) {
    $declaration->setAttribute('suivi_id', Suivi::exists(array('declaration_id' => $declaration->getId())));
  }

}
catch (Exception $e) {
  print $e->getMessage();
}