<?php

class Ifieldnad {

  public static $max_length = array(
    '3039.01'   => '35',
    '3036.01'   => '35',
    '3036.02'   => '35',
    '3036.03'   => '35',
    '3042.01'   => '35',
    '3042.02'   => '35',
    '3042.03'   => '35',
    '3164.01'   => '35',
    '3251.01'   => '9',
    '3207.01'   => '3',
    '3148.01'   => '512',
    '3228.01'   => '26',
    '3229.01'   => '5',
    '3042-1.01' => '4',
    '3042-1.02' => '1',
  );

  const FORMAT_OTHER = 0;
  const FORMAT_EMAIL = 1;
  const FORMAT_SIRET = 2;

  public static $formats = array(
      self::FORMAT_OTHER => 'Aucun',
      self::FORMAT_EMAIL => 'Email'
  );

  /*
  * 35--> 01 = identifiant
   35--> 02 = Nom
   35--> 03 = nom2 ou qualite
   35--> 04 = forme juridique ou titre
   35--> 05 = rue adresse
   35--> 06 = adresse2
   35--> 07 = adresse3
   35--> 08 = ville
   9--> 09 = code postal
   3--> 10 = pays
   35--> 11 = contact
   512--> 12 = telephone
   512--> 13 = e - mail
  */

  public static function renderHTML($ifield, $name, $value) {

    $html = '<div data-type=":data-type:">';
    if ($ifield->type_simple == '3207') {
      $type = 'select';
      $html .= '<select name=":name:" class="select type-nad select-country">';
      foreach (Country::collect(array('order' => array('name_fr' => 'ASC'))) as $country) {
        $selected = ($value !== null && $country->getId() == $value) ? 'selected="selected"' : '';
        $html .= '<option value="' . $country->getId() . '" ' . $selected . ' >' . $country->name_fr . '</option>';
      }
      $html .= '</select>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
    }
    else {
      $maxlength = self::$max_length[$ifield->type_simple . '.' . $ifield->no_donnee_simple];
      if ($ifield->maxlength > 0) {
        $maxlength = $ifield->maxlength;
      }
      $type = 'input';
      $html .= '<div class="elt-field">';
      $html .= '  <input type="text"
                             class="text type-nad"
                             name=":name:"
                             ' . ($maxlength > 0 ? 'maxlength="' . $maxlength . '"' : '') . '
                             value=":value:" />';
      $html .= '</div>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';

    }

    $html .= '</div>';
    $html = str_replace(array(':name:',
                              ':value:',
                              ':data-type:'),
                        array($name,
                              $value,
                              $type),
                        $html);
    return $html;
  }

  public static function asTradeXpressExportHash($ifield, $value) {
    if ($ifield->type_simple == '3207') {
      if ($value > 0 && Country::exists((int) $value)) {
        return Country::getInstance((int) $value)->code;
      }
      else {
        return '';
      }
    }
    return $value;
  }

  public static function validate($ifield, $value, $other_field = null) {

    $value_length = strlen($value);

    if ($ifield->format == self::FORMAT_EMAIL && $value_length > 0 && !filter_var($value, FILTER_VALIDATE_EMAIL)) {
        throw new Exception('Le format de l\'adresse de messagerie est incorrect.');
    }


    if ($ifield->minlength > 0 && $value_length > 0) {
        if ($value_length < $ifield->minlength) {
            if ($ifield->maxlength == $ifield->minlength) {
                throw new Exception($ifield->minlength . ' caractères sont attendus.');
            } else {
                throw new Exception($ifield->minlength . ' caractères sont attendus au minimum.');
            }
        }
    }
  }
}
