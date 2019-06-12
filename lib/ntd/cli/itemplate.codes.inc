<?php

try {

  foreach(Itemplate::collect() as $itemplate) {
    $itemplate->setAttribute('code', $itemplate->getCode());
  }

}
catch (Exception $e) {
  $err->add($e);
}
