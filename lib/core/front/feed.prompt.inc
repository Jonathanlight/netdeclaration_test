<?php

try {

  $url = $req->url;

  if (strtolower(substr($url, 4)) != 'http') {
    $url = 'http://'.P('app.domain').$url;
  }

  $ctx->snippet = Snippet::getInstance('feed.prompt',
                                       array('properties' => array('title', 
                                                                   'content')));
  $ctx->url = $url;

  $res->useTemplate();

}
catch (Exception $e) { $err->add($e); }
