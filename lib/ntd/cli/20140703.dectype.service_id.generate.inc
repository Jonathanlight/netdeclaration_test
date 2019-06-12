<?php

try {

  foreach (Dectype::collect() as $dectype) {
    $dectype->setAttribute('service_id',
                           Service::exists(array('document_code' => $dectype->document_code,
                                                 'type' => Service::TYPE_FORMULAIRE)));
  }

}
catch (Exception $e) {
  print $e->getMessage();
}