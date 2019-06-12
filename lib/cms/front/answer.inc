<?php

try {

  $component = Component::getInstance((int) $req->id,
                                      array('include' => array('faq')));

  if (!$component->getFaq()->isOnline()) {
    throw new MaliciousException();
  }
  
  $res->sendMessage($component->content);

}
catch (Exception $e) { $err->add($e); }
