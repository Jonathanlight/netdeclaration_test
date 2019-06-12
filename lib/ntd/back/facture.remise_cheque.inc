<?php

try {


  $date = Date::toDb($req->date);

  $method = Method::getInstance(array('code' => 'cheque'));
  $payments = Payment::collect(array('filters' => array('method_id' => $method->getId(),
                                                        'paid_at' => $date)));
  $total = 0;
  $rows = array();
  foreach ($payments as $payment) {
    $factures = $payment->getFactures();
    $emetteur = '';
    if ($factures->count() == 1) {
      try {
        $emetteur = $factures->first()->getAdherent()->company;
      } catch (Exception $e) {
        S('log')->error($e, __METHOD__);
      }
    }
    if (empty($emetteur)) {
      $emetteur = $payment->description;
    }

    $row = array('Emetteur' => $emetteur,
                 'Banque' => $payment->name,
                 'Montant' => ExportEBP::amount($payment->amount));
    $rows[] = $row;
    $total += $payment->amount;
  }

  $ctx->date = $date;
  $ctx->total = ExportEBP::amount($total);
  $ctx->rows = $rows;

  $ctx->_keep_templates = true;
  $res->useTemplates(array(null, true));

}
catch (Exception $e) {
  $err->add($e);
}
