<?php

try {

  $limit = P('engine.searcher.list.size') ?: 5;

  $opts = array('query' => $req->query,
                'limit' => $limit,
                'partial' => true,
                'offset' => $req->offset);

  $ctx->setAttributes(Engine::query($opts)->asHash());
  $ctx->query = $req->query;

  $res->setSeo(l('search'));

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
