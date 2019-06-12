<?php

try {

  $formulairetypes = Formulairetype::collect();
  foreach ($formulairetypes as $formulairetype) {
    $millesimes = getMillesimes($formulairetype)->asSet('id');
    $records = array();

    foreach ($millesimes as $millesime_id) {
      if (!Millesime::exists((int)$millesime_id)) {
        S('log')->trace('unknown millesime_id #' . $millesime_id . ' on ftype #' . $formulairetype->getId());
        continue;
      }

      $_millesimes = S('dbo')->query('SELECT millesime_id FROM `'.Formulairetype::TABLE_MILLESIME.'` WHERE formulairetype_id = ' . $formulairetype->getId())
                             ->asSet('millesime_id');
      if (!in_array($millesime_id, $_millesimes)) {
        $record = array(
          'formulairetype_id' => $formulairetype->getId(),
          'millesime_id'      => (int)$millesime_id,
          'is_repetable'      => $formulairetype->hasFlag(Formulairetype::FLAG_REPETABLE) ? 1 : 0,
          'is_v1'             => $formulairetype->hasFlag(Formulairetype::FLAG_OLD_SYSTEM) ? 1 : 0
        );
        S('dbo')->insert(Formulairetype::TABLE_MILLESIME, $record);
      }
    }
  }

} catch (Exception $e) {
  $err->add($e);
}

function getMillesimes($ftype) {
  if ($ftype->hasFlag(Formulairetype::FLAG_OLD_SYSTEM)) return Millesime::collect();
  return Millesime::collect(array('filters' => array('|IN|id' => $ftype->millesimes)));
}
