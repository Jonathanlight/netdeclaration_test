<?php

try { 

  if (!$req->getUser()->isModerator()) {
    throw new PrivilegeException(l('error.privilege'));
  }

  $item = Item::getInstanceByKey($req->item_key); 

  $req->track();

  if (Extension::exists('board') && $item->getModelId() == Model::id('topic')) {
    $res->sendRedirect($item->getForum());
    $item->destroy();
  }
  elseif ($item->getModelId() == Model::id('comment')) {
    $res->sendRedirect();
    $item->destroy();
  }
  else {
    throw new Exception('Attention ! This kind of item can not be detroyed.');
  }

}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }