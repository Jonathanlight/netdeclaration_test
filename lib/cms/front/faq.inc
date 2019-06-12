<?php

try {

  $faq = Faq::getInstance($req->code);

  if (!$faq->isOnline()) {
    throw new MaliciousException();
  }

  $faq->track();

  $ctx->faq = $faq;
  $ctx->components = $faq->getComponents();

  $res->useTemplate();

}
catch (Exception $e) {
  $log->error($e);
  $err->add($e);
}