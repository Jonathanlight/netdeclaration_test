<?php

try {

  foreach(Formulairetype::collect() as $ftype) {
    $ftype->build();
  }

}
catch (Exception $e) {
  $err->add($e);
}
