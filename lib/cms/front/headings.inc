<?php

try {

  $breadcrumb = array('dossiers');

  $filters = array('status' => 1);
  if ($req->type >= 1 && Heading::$types[$req->type]) {

    $filters['type'] = (int) $req->type;
    $breadcrumb = array(Heading::$types[$req->type] => '/ezine/headings?type='.$req->type);
  }
  $opts =  array('filters' => $filters,
                 'order' => array('position', 'name'));
  $headings = Heading::collect($opts);
  
  $articles = array();
  $opts = array('filters' => array('status' => 1),
                'limit' => 10,
                'order' => array('published_at' => 'DESC'));
  foreach ($headings as $heading) {
    $articles[$heading->getId()] = $heading->getArticles($opts);
  }

  $ctx->articles = $articles;
  $ctx->headings = $headings;
  
  $res->setSeo('e-zine');
  $res->setBreadcrumb($breadcrumb);
  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }