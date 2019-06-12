<?php

try {
    $adherent = Adherent::getInstance($req->id);
    $ctx->adherent = $adherent;

    $res->useTemplate();
}
catch (Exception $e) {
    $log->error($e);
}
