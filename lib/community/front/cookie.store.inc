<?php

try {
  $cookie = $req->getCookie();
  if ($req->hasAttribute('location_code')) {
    $cookie->location_code = $req->location_code;
  } 
} 
catch (Exception $e) { }
