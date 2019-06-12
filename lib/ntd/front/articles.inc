<?php

try{
  
  $ctx->articles = NetDeclaration::getActualites();

  $page = Page::getInstance('front.articles');

  $req->track('articles', 'ntd');
  $res->setSeo($page);
  $res->setBreadcrumb(array('page d\'accueil' => '/',
                            $page->title => '/articles'));
  $res->useTemplate();
}
catch(Exception $e){

}

