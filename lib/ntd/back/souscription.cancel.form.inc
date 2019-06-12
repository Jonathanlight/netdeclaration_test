<?php
try {

  $ctx->souscription = Souscription::getInstance((int) $req->id);  

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
