<?php

try {

  $facture = Facture::getInstance((int) $req->id);

  $prices = $facture->data_prices;
  $prices['price_ht'] = 0;
  $prices['price_ttc'] = 0;
  $prices['price_tva'] = 0;
  $facture->setAttribute('data_prices', $prices);
  $facture->setAttribute('price_ttc', 0);

  $res->sendMessage('Le montant de cette facture a été passée à 0 euros.');

}
catch (Exception $e) {
  $err->add($e);
}
