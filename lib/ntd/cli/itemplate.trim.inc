<?php

try {

  foreach(Itemplate::collect() as $itemplate) {
    $itemplate->setAttribute('psp', trim($itemplate->psp));
  }

}
catch (Exception $e) {
  $err->add($e);
}