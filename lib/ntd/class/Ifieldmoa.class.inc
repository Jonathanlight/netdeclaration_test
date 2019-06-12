<?php


class Ifieldmoa {

  public static function renderHTML($ifield, $name, $value) {
    $html  = '<div class="elt-field">';
    $html .= '  <input type="text"
                       class="text type-moa"
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
    if (!ctype_digit(str_replace('-', '', $value))) {
      throw new Exception('la valeur doit être un entier.');
    }

  }

}
