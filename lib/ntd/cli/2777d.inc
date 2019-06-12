<?php

try {

  $ftype = Formulairetype::getInstance('2777D');
  $ftype->build();
  foreach($ftype->getIfields() as $ifield) {
    //$ifield->commit(array('millesimes' => 4));
  }

  $ftype = Formulairetype::getInstance('P-IDENTIF');
  $ftype->build();
  foreach($ftype->getIfields() as $ifield) {
    //$ifield->commit(array('millesimes' => 4));
  }

}
catch (Exception $e) {
  $log>error($e);
}
