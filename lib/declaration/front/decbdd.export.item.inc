<?php

try {

  $req->debug();

  $model = $req->model;
//  $limit = (int) $req->limit;
//  $page = (int) $req->page;
  $ids = (array) $req->ids;

  $export = array();
  $items = Item::collect($model, array('order' => array('id' => 'ASC'),
                                       //                                       'limit' => $req->limit,
                                       //                                       'offset' => $req->offset,
                                       'filters' => array(
//                                         '|>|id' => ($page - 1) * $limit,
//                                         '|<=|id' => $page * $limit,
'|IN|id' => $ids
                                       )));

//  S('log')->debug($items->asSql(), __METHOD__);
  foreach ($items as $item) {
    $export[$model][$item->getId()] = $item->getAttributes();
    foreach ($item->getProperties() as $name => $value) {
      $export[$model][$item->getId()]['property_' . $name] = $value;
    }
  }

//  $export['last_id'] = $items->count() > 0 ? $items->last()->getId() : '0';

//  $table_status = S('dbo')->fetchHash("SHOW TABLE STATUS LIKE '" . T($model) . "'");
//  $export['next_increment_id'] = $table_status['Auto_increment'];

  $res->write(var_export($export, true));
  $res->setFormat(Response::FORMAT_TEXT);
  $res->useTemplates(array(null));

}
catch (Exception $e) {
  $err->add($e);
  $res->useTemplates(array(null));
}