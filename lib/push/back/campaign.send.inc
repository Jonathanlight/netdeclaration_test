<?php

try { 

  $record = $req->record;
  unset($record['status']);
  $campaign = Campaign::getInstance($req->id);
  $campaign->commit($record);
  $campaign->send($campaign->test_bases);
  $res->sendMessage('Message envoyé en mode BAT.');

}
catch (Exception $e) { $err->add($e); }

