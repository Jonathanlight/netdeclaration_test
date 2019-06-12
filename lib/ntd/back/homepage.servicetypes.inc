<?php

try {

  $ctx->servicetypes = HomepageHelper::getServiceTypes();

  $res->setFormat(Response::FORMAT_TEXT);
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}