<?php

try {
  
  $formulairetype = Formulairetype::getInstance((int) $req->id);
  $formulairetype->export();

  $res->sendMessage('Export terminé.');

}
catch (Exception $e) {
  $err->add($e);
}
