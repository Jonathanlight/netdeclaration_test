<?php

try {

  $page = Page::getInstance('page.signup');

  $ctx->page = $page;

  $res->setBreadcrumb(array('page d\'accueil' => '/',
                            $page->title => $page->asUrl()));
  $res->setSeo($page);
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
