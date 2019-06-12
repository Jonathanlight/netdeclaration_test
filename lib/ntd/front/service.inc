<?php

try {

  $service = Service::getInstance((int) $req->id);
  $servicetype = $service->getServicetype();
  $service->track();

  $ctx->service = $service;
  $ctx->servicetype = $servicetype;

  $res->setBreadcrumb(array('page d\'accueil' => '/',
                            $servicetype->getProperty('title') => $servicetype->asUrl(),
                            strip_tags($service->getProperty('title')) => $service->asUrl()));
  $res->setSeo(array('title' => strip_tags($service->getProperty('title')),
                     'description' => $service->getProperty('description')));
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}