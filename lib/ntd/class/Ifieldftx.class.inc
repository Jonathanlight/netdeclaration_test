<?php

class Ifieldftx {

  public static function renderHTML($ifield, $name, $value) {
    $maxlength = 0;
    if ($ifield->maxlength > 0) {
      $maxlength = $ifield->maxlength;
    }

    $html  = '<div class="elt-field">';
    $html .= '  <input type="text"
                       class="text type-ftx"
                       name=":name:"
                       ' . ($maxlength > 0 ? 'maxlength="' . $maxlength . '"' : '') . '
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
    $value_length = strlen($value);

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
