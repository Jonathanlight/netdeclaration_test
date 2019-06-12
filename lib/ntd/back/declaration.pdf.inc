<?php

try {

  $declaration = Declaration::getInstance((int) $req->id);

  $file = $declaration->generatePdf();

  $res->sendData($file);

} catch (Exception $e) { $err->add($e); }
