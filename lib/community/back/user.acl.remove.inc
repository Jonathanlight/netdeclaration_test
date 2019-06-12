<?php

try {

  $user = User::getInstance($req->id);

  ACL::removeAccess($user, Item::getInstanceByKey($req->item_key));

}
catch (Exception $e) { $err->add($e); }
