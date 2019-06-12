<?php

try {

  $adherent = Adherent::getInstance($req->id);
  $ctx->adherent = $adherent;
  $ctx->adherent_user = $adherent->getUser();

  $res->useTemplate();

}
catch (Exception $e) {
  $log->error($e);
}
