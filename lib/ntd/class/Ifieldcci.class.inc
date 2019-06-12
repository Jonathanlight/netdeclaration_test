<?php


class Ifieldcci {

  public static function renderHTML($ifield, $name, $value) {
    $options = Dicoedi::asOptions($ifield->getTableEDI());
    if ($options == Dicoedi::OPTION_CHECKBOX) {
      $checked = $value == 1 ? 'checked="checked"' : '';
      $html = '';
      if ($ifield->hasFlag(Ifield::FLAG_CCI_DEFAULT)) {
          $html .= '<input type="hidden" name=":name:" value="0" />';
      }
      $html .= '<input type="checkbox"
                      class="checkbox type-cci"
                      name=":name:"
                      value="1" ' . $checked . ' /> ';
    }
    else {
      if ($ifield->hasflag(Ifield::FLAG_AUTOCOMPLETE_VALUES)) {
        $type = 'input';
        $html .= '<div class="elt-field" style="position:relative;">';
        $html .= '  <input type="hidden" name=":name:" value="'.$value.'" />';
        $html .= '  <input type="text"
                           class="text type-cci"
                           value="'.$options[$value].'"
                           data-action="/account/declaration/fields.cci/-/id/'.$ifield->getId().'"
                           />';
        $html .= '  <div class="autocomplete-container"></div>';
        $html .= '</div>';
        $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
      }
      else {
        $html = '<select name=":name:">';
        $html .= '<option value="">-</option>';
        foreach ($options as $_value => $label) {
          $selected = ($value !== null && $_value == $value) ? 'selected="selected"' : '';
          $html .= '<option value="' . $_value . '" ' . $selected . ' title="' . h(c($label)) . '">' . c($label) . '</option>';
        }
        $html .= '</select>';
      }
    }

    $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';

    $html = str_replace(array(':name:'), array($name), $html);
    return $html;
  }

}
