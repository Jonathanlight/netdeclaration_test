<?php

  // replace BOM : $text = str_replace("\xEF\xBB\xBF", '', $text);

  // Voir : https://sites.google.com/site/murmurhash/
  //        http://en.wikipedia.org/wiki/CityHash


class String extends ActiveRecord
{
  const FLAG_PROTECTED = 1;
  public static $flags = array(self::FLAG_PROTECTED => 'protégé');

  public function onAfterStore() {
    $this->syncAttributes();
  }

  public function syncAttributes() {
    $locales = array();
    $rs = $this->dbo->query('SELECT value, locale'.
                            ' FROM '.Item::TABLE_PROPERTY
                            .' WHERE model_id='.$this->getModelId()
                            .  ' AND record_id='.$this->getId()
                            .' ORDER BY locale ASC');
    $cache = '';
    foreach ($rs as $row) {
      if (empty($row['value'])) continue ;
      $cache .= $row['value']."\n";
      if (!in_array($row['locale'], $locales)) $locales[] = $row['locale'];
    }
    $attrs = array('cache' => $cache,
                   'locales' => array_sum($locales));
    $this->setAttributes($attrs);    
  }
  
  public function asFinderHash($hash) {
    $lines = explode("\n", $hash['cache']);
    $hash['cache'] = $lines[0];
    return $hash;
  }

  public static function CacheWrite() {
    $rs = S('dbo')->query('SELECT p.value, p.locale, s.name, s.app'
                          .' FROM '.Item::TABLE_PROPERTY.' AS p,'
                          .     ' '.T('string').' AS s'
                          .' WHERE p.model_id='.I('string')
                          .  ' AND p.record_id=s.id'
                          .  ' AND s.status>0'
                          .' ORDER BY s.name ASC');
    foreach (App::all() as $app) { 
      $name = $app['app.name'];
      $path = APP_PATH.'/'.$app['app.extension'].'/locales';
      if (!is_dir($path)) {
        mkdir($path);
      }
      $strings = array();
      foreach ($rs as $row) {
        if (!empty($row['app']) && $row['app'] != $name) continue ;
        $strings[$row['locale']] = (array) $strings[$row['locale']];
        $strings[$row['locale']][$row['name']] = $row['value']; 
      }
      $words = array();
      $filenames = array();
      foreach ($strings as $locale => $words) {
        $filename = 'messages_'.I18N::code($locale).'.inc';
        $filenames[] = $filename;
        $file = $path.'/'.$filename; 
        file_put_contents($file,
                          '<?php'."\n\n".
                          '$strings = '.var_export($words, true).';'.
                          "\n");
      }
      $files = glob($path.'/*.inc');
      $files = $files ?: array();
      foreach ($files as $file) {
        $filename = basename($file);
        if (in_array($filename, $filenames)) continue ;
        if (file_exists($file)) {
          S('log')->trace('unlink : '.$file, __METHOD__);
          unlink($file);
        }
      }
    }
  }

  //---------------------------

  public static function crc32($data) {
    return sprintf('%u', crc32($data));
  }

  public static function crc16($data) {
    $crc = 0xFFFF;
    for ($i = 0; $i < strlen($data); $i++) {
      $x = (($crc >> 8) ^ ord($data[$i])) & 0xFF;
      $x ^= $x >> 4;
      $crc = (($crc << 8) ^ ($x << 12) ^ ($x << 5) ^ $x) & 0xFFFF;
    }
    return $crc;
  }

  public static function isUtf8(&$str) {
    $l = strlen($str);
    for ($i = 0; $i < $l; $i++) {
      if (ord($str[$i]) < 0x80) $n = 0;
      elseif ((ord($str[$i]) & 0xE0) == 0xC0) $n = 1;
      elseif ((ord($str[$i]) & 0xF0) == 0xE0) $n = 2;
      elseif ((ord($str[$i]) & 0xF0) == 0xF0) $n = 3;
      else return false;
      for ($j = 0; $j < $n; $j++) {
	if ((++$i == $l) || ((ord($str[$i]) & 0xC0) != 0x80)) return false;
      }
    }
    return true;
  }

  public static function slugify($str) {
    return self::urlify($str);
  }

  public static function urlify($str) {
    $str = trim($str);
    if (empty($str)) return '';
    $str = self::stripAccents($str);
    $str = strtolower($str);
    $str = preg_replace('/&.+?;/', '', $str);
    $str = preg_replace(array('/(\s|[^\w-]|-|,)+/u'), array('-'), $str);
    $str = trim($str, '-');
    $str = urlencode($str);
    return $str;
  }

  /* http://tidy.sourceforge.net/docs/quickref.html#replace-color */
  public static function tidy($str, $opts=null) {
    //S('log')->debug($str);
    if (!function_exists('tidy_get_config')) return $str;
    $opts = (array) $opts;
    $config = array('indent'           => true,
                    'indent-spaces'    => 2,
                    'add-xml-space'    => true,
                    'output-xhtml'     => true,
                    'wrap'             => $opts['wrap'] ? $opts['wrap'] : 200,
                    'show-body-only'   => true,
                    'uppercase-tags'   => true,
                    'word-2000'        => true,
                    'bare'             => true,
                    'logical-emphasis' => true,
                    'force-output'     => true,
                    'clean'            => false,
                    'vertical-space'   => true,
                    'fix-uri'          => false,
                    'char-encoding'    => 'utf8');
    //    $config = array();
    $str = str_ireplace(array('<style>', '</style>'),
                        array('[kwostyle]', '[/kwostyle]'),
                        $str);

    $tidy = new tidy();
    $tidy->parseString($str, $config, 'utf8');
    $tidy->cleanRepair();
    $str = (string) $tidy;
    //    S('log')->debug($str);
    $str = str_ireplace(array('[kwostyle]', '[/kwostyle]', '%28%28', '%29%29'),
                        array('<style>', '</style>', '((', '))'),
                        $str);
    //    $str = preg_replace('/\&amp;/u', '&', $str);
    //    error_log('--> '.$str);
    return $str;
  }

  public static function capitalize($input, $encoding='UTF-8') {
    if (is_array($input)) {
      foreach ($input as &$value) $value = self::capitalize($value, $encoding);
      return $input;
    }
    return mb_strtoupper(mb_substr($input, 0, 1, $encoding), $encoding)
         . mb_substr($input, 1, strlen($input), $encoding);
  }

  public static function polish($input) {
    $words = S('dbo')->asSet('SELECT name'
                             .' FROM '.T('badword')
                             .' WHERE locale='.S('res')->getLocale());
    $pattern = '/('.join('|', $words).')/ui';
    $input = preg_replace($pattern, '***', $input);
    return $input;
  }

  public static function bind($str, $bindings) {
    if (empty($bindings) || strlen($str) <= 3 || !is_array($bindings)) return $str;
    $patterns = array();
    foreach ($bindings as $key => $value) {
      $patterns[] = '/\$\{'.$key.'\}/u';
    }
    $str = preg_replace($patterns, $bindings, $str);
    return $str;
  }

  public static function bind2($str, $bindings) {
    if (empty($bindings) || strlen($str) <= 3 || !is_array($bindings)) return $str;
    $patterns = array();
    foreach ($bindings as $key => $value) {
      $patterns[] = '/\(\('.$key.'\)\)/u';
    }
    $str = preg_replace($patterns, $bindings, $str);
    return $str;
  }

  public static function markers($content, $open, $close) {
    $o = preg_quote($open);
    $c = preg_quote($close);
    $regexpr = '/'.$o.'([^'.$c.']+)'.$c.'/u';
    //    error_log($regexpr.$content);
    preg_match_all($regexpr, $content, $matches);
    return empty($matches) ? array() : $matches[1];
  }

  public static function isRude(&$input, $locale=null) {
    $locale = $locale ? $locale : S('res')->getLocale();
    $words = S('dbo')->asSet('SELECT name'
                             .' FROM '.T('badword')
                             .' WHERE locale='.S('res')->getLocale());
    $pattern = '/('.join('|', $words).')/ui';
    return preg_match_all($pattern, $input, $matches) >= 1;
  }

  public static function clean($input, $opts=null) {
    if (empty($input)) return $input;
    $opts = (array) $opts;
    if (is_array($input)) {
      foreach ($input as $k => $value) $input[$k] = self::clean($value, $opts);
      return $input;
    }
    $to = $opts['strict'] === true ? array(' ', ' ') : array('&lt;', '&gt;');
    $input = str_replace(array('<', '>'), $to, $input);
    return $input;
  }

  public static function filter($str, $opts=null) {
    //    $input = self::polish($input);
    $opts = (array) $opts;
    $debug = $opts['debug'] == true;

    $str = str_replace(array('<u>', '</u>',
                             '<h1>', '<h2>', '<h3>',
                             '</h1>', '</h2>', '</h3>'),
                       array('<span class="underline">', '</span>',
                             '<strong>', '<strong>', '<strong>',
                             '</strong>', '</strong>', '</strong>'),
                       $str);
    $str = $opts['bbcode'] !== false ? self::bbcodize($str) : $str;
    if (!function_exists('tidy_get_config')) {
      return htmlspecialchars(strip_tags($str,
                                         '<br><strong><em><h1><h2><h3><p><pre><blockquote>',
                                         'UTF-8'));
    }

    $config = array('indent'           => true,
                    'indent-spaces'    => 2,
                    'output-xhtml'     => true,
                    'wrap'             => 200,
                    'show-body-only'   => true,
                    'uppercase-tags'   => true,
                    'word-2000'        => true,
                    'logical-emphasis' => true,
                    'force-output'     => true,
                    'hide-comments'    => true,
                    'clean'            => true,
                    'fix-uri'          => true,
                    'vertical-space'   => true,
                    'char-encoding'    => 'utf8');
    $tidy = new tidy;
    $tidy->parseString($str, $config, 'utf8');
    $tidy->cleanRepair();
    $str = (string) $tidy;
    $str = str_replace(array('<a href="http'),
                       array('<a target="_blank" href="http'),
                       $str);
    if ($debug === true) {
      print("\n".$str.'-----[clean debug]--------'."\n");
    }
    try {
      $suspicious_tags = array('script', 'object', 'embed', 'link', 'iframe', 'form',
                               'param', 'input', 'select', 'option', 'textarea', 'link',
                               'table', 'tr', 'td', 'tbody', 'style', 'area',
                               'video', 'audio', 'source', 'canvas', 'svg', 'eventsource',
                               'details', 'meter');
      $suspicious_attr = array('lowsrc', 'dynsrc', 'background', 'ping', 'id', 'name',
                               //                               'class',
                               'contenteditable');
      $str = String::tidy($str);
      $doc = new DOMDocument();
      @$doc->loadXML('<content>'.$str.'</content>');
      $nodes = $doc->getElementsByTagName('*');

      if ($nodes->length >= 1) {
        foreach ($nodes as $node) {
          if ($debug === true) print($node->nodeName."\n");
          if (in_array($node->nodeName, $suspicious_tags)) {
            throw new Exception($node->nodeName);
          }
          if ($node->attributes === null) {
            continue ;
          }
          foreach ($node->attributes as $attribute) {
            $name = strtolower($attribute->name);
            $value = strtolower($attribute->value);
            if (in_array($name, $suspicious_attr) ||
                strpos($value, 'javascript') !==  false ||
                strpos($value, '>') !==  false ||
                strpos($value, '(') !==  false ||
                strpos($value, ';') !==  false ||
                strpos($value, "'") !==  false ||
                substr($name, 0, 2) == 'on') {
              throw new Exception($name);
            }
            if ($name == 'style') {
              if (strpos($value, '/') !== false) {
                throw new Exception($value);
              }
            }
            if ($debug === true) print(' . '.$name.' > '.$value."\n");
          }
        }
      }
    }
    catch (Exception $e) {
      S('log')->warn($e, __METHOD__);
      $str = 'forbidden ('.$e->getMessage().')';
    }
    if ($debug === true) {
      print("------[/clean debug]--------\nOUTPUT:".substr($str, strpos($str, ':'), strlen($str))."\n\n\n");
    }
    $str = preg_replace('/(<br\s?\/?>\s*){3,}/Diu', '<br /><br /><br />', $str);
    $str = preg_replace('/(<br\s?\/?>\s*)+$/Diu', '', $str);
    $str = preg_replace('/\&amp;/u', '&', $str);
    return $str;
  }

  public static function cleanEmbed($str) {
    /*
    static $urls = array('www.dailymotion.com' => array('regex' => '\/video\/([\w\d]+)_.*',
                                                        'embed' => '<object width="420" height="339"><param name="movie" value="http://www.dailymotion.com/swf/\1&autoPlay=1&related=1" /><param name="allowFullScreen" value="true" /><param name="allowScriptAccess" value="always" /><embed src="http://www.dailymotion.com/swf/\1_back-on-topps-3-there-goes-my-wood_fun&autoPlay=1&related=1" type="application/x-shockwave-flash" width="420" height="339" allowFullScreen="true" allowScriptAccess="always"></embed></object>'),
                         'www.youtube.com' => array('regex' => '\/watch\?v\=([\w\d_\-]+).*',
                                                    'embed' => '<object width="560" height="340"><param name="movie" value="http://www.youtube.com/v/\1&hl=en&fs=1&"></param><param name="allowFullScreen" value="true"></param><param name="allowscriptaccess" value="always"></param><embed src="http://www.youtube.com/v/\1&hl=en&fs=1&" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width="560" height="340"></embed></object>'));
    */
    static $urls = array('www.dailymotion.com' => array('regex' => '\/video\/([\w\d]+)_.*',
                                                        'embed' => '<iframe frameborder="0" width="420" height="339" src="http://www.dailymotion.com/embed/video/\1?theme=none"></iframe>'),
                         'www.youtube.com' => array('regex' => '\/watch\?v\=([\w\d_\-]+).*',
                                                    'embed' => '<iframe title="YouTube video player"  width="420" height="339" src="http://www.youtube.com/embed/\1" frameborder="0" allowfullscreen></iframe>'),
                         'vimeo.com' => array('regex' => '\/([\d]+)',
                                              'embed' => '<iframe src="http://player.vimeo.com/video/\1"  width="420" height="339" frameborder="0"></iframe>'));
    /* http://kb2.adobe.com/cps/127/tn_12701.html */
    static $allowed_tags = array('iframe' => array('attributes' => array('width', 'height', 'src', 'frameborder', 'allowfullscreen')),
                                 'object' => array('attributes' => array('width', 'height', 'classid', 'codebase', 'movie', 'id', 'data', 'type', 'name')),
                                 'embed' => array('attributes' => array('src', 'type', 'allowscriptaccess', 'allowfullscreen', 'id',
                                                                        'width','height', 'pluginspage', 'scale', 'wmode', 'movie',
                                                                        'quality', 'flashvars', 'name', 'swliveconnect', 'play',
                                                                        'loop', 'menu', 'align', 'salign','bgcolor', 'base')),
                                 'param' => array('attributes' => array('name', 'value')));

    if (filter_var($str, FILTER_VALIDATE_URL)) {
      $host = parse_url($str, PHP_URL_HOST);
      if (isset($urls[$host])) {
        return preg_replace('/'.preg_quote('http://'.$host, '/').$urls[$host]['regex'].'/', $urls[$host]['embed'], $str);
      }
    }
    $doc = new DOMDocument();
    $doc->formatOutput = true;
    @$doc->loadHTML('<content>'.$str.'</content>');
    $xpath = new DOMXPath($doc);
    $start_node = $xpath->evaluate('//object | //embed')->item(0);
    if ($start_node === null) {
      throw new Exception('embed not found');
    }
    foreach ($start_node->parentNode->getElementsByTagName('*') as $node) {
      if (!isset($allowed_tags[$node->nodeName])) {
        $node->parentNode->removeChild($node);
        continue;
      }
      if ($node->attributes !== null) {
        foreach ($node->attributes as $attribute) {
          if (!in_array(strtolower($attribute->name), $allowed_tags[$node->nodeName]['attributes'])) {
            $node->removeAttribute($attribute->name);
          }
        }
      }
      if ($node->nodeName == 'param' && $node->hasAttribute('name')) {
        if (!in_array(strtolower($node->getAttribute('name')), $allowed_tags['embed']['attributes'])) {
          $node->parentNode->removeChild($node);
        }
      }
    }
    if ($start_node === null) {
      throw new Exception('embed not found');
    }
    return $doc->saveXML($start_node,LIBXML_NOEMPTYTAG);
  }

  public static function bbcodize($str) {
    $str = str_replace(array('[b]', '[/b]', '[i]', '[/i]', '[u]', '[/u]',
                             '[quote]', '[/quote]', '[code]', '[/code]'),
                       array('<strong>', '</strong>', '<em>', '</em>', '<span class="underline">', '</span>',
                             '<blockquote>', '</blockquote>', '<code>', '</code>'),
                       $str);
    return $str;
  }

  public static function decorate($str) {
    $emoticons = array(':)' => 'smile',
                       '=)' => 'smile',
                       ':|' => 'neutral',
                       '=|' => 'neutral',
                       ' :[' => 'sad',
                       ':(' => 'sad',
                       '=(' => 'sad',
                       ':D' => 'big_smile',
                       '=D' => 'big_smile',
                       ':o' => 'yikes',
                       ':O' => 'yikes',
                       ';)' => 'wink',
                       ' :/' => 'tongue',
                       ':P' => 'tongue',
                       ':lol:' => 'lol',
                       ':mad:' => 'mad',
                       ':rolleyes:' => 'roll',
                       ':cool:' => 'coll',
                       );
    foreach ($emoticons as $key => &$value) {
      $value = '<img src="/'.PIX_PATH.'/emoticons/'.$value.'.png" class="emoticon" />';
    }
    return str_replace(array_keys($emoticons),
                       $emoticons,
                       $str);
  }

  public static function texturize($str) {
    if (strpos($str, '<') !== false) return $str;
    $str = preg_replace('/\'/u', '’', $str);
    return $str;
  }

  public static function crypt($str) {
    return substr(hash('md5', $str.KWO_SEED), 0, 8);
  }

  public static function password($length=8) {
    $seed = 'abcdefhikmnrstuwxz'.'2456789';
    $ret  = '';
    for ($i = 1; $i <= $length; $i++) {
      $ret .= $seed[mt_rand(0, strlen($seed) - 1)];
    }
    return $ret;
  }

  public static function asSet($str, $separator=null) {
    if (is_array($str)) {
      return $str;
    }
    $str = trim($str);
    if (empty($str)) {
      return array();
    }
    if ($separator !== null) {
      $parts = explode($separator, $str);
    }
    else {
      $parts = preg_split('/(\r)?\n|,|;|\t/u', $str, -1);
    }
    $results = array();
    foreach ($parts as $key => $value) {
      $value = trim($value, "' ");
      if (empty($value)) continue ;
      $results[] = $value;
    }
    return $results;
  }

  public static function asHash($str, $separator=null) {
    $set = self::asSet($str, $separator);
    $hash = array();
    foreach ($set as $elt) {
      list ($key, $value) = explode('=', $elt);
      $key = trim($key);
      $value = trim($value);
      $hash[$key] = $value;
    }
    return $hash;
  }

  public static function normalize($str) {
    $s = strtolower($s);
    $str = self::stripAccents($str);
    $str = preg_replace('/(\s|\W)/u', '', $str);
    return $str;
  }

  public static function stripAccents($str) {
    $patterns = array('/[àáâãäåāăąĄĂÀÁÂÃÄÅ]/u',
                      '/[þÞ]/u',
                      '/[çčÇĆćĈĉĊċČč]/u',
                      '/[ðďĎďĐđ]/u',
                      '/[èéêëēėęěěÈÉÊËĒĖĘĚ]/u',
                      '/[ĜĝĞğĠġĢģ]/u',
                      '/[ĤĥĦħ]/u',
                      '/[ìíîïÌÍÎÏĨĩĪīĮįİı]/u',
                      '/[Ĵĵ]/u',
                      '/[Ķķĸ]/u',
                      '/[ĹĺĻļĽľŁł]/u',
                      '/[ñňÑŇŃńŅņŇň]/u',
                      '/[òóôõöøÒÓÔÕÖØŌōŐő]/u',
                      '/[ŕřŔŘŔŕŖŗ]/u',
                      '/[šßŠŚśŜŝŞş]/u',
                      '/[ŢţŤťŦŧ]/u',
                      '/[ùúūũûŭüůųÙÚŪŨÛŬÜŮŲŮ]/u',
                      '/[Ŵŵ]/u',
                      '/[ýÿŷÝŶŸ]/u',
                      '/[ŹźŻż]/u');
    $replacements = array('a', 'b', 'c', 'd', 'e', 'g', 'h',
                          'i', 'j', 'k', 'l', 'n', 'o', 'r',
                          's', 't', 'u', 'w', 'y', 'z');
    $str = preg_replace($patterns, $replacements, $str);
    return $str;
  }

  public static function toSize($size) {
    if ($size > 1048576) $type = 'M';
    elseif ($size > 1024) $type = 'K';
    else $type = '';
    if ($type === 'K') $ret = number_format($size / 1024,1, '.', '');
    elseif ($type === 'M') $ret = number_format($size / 1048576,1, '.', '');
    else $ret = number_format($size, 0, '', '');
    return $ret.$type;
  }

  public static function dataImage() {
    return 'data:image/gif;base64,R0lGODlhAQABAID/AMDAwAAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==';
  }

  public static function spacer() {
    header('Content-type: image/gif');
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c".
           "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
           71,73,70,56,57,97,1,0,1,0,128,255,0,192,192,192,0,0,0,
           33,249,4,1,0,0,0,0,44,0,0,0,0,1,0,1,0,0,2,2,68,1,0,59);
  }

  public static function extractTags($str, $open, $close) {
    $tags = array();
    $offset = 0;
    $open_len = strlen($open);
    $close_len = strlen($close);
    while (($i = strpos($str, $open, $offset)) !== false) {
      $i += $open_len;
      $offset = $i;
      $j = strpos($str, $close, $offset);
      if ($j === false) {
      	$offset = $i;
      	continue ;
      }
      $tags[] = substr($str, $i, ($j - $i));
      $offset = $j + $close_len;
    }
    return array_unique($tags);
  }

  public static function detectEncoding($str) {
    $enc = mb_detect_encoding($str, 'UTF-8,ISO-8859-15,ISO-8859-1', true);
    if ($enc === false) {
      throw new Exception('charset not found');
    }
    if (in_array($enc, array('ISO-8859-15', 'ISO-8859-1'))) {
      // http://fr.wikipedia.org/wiki/CP1252
      $cp_1252_chars = array(0x80, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
                             0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8e, 0x91,
                             0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
                             0x99, 0x9a, 0x9b, 0x9c, 0x9e, 0x9f);
      $l = strlen($str);
      while (--$l) {
        if (in_array(ord($str[$l]), $cp_1252_chars)) {
          return 'windows-1252';
        }
      }
    }
    return $enc;
  }

}

