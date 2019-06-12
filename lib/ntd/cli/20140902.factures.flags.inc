<?php

try {

  foreach (Facture::collect(array('filters' => array('type' => Facture::TYPE_FACTURE))) as $facture) {
    $start_at = strtotime($facture->start_at);
    if ($start_at < strtotime(Date::today())) {
      $facture->setFlag(Facture::FLAG_RAPPEL_1);
    }
    if ($start_at < date('Y-m-d', strtotime('- 20 days'))) {
      $facture->setFlag(Facture::FLAG_RAPPEL_2);
    }
    if ($start_at < date('Y-m-d', strtotime('- 40 days'))) {
      $facture->setFlag(Facture::FLAG_RAPPEL_3);
    }
  }

}
catch (Exception $e) {
  $err->add($e);
}