<?php

class Ifieldrff {

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
  public static $rofs = array(
    '',
    'IS',
    'ISGROUPE',
    'BIC',
    'RF',
    'BA',
    'BNC',
    'CVAE',
    'RCM',
    'CFE'
  );

  public static function renderHTML($ifield, $name, $value) {
    if ($ifield->code_edi == 'KD' && in_array($ifield->getFormulairetype()->code, array('F-IDENTIF', 'P-IDENTIF'))) {
      $default_value = $ifield->getDefaultValue();
      preg_match('/(?P<first_part>[A-Z]*)(?P<second_part>\d+)/', $default_value, $default_value);

      if (!is_array($value)) {
        preg_match('/(?P<first_part>[A-Z]*)(?P<second_part>\d+)/', $value, $value);
      }
      $html = '<div class="fidentif-rof"> ' . l('snippet:rof.details') . '
                <select name=":name:[first_part]" data-default-value="' . $default_value['first_part'] . '">';
      foreach (self::$rofs as $rof) {
        $selected = ($rof == $value['first_part']) ? 'selected="selected"' : '';
        $html .= '<option value="' . $rof . '" ' . $selected . '>' . $rof . '</value>';
      }
      $html .= '</select>
        <div class="elt-field">
          <input type="text"
                 class="text type-rff"
                 name=":name:[second_part]"
                 value="' . $value['second_part'] . '"
                 data-default-value="' . $default_value['second_part'] . '" />
        </div>';
      $html .= '<label class="click-label"><input type="checkbox" name=":name:[disabled]" value="1" ' . ($value['disabled'] > 0 ? 'checked="checked"' : '') . ' /> Cochez si vide </label>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div></div>';
    }
    elseif(in_array($ifield->getFormulairetype()->code, array('P-IDENTIF')) && in_array($ifield->code_edi, array('KA', 'KB', 'KC'))){
      $html = '<div class="elt-field">';
      $html .= '  <input type="text"
                         class="text type-rff"
                         name=":name:"
                         value=":value:" />';
      $html .= '</div>';
      //$html .= '<input type="button" value="Générer la référence" />';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
    }


    else {
        $maxlength = self::$max_length[$ifield->type_simple . '.' . $ifield->no_donnee_simple];
        if ($ifield->maxlength > 0) {
            $maxlength = $ifield->maxlength;
        }
      $html = '<div class="elt-field">';
      $html .= '  <input type="text"
                         class="text type-rff"
                         name=":name:"
                         ' . ($maxlength > 0 ? 'maxlength="' . $maxlength . '"' : '') . '
                         value=":value:" />';
      $html .= '</div>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';

    }

    $html = str_replace(array(':name:',
                              ':value:'),
                        array($name,
                              $value),
                        $html);
    return $html;
  }

  public static function asTradeXpressExportHash($ifield, $value) {
    if ($ifield->code_edi == 'KD' && in_array($ifield->getFormulairetype()->code, array('F-IDENTIF', 'P-IDENTIF'))) {
      if ($value['disabled'] > 0) {
        $value = '';
      }
      else {
        $value = $value['first_part'] . $value['second_part'];
      }
    }
    return $value;
  }

  public static function validate($ifield, $value, $other_field = null) {

    if (is_string($value)) {
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

}
