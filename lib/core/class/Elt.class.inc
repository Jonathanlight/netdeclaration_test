<?php

class Elt {

  public static $index = 0;

  public static function hidden($opts) {
   $attr = self::opts2html($opts);
   $html = '<input type="hidden"'.$attr.' value="'.self::protect($opts['value']).'" />';
   return $html;
  }

  public static function text($opts=null) {
    $opts = (array) $opts;
    if ($opts['html'] === true) {
      $opts['id'] = $opts['name'].'-'.time();
    }
    $attr = self::opts2html($opts).' class="text"';
    if ($opts['count'] > 0) {
      $opts['type'] = 'multitext';
      $cols = $opts['cols'] > 0 ? $opts['cols'] : 3;
      $rows = $opts['count'] / $cols;
      $html = '<table class="multitext fixed">'."\n";
      $values = (array) $opts['values'];
      for ($i = 1; $i <= $rows; $i++) {
        $html .= '<tr>';
        for ($j = 1; $j <= $cols; $j++) {
          $html .= '<td>';
          $value = $values[($i - 1) * $cols + $j - 1];
          $value = self::protect($value);
          $html .= '<input'.$attr.' value="'.$value.'" />';
          $html .= '</td>';
        }
        $html .= '</tr>';
      }
      $html .= '</table>';
    }
    elseif ($opts['rows'] < 1 && $opts['html'] !== true) {
      if (isset($opts['value'])) {
        $attr .= ' value="'.self::protect($opts['value']).'"';
      }
      $attr .= ' type="'.($opts['password'] == true ? 'password' : 'text').'"';
      if (!empty($opts['placeholder'])) {
        $attr .= ' data-placeholder="'.self::protect($opts['placeholder']).'"';
        $attr .= ' placeholder="'.self::protect($opts['placeholder']).'"';
        if (empty($opts['value'])) { }
      }
      $html = '<input'.$attr.' />';
      $opts['type'] = $opts['type'] ? $opts['type'] : 'text';
      if(isset($opts['tooltip'])) {
        $html .= ' <i class="fa fa-question-circle tooltip-handle" onmouseover="Kwo.Tooltip.show($(this), $(this).up(\'div.elt\').down(\'.elt-tooltip\'))" onmouseout="Kwo.Tooltip.hide()"></i>';
        $html .= '<div class="elt-tooltip" style="display:none;"><div class="elt-tooltip-content">'.$opts['tooltip'].'</div></div>';
        unset($opts['tooltip']);
      }
    }
    else {  
      if (!empty($opts['placeholder'])) {
        $attr .= ' data-placeholder="'.self::protect($opts['placeholder']).'"';
        $attr .= ' placeholder="'.self::protect($opts['placeholder']).'"';
        if (empty($opts['value'])) { }
      }
      $attr .= ' rows="'.intval($opts['rows']).'"';
      $html = '<textarea'.$attr.'>'.self::protect($opts['value']).'</textarea>';
      if ($opts['html'] === true) {
        $opts['type'] = 'richtext';
        $html .= '<script>
new Kwo.Editor("'.$opts['id'].'");
</script>'."\n";
      }
      $opts['type'] = $opts['type'] ? $opts['type'] : 'textarea';
    }
    $html = '<div class="elt-text-border">'.$html.'</div>';
    return self::render($html, $opts);
  }

  public static function code($opts=null) {
    $opts = (array) $opts;
    $opts['type'] = 'code';
    $html = '<code>'.self::protect($opts['value']).'</code>'."\n";
    return self::render($html, $opts);
  }

  public static function date($opts) {
    $opts = (array) $opts;
    if (!isset($opts['display']) && strpos($opts['name'], 'birth') !== false) {
      $opts['display'] = 'inline';
    }
    $opts['display'] = isset($opts['display']) ? $opts['display'] : 'modal';
    if ($opts['display'] == 'inline') {
      $opts['type'] = 'date-inline';
      return self::birthdate($opts)."\n";
    }
    if(!$opts['btn_calendar']) {
      $opts['events']['click'] = 'new Kwo.Datepicker(this);';
      $opts['readonly'] = 'readonly';
    }    
    $opts['size'] = '11';
    if (isset($opts['value'])) {
      $opts['value'] = H::date($opts['value']);
    }
    $opts['type'] = 'date';
    $html = self::text($opts);
    if($opts['btn_calendar']) {
      $html .='<a href="javascript:void(0)" class="btn-calendar" onclick="new Kwo.Datepicker($(this).previous(\'.elt-date\').down(\'input.text\'))" title="Ouvrir le calendrier"><i class="fa fa-calendar"></i> </a>';
    }
    return $html;
  }

  public static function datetime($opts) {
    $opts = (array) $opts;
    $opts['display'] = 'modal';

    $opts['events']['click'] = 'new Kwo.Datepicker(this, {has_time: true});';
    $opts['readonly'] = 'readonly';
    $opts['size'] = '20';
    if (isset($opts['value'])) {
      $opts['value'] = H::datetime($opts['value']);
    }
    $opts['type'] = 'date';
    return self::text($opts);
  }

  public static function select($opts=null) {
    $opts = (array) $opts;
    if (!empty($opts['flowin'])) {
      $opts['events']['change'] = 'Kwo.Elt.onNodeSelect(this, \''.$opts['flowin'].'\')';
    }
    $multiple = $opts['multiple'] === true ? ' multiple="multiple" ' : ''; // ajout Hugues
    $html = '<select'.$multiple.self::opts2html($opts).'>'."\n";
    if ($opts['options'] instanceof Collection) {
      $values = $opts['options']->asHash();
    }
    elseif (is_array($opts['options'])) {
      $values = $opts['options'];
    }
    elseif ($opts['options'] === null) {
      $values = array('0' => '-');
    }
    elseif (Extension::exists('tree') && $opts['options'] instanceof Tree) {
      $values = array(0 => '-') + $opts['options']->asColumnHash();
    }
    //    $values = $opts['options'] instanceof Collection ? $opts['options']->asHash() : $opts['options'];
    if ($values === 'countries' ||
        (strpos($opts['name'], 'country') !== false && $opts['options'] === null)) {
      $locale = $opts['locale'] ? $locale : self::locale();
      $column = $locale === I18N::LOCALE_FR ? 'name_fr' : 'name_en';
      $values = S('dbo')->asHash('SELECT id, '.$column
                                 .' FROM '.T('country')
                                 .' WHERE status=1'
                                 .' ORDER BY '.$column);
      $opts['value'] = $opts['value'] ? $opts['value'] : I18N::COUNTRY_FR;
    }
    elseif ($values === 'civilities' || strpos($opts['name'], 'civility') !== false) {
      $locale = $opts['locale'] ? $locale : self::locale();
      $values = array(0 => l('civility.m'),
                      1 => l('civility.mme'));
      if ($locale == I18N::LOCALE_FR) {
        $values[2] = l('civility.mlle');
      }
    }
    $default = $opts['value'];
    $default = $default instanceof ActiveRecord ? $default->getId() : $default;
    if (isset($opts['first'])) {
      $html .= ' <option value="">'.ucfirst($opts['first']).'</option>'."\n";
    }
    foreach ($values as $key => $value) {
      $html .= ' <option value="'.$key.'"'.($default == $key ? ' selected="selected"' : '').'>'.ucfirst($value).'</option>'."\n";
    }
    $html .= '</select>';
    $opts['type'] = $opts['type'] ? $opts['type'] : 'select';
    return self::render($html, $opts);
  }

  public static function yesno($opts=null) {
    $opts['options'] = array('1' => l('yes'),
                             '0' => l('no'));
    $opts['type'] = 'yesno';
    $opts['value'] = is_bool($opts['value']) ? intval($opts['value']) : $opts['value'];
    $opts['value'] = strlen($opts['value']) >= 1 ? $opts['value'] : '-1';
    return self::radio($opts);
  }

  public static function radio($opts=null) {
    $opts = (array) $opts;
    $attributes = ' type="radio" value="((value))"';
    if ($opts['name']) {
      $attributes .= ' name="'.$opts['name'].'"';
    }
    if ($opts['id']) {
      $attributes .= ' id="'.$opts['id'].'[((value))]"';
    }
    if ($opts['disabled'] === true) {
      $attributes .= ' disabled="disabled"';
    }
    if (is_array($opts['events'])) {
      foreach ($opts['events'] as $name => $event) {
        $attributes .= ' on'.$name.'="'.$event.'"';
      }
    }
    $html = '';
    $i = 0;
    $elt_id = $opts['name'].'-'.(self::$index++).'-';
    foreach ($opts['options'] as $key => $value) {
      if ($opts['id']) {
        $id = $opts['id'].'['.$key.']"';
      }
      else{
        $id = $elt_id.$i++;
      }
      $checked = isset($opts['value']) && $opts['value'] == $key ? ' checked="checked"' : '';
      $attr = str_replace('((value))', $key, $attributes);
      $html .= ' <label class="click-label" for="'.$id.'"><input'.$attr.$checked.' id="'.$id.'" />'.ucfirst($value).'</label>'."\n";
    }
    $opts['control-class'] = ' elt-options';
    $opts['type'] = $opts['type'] ? $opts['type'] : 'radio';
    return self::render(rtrim($html), $opts);
  }

  public static function interests($opts=null) {
    $opts['type'] = 'interests';
    $opts['options'] = Model::asHash('interest');
    if (isset($opts['values']) && $opts['values'] instanceof ActiveRecord) {
      $opts['values'] = $opts['values']->getInterests();
    }
    return self::checkbox($opts);
  }

  public static function checkbox($opts=null) {
    $opts = (array) $opts;
    if (is_array($opts['events'])) {
      foreach ($opts['events'] as $name => $event) {
        $events .= ' on'.$name.'="'.$event.'"';
      }
    }
    if (isset($opts['value'])) {
      $checked = $opts['value'] == 1 ? ' checked="checked"' : '';
      $disabled = $opts['disabled'] === true ? ' disabled="disabled"' : '';
      $html .= '<label><input type="checkbox" name="'.$opts['name'].'" value="1"'.$checked.$disabled.' ' .$events.' />'.ucfirst($opts['label']).'</label>'."\n";
      return self::render(rtrim($html),
                          array('type' => 'checkbox-single', 'class' => $opts['class'], 'style' => $opts['style']));
    }
    if ($opts['disabled'] === true) {
      $disabled = ' disabled="disabled"';
    }
    $values = (array) $opts['values'];
    $html = '';
    if(!$opts['many']) {
      $html = '<input type="hidden" name="'.$opts['name'].'" value="" />'."\n";
    }

    $i = 0;
    $elt_id = 'elt-'.(self::$index++).'-';
    foreach ($opts['options'] as $key => $value) {
      $id = $elt_id.$i++;
      $checked = in_array($key, $values) ? ' checked="checked"' : '';
      $html .= '<label class="click-label" for="'.$id.'"><input type="checkbox" name="'.$opts['name'].'[]" id="'.$id.'" value="'.$key.'"'.$checked.' '.$disabled.' '.$events.' />&nbsp;'.ucfirst($value).'</label>'."\n";
    }
    $opts['control-class'] = ' elt-options';
    $opts['type'] = $opts['type'] ? $opts['type'] : 'checkbox';
    return self::render(rtrim($html), $opts);
  }

  public static function flags($opts=null) {
    $opts['type'] = 'flags';
    return self::checkbox($opts);
  }

  public static function tags($opts=null) {
    $tags = $tags_html = '';
    if (isset($opts['values']) && !empty($opts['values'])) {
      $opts['values'] = $opts['values'] instanceof ActiveRecord ? $opts['values']->getTags() : (array) $opts['values'];
      if (!empty($opts['values'])) {
        $tags = join(',', $opts['values']);
        $span = '<span onclick="Kwo.Elt.onTagEdit($(this))">';
        $tags_html = $span.join('</span>'.$span, $opts['values']).'</span>';
      }
    }
    $html = '';
    $html .= '<input type="hidden" name="tags" value="'.$tags.'" />'."\n";
    $html .= '<input type="text" value="tag" class="text tag-add" title="tag" maxlength="32" size="16" onfocus="Kwo.Elt.onTagFocus(this)" />'."\n";
    $html .= '<img src="/'.PIX_PATH.'/tag.plus.png" onclick="Kwo.Elt.onTagAdd($(this).previous())" style="display:none;" />'."\n";
    $html .= '<div>'.$tags_html.'</div>'."\n";
    $opts['type'] = 'tags';
    return self::render($html, $opts);
  }

  public static function link($opts) {
    $confirm = $opts['confirm'] ? ' confirm="'.$opts['confirm'].'"' : '';
    $html  = '<a href="javascript:void(0)" class="elt-link"'.$confirm."\n";
    $html .= '   '.self::opts2html($opts);
    $html .= '>'.ucfirst($opts['label']).'</a>';
    return $html;
  }

  public static function file($opts=null) {
    $name = $opts['name'] ? ' name="'.$opts['name'].'"' : '';
    $html = '';
    if (isset($opts['name'])) {
      $name = $opts['name'];
      unset($opts['name']);
    }
    if (isset($opts['value'])) {
      $value = $opts['value'];
      unset($opts['value']);
    }
    $html .= '<input type="hidden" name="'.$name.'" value="'.self::protect($value).'" />';
    $opts['readonly'] = true;
    $opts['type'] = 'file';
    if (!empty($value)) {
      $opts['value'] = basename($value);
    }
    $params = '';
    if (strlen($opts['filter']) > 2) {
      $params = ",{filter:'".$opts['filter']."'}";
    }
    $opts['events']['click'] = 'new Kwo.Class.Upload(this'.$params.');';
    $html .= '<input type="text"'.self::opts2html($opts).$attr.' class="text" />';
    return self::render($html, $opts);
  }

  public static function image($opts=null) {
   $opts['readonly'] = true;
   $opts['events']['click'] = 'new Kwo.Class.Upload(Kwo.Elt.onImageCallback.bind($(this)),{filter:\'image\'});';
   $opts['src'] = $opts['src'] instanceof ActiveRecord
                ? ($opts['src']->isItem() ? $opts['src']->image : '')
                : $opts['src'];
   $style = $opts['style'];
   if (!empty($opts['src'])) {
     $src = strpos($opts['src'], '/') === false
          ? '/'.S('req')->getUser()->getPath().$opts['src']
          : $opts['src'];
     $opts['style'] .= 'display:none;';
     $onclick = ' onclick="new Kwo.Class.Upload(Kwo.Elt.onImageCallback.bind($(this).previous()),{filter:\'image\'});"';
   }
   else {
     $src = '/'.PIX_PATH.'/empty.gif';
     $img_style = 'display:none;';
     $onclick = ' onclick="new Kwo.Class.Upload(Kwo.Elt.onImageCallback.bind($(this).previous()),{filter:\'image\'});"';
   }
   if ($opts['max-width'] > 0) {
     $img_style .= ' max-width:'.$opts['max-width'].'px;';
   }
   if ($opts['max-height'] > 0) {
     $img_style .= ' max-height:'.$opts['max-height'].'px;';
   }
   $img_style = ' style="'.$img_style.'"';
   $value = basename($opts['value']);
   $html  = '';
   $html .= '<input type="text"'.self::opts2html($opts).' value="'.self::protect($value).'" class="text" />'."\n";
   $html .= '<img src="'.$src.'" class="elt-image-target"'.$img_style.$onclick.' />';
   $opts['type'] = 'image';
   return self::render($html, $opts);
 }

  public static function captcha($opts=null) {
    $n = rand(100, 999);
    $html = '';
    $html .= '<input type="hidden" name="_captcha_id" value="'.$n.'" />'."\n";
    $html .= '<input type="text captcha" name="_captcha" value="" size="6" maxlength="6"
        id="kwo-captcha-'.$n.'" autocomplete="off"
        title="'.ucfirst(l('enter_code_below')).'" />'."\n";
    $html .= '<img src="/'.CORE.'/captcha?'.time().'" class="captcha" style="vertical-align:bottom;" />';
    $opts['type'] = 'captcha';
    return self::render($html, $opts);
  }

  public static function button($opts=null) {
    $type = $opts['type'] ? $opts['type'] : 'submit';
    $onclick = $data = '';
    if (isset($opts['events'])) {
      $onclick = ' onclick="'.$opts['events']['click'].'"';
      $type = $opts['type'] ? $opts['type'] : 'button';
    }
    $datas = '';
    if (is_array($opts['data'])) {
      foreach ($opts['datas'] as $key => $value) {
        $datas = ' data-'.$key.'="'.$value.'"';
      }
    }
    if ($type == 'image') {
      $html = '<input type="'.$type.'" class="image" src="'.$opts['src'].'" '.$onclick.$datas.' />';
    } else {
      $html = '<input type="'.$type.'" class="button" value="'.ucfirst($opts['label']).'"'.$onclick.$datas.' />';
    }
    $opts['type'] = 'button';
    unset($opts['label']);
    return self::render($html, $opts);
  }

  public static function render($html, $opts) {
    $class = 'elt elt-'.$opts['type'];
    if (isset($opts['class'])) {
      $class .= ' '.$opts['class'];
    }
    if (isset($opts['readonly'])) {
      $class .= ' elt-readonly';
    }
    $out = "\n".'<div class="'.$class.'"'.($opts['required']?' required':'').'>'."\n";
    if (isset($opts['label'])) {
      $out .= '<label class="elt elt-label">'.ucfirst($opts['label']);
      if ($opts['required'] === true) {
        $out .= ' <span class="star-required" title="'.l('elt.required').'">*</span>';
      }
      if (isset($opts['help'])) {
        $action = substr($opts['help'], 0, 8) == 'snippet:' ? "new Kwo.Class.Snippet('".substr($opts['help'], 8)."')" : 'alert(1)';
        $out .= '<img src="/'.PIX_PATH.'/action/elt-help.png" onclick="'.$action.'" />';
      }
      if (isset($opts['tooltip'])) {
        //$out .= ' <img src="/app/ntd/pix/tooltip-info.png" onmouseover="Kwo.Elt.onTooltipShow($(this))" onmouseout="Kwo.Elt.onTooltipHide($(this))" />';
        //$out .= ' <img src="/app/ntd/pix/tooltip-info.png" onmouseover="Kwo.Tooltip.show($(this), $(this).up(\'div.elt\').down(\'.elt-tooltip\'))" onmouseout="Kwo.Tooltip.hide()" />';
        $out .= ' <i class="fa fa-question-circle tooltip-handle" onmouseover="Kwo.Tooltip.show($(this), $(this).up(\'div.elt\').down(\'.elt-tooltip\'))" onmouseout="Kwo.Tooltip.hide()"></i>';
      }
      $out .= '</label>'."\n";
    }
    $class = 'elt-control';
    if (isset($opts['control-class'])) {
      $class .= ' '.$opts['control-class'];
    }
    if (isset($opts['align'])) {
      $class .= ' elt-align-right';
    }
    if ($opts['wide'] === true) {
      $class .= ' elt-wide';
    }
    if ($opts['required'] === true) {
      $class .= ' elt-required';
    }
    /* QUIRK : SPAN : http://www.quirksmode.org/css/display.html#inlineblock */
    $out .= '<div class="'.$class.'">'."\n";
    $out .= $html."\n";
    $out .= '<div class="clear"></div>'."\n";
    if (isset($opts['legend'])) {
      $out .= '<em class="elt elt-legend">'.c($opts['legend']).'</em>'."\n";
    }
    $out .= '</div>'."\n"; // END ELT-CONTROL
    if (isset($opts['tooltip'])) {
      $out .= '<div class="elt-tooltip" style="display:none;"><div class="elt-tooltip-content">'.$opts['tooltip'].'</div></div>';
    }
    $out .= '</div>'."\n";
    return $out;
  }

  private static function opts2html($opts) {
    $str = '';
    if (!empty($opts['name'])) {
      $str .= ' name="'.$opts['name'].'"';
    }
    if (isset($opts['readonly']) && $opts['readonly'] == true) {
      $str .= ' readonly="readonly"';
    }
    if (isset($opts['size'])) {
      $str .= ' size="'.intval($opts['size']).'"';
    }
    if (isset($opts['maxlength'])) {
      $str .= ' maxlength="'.intval($opts['maxlength']).'"';
    }
    if (isset($opts['disabled']) && $opts['disabled'] == true) {
      $str .= ' disabled="disabled"';
    }
    if (isset($opts['class'])) {
      $str .= ' class="'.$opts['class'].'"';
    }
    if (isset($opts['tabindex'])) {
      $str .= ' tabindex="'.$opts['tabindex'].'"';
    }
    if (isset($opts['autocomplete'])) {
      $str .= ' autocomplete="'.($opts['autocomplete']?'on':'off').'"';
    }
    if (is_array($opts['events'])) {
      foreach ($opts['events'] as $name => $event) {
        $str .= ' '.'on'.$name.'="'.$event.'"';
      }
    }
    if (is_array($opts['datas'])) {
      foreach ($opts['datas'] as $key => $value) {
        $str .= ' '.'data-'.$key.'="'.$value.'"';
      }
    }
    if (isset($opts['id'])) {
      $str .= ' id="'.$opts['id'].'"';
    }
    if (isset($opts['style'])) {
      $str .= ' style="'.ltrim($opts['style']).'"';
    }
    return $str;
  }


  private static function protect($value) {
    return strtr($value,
                 array("'" => '&#039;',
                       '"' => '&quot;',
                       '<' => '&lt;',
                       '>' => '&gt;'));
   //return htmlentities($value, ENT_COMPAT, 'UTF-8');
  }

  public static function birthdate($opts) {
    /* opts : id, name, class */
    $name = $opts['name'] ? $opts['name'] : 'birth_date';
    $name = ' name="'.$name.'"';
    $id = $opts['id'] ? ' id="'.$opts['id'].'"' : '';
    $onchange = ' onchange="Kwo.DateManager.birthdate(this)"';
    $hash = Date::asHash($opts['value']);
    $hash = $hash ? $hash : array();
    $value = '';
    if (!empty($hash)) {
      $value = ' value="'.$hash['year'].'-'.$hash['month'].'-'.$hash['day'].'"';
    }
    $html = '<input type="hidden"'.$name.$id.$value.' class="birthdate_input" />';
    $html_day = '<select class="kwo-birthdate birthdate-day"'.$onchange.'>';
    $html_day .= empty($hash) ? '<option value="0">--</option>'."\n" : '';
    foreach (range(1, 31) as $i) {
      $selected = $i == $hash['day'] ? ' selected="selected"' : '';
      $html_day .= '<option value="'.$i.'"'.$selected.'>'.$i.'</option>';
    }
    $html_day .= '</select>';
    $html_month = '<select class="kwo-birthdate birthdate-month"'.$onchange.'>';
    $html_month .= empty($hash) ? ' <option value="0">----</option>'."\n" : '';
    foreach (range(1, 12) as $i) {
      $selected = $i == $hash['month'] ? ' selected="selected"' : '';

      $html_month .= '<option value="'.$i.'"'.$selected.'>'.I18N::month($i, self::locale()).'</option>';
    }
    $html_month .= '</select>';
    $html_year = '<select class="kwo-birthdate birthdate-year"'.$onchange.'>';
    $year = date('Y');
    $html_year .= empty($hash) ? '<option value="0">----</option>'."\n" : '';
    $min = $opts['age_min'] > 1 ? $opts['age_min'] : 5;
    foreach (range($year - $min, $year - 95) as $i) {
      $selected = $i == $hash['year'] ? ' selected="selected"' : '';

      $html_year .= '<option value="'.$i.'"'.$selected.'>'.$i.'</option>';
    }
    $html_year .= '</select>';
    if (self::locale() == I18N::LOCALE_FR) {
      $html .= $html_day.' '."\n".$html_month.' '."\n".$html_year;
    }
    else {
      $html .= $html_year.' '."\n".$html_month.' '."\n".$html_day;
    }
    return self::render($html, $opts);
  }

  public static function monthyear($opts=array()) {
    $name = $opts['name'] ? ' name="'.$opts['name'].'"' : '';
    $id = $opts['id'] ? ' id="'.$opts['id'].'"' : '';
    $onchange = ' onchange="Kwo.DateManager.monthyear(this)"';
    $opts['value'] = strlen($opts['value']) >= 6 ? $opts['value'] : Date::now();
    $hash = Date::asHash($opts['value']);
    $hash = $hash ? $hash : array();
    $value = '';
    if (!empty($hash)) {
      $value = ' value="'.$hash['year'].'-'.$hash['month'].'-01"';
    }
    $html = '<input type="hidden"'.$name.$id.$value.' />';
    $html_month = '<select class="kwo-month"'.$onchange.'>';
    foreach (range(1, 12) as $i) {
      $selected = $i == $hash['month'] ? ' selected="selected"' : '';
      $html_month .= '<option value="'.$i.'"'.$selected.'>'.I18N::month($i, self::locale()).'</option>';
    }
    $html_month .= '</select>';
    $html_year = '<select class="kwo-year"'.$onchange.'>';
    $year = date('Y');
    foreach (range($year + 5, $year - 90) as $i) {
      $selected = $i == $hash['year'] ? ' selected="selected"' : '';
      $html_year .= '<option value="'.$i.'"'.$selected.'>'.$i.'</option>';
    }
    $html_year .= '</select>';
    $html .= $html_month.' / '."\n".$html_year;
    $opts['type'] = 'monthyear';
    return self::render($html, $opts);
    //return "\n".$html;
  }

  public static function hbox($elts, $opts=null) {
    $opts = (array) $opts;
    $layout = $opts['layout'] ? ' layout-'.$opts['layout'] : '';
    $top = '';
    $html = '<ul class="hbox'.$layout.'">'."\n";
    foreach ($elts as $type => $elt) {
      if ($elt['elt'] == 'text' && $opts['wide'] === true) {
        $elt['wide'] = true;
      }
      if ($elt['elt'] == 'hidden') {
        $top .= call_user_func(array(self, $elt['elt']), $elt)."\n";
        continue ;
      }
      $html .= '<li>'.call_user_func(array(self, $elt['elt']), $elt).'</li>'."\n";
    }
    if ($opts['events']) {
      $html .= '<li class="events">'."\n";
      if ($opts['events']['submit']) {
        $html .= Elt::button(array('type' => 'submit',
                                   'label' => $opts['events']['submit']['label']));
        unset($opts['events']['submit']);
      }
      $set = array();
      foreach ($opts['events'] as $evt) {
        $set[] = Elt::link($evt);
      }
      $html .= join(' | '."\n", $set)."\n";
      $html .= '<div class="clear"></div>'."\n";
      $html .= '</li>'."\n";
    }
    $html .= '</ul>';
    return $top.$html;
  }

  public static function form($opts=null) {
    $opts = (array) $opts;
    $html = '';
    if ($opts['events']['submit']) {
      $onsubmit = $opts['events']['submit']['action'];
    }
    $html .= '<form onsubmit="'.$onsubmit.'; return false;">'."\n";
    $html .= self::hbox($opts['elts'], $opts);
    $html .= '</form>';
    return $html;
  }

  private static $locale = 0;
  public static function locale() {
    if (self::$locale < 1) {
      self::$locale = S('res')->getLocale();
    }
    return self::$locale;
  }

  public static function tooltip($opts = null){
    $out = ' <img class="img-tooltip" src="/app/ntd/pix/tooltip-info.png" onmouseover="Kwo.Tooltip.show($(this), $(this).next(\'.elt-tooltip\'))" onmouseout="Kwo.Tooltip.hide()" />';
    $out .= '<div class="elt-tooltip" style="display:none;"><div class="elt-tooltip-content">'.$opts['tooltip'].'</div></div>';
    return $out;
  }

}