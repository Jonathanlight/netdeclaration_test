<?php

try {

  if (!$req->hasAttribute('id', true)) {
    throw new Exception('Service inconnu');
  }

  $service = Service::getInstance((int)$req->id);

  if ($service->code != 'GREFFE') {
    throw new Exception('Service invalide');
  }

  NtdMiddleManager::useTemplate(false);

}
catch (Exception $e) {
  $err->add($e);
}
