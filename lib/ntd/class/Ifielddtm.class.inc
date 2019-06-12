<?php

// 102 = SSAAMMJJ
// 602 = SSAA
// 610 = SSAAMM
// 718 = SSAAMMJJSSAAMMJJ
// 801 = Année
// 802 = Mois

class Ifielddtm {

  public static function renderHTML($ifield, $name, $value) {

    $html = '<div data-type=":data-type:" class="elt-dtm-:data-type:">';
    $data_type = '';

    if ($ifield->getTableEDI() == '102') {
      $data_type = 'ssaammjj';
      $html .= '<div class="elt-field">';
      $html .= '  <input type="text"
                         class="text type-dtm input-date"
                         name=":name:"
                         value=":value:"/>';
      $html .= '</div>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
      if (!Date::isNull($value)) {
        $value = H::date($value);
      }
    }
    elseif ($ifield->getTableEDI() == '106') {
      $value = (array) $value;
      $data_type = 'mmjj';

      $html .= '<input type="hidden" name=":name:[value]" value="'.$value['value'].'" />';


      $html .= '<select name=":name:[day]" class="select day type-dtm input-date">';
      $html .= '<option value="">-</option>';
      foreach (range(1, 31) as $number) {
        $selected = ($value['day'] == $number) ? 'selected="selected"' : '';
        $number = str_pad($number, 2, 0, STR_PAD_LEFT);
        $html .= '<option value="' . $number . '" ' . $selected . ' >' . $number . '</option>';
      }
      $html .= '</select>';


      $html .= '<select name=":name:[month]" class="select month type-dtm input-date">';
      $html .= '<option value="">-</option>';
      foreach (I18n::$months[S('res')->getLocale()]['long'] as $number => $label) {
        $selected = ($value['month'] == $number) ? 'selected="selected"' : '';
        $number = str_pad($number, 2, 0, STR_PAD_LEFT);
        $html .= '<option value="' . $number . '" ' . $selected . ' >' . $label . '</option>';
      }
      $html .= '</select>';

      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
    }
    elseif ($ifield->getTableEDI() == '610') {

      $value = (array) $value;
      $data_type = 'ssaamm';

      $html .= '<input type="hidden" name=":name:[value]" value="'.$value['value'].'" />';

      $html .= '<select name=":name:[month]" class="select month type-dtm input-date">';
      $html .= '<option value="">-</option>';
      foreach (I18n::$months[S('res')->getLocale()]['long'] as $number => $label) {
        $selected = ($value['month'] == $number) ? 'selected="selected"' : '';
        // jdrzewinski
        $number = str_pad($number, 2, 0, STR_PAD_LEFT);
        $html .= '<option value="' . $number . '" ' . $selected . ' >' . $label . '</option>';
      }
      $html .= '</select>';

      $html .= '<select name=":name:[year]" class="select year type-dtm input-date">';
      $html .= '<option value="">-</option>';
      for ($annee = date('Y') - 15; $annee <= date('Y') + 1; $annee++) {
        $selected = ($value['year'] == $annee) ? 'selected="selected"' : '';
        $html .= '<option value="' . $annee . '" ' . $selected . '>' . $annee . '</option>';
      }
      $html .= '</select>';

      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
    }
    elseif ($ifield->getTableEDI() == '718') {
      $data_type = 'ssaammjjssaammjj';
      $html .= '<input type="hidden" name=":name:" value=":value:" />';
      list($begin_at, $end_at) = explode('#', $value);
      $html .= '<div class="elt-field">';
      $html .= '  <input data-name="begin_at"
                         type="text"
                         class="text type-dtm input-date"
                         value="' . $begin_at . '"/>';
      $html .= '</div>';
      $html .= '<div class="elt-field">';
      $html .= '  <input data-name="end_at"
                         type="text"
                         class="text type-dtm input-date"
                         value="' . $end_at . '"/>';
      $html .= '</div>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';

    }
    elseif ($ifield->getTableEDI() == '602') {
      $data_type = 'ssaa';
      $html .= '<select name=":name:" class="select type-dtm input-date">';
      $html .= '<option value="">-</option>';
      for ($annee = date('Y') - 16; $annee <= date('Y') + 1; $annee++) {
        $selected = ($value !== null && $annee == $value) ? 'selected="selected"' : '';
        $html .= '<option value="' . $annee . '" ' . $selected . ' title="' . $annee . '">' . $annee . '</option>';
      }
      $html .= '</select>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
    }
    elseif($ifield->getTableEDI() == '802') {
      $data_type = 'month_count';
      $html .= '<div class="elt-field">';
      $html .= '  <input type="text"
                         class="text type-dtm"
                         name=":name:"
                         maxlength="2"
                         value=":value:" />';
      $html .= '</div>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';

    }
    else {
      $html .= '<div class="elt-field">';
      $html .= '  <input type="text"
                         class="text type-dtm"
                         name=":name:"
                         value=":value:" />';
      $html .= '</div>';
      $html .= '<div class="elt-tooltip" style="display: none;"><div class="elt-tooltip-content"></div></div>';
      $data_type = 'unknown[' . $ifield->getTableEDI() . ']';
    }

    $html = str_replace(array(':name:',
                              ':value:',
                              ':data-type:'),
                        array($name,
                              $value,
                              $data_type),
                        $html);
    $html .= '</div>';
    return $html;
  }

  public static function validate($ifield, $value, $other_field = null) {
    if (substr($ifield->code, 0, 12) == 'F-IDENTIF_CB' && $other_field) {
        if ($ifield->imprime->getMillesime()->id >= 12 ) {
            $date_start = new DateTime(Date::toDb($other_field->getValue(0)));
            $date_end = new DateTime(Date::toDb($value));
            $interval = date_diff($date_start, $date_end);
            $month_interval = $interval->m + 12*$interval->y;

            if ($month_interval > 24) {
                throw new Exception('La durée de l\'exercice doit est inférieure ou égale à 24 mois.');
            } else if ($month_interval == 24) {
                if ($interval->d > 0) {
                    throw new Exception('La durée de l\'exercice doit est inférieure ou égale à 24 mois.');

                }
            }
        }
    }

    if ($ifield->getTableEDI() == '718') {
      list($begin_at, $end_at) = explode('#', $value);
      if (Date::isNull($begin_at) xor Date::asHash($begin_at) === false
      xor Date::isNull($end_at) xor Date::asHash($end_at) === false) {
        throw new Exception('Les 2 dates doivent être remplies.');
      }
    }
    elseif ($ifield->getTableEDI() == '802') {
      if (strlen($value) > 0 && (strcmp($value, (int) $value) != 0)) {
        throw new Exception('Veuillez saisir le nombre de mois (exemple 12) ou laissez vide');
      }
    }
  }

  public static function asTradeXpressExportHash($ifield, $value) {
    if ($ifield->getTableEDI() == '718') {
      list($begin_at, $end_at) = explode('#', $value);
      if (!Date::isNull($begin_at) && !Date::isNull($end_at)) {
        $begin_at = Date::asHash($begin_at);
        $end_at = Date::asHash($end_at);
        $value = $begin_at['year'] . str_pad($begin_at['month'], 2, 0, STR_PAD_LEFT) . str_pad($begin_at['day'], 2, 0, STR_PAD_LEFT) . $end_at['year'] . str_pad($end_at['month'], 2, 0, STR_PAD_LEFT) . str_pad($end_at['day'], 2, 0, STR_PAD_LEFT);
      }
      else {
        $value = '';
      }
    }
    elseif ($ifield->getTableEDI() == '102') {
      if (!Date::isNull($value)) {
        $hash = Date::asHash($value);
        $value = $hash['year'] . $hash['month'] . $hash['day'];
      }
    }
    elseif ($ifield->getTableEDI() == '106') {
      $value = (array) $value;
      $value = $value['month'] . $value['day'];
    }
    elseif ($ifield->getTableEDI() == '802') {
      if (strlen($value) > 0) {
        $value = (int) substr($value, 0, 2);
      }
    }
    elseif ($ifield->getTableEDI() == '610') {
      $value = (array) $value;
      $value = $value['year'].$value['month'];//str_pad($value['year'], 4, '0', STR_PAD_LEFT) . str_pad($value['month'], 2, '0', STR_PAD_LEFT);
    }
    return $value;
  }

}
