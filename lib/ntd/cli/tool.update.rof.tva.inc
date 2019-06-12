<?php

try {

  $document_code = Formulairetype::DOCUMENT_CODE_TVA;

  foreach (range(1, 999) as $key => $value) {
    $params = array('document_code' => $document_code,
                    'name'          => 'TVA' . $value);

    if (!Rof::exists($params)) {
      $rof = Rof::getInstance(true);
      $rof->commit($params);
    }
  }

} catch (Exception $e) {
  $err->add($e);
}
