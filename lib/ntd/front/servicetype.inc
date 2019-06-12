<?php

try {

  $servicetype = Servicetype::getInstance((int) $req->id);
  $services = $servicetype->getServices(array('|>|status' => 0,
                                              'order' => array('type' => 'ASC')));
  $servicetype->track();

  $ctx->servicetype = $servicetype;
  $ctx->services = $services;

  $res->setSeo(array('title' => strip_tags($servicetype->getProperty('title')),
                     'description' => $servicetype->getProperty('description')));
  $res->setBreadcrumb(array('page d\'accueil' => '/',
                            strip_tags($servicetype->getProperty('title')) => $servicetype->asUrl()));
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}