<?php

$res->resetTemplates();

// test curl :: curl -s -S http://dev.ntd-dev.li.kernix.net/webservice.insert.edi.message --data-binary @doc/test/suivi_rep.txt

try {

  NetDeclarationManager::manageWebServiceAccess();

  $log->enable();
  $log->trace('BEGIN');


  $request = $req->request;
  if (substr($request, -3, 3) != "END") throw new Exception("error request does not finish by 'END'");
  $request = trim(substr($request, 0, strlen($request) - 3));
  
  $pattern = '/INSERT\r/';
  $datas = preg_split($pattern, $request, null, PREG_SPLIT_NO_EMPTY);

  $messages = array();
  foreach ($datas as $data) {
    $rows = explode("\r", $data);
    $message = array('message' => array(), 'lines' => array());
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
        //$commit['declaration_id'] = (int) $commit['ref_envoi'];
        //unset($commit['ref_envoi']);
        $message['message'] = $commit;
      } else {
        $message['lines'][] = $commit;
      }
    }

    $messages[] = $message;
  }
  S('log')->debug($messages, __METHOD__);

  $insert_ok = true;
  foreach ($messages as $message_data) {
    $message = null;
    try {
      if (isset($message_data['message']['id'])) unset($message_data['message']['id']);
      $message = Edimessage::getInstance();
      // casts
      $year = substr($message_data['message']['date_reception'], 0 , 4);
      $month = substr($message_data['message']['date_reception'], 4 , 2);
      $day = substr($message_data['message']['date_reception'], 6 , 2);
      $message_data['message']['date_reception'] = Date::toDb($year . '-' . $month . '-' . $day);

      $message->commit($message_data['message']);
      $lines = array();
      foreach ($message_data['lines'] as $record) {
        if (isset($record['id'])) unset($record['id']);
        $record['edimessage_id'] = $message->getId();
        $line = Edimessagerow::getInstance();
        $line->commit($record);
        $lines[$line->getId()] = $line;
      }
    } catch (Exception $e) {
      $insert_ok = false;
      $log->debug($e);      
      if ($message && $message->isLoaded()) {
        try {
          $message->destroy();
        }
        catch (Exception $e) {
          $log->debug($e);
        }
        foreach ($lines as $line) {
          if (!$line->isLoaded()) continue;
          try {
            $line->destroy();
          }
          catch (Exception $e) {
            $log->debug($e);
          }
        }
      }
    }
  }
  $res->write($insert_ok ? 'OK' : 'KO');
  $log->trace('END [$insert_ok='.$insert_ok.']');

}
catch (Exception $e) {    
  $log->debug($e);
  $res->write('KO');
}

try {
  $mail = new Mail();
  $mail->addRecipient('npinchon@kernix.com');
  $mail->setSubject('[' . P('app.domain') . '][NTD] webservice.insert.edi.message');
  $body = 'Utilisation du webservice insert edi message.';
  $body .= 'INSERT OK ? ' . ($insert_ok ? 'OK' : 'KO');
  $body .= 'REQUEST : #' . $req->request . '#';
  $mail->setBody($body);
//  $mail->send();
} catch (Exception $e) {

}