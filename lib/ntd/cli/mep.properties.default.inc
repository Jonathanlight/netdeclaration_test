<?php

try {

  foreach (Service::collect() as $service) {
    $service->setProperty('title', $service->name, I18N::LOCALE_FR);
    $service->setProperty('description', $service->description_, I18N::LOCALE_FR);
  }
  foreach (Servicetype::collect() as $servicetype) {
    $servicetype->setProperty('title', $servicetype->name, I18N::LOCALE_FR);
  }

  foreach (Dectype::collect() as $dectype) {
    $dectype->setProperty('title', $dectype->name, I18N::LOCALE_FR);
    $dectype->setProperty('description', 'description par défaut', I18N::LOCALE_FR);
  }


}
catch (Exception $e) {
  $err->add($e);
}