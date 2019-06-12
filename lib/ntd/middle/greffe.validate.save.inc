<?php

try {

  $greffe = Greffe::getInstance((int)$req->id);
  if (!$greffe->hasAllDocuments() && $greffe->status >= Greffe::STATUS_VALID) {
    throw new Exception(l('error'));
  }

  $greffe->setStatus(Greffe::STATUS_VALID);
  $res->sendRedirect('/middle/greffe.validate/-/id/' . $greffe->getId());

}
catch (Exception $e) { $err->add($e); }