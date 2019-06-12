<?php

try {

  $ftype = Formulairetype::getInstance($req->ftype_id);
  $millesime = Millesime::getInstance($req->millesime_id);

  if($req->ifields) {

    foreach ($ftype->getIfields() as $ifield) {
      if (!in_array($millesime->getId(), $ifield->getMillesimes()->asSet('id'))) {
        $millesimes = $ifield->getMillesimes()->asSet('id');
        $millesimes[] = $millesime->getId();
        foreach ($millesimes as $millesime) {
          $ifield->addMillesime($millesime);
        }
        print $ifield->code."\n";
      }
    }
  }

  if($req->operations) {

    foreach ($ftype->getOperations() as $operation) {
      if (!in_array($millesime->getId(), $operation->millesimes)) {
        $millesimes = $operation->millesimes;
        $millesimes[] = $millesime->getId();
        $operation->commit(array('millesimes' => $millesimes));
        print $operation->name."\n";
      }
    }
  }

}
catch (Exception $e) {
  $err->add($e);
}
