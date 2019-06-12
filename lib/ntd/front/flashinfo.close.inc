<?php

try {

  NetDeclaration::flashInfoClose();

}
catch (Exception $e) {
  $err->add($e);
}