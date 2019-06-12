<?php

try {

  $offset = (int) $req->offset;
  $opts = array('filters' => array('|IN|status' => array(Declaration::STATUS_EDITABLE,
                                                         Declaration::STATUS_READY_TO_SEND,
                                                         Declaration::STATUS_SENT_TO_TRADXPRESS,
                                                         Declaration::STATUS_RECEIVED_BY_TRADXPRESS),
                                   'suivi_id' => 0),
                'metas' => 'updated_at',
                'order' => array('md.updated_at' => 'desc'),
                'limit' => 10,
                'offset' => $offset);

  $declarations = $ctx->_current_adherent->getDeclarations($opts);

  $ctx->declarations = $declarations;
  $ctx->offset = $offset;

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_DECLARATION);
  NtdMiddleManager::setBreadCrumb();
  NtdMiddleManager::useTemplate();
  NtdMiddleManager::setSEO();


}
catch (Exception $e) {
  $err->add($e);
}
