<?php

try {

  $item = Item::getInstance(MODEL, $req->id);

  $rs = $dbo->query('SELECT a.*, u.*'
                    .' FROM '.ACL::TABLE.' AS a,'
                    .     ' '.T('user').' AS u'
                    .' WHERE a.user_id=u.id'
                    .  ' AND a.model_id='.$item->getModelId()
                    .  ' AND a.record_id='.$item->getId()
                    .' ORDER BY u.email'); 

  $users = $rs->asCollection('user');

  $ctx->users = $users;

  $res->useTemplates('//acl');

}
catch (Exception $e) { $err->add($e); }
