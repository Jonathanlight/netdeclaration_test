<?php

try {

  $article = Article::getInstance((int) $req->id,
                                  array('include' => 'heading'));

  if (!$article->isOnline()) {
    $res->sendRedirect('/articles');
  }

  $article->track();

  $heading = $article->getHeading();
  $chapters = $article->getChapters();

  $last_articles = Article::collect(array('filters' => array('|!=|id' => $article->getId()),
                                          'limit' => 3,
                                          'order' => array('published_at' => 'DESC')));

  $breadcrumb = array('page d\'accueil' => '/',
                      Page::getInstance('front.articles')->title => '/articles',
                      $article);

  $req->track($article);

  $ctx->article = $article;
  $ctx->last_articles = $last_articles;


  $head_hash = $article->asHeadHash($req->getLocale());
  $res->setSeo(array(
    'title'       => $head_hash['title'] ?: $article->getName(),
    'description' => $head_hash['description'] ?: trim(strip_tags(str_replace(array("\r\n", "\r", "\n"), " ", $article->description))),
  ));

  $res->setBreadcrumb($breadcrumb);
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
