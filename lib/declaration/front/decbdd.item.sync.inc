<?php

$res->setFormat(Response::FORMAT_TEXT);
$res->useTemplates(array(null));

try {

  $req->debug();


  // ----- IMPORT
  if ($req->mode == 'import') {

    $out = array();

    $records = (array) $req->records;
    foreach ($records as $record) {
      $attributes = null;
      $properties = null;
      eval('$attributes = '.base64_decode($record['attributes']).';');
      eval('$properties = '.base64_decode($record['properties']).';');
      $model = $record['model'];

      $id = $attributes['id'];
      if ($id < 1) {
        $out[] = '[Erreur] Id < 1. id=' . $id;
        continue;
      }

      if (!Item::exists($model, $id)) {
        $table_status = S('dbo')->fetchHash("SHOW TABLE STATUS LIKE '" . T($model) . "'");
        if ($table_status['Auto_increment'] != $id) {
          $out[] = '[Erreur] l\'Auto_increment n\'est pas bon. Auto_increment=' . $table_status['Auto_increment'] . ' model=' . $model . ' id=' . $id;
          continue;
        }
        $item = Item::getInstance($model);
      }
      else {
        $item = Item::getInstance($model, $id);
        if (method_exists($item, 'onBeforeSync')) {
          if (!$item->onBeforeSync($record)) {
            $out[] = '[Erreur] ' . ' model=' . $model . ' id=' . $id;
            continue;
          }
        }
      }

      try {
        
        $item->commit($attributes);
        if (is_array($properties)) {
          $item->setProperties($properties);
        }
        Checksum::store($item);
        $out[] = '[OK] (id=' . $id . ')(item->getId()=' . $item->getId() . ')';
//        $out[] = var_export($attributes, true);
//        $out[] = var_export($properties, true);
      }
      catch (Exception $e) {
        $out[] = '[Erreur] (id=' . $id . ')(item->getId()=' . $item->getId() . ')' . $e->getMessage();
//        $out[] = var_export($attributes, true);
      }
    }

    $res->write(var_export(array('msg' => implode("\n", $out)), true));

  }


  // ----- EXPORT
  elseif ($req->mode == 'export') {

    $ids = (array) $req->ids;
    $model = $req->model;
    foreach ($ids as $id) {
      if (!Item::exists($model, $id)) {
//        $res->write(var_export(array('msg' => 'export Erreur : cet item '.$model.' n\'existe pas. id=' . $id), true));
        S('log')->trace('export Erreur : cet item ' . $model . ' n\'existe pas. id=' . $id, __METHOD__);
        continue;
      }
      $item = Item::getInstance($model, $id);
      $export[] = array(
        'model' => $item->getModel(),
        'attributes' => base64_encode(var_export($item->getAttributes(), true)),
        'properties' => base64_encode(var_export($item->getProperties(), true))
      );
    }
    $res->write(var_export($export, true));
  }


  // ----- SYNC
  elseif ($req->mode == 'sync') {

    $from_app = $req->from_app;
    $to_app = $req->to_app;
    $model = $req->model;
    $ids = (array) $req->ids;

    $ssl = false;
    if ($from_app == 'dev') {
        $ssl = true;
    }

    $export = DecBdd::get(DecBdd::$apps[$from_app],
                          'decbdd.item.sync',
                          array('mode' => 'export',
                                'model' => $model,
                                'ids' => $ids),
                          $ssl);

    if (isset($export['msg'])) {
      $res->write('<pre>');
      $res->write(var_export($export['msg'], true) . "\n\n");
      $res->write('</pre>');
      return;
    }
    if ($to_app == 'dev') {
        $ssl = true;
    } else {
        $ssl = false;
    }
    $result = DecBdd::post(DecBdd::$apps[$to_app],
                           'decbdd.item.sync',
                           array('mode' => 'import',
                                 'records' => $export,
                           ),
                            $ssl);

    $res->write('<p class="bg-info">' . nl2br($result['msg']) . '</p>');
//    $res->write('<pre>');
//    $res->write(var_export($result, true));
//    $res->write('</pre>');
  }

}
catch (Exception $e) {
  $err->add($e);
}