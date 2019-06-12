<?php

try {

  $greffe = Greffe::getInstance((int)$req->id);
  $valid_documents = 0;
  $error_documents = 0;
  $errors_msg = array();

  $documents = $greffe->getDocuments();

  // Dépôt
  if (!empty($_FILES['documents'])) {
    foreach ($_FILES['documents']["name"] as $key => $name) {
      if ($_FILES['documents']['error'][$key] == UPLOAD_ERR_NO_FILE) continue;
      if (GreffeManager::isValidDocument($_FILES['documents'], $key, GreffeManager::$authorized_doc_formats, $errors_msg)) {
        $valid_documents++;
        $path = GreffeManager::moveDocument($greffe, $_FILES['documents'], $key);
        $documents[$key] = array('greffe_id'   => $greffe->getId(),
                                 'type'        => $key,
                                 'register_at' => Date::toDb(Date::now()),
                                 'path'        => $path);
      }
      else if ($_FILES['error'][$key] != UPLOAD_ERR_OK) {
        $error_documents++;
      }
    }
  }

  // Mandat
  if (!empty($_FILES['mandat'])) {
    $key = GreffeManager::DOC_MANDAT_DEPOT;
    if ($_FILES['mandat']['error'][$key] != UPLOAD_ERR_NO_FILE) {
      if (GreffeManager::isValidDocument($_FILES['mandat'], $key, GreffeManager::$authorized_mandat_formats, $errors_msg)) {
        $valid_documents++;
        $path = GreffeManager::moveDocument($greffe, $_FILES['mandat'], $key);
        $documents[$key] = array('greffe_id'   => $greffe->getId(),
                                 'type'        => $key,
                                 'register_at' => Date::toDb(Date::now()),
                                 'path'        => $path);
      }
      else if ($_FILES['error'][$key] != UPLOAD_ERR_OK) {
        $error_documents++;
      }
    }
  }

  // Liasse
  if (!empty($_FILES['liasse'])) {
    $key = GreffeManager::DOC_LIASSE;
    if ($_FILES['liasse']['error'][$key] != UPLOAD_ERR_NO_FILE) {
      if (GreffeManager::isValidDocument($_FILES['liasse'], $key, GreffeManager::$authorized_liasse_formats, $errors_msg)) {
        $valid_documents++;
        $path = GreffeManager::moveDocument($greffe, $_FILES['liasse'], $key);
        $documents[$key] = array('greffe_id'   => $greffe->getId(),
                                 'type'        => $key,
                                 'register_at' => Date::toDb(Date::now()),
                                 'path'        => $path);
      }
      else if ($_FILES['error'][$key] != UPLOAD_ERR_OK) {
        $error_documents++;
      }
    }
  }

  $greffe->setDocuments($documents);

  if ($req->hasAttribute('link_liasse_declaration')) {
    $greffe->commit(array('link_liasse_declaration' => (int)$req->link_liasse_declaration));
  }


  $message_success = '';
  $message_error = '';
  if ($valid_documents == 1) {
    $message_success = c('1 document a été enregistré');
  }
  else if ($valid_documents > 0) {
    $message_success = c($valid_documents . ' documents ont été enregistrés');
  }
  else {
    $message_success = c('aucun document n\'a été enregistré');
  }

  if ($error_documents == 1) {
    $message_error .= c('1 document n\'a pas été enregistré');
  }
  else if ($error_documents > 1) {
    $message_error .= c($error_documents . ' documents n\'ont pas été enregistrés');
  }
  $message_error .= implode('<br />', $errors_msg);

  $domain = H::url('/');
  $head_version = P('app.head.version');
  $out = <<<__
<html>
  <head>
    <script type="text/javascript" src="{$domain}app/core/scripts/prototype.js?{$head_version}"></script>
    <script>
      $(parent.document.body).down("#result-container").show();
      $(parent.document.body).down("#result-container").innerHTML = "{$message_success}<br />{$message_error}";
      setTimeout(function() { parent.location.href = parent.location.href; }, 2000);
    </script>
  </head>
  <body></body>
</html>
__;

  $res->close();
  $res->write($out);
}
catch (Exception $e) { $err->add($e); }