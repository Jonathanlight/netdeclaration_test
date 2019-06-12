<?php

try {
  
  /*$method_id = (int) $req->method_id;
  if ($method_id < 1) {
    $res->sendMessage('Veuillez sélectionner un moyen de paiement.');
    return;
  }

  $method_details = h($req->method_details);
  $method_date = Date::toDb($req->method_date);*/

  $facture = Facture::getInstance((int) $req->id);
  $facture->commit(array('status' => Facture::STATUS_PAYE,
                         /*'method_id' => $method_id,
                         'method_details' => $method_details,
                         'method_date' => $method_date*/));

  /*$method = Method::getInstance($facture->method_id);
  $out = $method->request($facture);*/

  $res->sendMessage('Cette facture est passé en état PAYE. Les services associés ont été activés.');

}
catch (Exception $e) {
  $err->add($e);
}
