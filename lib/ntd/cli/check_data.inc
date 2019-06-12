<?php

try {

  print "Vérification des données en BDD : \n";
  if ($req->adherent) {

    $adherents = Adherent::collect();
    foreach ($adherents as $adherent) {
      $adherents_status[$adherent->status]++;

      $souscription_actives = $adherent->getAllSouscriptionsActive();
      foreach ($souscription_actives as $souscription_active) {
        if ($souscription_active->service_id == NetDeclarationManager::SERVICE_ADHESION_MAIN_PROFILE) {
          $adherents_services[NetDeclarationManager::SERVICE_ADHESION_MAIN_PROFILE]++;
        }
        elseif ($souscription_active->service_id == NetDeclarationManager::SERVICE_ADHESION_PROFILE_SECONDAIRE) {
          $adherents_services[NetDeclarationManager::SERVICE_ADHESION_PROFILE_SECONDAIRE]++;
        }
        if ($souscription_active->service_id == NetDeclarationManager::SERVICE_ACCES_EDI) {
          $adherents_services[NetDeclarationManager::SERVICE_ACCES_EDI]++;
        }
      }
    }
    print $adherents->count() . " Adhérents\n";
    foreach ($adherents_status as $status => $count) {
      print " - Status (" . Adherent::$statuses[$status] . ") : $count\n";
    }

    foreach ($adherents_services as $service_id => $count) {
      $service = Service::getInstance($service_id);
      print " - Service Souscris (" . $service->name . ") : $count\n";
    }
  }
  if ($req->facture) {

    $sql = "SELECT a.id
          FROM ntd_adherent a
          WHERE a.user_id NOT IN (SELECT u.id FROM cty_user u)";
    print "Adhérent dont le user n'existe plus : " . implode(', ', $dbo->asSet($sql)) . "\n";

    $sql = "SELECT s.id
          FROM ntd_souscription s
          WHERE s.adherent_id NOT IN (SELECT a.id FROM ntd_adherent a)";
    print "Souscription dont l'adherent n'existe plus : " . implode(', ', $dbo->asSet($sql)) . "\n";

    foreach (Facture::collect(array('filters' => array('adherent_id' => 0))) as $facture) {
      print " - Facture avec adherent = 0 (" . $facture->getId() . ")\n";
    }
    $sql = "SELECT f.id
            FROM ntd_facture f
            WHERE f.adherent_id NOT IN (SELECT a.id FROM ntd_adherent a)";
    print "Facture dont l'adherent n'existe plus : " . implode(', ', $dbo->asSet($sql)) . "\n";
  }

  if ($req->souscription) {

    $sql = "SELECT a.siret,
             s1.adherent_id,
             s1.id as s1_id,
             s1.start_at as s1_start_at,
             s1.finish_at as s1_finish_at,
             s1.status as s1_status,
             s1.souscription_renew_id as s1_souscription_renew_id,
             s2.id as s2_id,
             s2.start_at as s2_start_at,
             s2.finish_at as s2_finish_at,
             s2.status as s2_status,
             s2.souscription_renew_id as s2_souscription_renew_id
      FROM ntd_souscription s1, ntd_souscription s2, ntd_adherent a
      WHERE s1.adherent_id = s2.adherent_id
        AND s1.service_id = s2.service_id
        AND s1.id < s2.id
        AND s1.status != -20
        AND s2.status != -20
        AND s1.start_at != s2.finish_at
        AND s1.finish_at != s2.start_at
        AND (   (s1.start_at BETWEEN s2.start_at AND s2.finish_at)
             OR (s1.finish_at BETWEEN s2.start_at AND s2.finish_at))
        AND a.id = s1.adherent_id"; //
    $souscriptions = $dbo->asArray($sql);
    foreach ($souscriptions as $souscription) {
      $body .= $souscription['siret'] . '[' . $souscription['adherent_id'] . ']<br />';
      $body .= $souscription['s1_id'] . ' : ' . $souscription['s1_start_at'] . ' -> ' . $souscription['s1_finish_at'] . ' (état : ' . $souscription['s1_status'] . ')<br />';
      $body .= $souscription['s2_id'] . ' : ' . $souscription['s2_start_at'] . ' -> ' . $souscription['s2_finish_at'] . ' (état : ' . $souscription['s2_status'] . ')<br /><br />';

      //if ($req->repair) {
      // $_souscription = Souscription::getInstance($souscription['s1_id']);
      //$_souscription->setAttribute('status', Souscription::STATUS_CANCELLED);
      //}
    }
    print 'Souscription qui se chevauche : ' . count($souscriptions) . "\n";
  }


  if ($req->adherent_edi) {

    // Adhérents n'ayant le service Accès EDI, alors qu'ils ont des services EDI,
    // et vice-versa
    $adherents = Adherent::collect();
    foreach ($adherents as $adherent) {
      $souscriptions = $adherent->getSouscriptions(array('filters' => array('|<|start_at' => Date::today(),
                                                                            '|>|finish_at' => Date::today(),
                                                                            'status' => Souscription::STATUS_ACTIVE)));
      $has_service_edi = false;
      $has_acces_edi = false;
      foreach ($souscriptions as $souscription) {
        $service = $souscription->getService();
        if ($service->getId() == NetDeclarationManager::SERVICE_ACCES_EDI) {
          $has_acces_edi = true;
        }
        elseif ($service->type == Service::TYPE_EDI) {
          $has_service_edi = true;
        }
      }
      if ($has_service_edi && !$has_acces_edi) {
        $body .= "ERREUR Pas d'accès EDI et au moins 1 Service EDI : Adherent [" . $adherent->getId() . "]\n";
      }
      elseif (!$has_service_edi && $has_acces_edi) {
        {
          $body .= "ERREUR Accès EDI et aucun Service EDI : Adherent [" . $adherent->getId() . "]\n";
        }
      }
    }
  }


  if ($req->declaration_suivi_id) {
    foreach (Declaration::collect() as $declaration) {
      if ($declaration->suivi_id > 0 && !Suivi::exists(array('declaration_id' => $declaration->getId()))) {
        print 'ERROR : Declaration lié à un suivi : ' . $declaration->getId() . "\n";
      }
    }
  }

  if ($req->declaration_suivi_id2) {
    foreach (Declaration::collect() as $declaration) {
      if ($declaration->suivi_id != Suivi::exists(array('declaration_id' => $declaration->getId()))) {
        print 'Declaration non liée à son suivi : Declaration[' . $declaration->getId() . '] suivi_id['.$declaration->suivi_id.'] Suivi[' . Suivi::exists(array('declaration_id' => $declaration->getId())) . ']'."\n";
        if($req->fix == 1) {
          $declaration->setAttribute('suivi_id', Suivi::exists(array('declaration_id' => $declaration->getId())));
        }
      }
    }
  }

  print str_replace('<br />', "\n", $body);

  $mail = new Mail();
  $mail->setSubject('[NTD][Check data] Rapport');
  //file_put_contents('doc/ntd/rapport.txt', $body);
  $mail->setBody(nl2br($body));
  $mail->addRecipient('npinchon@kernix.com');
//  $mail->send();

}
catch (Exception $e) {
  print $e->getMessage();
}
