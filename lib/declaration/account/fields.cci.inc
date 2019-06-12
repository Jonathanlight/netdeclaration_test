<?php

try {

  $res->setFormat(Response::FORMAT_TEXT);

  if (!$req->hasAttribute('id', true)) {
    throw new Exception(l('error'));
  }


  $field = Ifield::getInstance((int)$req->id);

  $filters = array(
    'code_table' => $field->getTableEDI(),
    array(
      array(array('|%%|name' => $req->query)),
      array('OR' => array(array('|%%|value' => $req->query))),
    )
  );
  $dicoedis = Dicoedi::collect(array('filters' => $filters));

  $ctx->options = $dicoedis->asHash('value', 'name');

  $res->resetTemplates();
  $res->useTemplate();

} catch (Exception $e) {
  $err->add($e);
}
