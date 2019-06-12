<?php

try {

  $models = array(
    'dectype',
    'dicoedi',
    'formulairetype',
    'ifield',
    'imodel',
    'itemplate',
    'millesime',
    'operation',
    'rof',
    'service',
  );

  $export = array();
  foreach ($models as $model) {
    $items = Item::collect($model);
    /*$items_metas = Item::collect($model,
                                 array('order' => array('md.updated_at' => 'ASC'),
                                       'metas' => array('updated_at')));*/
    $export[$model]['count'] = $items->count();
//    $export[$model]['metas_count'] = $items_metas->count();
//    $export[$model]['last_updated_at'] = $items_metas->first()->getMeta('updated_at');
  }

  $res->write(var_export($export, true));
  $res->setFormat(Response::FORMAT_TEXT);
  $res->useTemplates(array(null));

}
catch (Exception $e) {
  $err->add($e);
}