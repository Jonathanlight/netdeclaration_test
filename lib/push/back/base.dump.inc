<?php

try {

  if ($req->id < 1) {
    throw new Exception('Base inconnue');
  }

  $dbo->exec('DELETE FROM '.Base::TABLE_EMAIL
             .    ' WHERE base_id='.$req->id);

  $n = $dbo->affectedRows();

  $res->sendMessage('La base a bien été vidée : '
                    .$n.' adresse(s) supprimée(s)');

}
catch (Exception $e) { $err->add($e); }
