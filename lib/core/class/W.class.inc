<?php

class W {

  public static function abuse(ActiveRecord $item, $opts=null) {
    if (!Extension::exists('abuse')) return '';
    $opts = (array) $opts;
    $class = $opts['class'] ?: 'widget-action-abuse';
    $label = $opts['label'] ?: l('abuse.label');
    $title = $opts['title'] ?: l('abuse.title');
    $icon  = $opts['icon']  ?: '<img src="/app/alert/pix/flag-off.png" />';
    return '<a href="javascript:void(0)" class="widget-action '.$class.'" title="'.$title.'" onclick="new Kwo.Class.Abuse(this); return false;" data-item="'.$item->getKey().'" onmouseover="$(this).turn()" onmouseout="$(this).turn()"><span>'.$icon.''.$label.'</span></a>';
  }

  public static function advert($format=null, $opts=null) {
    if (!Extension::exists('adserver')) return '';
    return Advert::display($format, $opts);
  }

  public static function alert($item=null, $opts=null) {
    if (!Extension::exists('alert')) return '';
    $opts = (array) $opts;
    $html = '';
    if ($item instanceof ActiveRecord) {
      $datas = ' data-item="'.$item->getKey().'"';
    }
    else {
      $datas = ' data-keyword="'.str_replace('"', ' ', (string) $item).'"';
    }
    $onclick = 'new Kwo.Composer.Alert(this)';
    $class = $opts['class'] ? $opts['class'] : 'kwo-alert-button';
    $label = $opts['label'] ? $opts['label'] : l('alert.widget.link');
    $html  .= '<a href="javascript:void(0)" class="'.$class.'"'.$datas.' onclick="'.$onclick.'"><span>'.$label.'</span></a>';
    return $html;
  }

  public static function auth() {
    /*    if (S('res')->hasCacheHandler()) {
      $html = '<script>Event.observe(window, "load", Kwo.initAuthBox);</script>';
    }
    else { */
      $html = Template::render('community:widget.auth', true);
      /*    } */
    return '<div id="kwo-auth-box">'.$html.'</div>';
  }

  public static function favorite(ActiveRecord $item, $opts=array()) {
    // ajouter à ma sélection
    $class = $opts['class'] ? $opts['class'] : 'kwo-favorite-button';
    $label = isset($opts['label']) ? $opts['label'] : l('favorite.widget.label');
    $icon = $opts['icon'] ? $opts['icon'] : '/app/community/pix/favorite.png';
    $title = $opts['title'] ? ' title="'.$opts['title'].'"' : '';
    $html  = '<a href="javascript:void(0)" data-item="'.$item->getKey().'"'."\n";
    $html .= '   class="widget-action '.$class.'"'.$title."\n";
    $html .= '   onclick="new Kwo.Composer.Favorite(this)"><span><img src="'.$icon.'"/>'.$label.'</span></a>'; 
    return $html;
  }

  public static function fan(ActiveRecord $item, $opts=array()) {
    $class = $opts['class'] ? $opts['class'] : 'kwo-fan-button';
    $label = $opts['label'] ? $opts['label'] : l('fan.widget.label');
    $icon = $opts['icon'] ? $opts['icon'] : '/app/community/pix/fan.png';
    $title = $opts['title'] ? ' title="'.$opts['title'].'"' : '';
    $args = '{model_id: '.$item->getModelId().', record_id: '.$item->getId().'}';
    $html  = '<a href="javascript:void(0)" data-item="'.$item->getKey().'"'."\n";
    $html .= '   class="widget-action '.$class.'"'.$title.' alt="fan"'."\n";
    $html .= '   onclick="new Kwo.Composer.Favorite(this)"><span><img src="'.$icon.'"/>'.$label.'</span></a>';
    return $html;
  }

  public static function captcha() {
    return '<span class="kwo-captcha-box">'.Template::render('/widget.captcha', true).'</span>';
  }

  public static function cart() {
    if (!Extension::exists('shop')) return '';
    $order_id = (int) S('req')->getCookie()->getAttribute('order_id');
    $opts = null;
    if ($order_id >= 1) {
      try {
        $order = Order::getInstance($order_id, array('ignore' => true));
        $opts = array('item' => $order);
      }
      catch (Exception $e) {
        S('log')->error($e, __METHOD__);
        $order_id = 0;
        S('req')->getCookie()->removeAttribute('order_id');
      }
    }
    $html = Cache::request('/shop/cart.widget', array('id' => $order_id), $opts);
    return '<span id="kwo-cart-widget">'.$html.'</span>';
  }

  public static function clock($params=null) {
    return Template::render('/widget.clock', null);
  }

  public static function comment(ActiveRecord $item, $opts=null) {
    if (!Extension::exists('comment')) return '';
    $html  = '<div class="widget-comments" data="'.$item->getKey().'">'."\n";
    $html .= H::get('/comment/comments', 
                    array('item_key' => $item->getKey()),
                    array('item' => $item));
    $html .= '</div>';
    return $html;
  }

  public static function currencies() {
    if (!Extension::exists('shop')) return '';
    $opts = array('key' => 'currencies');
    return Cache::request('/shop/currencies.widget', null, $opts);
  }

  public static function debug() {
    $values = S('ctx')->getAttributes('debug');
    $values['_content'] = 'hidden';
    return Template::render('/widget.debug', array('context' => $values));
  }

  public static function feed($url, $opts=array()) {
    $class = $opts['class'] ? $opts['class'] : 'kwo-feed-button';
    $label = $opts['label'] ? $opts['label'] : l('feed.widget.label');
    $icon = $opts['icon'] ? $opts['icon'] : '/'.PIX_PATH.'/feed.icon.png';
    $title = $opts['title'] ? ' title="'.$opts['title'].'"' : '';

    $html  = '<a href="javascript:void(0)" class="widget-action '.$class.'"'.$title."\n";
    $html .= '   data-url="'.$url.'"';
    $html .= '   onclick="new Kwo.Composer.Feed(this)"><span><img src="'.$icon.'"/>'.$label.'</span></a>';

    return $html;
  }

  public static function form($args) {
    if (!Extension::exists('form')) return '';
    if (is_numeric($args)) {
      $args = array('id' => $args);
    }
    elseif (!is_array($args)) {
      $args = array('code' => $args);
    }
    $opts = array('ttl' => 0);
    return Cache::request('/form/widget', $args, $opts);
  }

  public static function homepage($msg) {
    return Template::render('/widget.homepage',
                            array('label' => $msg));
  }

  public static function locales() {
    $locales = S('app')->getLocales();
    if (!is_array($locales)) {
      return '';
    }
    $bindings['locale'] = S('res')->getLocale();
    foreach ($locales as $locale) {
      $bindings['locales'][$locale] = I18N::$locale_labels[$locale];
    }
    return Template::render('/widget.locales', $bindings);
  }

  public static function moderation($item, array $actions) {
    if (!S('req')->isModerator()) return ;
    $urls = array();
    foreach ($actions as $key => $value) {
      if (is_numeric($key)) {
        $key = $value;
      }
      if (empty($value)) continue ;
      if ($key === 'lock') {
        if (!$item->hasBit(Meta::BIT_LOCKED)) {
          $urls['fermer'] = '/core/item.lock?item_key='.$item->getKey();
        }
      }
      elseif ($key === 'pin') {
        if (!$item->hasBit(Meta::BIT_PINNED)) {
          $urls['figer'] = '/core/item.pin?item_key='.$item->getKey();
        }
      }
      elseif ($key === 'destroy') {
        $urls['supprimer'] = '/core/item.destroy?item_key='.$item->getKey();
      }
      elseif ($key === 'ban') {
        if ($item->user_id >= 1) {
          $urls['bannir'] = '/community/user.ban?user_id='.$item->user_id;
        }
      }
      else {
        $urls[$key] = $value.'/-/item_key/'.$item->getKey();
      }
    }
    if (count($urls) < 1) return '';
    foreach ($urls as $label => &$url) {
      if ($url[0] === '/') {
        $url = 'Kwo.exec(\''.$url.'\', null, {confirm:true, callback:true})';
      }
      elseif ($url[0] ===  'D') {
        $url = 'new Kwo.Dialog(\''.substr($url, 1).'\')';
      }
      $url = '<a href="javascript:void(0)" onclick="'.$url.'">'.$label.'</a>';
    }
    $html = '<div class="kwo-moderator-actions">'."\n";
    $html .= join(' - '."\n", $urls);
    $html .= '</div>';
    return $html;
  }

  public static function newsletter($code, $opts=array()) {
    if (!Extension::exists('push')) return '';
    try {
      $item = Base::getInstance(
                                array('code' => $code,
                                      'locale' => S('res')->getLocale()));
    }
    catch (Exception $e) { return 'Attention ! invalid newsletter ('.$code.')!'; }

    $class = $opts['class'] ? ' '.$opts['class'] : ' kwo-newsletter-button';
    $label = $opts['label'] ? $opts['label'] : l('widget.push.label');
    $icon = $opts['icon'] ? $opts['icon'] : '/app/push/pix/newsletter.icon.png';
    $title = $opts['title'] ? ' title="'.$opts['title'].'"' : '';

    $data = ' data-item="'.$item->getKey().'"';
    $html  = '<a href="javascript:void(0)" class="widget-action'.$class.'"'.$title."\n";
    $html .= '   onclick="new Kwo.Class.Newsletter(this)"'.$data.'><span><img src="'.$icon.'"/>'.$label.'</span></a>';

    return $html;
  }

  public static function opinion($item) {
    $html  = '<span class="utils opinion-utils">'."\n";
    if (Extension::exists('rating')) {
      $html .= self::thumb($item);
    }
    if (Extension::exists('abuse')) {
      $html .= self::abuse($item);
    }
    $html .= '</span>';
    return $html;
  }

  public static function poll($code='') {
    if (!Extension::exists('poll') || empty($code)) return '';
    $args = array('code' => $code);
    return H::get('/poll/poll', $args);
  }

  public static function rate(ActiveRecord $item, $opts=array()) {
    if (!Extension::exists('rating')) return '';
    $args = $opts;
    $args['star_count'] = 5;
    $args['model_id'] = $item->getModelId();
    $args['record_id'] = $item->getId();
    if ($args['value'] === true || empty($args['value'])) {
      $args['value'] = (int) Meta::get($item, 'rating');
    }
    else {
      $args['value'] = (int) $args['value'];
    }
    return Template::render('rating:widget', $args);
  }

  public static function share($item=null, $opts=null) {
    if (!Extension::exists('share')) return '';
    $opts = (array) $opts;
    if (!($item instanceof ActiveRecord)) {
      $item = is_string($item) ? $item : '/';
      $item = Url::asItem($item);
    }
    $datas = ' data-item="'.$item->getKey().'"';
    if ($opts['count'] === true) {
      $n = $item->getMeta('shares');
      if ($n >= 1) {
        $label .= ' | '.$n;
      }
    }
    if (isset($opts['mode'])) {
      $datas .= ' data-mode="'.$opts['mode'].'"';
    }
    $class = $opts['class'] ? $opts['class'] : 'kwo-share-button';
    $label = isset($opts['label']) ? $opts['label'] : l('share.widget.label');
    $icon  = isset($opts['icon']) ? $opts['icon'] : '/app/share/pix/share-icon-16x16.png';
    $img = '';
    if (!empty($icon)) {
      $img = '<img src="'.$icon.'" />';
    }
    if (strpos($img, '.png') !== false) {
      $class .= ' png';
    }
    $title = $opts['title'] ? ' title="'.$opts['title'].'"' : '';
    $html  = '<a href="javascript:void(0)" class="widget-action '.$class.'"'.$title.' alt="share"'."\n";
    $html .= '   onclick="new Kwo.Composer.Share(this)"'.$datas.'><span>'.$img.$label.'</span></a>';
    return $html;
  }

  public static function thumb($item) {
    $metas = $item->getMetas('dislike', 'like');
    $html = '';
    foreach (array('down', 'up') as $direction) {
      $html .= '<span><a href="javascript:void(0)" data-item="'.$item->getKey().'""'."\n";
      $html .= '   class="widget-action widget-action-thumb thumb-'.$direction.'"'."\n";
      $html .= '   onclick="Kwo.Rating.onThumb(this)"'."\n";
      $html .= '   onmouseover="$(this).turn()"'."\n";
      $html .= '   onmouseout="$(this).turn()"><span>';
      $html .= '<img src="/app/rating/pix/thumb-'.$direction.'-off.png" />';
      $html .= intval($metas[$direction == 'up' ? 'like' : 'dislike']);
      $html .= '</span></a></span> ';
    }
    return $html;
  }

  public static function like($item, $opts=null) {
    $opts = (array) $opts;
    $attributes = array('class' => array('widget-i-like'),
                        'on' => array('click' => 'new Kwo.Class.Like(this)'),
                        'data' => array('item' => $item->getKey()));
    $label = $opts['label'] ?: 'I like';
    if (($n = $item->getMeta('like')) > 0) {
      $label .= ' <span>('.$n.')</span>';
    }
    return H::elt('span', $label, $attributes);
  }

  public static function tracker($name, $group=null) {
    S('req')->track($name, $group=null);
  }

}
