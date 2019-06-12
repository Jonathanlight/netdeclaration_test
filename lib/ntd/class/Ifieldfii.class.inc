<?php


class Ifieldfii {

  public static function renderHTML($ifield, $name, $value) {

    $ibans = (S('ctx')->adherent) ? S('ctx')->adherent->asIbansHash() : array();

    $html .= '<select name=":name:" class="select type-fii">';
    $html .= '<option value="">Veuillez choisir un IBAN (si montant est > 0)</option>';
    foreach ($ibans as $key => $label) {
      $selected = ($value !== null && $key == $value) ? 'selected="selected"' : '';
      $html .= '<option value="' . $key . '" ' . $selected . ' >' . $label . '</option>';
    }
    $html .= '</select>';
    $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';

    
    if (count($ibans) < 1) {
      $html = '<div style="display:none;">' . $html . '</div>';
      $html .= '<p>Compte Bancaire non renseigné. Veuillez enregistrer votre IBAN dans votre espace privatif</p>';
    }    


    $html = str_replace(array(':name:',
                              ':value:'),
                        array($name,
                              $value),
                        $html);

    return $html;
  }

  public static function validate($ifield, $value, $other_field = null) {

  }

}
