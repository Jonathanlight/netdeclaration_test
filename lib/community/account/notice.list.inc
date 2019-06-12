<?php

try { 

  $opts = array('filters' => array('|&|flags' => Notice::FLAG_ACCOUNT),
                'order' => array('position' => 'ASC'));

  if (!Extension::exists('social')) {
    $opts['filters']['|<>|id'] = Notice::INBOX;
  }

  $notices = Notice::collect($opts);

  $ctx->all_notices = $notices;
  $ctx->user_notices = $user->getNotices();

  $res->setMenu('notices');
  $res->setTitle(l('account.notices'));

}
catch (Exception $e) { $err->add($e); }
