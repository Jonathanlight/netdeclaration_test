<?php

try {

  $adherent = Adherent::getInstance((int) $req->id);
  $date_today = Date::today();
  $view_only = (int) $req->view_only;
  $date_today = empty($req->date) ? Date::today() : Date::toDb($req->date);
  //$date_today = '2012-07-01';
  $rapport = $adherent->renewSouscriptionsNew($date_today, $view_only, false);
  $ctx->rapport = $rapport;
  $res->useTemplate();

}
catch (Exception $e) {
  $ctx->rapport = $e->getMessage();
  $log->error($e);
}
