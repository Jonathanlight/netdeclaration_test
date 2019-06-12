<?php

try {

  if(P('app.state') != 'dev') return;

  $model = $req->model;

  $limit = $model == 'itemplate' ? 50: 1000;
  $page = max(1, (int) $req->page);

  $ctx->exports = $ctx->exports = DecBdd::getAll('decbdd.export.item',
                                                 array('model' => $model,
                                                       'limit' => $limit,
                                                       'page' => $page));

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
  $ctx->limit = $limit;
  $ctx->model = $model;
  $ctx->page = $page;


  ///////////////
  $rows = array();
  for ($id_counter = 1; $id_counter <= $max_last_id; $id_counter++) {
    $row = array('id' => $id_counter,
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
      $is_at_least_one = $is_at_least_one || isset($ctx->exports[$app][$model][$id_counter]);
    }
    if (!$is_at_least_one) {
//      S('log')->trace('!$is_at_least_one', __FILE__);
      continue;
    }


    if ($model == 'ifield') {
      foreach (DecBdd::$apps as $app => $hostname) {
        unset($ctx->exports[$app][$model][$id_counter]['formulairetype_id']);
      }
    }

    // ----- Set the reference item
    foreach (DecBdd::$apps as $app => $hostname) {
      $row['app_reference'] = $app;
      $row['item_reference'] = (array) $ctx->exports[$app][$model][$id_counter];
      break;
    }



    // ----- find field containing differences
    foreach (DecBdd::$apps as $app => $hostname) {
      if ($app == $row['app_reference']) {
        continue;
      }

      $item = (array) $ctx->exports[$app][$model][$id_counter];
      $has_diff = (strcmp(md5(var_export($row['item_reference'], true)), md5(var_export($item, true))) !== 0);

      $row['are_all_same'] = $row['are_all_same'] && !$has_diff;
      if (!$has_diff) {
        // S('log')->trace('!$has_diff', __FILE__);
        continue;
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
        if($model == 'itemplate' && in_array($field, array('psp', 'html'))) {
        //  continue;
        }
        $row['values'][$app][$field] = array(
          'value' => $ctx->exports[$app][$model][$id_counter][$field],
          'is_diff' => $ctx->exports[$app][$model][$id_counter][$field] !== $ctx->exports[$row['app_reference']][$model][$id_counter][$field],
        );
      }
    }

    // ----- include in results ?

//    if (count($row['fields']) < 1) {
    if ($row['are_all_same']) {
      continue;
    }
    $rows[] = $row;
  }

  $ctx->rows = $rows;

  $res->useTemplates(array(null, 'skeleton.decbdd', true));

}
catch (Exception $e) {
  $err->add($e);
}