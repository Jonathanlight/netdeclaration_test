<?php

try {

  $adherent_type = (int) $req->adherent_type;
  $adherent_level = (int) $req->adherent_level;


  $opts = array('filters' => array('|%%|adherent_types' => $adherent_type,
                                   'status' => Service::STATUS_ONLINE));

  $service_efis = Service::collect(array('filters' => array('type' => Service::TYPE_FORMULAIRE,
                                                            $opts['filters']),
                                         'order' => array('position_catalogue' => 'ASC')));
  $service_edis = Service::collect(array('filters' => array('type' => Service::TYPE_EDI,
                                                            $opts['filters']),
                                         'order' => array('position_catalogue' => 'ASC')));

  $ctx->service_efis = $service_efis;
  $ctx->service_edis = $service_edis;
  $ctx->adherents = array();
  $ctx->current_adherent = array('type' => $adherent_type, 'level' => $adherent_level);

  NtdMiddleManager::useTemplate(false);

}
catch (Exception $e) {
  $err->add($e);
}