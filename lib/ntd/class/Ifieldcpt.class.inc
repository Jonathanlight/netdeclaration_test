<?php


class Ifieldcpt {

  public static function renderHTML($ifield, $name, $value) {
    $html = '<div class="elt-field">';
    $maxlength = '';//$ifield->type_simple == '6345' ? 'maxlength="3"' : '';
    $html .= '  <input type="text"
                       class="text type-cpt"
                       name=":name:"
                       value=":value:"
                       data-type_simple="' . $ifield->type_simple . '" 
                       '.$maxlength.'
                       />';
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
    /*if ($ifield->type_simple == '5402') {
      if (strpos($value, ',') !== false) {
        throw new Exception('Utilisez un point pour séparer les décimales.');
      }
      elseif (!is_numeric($value)) {
        throw new Exception('Le taux de change à saisir doit être une valeur numérique.');
      }
    } */
  }

}
