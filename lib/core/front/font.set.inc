<?php

try {

  $cookie = $req->getCookie();

  if (!$req->hasAttribute('text_size')) {
    $cookie->text_size = $cookie->text_size == 1 ? 0 : 1;
  }

}
catch (Exception $e) { }