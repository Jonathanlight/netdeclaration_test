<?php


class Ifieldcom {

  public static $max_length = array(
    '3148.01' => '512',
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
      $html .= '<select name=":name:" class="select type-com select-country">';
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
                             class="text type-com"
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

}
