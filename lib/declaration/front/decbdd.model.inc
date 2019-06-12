<?php

try {

  $req->debug();

  if (P('app.state') != 'dev') return;

  $model = $req->model;

  $limit = $model == 'itemplate' ? 50 : 10;
  $record_ids = (array) $req->ids;

  $ctx->exports = DecBdd::getAll('decbdd.export.item',
                                 array('model' => $model,
                                       'ids' => $record_ids));

  // comparaison par ID
  $max_last_id = 0;
  $max_next_increment_id = 0;
  $ctx->last_id = array();
  foreach ($ctx->exports as $app => $export) {
    $max_last_id = max($max_last_id, $export['last_id']);
    $max_next_increment_id = max($max_next_increment_id, $export['next_increment_id']);
    $ctx->last_id[$app] = $export['next_increment_id'];
  }
  $ctx->max_last_id = $max_last_id;
  $ctx->max_next_increment_id = $max_next_increment_id;
  $ctx->max_item_id = $max_next_increment_id - 1;
  $ctx->limit = $limit;
  $ctx->model = $model;
  $ctx->reference_app = null;
  $ctx->apps = array_keys(DecBdd::$apps);
  foreach (DecBdd::$apps as $app => $hostname) {
    $ctx->reference_app = $app;
    break;
  }


  ///////////////
  $rows = array();
//  for ($id_counter = 1 + (($page - 1) * $limit); $id_counter <= ($page * $limit); $id_counter++) {
  foreach($record_ids as $record_id) {
    $row = array('id' => $record_id,
                 'class' => array(),
                 'diff' => array(),
                 'fields' => array(),
                 'items' => array(),
                 'app_reference' => null,
                 'item_reference' => null,
                 'are_all_same' => true);


    // ----- Is at least one set ? No => continue
    $is_at_least_one = false;
    foreach (DecBdd::$apps as $app => $hostname) {
      $is_at_least_one = $is_at_least_one || isset($ctx->exports[$app][$model][$record_id]);
    }
    if (!$is_at_least_one) {
      continue;
    }


    // ----- Set the reference item
    foreach (DecBdd::$apps as $app => $hostname) {
      $row['item_reference'] = (array) $ctx->exports[$app][$model][$record_id];
      break;
    }


    // ----- find field containing differences
    foreach (DecBdd::$apps as $app => $hostname) {
      if ($app == $ctx->reference_app) {
        continue;
      }

      $item = (array) $ctx->exports[$app][$model][$record_id];
      $has_diff = (strcmp(md5(var_export($row['item_reference'], true)), md5(var_export($item, true))) !== 0);

      $row['are_all_same'] = $row['are_all_same'] && !$has_diff;
      if (!$has_diff) {
        // S('log')->trace('!$has_diff', __FILE__);
//        continue;
      }

      foreach ($row['item_reference'] as $field => $value) {
        if ($item[$field] === $value) {
          continue;
        }
        $row['fields'][$field] = $field;
      }
      foreach ($item as $field => $value) {
        if ($row['item_reference'][$field] === $value) {
          continue;
        }
        $row['fields'][$field] = $field;
      }
    }

    $row['fields']['name'] = 'name';
    foreach (DecBdd::$apps as $app => $hostname) {
      foreach ($row['fields'] as $field) {
        $row['values'][$app][$field] = array(
          'value' => $ctx->exports[$app][$model][$record_id][$field],
          'is_diff' => $ctx->exports[$app][$model][$record_id][$field] !== $ctx->exports[$ctx->reference_app][$model][$record_id][$field],
        );
      }
    }

    // ----- include in results ?

//    if (count($row['fields']) < 1) {
    if ($row['are_all_same']) {
//      continue;
    }
    $rows[] = $row;
  }

  $ctx->rows = $rows;

  $res->setFormat(Response::FORMAT_JSON);
//  $res->useTemplates(array(null, 'skeleton.decbdd', true));

}
catch (Exception $e) {
  $err->add($e);
}