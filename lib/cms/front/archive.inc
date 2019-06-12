<?php

try { 

   $month = $req->hasAttribute('month', true) ? $req->month : date('m');
   $year = $req->hasAttribute('year', true) ? $req->year : date('Y');
   $filters = array('|M|publication_date' => $month,
                    '|Y|publication_date' => $year,
                    'heading_id' => 1);
   $opts = array('filters' => $filters,
                 'order' => array('publication_date' => 'DESC'));

  $filters = array('heading_id' => 1);
  
  $opts = array('filters' => $filters,
                'include' => 'heading',
                'limit' => 10,
                'offset' => (int)$req->offset,
                'order' => array('published_at' => 'DESC'));
  
  $articles = Article::collect($opts);
  
  $ctx->articles = $articles;
  $ctx->year = (int) $year;
  $ctx->month = (int) $month;
  
  $res->setSeo('archive');
  $res->useTemplate();
  
}
catch (Exception $e) { $err->add($e); }
