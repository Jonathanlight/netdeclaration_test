<?php

$res->resetTemplates();

try {

  NetDeclarationManager::manageWebServiceAccess();

  /*
   * TEST :
UPDATE
where_ref_message=test1|siret_emetteur=mon_siret1
where_ref_message=test1|where_no_dest=1|type_dest=mon type
where_ref_message=test1|where_no_dest=2|type_dest=ta tata
UPDATE
where_ref_message=test2|siret_emetteur=mon_siret2
where_ref_message=test2|where_no_dest=1|siret=le siret
where_ref_message=test2|where_no_dest=2|siret=c tro bien
   */

  /*
  *
  * FORMAT DE LA REQUÊTE :
  * UPDATE\r\n
  * Informations Suivi\n
  * Destinaire1\n
  * Destinaire2\n
  * UPDATE\r\n
  * Informations Suivi\n
  * Destinaire1\n
  * Destinaire2\n
  *
  *
  * syntaxe :
  * NomDuChamp1=Valeur1|NomDuChamp2=Valeur2|NomDuChamp3=Valeur3
  */
  //$req->debug();

  $request = trim($req->request);
  if (substr($request, -3, 3) != "END") throw new Exception("error request does not finish by 'END'");
  $request = trim(substr($request, 0, strlen($request) - 3));

  $pattern = "/UPDATE/";
  $datas = preg_split($pattern, $request, null, PREG_SPLIT_NO_EMPTY);

  $suivis = array();
  foreach ($datas as $data) {
    $rows = explode("\r\n", $data);
    $suivi = array('suivi' => array(), 'destinataires' => array());
    $row_number = 0;

    foreach ($rows as $row) {
      $row = trim($row);
      if (empty($row)) continue;
      $row_number++;

      $cols = explode('|', $row);
      $commit = array();
      $where = array();

      foreach ($cols as $col) {
        list($key, $value) = explode('=', $col);
        $key = h(trim($key));
        $value = h(trim($value));
        if (empty($key)) continue;
        if ($key == 'message') $value = str_replace('&lt;br&gt;', '<br />', $value);

        if (substr($key, 0, 6) == 'where_') {
          $key = substr($key, 6);
          $where[$key] = $value;
        } else {
          $commit[$key] = $value;
        }
      }

      if ($row_number == 1) {
        if (isset($commit['ref_envoi'])) {
          $commit['declaration_id'] = (int) $commit['ref_envoi'];
        }
        unset($commit['ref_envoi']);
        $suivi['suivi'] = array('record' => $commit, 'where' => $where);
      } else {
        $suivi['destinataires'][] = array('record' => $commit, 'where' => $where);
      }
    }
    $suivis[] = $suivi;
  }



  $update_ok = true;
  foreach ($suivis as $suivi_data) {
    try {
      $record = $suivi_data['suivi']['record'];
      $where = $suivi_data['suivi']['where'];
      if (isset($record['id'])) unset($record['id']);
      if(!Suivi::exists($where)) continue;
      $suivi = Suivi::getInstance($where);
      $suivi->commit($record);

      foreach ($suivi_data['destinataires'] as $destinataire_data) {
        $record = $destinataire_data['record'];
        $where = $destinataire_data['where'];
        if (isset($record['id'])) unset($record['id']);
        $where['suivi_id'] = $suivi->getId();
        if(!Destinataire::exists($where)) continue;
        $destinataire = Destinataire::getInstance($where);
        $destinataire->commit($record);
      }
    } catch (Exception $e) {
      $update_ok = false;
      //$err->add($e);
      $log->debug($e->getTraceAsString());
      break;
    }
  }
  $res->write($update_ok ? 'OK' : 'KO 1');



}
catch (Exception $e) {
  //$err->add($e);
  $log->error($e);
  $res->write('KO 2');
}


try {
  $mail = new Mail();
  $mail->addRecipient('npinchon@kernix.com');
  $mail->setSubject('['.P('app.domain').'][NTD] webservice.update.edi');
  $body = 'Utilisation du webservice update edi.';
  $body .= 'INSERT OK ? ' . ($update_ok ? 'OK' : 'KO');
  $body .= 'REQUEST : #' . $req->request . '#';
  $mail->setBody($body);
  //$mail->send();
} catch (Exception $e) {

}