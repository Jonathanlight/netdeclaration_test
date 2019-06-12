<?php

try {

  $declarations = Declaration::collect(array('include' => 'dectype',
                                               'filters' => array(T('dectype').'.code' => 'DAS2T')));

  $declaration_updated_ids = array();

  foreach ($declarations as $declaration) {
    $das2ts = $declaration->getFormulaires(array('filters' => array('formulairetype_id' => 350)));
    $das2tvs = $declaration->getFormulaires(array('filters' => array('formulairetype_id' => 351)));

    if (!$das2ts->count()) {
      continue;
    }

    $das2t = $das2ts->first();

    if (!$das2tvs->count()) {
      continue;
    }

    foreach ($das2tvs as $das2tv) {
      $das2tv_data = $das2tv->data;
      $das2tv_values = $das2tv->fields_values;

      $updated = false;
      if (empty($das2tv_data['AD']) && !empty($das2t->data['AA01'])) {
        $das2tv_data['AD'] = $das2t->data['AA01'];
        $updated = true;
      }
      if (empty($das2tv_values['AD']) && !empty($das2t->fields_values['AA01'])) {
        $das2tv_values['AD'] = $das2t->fields_values['AA01'];
        $updated = true;
      }
      if ($updated) {
        if (!in_array($declaration->id, $declaration_updated_ids)) {
          $declaration_updated_ids[] = $declaration->id;
        }
        if ($req->force) {
          $das2tv->commit(array('data' => $das2tv_data, 'fields_values' => $das2tv_values));
        }
      }
    }
  }
  S('log')->debug($declaration_updated_ids);
  S('log')->debug(count($declaration_updated_ids));

} catch (Exception $e) {
    $err->add($e);
}
