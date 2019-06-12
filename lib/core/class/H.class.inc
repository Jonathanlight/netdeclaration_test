<?php

// X-Frame-Options: deny

final class H {
  private static $locale = 0;
  private static $currency = null;

  public static function head($opts = null) {
    $opts = (array) $opts;
    $opts['ie'] = isset($opts['ie']) ? $opts['ie'] : true;
    $res = S('res');
    $req = S('req');
    $ctx = S('ctx');
    $ext = P('app.extension');
    $lang = $res->lang ? : I18N::$metas[self::locale()];
    $title = $res->metas['title'] ? $res->metas['title'] : P('app.name');
    $html = ' <title>' . h(c($title)) . '</title>' . "\n";
//    $html .= ' <meta lang="'.$lang.'" />'."\n";
    if ($opts['doctype'] == 'HTML5') {
      $html .= '<meta charset="utf-8" />'. "\n";
    }
    $html .= ' <meta http-equiv="Content-Language" content="' . $lang . '" />' . "\n";
    $html .= ' <meta http-equiv="Content-Script-Type" content="text/javascript" />' . "\n";

    $html .= ' <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />' . "\n";
    $html .= ' <meta http-equiv="X-UA-Compatible" content="IE=edge" />' . "\n";
    $html .= ' <script type="text/javascript">var _user_id = ' . intval($ctx->_user['id']) . '; ';

    $html .= 'var _locale = ' . self::locale() . '; ';
    $html .= 'var _scope = "' . $req->scope() . '";</script>' . "\n";

    foreach (array('scripts', 'styles', 'feeds', 'metas') as $value) {
      $opts[$value] = (array) $opts[$value];
    }

    $scopes = array('front', 'account', 'middle');
    $scope = $req->scope();

    $scripts = array('/app/core/scripts/prototype.js',
                     '/app/core/scripts/kwo.js');
    $controllers = array_key_exists('controllers', $opts)
        ? (bool) $opts['controllers']
        : false;
    if ($controllers && is_array(P('controllers'))) {
      foreach (P('controllers') as $value) {
        $scripts[] = '/app/' . $value . '/controller.js';
      }
    }

    if(!$opts['autoscripts_disabled']) {
    $script = 'app/' . $ext . '/controller.js';
    if (file_exists($script)) {
      $scripts[] = '/' . $script;
    }
    else {
      $script = 'app/' . $ext . '/scripts/master.js';
      if (file_exists($script)) {
        $scripts[] = '/' . $script;
      }
      if ($scope === 'front' || $scope === 'account') {
        $script = 'app/' . $ext . '/scripts/front.js';
        if (file_exists($script)) {
          $scripts[] = '/' . $script;
        }
        if ($scope === 'account') {
          $script = 'app/' . $ext . '/scripts/account.js';
          if (file_exists($script)) {
            $scripts[] = '/' . $script;
          }
        }
      }
      elseif ($scope === 'middle') {
        $script = 'app/' . $ext . '/scripts/middle.js';
        if (file_exists($script)) {
          $scripts[] = '/' . $script;
        }
      }
      if ($scope === 'front' || $scope === 'middle' ||
          ($scope === 'account' && $ext === $req->extension())) {
        $script = 'app/' . $ext . '/scripts/' . $req->action() . '.js';
        if (file_exists($script)) {
          $scripts[] = '/' . $script;
        }
      }
    }
    }

    $opts['scripts'] = array_merge($opts['scripts'], $res->scripts);
    foreach ($opts['scripts'] as $value) {
      $scripts[] = strpos($value, '/') === false
          ? '/app/' . $extension . '/scripts/' . $value . '.js'
          : $value;
    }
    $scripts = array_merge($scripts, (array) P($scope . '.scripts'));


    $styles = array();
    if(!$opts['autostyles_disabled']) {


    $style = 'app/' . $ext . '/style.css';
    if (file_exists($style)) {
      $styles[] = '/' . $style;
    }
    else {
      $style = 'app/' . $ext . '/styles/master.css';
      if (file_exists($style)) {
        $styles[] = '/' . $style;
      }
      if ($scope === 'front' || $scope === 'account') {
        $style = 'app/' . $ext . '/styles/front.css';
        if (file_exists($style)) {
          $styles[] = '/' . $style;
        }
        if ($scope === 'account') {
          $style = 'app/' . $ext . '/styles/account.css';
          if (file_exists($style)) {
            $styles[] = '/' . $style;
          }
        }
      }
      elseif ($scope === 'middle') {
        $style = 'app/' . $ext . '/styles/middle.css';
        if (file_exists($style)) {
          $styles[] = '/' . $style;
        }
      }
      if ($scope === 'front' || $scope === 'middle' ||
          ($scope === 'account' && $ext === $req->extension())) {
        $style = 'app/' . $ext . '/styles/' . $req->action() . '.css';
        if (file_exists($style)) {
          $styles[] = '/' . $style;
        }
      }
    }
    }

    $opts['styles'] = array_merge($opts['styles'], $res->styles);
    foreach ($opts['styles'] as $value) {
      $styles[] = strpos($value, '/') === false ? '/app/' . $extension . '/styles/' . $value . '.css' : $value;
    }
    $styles = array_merge($styles, (array) P($scope . '.styles'));

//    array_unshift($styles, '/app/'.$ext.'/style.css');

    $metas = array_merge($opts['metas'], $res->metas, (array) P('front.metas'));
    $properties = array();

    foreach ($metas as $key => $value) {
      if ($key[2] == ':') {
        $properties[$key] = $value;
        continue;
      }
      $html .= ' <meta name="' . $key . '" content="' . h($value) . '" />' . "\n";
    }

    foreach ($properties as $key => $value) {
      $html .= ' <meta property="' . $key . '" content="' . h($value) . '" />' . "\n";
    }

    $head_suffix = P('app.head.version') > 0 ? '?' . P('app.head.version') : '';
    //$head_suffix = '?'.time();

    // hugues BEGIN
    if ($opts['compile'] === true) {
      $script_compile_filepath = 'app/' . $ext . '/scripts/' . P('app.head.version') . '_' . $req->action() . '.js';
      $script_content = '';
      foreach ($scripts as $script) {
        $script_content .= file_get_contents(trim($script, '/'));
      }
      file_put_contents($script_compile_filepath, $script_content);
      $scripts = array('/' . $script_compile_filepath);

      $style_compile_filepath = 'app/' . $ext . '/styles/' . P('app.head.version') . '_' . $req->action() . '.css';
      $style_content = '';
      foreach ($styles as $style) {
        $style_content .= file_get_contents(trim($style, '/'));
      }
      file_put_contents($style_compile_filepath, $style_content);
      $styles = array('/' . $style_compile_filepath);
    }
    // hugues END


    if($opts['no_scripts'] !== false) {
      foreach ($scripts as $script) {
        $html .= ' <script src="' . FS . $script . $head_suffix . '" type="text/javascript"></script>' . "\n";
      }
    }

    foreach ($styles as $style) {
      $media = (strpos($style, 'print') !== false) ? 'print' : 'screen';
      if(S('req')->action() == 'account.declaration.edit' && $media == 'screen') $media = 'all';
      $html .= ' <link rel="stylesheet" href="' . FS . $style . $head_suffix . '" type="text/css" media="' . $media . '" />' . "\n";
    }

    foreach ($res->links as $rel => $hash) {
      $params = '';
      foreach ($hash as $key => $value) {
        $params .= ' ' . $key . '="' . $value . '"';
      }
      $html .= ' <link' . $params . ' />' . "\n";
    }

    $feeds = array_merge($opts['feeds'], $res->feeds, (array) P('front.feeds'));
    foreach ($feeds as $name => $url) {
      $html .= ' <link rel="alternate" href="' . $url . '" type="application/rss+xml" title="' . $name . '" />' . "\n";
    }

    if (!empty($opts['ie'])) {
      if ($opts['ie'] === true) {
        $path = 'app/' . $ext . '/styles/ie.css';
        $path = file_exists($style) ? $ext : CORE;
      }
      else {
        $path = $opts['ie'];
      }
      $html .= ' <!--[if IE 8]>
 <link rel="stylesheet" href="' . FS . '/app/' . $path . '/styles/ie8.css' . $head_suffix . '" type="text/css" />
 <![endif]-->' . "\n";
      $html .= ' <!--[if lt IE 8]>
 <link rel="stylesheet" href="' . FS . '/app/' . $path . '/styles/ie.css' . $head_suffix . '" type="text/css" />
 <![endif]-->' . "\n";
      $html .= ' <!--[if IE 7]>
 <link rel="stylesheet" href="' . FS . '/app/' . $path . '/styles/ie7.css' . $head_suffix . '" type="text/css" />
 <![endif]-->' . "\n";
      $html .= ' <!--[if IE 6]>
 <link rel="stylesheet" href="' . FS . '/app/' . $path . '/styles/ie6.css' . $head_suffix . '" type="text/css" />
 <![endif]-->' . "\n";
      /*$html .= ' <!--[if IE]>
 <link rel="SHORTCUT ICON" href="'.FS.'/'.APP_PATH.'/'.$ext.'/pix/favicon.ico" />
 <![endif]-->'."\n";*/
    }

    $html .= ' <link rel="icon" href="' . FS . '/' . APP_PATH . '/' . $ext . '/pix/favicon.png" type="image/png" />' . "\n";

    if ($opts['doctype'] == 'HTML5') {
      $head = '<!DOCTYPE html>' . "\n";
      $head .= '<html lang="' . $lang . '">' . "\n\n";
    }
    else
    if ($opts['doctype'] == 'HTML4') {
      $head = '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" ';
      $head .= '"http://www.w3.org/TR/html4/strict.dtd">' . "\n";
      $head .= '<html>' . "\n\n";
    }
    else {
      $head = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" ';
      $head .= '"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">' . "\n";
      $head .= '<html xmlns="http://www.w3.org/1999/xhtml">' . "\n\n";
    }

    $head .= '<head>' . "\n";

    $head .= $html;
    $head .= '</head>' . "\n\n";
    $body_class = 'scope-' . $req->scope() . ' extension-' . $req->extension() . ' action-' . str_replace('.', '-', $req->action());
    if ($ctx->hasAttribute('_body_class')) {
      $body_class .= ' ' . $ctx->getAttribute('_body_class');
    }
    $head .= '<body class="' . $body_class . '">' . "\n";
    $html = $head;

    return $html;
  }

  public static function identity($item) {
    $locale = S('res')->getLocale();
    $identity = $item instanceof ActiveRecord ? $item->asIdentityHash($locale) : $item;
    $html = '<table class="item-identity"><tr>' . "\n";
    if (!empty($identity['image'])) {
      $html .= '<td class="identity-image">' . "\n";
      $html .= ' <img src="' . $identity['image'] . '" class="item" />' . "\n";
      $html .= '</td>' . "\n";
    }
    $html .= '<td>' . "\n";
    $html .= ' <strong>' . c($identity['name']) . '</strong>' . "\n";
    $html .= ' <p>' . c($identity['description']) . '</p>' . "\n";
    $html .= '</td>' . "\n";
    $html .= '</tr></table>' . "\n";
    return $html;
  }

  public static function values($hash) {
    S('log')->trace('DEPRECATED');
    $out = json_encode($hash);
    $out = htmlspecialchars($out);
    return $out;
  }

  public static function args($hash) {
    $out = json_encode($hash);
    $out = htmlspecialchars($out);
    return $out;
  }

  public static function breadcrumb($opts = null) {
    $opts = (array) $opts;
    $separator = $opts['separator'] ? $opts['separator'] : ' > ';
    $res = S('res');
    $breadcrumb = S('ctx')->_breadcrumb;
    if (is_array($opts['prefix']) && is_array($breadcrumb)) {
      $breadcrumb = $opts['prefix'] + $breadcrumb;
    }
    if ($breadcrumb === null) return '';
    $links = array();
    $count = count($breadcrumb);
    $i = 1;
    foreach ($breadcrumb as $label => $url) {
      if (is_int($label)) {
        if ($url instanceof ActiveRecord) {
          $label = $url->getTitle();
          $url = $url->asUrl();
        }
        else {
          $label = $url;
          $url = '/';
        }
      }
      if ($url instanceof ActiveRecord) {
        $url = $url->asUrl();
      }
      $label = ucfirst($label);
      $label = strpos($label, '<') !== false ? h($label) : $label;
      if ($i === $count) {
        $links[] = '<span class="breadcrumb__elem">' . $label . '</span>';
        break;
      }
      $links[] = '<a class="breadcrumb__elem" href="' . $url . '">' . $label . '</a>';
      $i++;
    }
    $html = '<nav class="breadcrumb">' . join($separator, $links) . '</nav>';
    return $html;
  }

  public static function error($msg) {
    $template = P('template.error') ? P('template.error') : '/error';
    return Template::render($template, array('_error_msg' => $msg));
  }

  public static function avatar($hash) {
    $hash = (array) ($hash instanceof ActiveRecord ? $hash->getAttributes() : $hash);
    if (($hash['user_flags'] & User::FLAG_IMAGE) > 0) {
      $path = USR_PATH . '/' . $hash['user_path'] . '/_a.jpg';
    }
    else {
      $path = APP_PATH . '/community/pix/avatar.jpg';
    }
    return '<img src="/' . $path . '" class="avatar" />';
  }

  public static function button($label, $opts = null) {
    $type = $opts['type'] ? $opts['type'] : 'submit';
    $class = 'button';
    $class .= $opts['class'] ? ' ' . $opts['class'] : '';
    return '<input type="' . $type . '" class="' . $class . '" value="' . ucfirst($label) . '" />';
  }

  public static function ellipse($content, $opts = array()) {
    $content = strip_tags(html_entity_decode($content, ENT_QUOTES, 'UTF-8'));
    $opts['length'] = $opts['length'] ? $opts['length'] : 80;
    return strlen($content) < $opts['length']
        ? $content
        : substr($content, 0, $opts['length']) . '&hellip;';
  }

  public static function user($user) {
    if ($user instanceof ActiveRecord) {
      if ($user->isA(Model::id('user'))) {
        $user_id = $user->getId();
        $user_name = $user->name;
      }
      else {
        $user_id = $user->user_id;
        $user_name = $user->user_name;
      }
    }
    else {
      $user_name = $user;
    }
    return '<span class="kwo-user">' . $user_name . '</span>';
  }

  public static function foot($opts = null) {
    $opts = (array) $opts;
    $html = '';
    if ($opts['debug'] === true) {
      $html .= Widget::debug();
    }
    $html .= '</body></html>';
    //    S('res')->track_page = true;
    return $html;
  }

  public static function country($country_id, $locale = null) {
    $locale = $locale >= 1 ? $locale : self::locale();
    $column = 'name' . ($locale === I18N::LOCALE_FR ? '_fr' : '_en');
    return S('dbo')->fetchValue('SELECT ' . $column
        . ' FROM ' . T('country')
        . ' WHERE id=' . intval($country_id));
  }

  public static function amount($sum, $currency_id = null) {
    $currency = array('rate' => 1,
                      'symbol' => '€',//'EUR',
                      'decimal_point' => ',');
    if (!is_array(self::$currency)) {
      if (!S('req')->isHttp()) {
        self::$currency = $currency;
      }
      else {
        $currency_id = S('req')->getCookie()->currency_id;
        if ($currency_id >= 1) {
          try {
            $c = Currency::getInstance(array('id' => $currency_id,
                                             'status' => 1));
            $currency = array('rate' => $c->rate,
                              'symbol' => $c->code,
                              'decimal_point' => $c->decimal_point);
          }
          catch (Exception $e) {
          }
        }
        self::$currency = $currency;
      }
    }
    $currency = self::$currency;
    $value = number_format(($sum * $currency['rate']), 2, $currency['decimal_point'], ' ');
    if ($currency['symbol'] === 'USD') {
      $ret = '$' . $value;
    }
    else {
      $ret = $value . ' ' . $currency['symbol'];
    }
    return $ret;
  }

  public static function decimal($val, $dec = 2) {
    return number_format($val, 2, '.', '');
  }

  public static function date($date, $user_friendly = false) {
    if (strlen($date) < 6 || substr($date, 0, 4) === '0000') return '';
    $hash = Date::asHash($date);
    $html = $hash['day'] . '/' . $hash['month'] . '/' . $hash['year'];
    if ($user_friendly === true) {
      if (Date::isToday($hash)) $html = l('today');
      elseif (Date::isYesterday($hash)) $html = l('yesterday');
    }
    return $html;
  }

  public static function datetime($date) {
    if (strlen($date) < 6 || substr($date, 0, 4) === '0000') return '';
    $hash = Date::asHash($date);
    $html = $hash['day'] . '/' . $hash['month'] . '/' . $hash['year'] . ' ' . $hash['hour'] . ':' . $hash['min'];
    return $html;
  }

  public static function when($date) {
    if (strlen($date) < 6 || substr($date, 0, 4) === '0000') return '';
    $hash = Date::asHash($date);
    $html = $hash['day'] . '/' . $hash['month'] . '/' . $hash['year'] . ' ' . $hash['hour'] . ':' . $hash['min'];
    if (Date::isToday($hash)) {
      $n = time() - $hash['ts'];
      if ($n < 60) {
        $n = $n >= 1 ? $n : 1;
        $html = l('when.seconds.ago', array('n' => $n));
      }
      elseif ($n < 3600) {
        $html = l('when.minutes.ago', array('n' => floor($n / 60)));
      }
      elseif ($n < 43200) {
        $html = l('when.hours.ago', array('n' => floor($n / 3600)));
      }
      else {
        $html = l('when.today', array('time' => $hash['hour'] . ':' . $hash['min']));
      }
    }
    elseif (Date::isYesterday($hash)) {
      $html = l('when.yesterday', array('time' => $hash['hour'] . ':' . $hash['min']));
    }
    return $html;
  }

  public static function datenice($date) {
    $locale = self::locale();
    $time = strtotime($date);
    $html = '';
    if ($locale == I18N::LOCALE_EN) {
      $html .= ucfirst(I18N::$months[$locale]['long'][date('n', $time)]);
      $html .= date(' j', $time);
      $html .= ', ';
      $html .= date(' Y ', $time);
      $h = date('H:i', $time);
      if ($h != '00:00') {
        $html .= ' at ' . $h;
      }
    }
    else {
      $html .= I18N::$days[$locale]['long'][date('N', $time)];
      $html .= date(' j ', $time);
      $html .= ucfirst(I18N::$months[$locale]['long'][date('n', $time)]);
      $html .= date(' Y', $time);
      $h = date('H:i', $time);
      if ($h != '00:00') {
        $html .= ', ' . $h;
      }
    }
    return $html;
  }

  public static function age($date) {
    if (strlen($date) < 6 || substr($date, 0, 4) === '0000') return '';
    $hash = Date::asHash($date);
    $today = array('month' => date('n'), 'day' => date('j'), 'year' => date('Y'));
    $years = $today['year'] - $hash['year'];
    if ($today['month'] <= $hash['month']) {
      if ($hash['month'] == $today['month']) {
        if ($hash['day'] > $today['day']) {
          $years--;
        }
      }
      else {
        $years--;
      }
    }
    return $years;
  }

  public static function locale() {
    if (self::$locale < 1) {
      self::$locale = S('res')->getLocale();
    }
    return self::$locale;
  }

  public static function escapeHtml($str) {
    return h($str);
  }

  //  http://www.thespanner.co.uk/2011/09/12/protecting-against-xss/
  public static function escapeJs($input) {
    if (strlen($input) < 1) return '';
    $output = strtr($input,
                    array('\\' => '\\\\', "'" => "\\'", '"' => '\\"',
                          "\r" => '\\r', "\n" => '\\n', '</' => '<\/'));
    //$output = preg_replace("/[^\\x01-\\x7F]/", "", $output);
    return $output;
  }

  public function proxy($url, $item = null) {
    $query = 'url=' . urlencode($url);
    if ($input != null) {
      $query .= '&item_key=' . $item->getKey();
    }
    return '/core/proxy?' . $query;
  }

  public static function get($url, $args = null, $opts = null) {
    if ($args instanceof ActiveRecord) {
      $args = array('id' => $args->getId());
    }
    if ($opts instanceof ActiveRecord) {
      $opts = array('item' => $opts);
    }
    $opts = (array) $opts;
    $opts['ttl'] = intval($opts['ttl']) > 0 ? (int) $opts['ttl'] : 0;
    return Cache::request($url, $args, $opts);
  }

  public static function inc($templates, $bindings = true) {
    return Template::render($templates, $bindings);
  }

  public static function options($hash, $default = '') {
    $html = '';
    $hash = $hash instanceof Collection ? $hash->asHash() : $hash;
    $default = $default instanceof ActiveRecord ? $default->getId() : $default;
    foreach ($hash as $key => $value) {
      $html .= ' <option value="' . $key . '"' . ($default == $key ? ' selected' : '') . '>' . c($value) . '</option>' . "\n";
    }
    return $html;
  }

  public static function link($label, $attributes) {
    return self::elt('a', $label, $attributes);
  }

/*  public static function onload($js) {
    return self::trigger($js);
  }*/

  public static function trigger($js) {
    return self::elt('img', null,
                     array('on' => array('load' => $js),
                           'class' => array('js-loader')));
  }

  private static $voids = array('input', 'button', 'link', 'meta', 'img');

  public static function elt($tag, $content, $attrs = null) {
    if (is_array($tag)) {
      $html = '';
      foreach ($tag as $t) {
        $html .= self::elt($t['tag'], $t['content'], $t['attributes']);
      }
      return $html;
    }
    $attrs = (array) $attrs;
    $is_void = false;
    $tag = strtolower($tag);
    if (in_array($tag, self::$voids)) {
      $is_void = true;
      if ($tag == 'img') {
        if (!empty($content)) {
          $attrs['src'] = $content;
          $content = '';
        }
        if (empty($attrs['src'])) {
          $attrs['src'] = String::dataImage();
        }
      }
      else if (!empty($content)) {
        if ($tag == 'input' && $attrs['type'] == 'image') {
          $attrs['src'] = $content;
        }
        else {
          $attrs['value'] = $content;
        }
      }
      if ($tag == 'input') {
        $attrs['type'] = $attrs['type'] ? : 'text';
      }
    }
    if ($tag == 'a' && !isset($attrs['href'])) {
      $attrs['href'] = 'javascript:void(0)';
    }
    if (empty($attrs['class'])) {
      unset($attrs['class']);
    }
    if (empty($attrs['style'])) {
      unset($attrs['style']);
    }
    $attrs = Hash::asAttributes($attrs);
    if (!empty($attrs)) {
      $attrs = ' ' . $attrs;
    }
    $html = '<' . $tag . $attrs;
    if ($is_void === true) {
      $html .= ' />';
    }
    else {
      if ($content === null) {
        $html .= '>';
      }
      else {
        $html .= '>' . $content . '</' . $tag . '>';
      }
    }
    return $html;
  }



  public static function input_geoloc($name, $value, $options = array()) {
    $attrs = array('class' => 'text',
                   'type' => 'text',
                   'name' => $name,
                   'id' => $name,
                   'readonly' => '',
                   'style' => array('width:220px'),
                   'on' => array('click' => 'new Kwo.Geolocpicker(this)'));
    $html = self::elt('input', $value, $attrs);
    return $html;
  }

  public static function url($action = '', $params = null, $opts = null) {
    $params = (array) $params;
    $opts = (array) $opts;
    $app = $opts['app'] ? : App::getInstance(P('app.name'));

    $url = trim($action);
    if (strpos($url, '://') === false) {
      $url = $url[0] != '/' ? '/' . $url : $url;
      $prefix = $app->getAttribute('app.url.secure') ? 'https://' : 'http://';
      if ($app->getAttribute('app.url.user')) {
        $prefix .= $app->getAttribute('app.url.user');
        if ($app->getAttribute('app.url.password')) {
          $prefix .= ':' . $app->getAttribute('app.url.password');
        }
        $prefix .= '@';
      }
      $prefix .= $app->getAttribute('app.domain');
      $prefix .= $app->getAttribute('app.url.port') ? ':' . $app->getAttribute('app.url.port') : '';
      $url = $prefix . $url;
    }
    if (count($params) >= 1) {
      $sep = strpos($action, '?') === false ? '?' : '&';
      $url .= $sep . http_build_query($params);
    }
    return $url;
  }

  public static function countries($country_id = 0, $locale = null) {
    $country_id = $country_id ? $country_id : I18N::COUNTRY_FR;
    $locale = $locale ? $locale : self::locale();
    $lang = $locale === I18N::LOCALE_FR ? '_fr' : '_en';
    $countries = S('dbo')->asHash('SELECT id, name' . $lang
        . ' FROM ' . T('country')
        . ' WHERE status=1'
        . ' ORDER BY name' . $lang);
    $ret = '' . "\n";
    foreach ($countries as $id => $name) {
      $selected = $country_id == $id ? ' selected="selected"' : '';
      $ret .= ' <option value="' . $id . '"' . $selected . '>' . ucfirst(strtolower($name)) . '</option>' . "\n";
    }
    return $ret;
  }

  public static function birthdate($value = null, $opts = array()) {
    /* opts : id, name, class */
    $name = $opts['name'] ? $opts['name'] : 'birth_date';
    $name = ' name="' . $name . '"';
    $id = $opts['id'] ? ' id="' . $opts['id'] . '"' : '';
    //$onchange = ' onchange="Kwo.BirthDate.change(this)"';
    $onchange = ' onchange="Kwo.DateManager.birthdate(this)"';
    $hash = Date::asHash($value);
    $hash = $hash ? $hash : array();
    $value = '';
    if (!empty($hash)) {
      $value = ' value="' . $hash['year'] . '-' . $hash['month'] . '-' . $hash['day'] . '"';
    }
    $html = '<input type="hidden"' . $name . $id . $value . ' class="birthdate_input" />';
    $html_day = '<select class="kwo-birthdate birthdate-day"' . $onchange . '>';
    $html_day .= empty($hash) ? '<option value="0">--</option>' . "\n" : '';
    foreach (range(1, 31) as $i) {
      $selected = $i == $hash['day'] ? ' selected="selected"' : '';
      $html_day .= '<option value="' . $i . '"' . $selected . '>' . $i . '</option>';
    }
    $html_day .= '</select>';
    $html_month = '<select class="kwo-birthdate birthdate-month"' . $onchange . '>';
    $html_month .= empty($hash) ? ' <option value="0">----</option>' . "\n" : '';
    foreach (range(1, 12) as $i) {
      $selected = $i == $hash['month'] ? ' selected="selected"' : '';

      $html_month .= '<option value="' . $i . '"' . $selected . '>' . I18N::month($i, self::locale()) . '</option>';
    }
    $html_month .= '</select>';
    $html_year = '<select class="kwo-birthdate birthdate-year"' . $onchange . '>';
    $year = date('Y');
    $html_year .= empty($hash) ? '<option value="0">----</option>' . "\n" : '';
    foreach (range($year - 5, $year - 95) as $i) {
      $selected = $i == $hash['year'] ? ' selected="selected"' : '';

      $html_year .= '<option value="' . $i . '"' . $selected . '>' . $i . '</option>';
    }
    $html_year .= '</select>';
    if (self::locale() == I18N::LOCALE_FR) {
      $html .= $html_day . ' ' . "\n" . $html_month . ' ' . "\n" . $html_year;
    }
    else {
      $html .= $html_year . ' ' . "\n" . $html_month . ' ' . "\n" . $html_day;
    }
    return "\n" . $html;
  }

  public static function debug($var) {
    return var_export($var, true);
  }

}
