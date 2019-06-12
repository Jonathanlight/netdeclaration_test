<?php

/*- 12.345,67 (German)
- 12,345.67 (English)
- 12 345,67 (French)
- 12'345,67 (Swiss)*/

class I18N {

  const LOCALE_FR = 1;
  const LOCALE_EN = 2;
  const LOCALE_ES = 4;
  const LOCALE_IT = 8;
  const LOCALE_PT = 16;
  const LOCALE_DE = 32;
  const LOCALE_JA = 64;

  const COUNTRY_FR = 250;

  public static $locales = array(self::LOCALE_DE => 'de',
                                 self::LOCALE_EN => 'en',
                                 self::LOCALE_ES => 'es',
                                 self::LOCALE_FR => 'fr',
                                 self::LOCALE_IT => 'it',
                                 self::LOCALE_JA => 'ja');

  public static $locale_labels = array(self::LOCALE_DE => 'Deutsch',
                                       self::LOCALE_EN => 'English',
                                       self::LOCALE_ES => 'Espa&#241;ol',
                                       self::LOCALE_FR => 'Français',
                                       self::LOCALE_IT => 'Italiano',
                                       self::LOCALE_PT => 'Portugu&#234;s');

  public static $metas = array(self::LOCALE_DE => 'de_DE',
                               self::LOCALE_EN => 'en_EN',
                               self::LOCALE_ES => 'es_ES',
                               self::LOCALE_FR => 'fr_FR',
                               self::LOCALE_IT => 'it_IT',
                               self::LOCALE_JA => 'ja');
  
  public static $months = array(self::LOCALE_FR => array('short' => array(1 => 'janv', 2 => 'fév', 3 => 'mars', 4 => 'avr', 5 => 'mai', 6 => 'juin', 
                                                                        7 => 'juil', 8 => 'aout', 9 => 'sept', 10 => 'oct', 11 => 'nov' , 12 => 'déc'),
                                                       
                                                         'long' => array(1 => 'janvier', 2 => 'février', 3 => 'mars', 4 => 'avril', 5 => 'mai', 6 => 'juin', 
                                                                         7 => 'juillet', 8 => 'août', 9 => 'septembre', 10 => 'octobre', 11 => 'novembre', 12 => 'décembre')),
                                
                                self::LOCALE_EN => array('short' => array(1 => 'jan', 2 => 'feb', 3 => 'mar', 4 => 'apr', 5 => 'may', 6 => 'jun', 
                                                                          7 => 'jul', 8 => 'aug', 9 => 'sep', 10 => 'oct', 11 => 'nov' , 12 => 'dec'),
                                                         
                                                         'long' => array(1 => 'january', 2 => 'february', 3 => 'march', 4 => 'april', 5 => 'may', 6 => 'june', 
                                                                         7 => 'july', 8 => 'august', 9 => 'september', 10 => 'october', 11 => 'november', 12 =>'december')));
  
  public static $days = array(self::LOCALE_FR => array('short' => array(1 => 'lun', 2 => 'mar', 3 => 'mer', 4 => 'jeu', 5 => 'ven', 6 => 'sam', 7 => 'dim'),
                                                       'long' => array(1 => 'lundi', 2 => 'mardi', 3 => 'mercredi', 4 => 'jeudi', 5 => 'vendredi', 6 => 'samedi', 7 => 'dimanche')),
                              
                              self::LOCALE_EN => array('short' => array(1 => 'mon', 2 => 'tue', 3 => 'wed', 4 => 'thu', 5 => 'fri', 6 => 'sat', 7 => 'sun'),
                                                       'long' => array(1 => 'monday', 2 => 'tuesday', 3 => 'wednesday', 4 => 'thursday', 5 => 'friday', 6 => 'saturday', 7 => 'sunday')));
  
  public static function locales() {
    $locales = P('back.locales');
    if ($locales === null) {
      $locales = P('app.locales');
    }
    $locales = (array) $locales;
    $hash = array();
    foreach ($locales as $locale) {
      $hash[$locale] = self::$locales[$locale];
    }
    return $hash;
  }
  
  public static function day($num, $locale=self::LOCALE_FR, $size='long') {
    return self::$days[$locale][$size][$num];
  } 

  public static function month($num, $locale=self::LOCALE_FR, $size='long') {
    return self::$months[$locale][$size][$num];
  }
  
  public static function lang($lang) {
    if (is_numeric($lang)) {
      $ret = self::$locales[$lang];
      return strlen($ret) >= 2 ? $ret : 'fr';
    }
    $locales = array_flip(self::$locales);
    $ret = $locales[$lang];
    return $ret ? $ret : self::LOCALE_FR;
  }

  public static function getCountries($locale=self::LOCALE_FR) {
    $lang = $locale === self::LOCALE_FR ? '_fr' : '_en';
    return S('dbo')->asHash('SELECT id, name#lang#'
                            .' FROM '.T('country')
                            .' WHERE status=1'
                            .' ORDER BY name#lang#',
                            array('#lang#' => $lang));
  }

  public static function code($locale) {
    if (!is_numeric($locale)) return $locale;
    return self::$locales[$locale];
  }

}