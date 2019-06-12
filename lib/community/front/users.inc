<?php

try {

  $opts = array('filters' => array('|>|status' => 0));
  $ctx->users = User::collect($opts);

  $res->useTemplate();

} catch (Exception $e) { $err->add($e); }