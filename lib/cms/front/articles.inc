<?php

try {

  $filters = array('status' => 1);
  if ($req->hasAttribute('heading_id')) {
    $filters['heading_id'] = (int) $req->heading_id;
  }
  if ($req->hasAttribute('tag')) {
    $filters['|TAG|'] = $req->tag;
  }
  if ($req->hasAttribute('interest_id')) {
    $filters['|INTEREST|'] = (int) $req->interest_id;
  }

  $opts = array('filters' => $filters,
                'limit' => 3,
                'offset' => (int) $req->offset,
                'order' => array('published_at' => 'DESC'));
  $articles = Article::collect($opts);

  $ctx->articles = $articles;

  $res->setSeo('Articles');
  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }