<?php

try {

  $ctx->servicetypes = HomepageHelper::getServiceTypes();
  $ctx->services = HomepageHelper::getServices();
  $ctx->forwho_pages = HomepageHelper::getForWhoPages();

  $ctx->snippet_introduction = Snippet::getInstance(HomepageHelper::SNIPPET_INTRODUCTION_CODE);
  $ctx->snippet_services = Snippet::getInstance(HomepageHelper::SNIPPET_SERVICES_CODE);
  $ctx->snippet_forwho = Snippet::getInstance(HomepageHelper::SNIPPET_FORWHO_CODE);
  $ctx->snippet_payment = Snippet::getInstance(HomepageHelper::SNIPPET_PAIEMENT_CODE);
  $ctx->snippet_partenaires = Snippet::getInstance(HomepageHelper::SNIPPET_PARTENAIRES_CODE);

  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}