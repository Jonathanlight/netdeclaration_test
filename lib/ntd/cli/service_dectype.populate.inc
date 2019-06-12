<?php

try {

  foreach (Dectype::collect() as $dectype) {
    if ($dectype->service_id > 0) {
      S('dbo')->insert('ntd_service_dectype',
                       array('service_id' => $dectype->service_id,
                             'dectype_id' => $dectype->getId()));
    }

  }

}
catch (Exception $e) {
  $err->add($e);
}