<?php


class Ifieldpcd {

  public static function renderHTML($ifield, $name, $value) {
    $html  = '<div class="elt-field">';
    $html .= '  <input type="text"
                       class="text type-pcd"
                       name=":name:"
                       value=":value:" />';
    $html .= '</div>';
    $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';

    $html = str_replace(array(':name:',
                              ':value:'),
                        array($name,
                              $value),
                        $html);

    return $html;
  }

  public static function validate($ifield, $value, $other_field = null) {
    if (strpos($value, ',') !== false) {
      throw new Exception('Utilisez un point pour séparer les décimales.');
    }
    elseif (!is_numeric($value)) {
      throw new Exception('La valeur doit être un nombre entier ou décimal (avec 2 décimales maximum).');
    }
    elseif($value < 0){
      throw new Exception('La valeur doit être un nombre positif.');
    }
  }

}
