<?php

try {

  $recovery_day = date('N');

  // Seulement le Vendredi
  if ($recovery_day == 5 || $req->hasAttribute('force')) {

    $args = array();

    $facture_list = FactureRecoveryManager::getFactureSetByAdherentToBeRecovery($args);
    if (count($facture_list) > 0) {
      $filename = FactureRecoveryManager::generateRecoveryPdf($args);

      foreach ($facture_list as $facture_set) {
        $filters = array('|IN|id' => $facture_set);
        $factures = Facture::collect(array('filters' => $filters));

        foreach ($factures as $facture) {
          $facture->setAttributes(array(
            'recovery_at' => Date::today(),
            'is_recovery' => 1
          ));
        }
      }

      $url = H::url($filename);
      $message = 'Un fichier a été généré et est disponible en téléchargement <a href="'.$url.'">ici</a>';
      $opts = array('attachments' => $filename);
    }
    else {
      $message = 'Il n\'y a aucune facture en recouvrement';
      $opts = array();
    }

    $args = array('message' => $message);

    // Send letter
    Letter::send('alert_recovery', NetDeclaration::getMailAdmin(), $args, $opts);

  }

} catch (Exception $e) {
  $err->add($e);
}
