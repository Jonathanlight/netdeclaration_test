<?php

try {
  
  $mailing = Mailing::getInstance($req->id);
  $campaign = Campaign::getInstanceByItem($mailing);
  $campaign->send(Mailing::BAT_BASE_ID);

  $res->sendMessage('message envoyé');

}
catch (Exception $e) { $err->add($e); }
