<?php

try { 

  if ($req->hasAttribute('code', true)) {
    $letter = Letter::getInstance($req->code, 
                                  array('properties' => true));
    $ctx->subject = $letter->subject;
    $ctx->body = $letter->body;
    $ctx->from_name = $letter->from_name;
    $ctx->from_email = $letter->from_email;
    $ctx->cc = $letter->cc_set;
    $ctx->bcc = $letter->bcc_set;
  }

  $res->useXml();

}
catch (Exception $e) { $err->add($e); }
