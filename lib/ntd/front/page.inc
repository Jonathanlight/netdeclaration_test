<?php

try {

  $args = null;
  if ($req->hasAttribute('code', true)) {
    $args = array('code' => $req->code);
  }
  elseif ($req->hasAttribute('id', true)) {
    $args = (int) $req->id;
  }

  $page = Page::getInstance($args);
  $page->track();

  $ctx->page = $page;
  $ctx->partial = $req->isXhr();

  $req->track($page);

  $res->setBreadcrumb(array('page d\'accueil' => '/',
                            $page->title => $page->asUrl()));
  $res->setSeo($page);
  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }