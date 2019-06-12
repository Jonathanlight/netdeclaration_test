<?php

try {

  $adherent = Adherent::getInstance((int) $req->id);
  $view_only = (int) $req->view_only;
  $include_forfait = (int) $req->include_forfait;
  $check_souscription_already_created = (int) $req->check_souscription_already_created;
  $date_today = Date::today();
  $date_today = empty($req->date) ? Date::today() : Date::toDb($req->date);

  $rapport = $adherent->renewSouscriptions($date_today,
                                           $view_only,
                                           false,
                                           $include_forfait,
                                           $check_souscription_already_created);

  $ctx->rapport = $rapport;

  $res->useTemplate();

}
catch (Exception $e) {
  $log->error($e);
}
