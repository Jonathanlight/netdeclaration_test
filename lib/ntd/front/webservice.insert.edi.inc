<?php

$res->resetTemplates();

try {

  NetDeclarationManager::manageWebServiceAccess();

  //c:\Works\ntd>curl -s -S http://dev.ntd-dev.li.kernix.net/webservice.insert.edi --data-urlencode request@maj_err_initiale.txt


  /*
   * TEST :
INSERT 
ref_message=test1|intervenant=test|message=test|origine=test|date_depot=test|type_doc=test|sens=test|type_mess=test|type_decl=test|liste_formulaire=test|siret_emetteur=test|siret_decl=test|nom_decl=test|no_interchange=test|no_message=test|debut_periode=test|fin_periode=test|list_dest=test
suivi_id=test|ref_message=test1|no_dest=1|type_dest=test|siret=test|nom_dest=test|no_interchange=test|no_message=test|status=test|date_ack=test|message=test|flg_depot=test|flg_envoi=test|flg_ack=test
suivi_id=tata|ref_message=test1|no_dest=2|type_dest=tata|siret=tata|nom_dest=tata|no_interchange=tata|no_message=tata|status=tata|date_ack=tata|message=tata|flg_depot=tata|flg_envoi=tata|flg_ack=tata
INSERT
ref_message=test2|intervenant=test|message=test|origine=test|date_depot=test|type_doc=test|sens=test|type_mess=test|type_decl=test|liste_formulaire=test|siret_emetteur=test|siret_decl=test|nom_decl=test|no_interchange=test|no_message=test|debut_periode=test|fin_periode=test|list_dest=test
suivi_id=test|ref_message=test2|no_dest=1|type_dest=test|siret=test|nom_dest=test|no_interchange=test|no_message=test|status=test|date_ack=test|message=test|flg_depot=test|flg_envoi=test|flg_ack=test
suivi_id=tata|ref_message=test2|no_dest=2|type_dest=tata|siret=tata|nom_dest=tata|no_interchange=tata|no_message=tata|status=tata|date_ack=tata|message=tata|flg_depot=tata|flg_envoi=tata|flg_ack=tata
   */

  /*
  *
  * FORMAT DE LA REQUÊTE :
  * INSERT\r\n
  * Informations Suivi\n
  * Destinaire1\n
  * Destinaire2\n
  * INSERT\r\n
  * Informations Suivi\n
  * Destinaire1\n
  * Destinaire2\n
  *
  *
  * syntaxe :
  * NomDuChamp1=Valeur1|NomDuChamp2=Valeur2|NomDuChamp3=Valeur3
  */

//  $req->debug();
  $log->enable();
  //$dbo->monitor();

  $request = $req->request;
  if (substr($request, -3, 3) != "END") throw new Exception("error request does not finish by 'END'");
  $request = trim(substr($request, 0, strlen($request) - 3));
  
  $pattern = '/INSERT\r/';
  $datas = preg_split($pattern, $request, null, PREG_SPLIT_NO_EMPTY);

  $suivis = array();
  foreach ($datas as $data) {
    $rows = explode("\r", $data);
    $suivi = array('suivi' => array(), 'destinataires' => array());
    $row_number = 0;
    foreach ($rows as $row) {
      $row = trim($row);
      if (empty($row)) continue;
      $row_number++;

      $cols = explode('|', $row);
      $commit = array();
      foreach ($cols as $col) {
        list($key, $value) = explode('=', $col);
        $key = h(trim($key));
        $value = h(trim($value));
        if (empty($key)) continue;
        if ($key == 'message') $value = str_replace('&lt;br&gt;', '<br />', $value);
        $commit[$key] = $value;
      }

      if ($row_number == 1) {
        $commit['declaration_id'] = (int) $commit['ref_envoi'];
        unset($commit['ref_envoi']);
        $suivi['suivi'] = $commit;
      } else {
        $suivi['destinataires'][] = $commit;
      }
    }

    $suivis[] = $suivi;
  }  
  $insert_ok = true;
  foreach ($suivis as $suivi_data) {
    $suivi = null;
    try {
      if (isset($suivi_data['suivi']['id'])) unset($suivi_data['suivi']['id']);
      if (!Suivi::exists(array('ref_message' => $suivi_data['suivi']['ref_message']))) {
        $suivi = Suivi::getInstance();
        $suivi->commit($suivi_data['suivi']);
      }
      else {
        $suivi = Suivi::getInstance(array('ref_message' => $suivi_data['suivi']['ref_message']));
      }
      $destinataires = array();
      foreach ($suivi_data['destinataires'] as $record) {

        if (isset($record['id'])) unset($record['id']);
        if (Destinataire::exists(array('ref_message' => $record['ref_message'],
                                       'no_dest' => $record['no_dest']))
        ) {
          continue;
        }
        $record['suivi_id'] = $suivi->getId();
        $destinataire = Destinataire::getInstance();
        $destinataire->commit($record);
        $destinataires[$destinataire->getId()] = $destinataire;
      }
    } catch (Exception $e) {
      $insert_ok = false;
      $log->debug($e);      
      if ($suivi && $suivi->isLoaded()) {
        try {
          $suivi->destroy();
        }
        catch (Exception $e) {
          $log->debug($e);
        }

        foreach ($destinataires as $destinataire) {
          if (!$destinataire->isLoaded()) continue;
          try {
            $destinataire->destroy();
          }
          catch (Exception $e) {
            $log->debug($e);
          }
        }
      }
    }
  }
  $res->write($insert_ok ? 'OK' : 'KO');


}
catch (Exception $e) {    
  $log->debug($e);
  $res->write('KO');
}

try {
  $mail = new Mail();
  $mail->addRecipient('npinchon@kernix.com');
  $mail->setSubject('[' . P('app.domain') . '][NTD] webservice.insert.edi');
  $body = 'Utilisation du webservice insert edi.';
  $body .= 'INSERT OK ? ' . ($insert_ok ? 'OK' : 'KO');
  $body .= 'REQUEST : #' . $req->request . '#';
  $mail->setBody($body);
//  $mail->send();
} catch (Exception $e) {

}