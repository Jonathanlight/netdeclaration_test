<?php

try {

  $adherent = NetDeclaration::getCurrentAdherent();

  $filters = array();
  $order = array('created_at' => 'desc');
  $offset = 0;

  $offset = 0;
  if ($req->hasAttribute('search', true)) {
    $search = (array) $req->search;

    if (isset($search['periode_from']) && $search['periode_from']) {
      $filters['|>=|created_at'] = Date::toDb($search['periode_from']);
    }
    if (isset($search['periode_to']) && $search['periode_to']) {
      $filters['|<=|created_at'] = Date::toDb($search['periode_to']);
    }

    if (isset($search['status']) && $search['status'] != '') {
      $filters['status'] = (int)$search['status'];
    }

    if (isset($search['offset'])) {
      $offset = (int)$search['offset'];
    }
  }

  $dossiers = $adherent->getGreffedossiers(array('filters' => $filters,
                                                 'metas'   => array('created_at'),
                                                 'order'   => $order,
                                                 'limit'   => 5,
                                                 'offset'  => $offset));

  $ctx->dossiers = $dossiers;
  $ctx->facture = GreffeManager::getUnpaidFacture($adherent);
  $ctx->souscription = GreffeManager::getAvaillableSouscription($adherent);

  $ctx->search = $search ?: array();

  if (!$req->isXHR()) {
    NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_GREFFE);
    NtdMiddleManager::setBreadCrumb(array('Greffe'));
    NtdMiddleManager::useTemplate();
    NtdMiddleManager::setSEO();
  }
  else {
    $res->useTemplates(null,
                       'app/ntd/templates/middle/greffe.results.psp');
  }

}
catch (Exception $e) {
  $err->add($e);
}
