<?php

try {

  $type_compte = $req->type_compte;
  $forme_juridique = $req->forme_juridique;
  $is_gerant = (int)$req->is_gerant > 0;
  $mode_direction = $req->mode_direction;
  $compte_public = $req->is_public;

  $docs = array();
  foreach (GreffeManager::getRequiredDocs($type_compte, $forme_juridique, $is_gerant, $mode_direction, $compte_public) as $doc) {
    $docs[$doc] = GreffeManager::$docs[$doc];
  }
  $ctx->docs = $docs;

  NtdMiddleManager::useTemplate(false);

}
catch (Exception $e) { $log->error($e); }