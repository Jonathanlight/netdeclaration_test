<?php

try {

  $model = $req->model;
  if (Model::id($model) < 1) {
    print 'Model not found';
    return;
  }
  $from_id = (int) $req->from;
  $to_id = (int) $req->to;
  $group_count = 20;

  foreach (range($from_id, $to_id, min($group_count, $to_id - $from_id)) as $step) {

    print $step . "\n";
    print strip_tags(H::get(H::url('/decbdd.item.sync', null, array('app' => App::getInstance('xmiddle'))),
                            array('from_app' => 'dev',
                                  'to_app' => 'preprod',
                                  'mode' => 'sync',
                                  'model' => $model,
                                  'ids' => range($step, $step + $group_count)),
                            array('ttl' => 0))) . "\n";
  }

}
catch (Exception $e) {
  $err->add($e);
}