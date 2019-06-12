<?php

try {

  $edimessage = Edimessage::getInstance((int)$req->id);
  $ctx->edimessage = $edimessage;

  $args = array('order' => array('no_donnees' => 'ASC'));
  $ctx->edimessagerows = $edimessage->getEdimessagerows($args);

  $ctx->print = $req->hasAttribute('print');
  if (!$req->hasAttribute('print')) {
    NtdMiddleManager::useTemplate(false);
  }
  else {
    $res->useTemplates(null, 'skeleton.pdf', 'app/ntd/templates/middle/suivi.edimessage.psp');
  }

}
catch (Exception $e) {
  $err->add($e);
}
