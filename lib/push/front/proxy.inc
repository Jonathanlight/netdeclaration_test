<?php

try {
  
  $campaign_id = (int) ($req->knxcid ?: $req->campaign_id);
  $email_id = (int) ($req->eid ?: $req->email_id);
  $url_id = (int) ($req->uid ?: $req->url_id);

  $hash = String::crypt($campaign_id.$email_id);
  
  if ($req->hash !== $hash) {
    throw new Exception('invalid hash');
  }
  
  $url = Url::asString($url_id);
  
  if (empty($url)) {
    throw new Exception('url unknown ('.$url_id.')');
  }
  
  $n = Act::add(array('email_id' => $email_id,
                      'campaign_id' => $campaign_id,
                      'type' => Act::TYPE_REDIRECTION,
                      'value' => $url_id));
  if ($n >= 1) {
    Act::add(array('email_id' => $email_id,
                   'campaign_id' => $campaign_id,
                   'type' => Act::TYPE_VISIT,
                   'value' => $req->getId()));
  }

  Act::add(array('email_id' => $email_id,
                 'campaign_id' => $campaign_id,
                 'type' => Act::TYPE_SUCCESS));
  
  $separator = strpos($url, '?') > 6 ? '&' : '?';
  $res->sendRedirect($url.$separator
                     .'email_id='.$email_id.'&campaign_id='.$campaign_id);
}
catch (Exception $e) { 
  $req->debug();
  $log->error($e); 
  $res->sendRedirect('/push/empty');
}

