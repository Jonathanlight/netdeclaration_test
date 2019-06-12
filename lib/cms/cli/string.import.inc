<?php

try {

  $files = glob('app/*/locales/messages_*.inc');

  foreach ($files as $file) {
    if (strpos($file, '_fr.inc') > 1) $locale = I18N::LOCALE_FR;
    elseif (strpos($file, '_en.inc') > 1) $locale = I18N::LOCALE_EN;
    else continue ;
    $words = array();
    include $file;
    list (, $extension,,) = explode('/', $file);
    $app = '';
    if (Extension::id($extension) >= Extension::EXTERNAL_THRESHOLD) {
      $app = $extension;
    }
    if (empty($words)) continue ;
    foreach ($words as $word => $value) {
      //      if ($word != 'first_name') continue ;
      if (empty($value)) continue ;
      $string_id = String::id(array('name' => $word));
      if ($string_id > 0) {
        $string = String::getInstance($string_id);
      }
      else {
        $string = String::getInstance();
        $string->commit(array('name' => $word,
                              'status' => 1,
                              'app' => $app));
      }
      if (($string->locales & $locale) < 1) {
        $string->commit(array('locales' => $string->locales | $locale));
      }
      $string->setProperty('label', $value, $locale);
      $string->syncAttributes();
    }
  }

}
catch (Exception $e) { $err->add($e); }
