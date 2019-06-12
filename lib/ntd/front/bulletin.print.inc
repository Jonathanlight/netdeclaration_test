<?php

try {

  $adherent = Adherent::getInstance($req->id);

  $ctx->adherent = $adherent;

  $res->useTemplates(null, 'skeleton.pdf', true);

}
catch (Exception $e) {
  $err->add($e);
}