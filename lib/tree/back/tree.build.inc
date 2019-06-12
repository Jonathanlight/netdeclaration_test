<?php

try {

  $tree = Tree::getInstance($req->id);
  $tree->build();

  $res->sendMessage('construction effectuée.');

}
catch (Exception $e) { $err->add($e); }