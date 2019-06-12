<?php

try {

  $count1 = 0;
  $count2 = 0;
  $total = 0;
  $count_diff = 0;

  foreach (Facture::collect(array('filters' => array('type' => Facture::TYPE_FACTURE,
                                                     '|>|price_ttc' => 0))) as $facture) {
    /*foreach($facture->data_purchases as $purchase) {
      if(!Date::isNull($purchase['date_from'])) {
        print $facture->getId();
      }
    }*/
    $total++;
    $count1 += count($facture->data_purchases);
    $count2 += $facture->getSouscriptions()->count();
    if ($facture->getSouscriptions()->count() != count($facture->data_purchases)) {
      $count_diff++;
      ///continue;
      print 'facture ' . $facture->getId() . "\n";
      print 'souscription ' . $facture->getSouscriptions()->count() . "\n";
      print 'purchase ' . count($facture->data_purchases) . "\n";
      break;
    }
  }

  print 'count purchase : ' . $count1 . "\n";
  print 'count souscription : ' . $count2 . "\n";
  print 'count diff : ' . $count_diff . "\n";
  print 'Total : ' . $total . "\n";

}
catch (Exception $e) {
  $err->add($e);
}