<?php

try {

  $iban = $ctx->_current_adherent->getIban((int) $req->id);
  $iban->destroy();
  $res->sendMessage(l('flash.delete.success'));

}
catch (Exception $e) {
  $err->add($e);
}
