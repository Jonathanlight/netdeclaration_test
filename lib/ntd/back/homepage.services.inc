<?php

try {

  $ctx->services = HomepageHelper::getServices();

  $res->setFormat(Response::FORMAT_TEXT);
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}