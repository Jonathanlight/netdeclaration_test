<?php

try {

  $campaign_id = (int) ($req->knxcid > 0 ? $req->knxcid : $req->campaign_id);
  $email_id = (int) ($req->eid > 0 ? $req->eid : $req->email_id);

  if ($req->hash !== String::crypt($campaign_id.$email_id)) {
    throw new Exception();
  }

  $campaign = Campaign::getInstance($campaign_id);
  $email = Email::getInstance($email_id);

  if ($req->confirm == 1) {
    foreach ($campaign->bases as $base_id) {
      if (Base::exists($base_id)) {
        $base = Base::getInstance($base_id);
        $base->removeEmail($email->email);
      }
    }

    $type = $campaign->hasFlag(Campaign::FLAG_BLACKLIST)
          ? Act::TYPE_BLACKLIST
          : Act::TYPE_REMOVE;
    Act::add(array('email_id' => $email->getId(),
                   'campaign_id' => $campaign->getId(),
                   'type' => $type,
                   'value' => $campaign->newsletter_id));
    $ctx->is_removed = 1;
  }
  else {
    Act::add(array('email_id' => $email_id,
                   'campaign_id' => $campaign_id,
                   'type' => Act::TYPE_SUCCESS));
  }

  $ctx->email = $email_id < 1 ? 'xx@xx.xxx' : $email->email;
  $res->useTemplate();

}
catch (Exception $e) {
  $req->debug();
  $err->add(l('error.item.unknown'));
}
