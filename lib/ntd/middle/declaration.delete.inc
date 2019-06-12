<?php

try {

  $declaration = Declaration::getInstance((int) $req->id);
  if ($declaration->status != Declaration::STATUS_EDITABLE) {
    throw new Exception('La déclaration N°' . $declaration->getId() . ' ne peut pas être supprimée.');
  }

  $declaration->destroy();
  $res->sendMessage('La déclaration N°' . $declaration->getId() . ' a bien été supprimée.');

}
catch (Exception $e) {
  $err->add($e);
}
