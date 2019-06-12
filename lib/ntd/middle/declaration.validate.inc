<?php

try {

  $declaration = Declaration::getInstanceAuth((int) $req->id, $user);

  $destinataires_labels = array();

  $destinataires = array();

  if ($declaration->getDectype()->hasFlag(Dectype::FLAG_OLD_SYSTEM) && count($declaration->getDectype()->destinataires) == 0) {
    $destinataires_labels[] = 'DGFiP';

    /*foreach ((array) $req->destinataires as $type => $hash) {
      if ($hash['checked'] < 1) continue;
      unset($hash['checked']);
      if ($type != Destinataire::TYPE_CEC) {
        continue;
      }
      foreach (array('siret' => 'SIRET',
                     'nom_1' => 'Nom 1',
                     'rue_1' => 'Rue 1',
                     'ville' => 'Ville',
                     'code_postal' => 'Code postal') as $field => $label) {
        if (empty($hash[$field])) {
          throw new Exception('Veuillez remplir le champ "' . $label . '" du destinataire CEC.');
        }
      }
      $destinataires[$type] = count($hash) > 0 ? $hash : 1;
      $destinataires_labels[] = Destinataire::$types[$type];
    }*/
  }
  else {

    foreach ((array) $req->destinataires as $type => $hash) {
      if ($hash['checked'] < 1) continue;
      unset($hash['checked']);
      if ($type == Destinataire::TYPE_OGA) {
        if (empty($hash['siretoga'])) {
          throw new Exception('Veuillez sélectionner un OGA dans la liste.');
        }
        if (empty($hash['idoga'])) {
          throw new Exception('Veuillez remplir le N° Identification à l\'OGA.');
        }
      }
      elseif ($type == Destinataire::TYPE_CEC) {
        foreach (array('no_ref_interne_cec' => 'N° de référence',
                       'siret' => 'SIRET',
                       'nom_1' => 'Nom 1',
                       'rue_1' => 'Rue 1',
                       'ville' => 'Ville',
                       'code_postal' => 'Code postal') as $field => $label) {
          if (empty($hash[$field])) {
            throw new Exception('Veuillez remplir le champ "' . $label . '" du destinataire CEC.');
          }
        }
      }
      $destinataires[$type] = count($hash) > 0 ? $hash : 1;
      $destinataires_labels[] = Destinataire::$types[$type];
    }
    if (count($destinataires) < 1) {
      throw new Exception('Veuillez choisir au moins 1 destinataire.');
    }
  }

  if ($declaration->status > Declaration::STATUS_EDITABLE) {
//    throw new Exception('Cette déclaration ne peut pas être validée. Elle a déjà été validée précédemment.');
  }
  $declaration->commit(array('status' => Declaration::STATUS_READY_TO_SEND,
                             'destinataires' => $destinataires));

  $message = 'Votre déclaration a bien été validée, et sera bientôt transmise aux destinataires suivants : ';
  $message .= implode(",\n", $destinataires_labels);
  $res->sendMessage($message);

}
catch (Exception $e) {
  $err->add($e);
}
