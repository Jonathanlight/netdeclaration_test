<?php

try {

  $ctx->page = Page::getInstance(h($req->code));

  NtdMiddleManager::setBreadCrumb($ctx->page->title);
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO($ctx->page->title);

}
catch (Exception $e) {
  $err->add($e);
}
