<?php

try {


  $factures = Facture::collect();
  $html = '';
  foreach ($factures as $facture) {
    $context = new Context();

    $context->facture = $facture;
    $context->no_skeleton = $facture;

    $context->address = $facture->data_address;
    $context->adherent = $facture->data_adherent;
    $context->purchases = $facture->data_purchases;
    $context->prices = $facture->data_prices;

    $html .= H::inc('facture.print', $context).'<hr />';
  }

  //$ctx->_keep_templates = true;

  $res->useTemplates(array(null));
  $res->setLink('stylesheet', array('href' => '/app/ntd/styles/front.css', 'type' => 'text/css'));
  $res->setLink('stylesheet', array('href' => '/app/ntd/styles/account.css', 'type' => 'text/css'));
  $res->setLink('stylesheet', array('media' => 'print', 'href' => '/app/ntd/styles/print.css', 'type' => 'text/css'));
  $res->setTitle($facture->getType() . ' N°' . $facture->getId());
  $res->write(H::head() . $html . H::foot());
}
catch (Exception $e) {
  $err->add($e);
}
