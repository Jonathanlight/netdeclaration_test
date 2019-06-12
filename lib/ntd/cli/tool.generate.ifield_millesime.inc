<?php

try {

  $ifields = Ifield::collect();
  foreach ($ifields as $ifield) {
    $millesimes = $ifield->millesimes;
    $records = array();

    foreach ($millesimes as $millesime_id) {
      if (!Millesime::exists((int)$millesime_id)) {
        S('log')->trace('unknown millesime_id #' . $millesime_id . ' on ifield #' . $ifield->getId());
        continue;
      }

      $_millesimes = S('dbo')->query('SELECT millesime_id FROM `'.Ifield::TABLE_MILLESIME.'` WHERE ifield_id = ' . $ifield->getId())
                             ->asSet('millesime_id');
      if (!in_array($millesime_id, $_millesimes)) {
        $record = array(
          'ifield_id'     => $ifield->getId(),
          'millesime_id'  => $millesime_id,
          'is_extensible' => $ifield->indice_donnee == '0001'
        );
        S('dbo')->insert(Ifield::TABLE_MILLESIME, $record);
      }
    }
  }

} catch (Exception $e) {
  $err->add($e);
}
