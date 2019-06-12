<?php

/* rss agent : google desktop|rss|feed|wordpress|blog|gator|syndicat|pubsub|news|veoh|php|harvest|voyager|indy| */
/* rss domain : newserbay|parwch0|ns202191|car75|confix */

class Tracker {

  const COOKIE_NAME = 'tracker';

  private $cookie = null;
  private $crc = null;
  private $dbo = null;
  private $req = null;
  private $seal_required = false;
  private $ttl = 1800;
  private $ts = null;

  const SEAL_SEED = 1001977;

  const CATEGORY_ERROR = 'errors';
  const CATEGORY_PAGE  = 'pages';
  const CATEGORY_EVENT = 'events';

  const TABLE_HIT     = 'tkr_hit';
  const TABLE_TMP     = 'tkr_hit_tmp';
  const TABLE_ROBOT   = 'tkr_robot';
  const TABLE_SEARCH  = 'tkr_search';
  const TABLE_STRING  = 'tkr_string';
  const TABLE_VISITOR = 'tkr_visitor';

  const MEDIUM_DIRECT    = '1';
  const MEDIUM_CPM       = '2';
  const MEDIUM_SEARCH    = '3';
  const MEDIUM_LINK      = '4';
  const MEDIUM_CPC       = '5';
  const MEDIUM_CAMPAIGN  = '6';
  const MEDIUM_RSS       = '7';
  const MEDIUM_USER      = '8';
  const MEDIUM_AFFILIATE = '9';
  const MEDIUM_MAIL      = '10';
  const MEDIUM_SOCIAL    = '11';

  public static $mediums = array(self::MEDIUM_CPC       => 'CPC',
                                 self::MEDIUM_CPM       => 'CPM',
                                 self::MEDIUM_DIRECT    => 'accès direct',
                                 self::MEDIUM_AFFILIATE => 'affiliation',
                                 self::MEDIUM_RSS       => 'flux (RSS)',
                                 self::MEDIUM_MAIL      => 'mail transactionnel',
                                 self::MEDIUM_CAMPAIGN  => 'mailing',
                                 self::MEDIUM_SEARCH    => 'moteur de recherche',
                                 self::MEDIUM_USER      => 'parrainage',
                                 self::MEDIUM_SOCIAL    => 'réseau social',
                                 self::MEDIUM_LINK      => 'site affluent');
  const STR_CATEGORY = 1;
  const STR_ACTION   = 2;
  const STR_HOST     = 10;
  const STR_QUERY    = 15;
  const STR_SOURCE   = 20;
  const STR_TERM     = 21;
  const STR_CAMPAIGN = 22;

  public static $disabled = false;

  public function __construct() { 

    $this->dbo = S('dbo');
    $this->req = S('req');
    $this->ts = time();
    $this->cookie = $this->req->getCookie(self::COOKIE_NAME); 

    if ($this->hasValidSeal()) { 
      if ($this->hasExpired() || $this->isNewSource()) {
        if (self::$disabled === true || $this->isBot()) {
          throw new Exception();
        }
        $this->renew();
      }
      elseif (($this->ts - $this->cookie->getAttribute('ts')) > 60) {
        $this->setCookieAttributes(array('ts' => $this->ts));
      }
    }
    else { 
      /*      if ($this->isBot()) {
        throw new Exception();
      }
      if (self::$disabled === true) {
        $row = $this->getDb();
        if ($row['visit_id'] < 0) throw new Exception();
        }*/
      if (self::$disabled === true || $this->isBot()) {
        throw new Exception();
      }
      $this->init();

    }

    $visit_id = (int) $this->cookie->getAttribute('visit_id'); 
    $this->req->setParameter('visit_id', $visit_id);

    if ($this->req->isNewVisit()) {
      S('log')->trace('new visit ('.$visit_id.') ['.$this->req->getUrl().']');
      $number = $this->cookie->getAttribute('number') + 1;
      $this->req->setParameter('visit_number', $number);
      $actual = $this->cookie->getAttribute('actual') ?: $this->ts;
      $attrs = array('number' => $number,
                     'previous' => $actual,
                     'actual' => $this->ts);
      if ($this->req->hasAttribute('knxsid', true)) {
        $attrs['sponsorship_id'] = (int) $this->req->getAttribute('knxsid');
      }
      $this->setCookieAttributes($attrs);
      S('app')->hook('onNewVisit');
    }

    $this->seal();

  }

  private function setCookieAttributes($attr) {
    if (isset($attr['visit_id']) || isset($attr['visitor_id']) || isset($attr['ts'])) {
      $this->seal_required = true;
    }
    $this->cookie->setAttributes($attr);
  }

  private function seal() {
    if ($this->seal_required === false) return ;
    $visit_id = $this->cookie->getAttribute('visit_id');
    $visitor_id = $this->cookie->getAttribute('visitor_id');
    $seal = $this->calcSeal($visit_id, $visitor_id, $this->ts);
    $this->cookie->setAttributes(array('seal' => $seal,
				       'd' => date('d'),
                                       'ts' => $this->ts));
    $this->trace($this->cookie->getAttributes());
  }

  private function calcSeal($visit_id, $visitor_id, $ts) {
    return $visit_id + $visitor_id + $ts - self::SEAL_SEED;
  }

  private function hasValidSeal() {
    $visit_id = $this->cookie->getAttribute('visit_id'); 
    $visitor_id = $this->cookie->getAttribute('visitor_id');
    $ts = $this->cookie->getAttribute('ts');
    $seal = $this->cookie->getAttribute('seal');
    if ($visit_id < 1 || $visitor_id < 1 || $ts < 1 || empty($seal)) {
      return false;
    }
    return $this->calcSeal($visit_id, $visitor_id, $ts) == $seal;
  }

  private function isNewSource() {
    if (self::$disabled === true) return false;
    $keys = array('utm_source', 'utm_medium', 'utm_term', 'utm_campaign', 'utm_content', 'utm_id',
		  'knxs', 'knxm', 'knxt', 'knxc',
                  'knxsid', 'knxcid', 'knxaid',
		  'affiliate_id',
		  'gclid', 'ovchn');
    $source = '';
    $attrs = $this->req->getAttributes();
    foreach ($keys as $key) {
      if (empty($attrs[$key])) continue ;
      $source .= $key.'='.$attrs[$key].';';
    }
    if (empty($source)) return false;
    $crc = String::crc32($source);
    if ($this->cookie->getAttribute('source') == $crc) {
      return false;
    }
    S('log')->trace($source, __METHOD__);
    $this->setCookieAttributes(array('source' => $crc));
    return true;
  }

  private function hasExpired() {
    $ts = $this->cookie->getAttribute('ts');
    $diff = $this->ts - $ts;
    $bool = ($diff > $this->ttl || $this->cookie->getAttribute('d') != date('d'));
    $this->trace('hasExpired ['.date('Y-m-d', $ts).']');
    return $bool;
  }

  private function init() {
    $row = $this->getDb();
    if ($row['visit_id'] > 0) return ;
    if ($row['visitor_id'] < 1) {
      $this->req->setParameter('is_new_visitor', true);
      //      S('log')->trace('NEW VISITOR', __METHOD__);
    }
    $this->isNewSource();
    $this->req->setParameter('is_new_visit', true);
    $this->trackVisit($row['visitor_id']);
  }

  private function renew() {
    $this->trace('renew');
    $this->req->setParameter('is_new_visit', true);
    $visitor_id = $this->cookie->getAttribute('visitor_id');
    $this->trackVisit($visitor_id);
  }

  private function trackVisit($visitor_id=0) {
    $req = $this->req;
    $cookie = $this->cookie;

    $referer = self::getReferer($req->getClient('referer'),
                                $req->getAttributes());

    $agent = Report::ua2hash($req->getClient('agent'));

    $row = array('locale' => S('res')->getLocale(),
                 'host' => self::str2id($req->getServer('host'),
                                        Tracker::STR_HOST),
                 'number' => (int) $cookie->getAttribute('number'),
                 'medium' => $referer['medium'],
                 'source' => $referer['source'],
                 'term' => $referer['term'],
                 'campaign' => $referer['campaign'],
                 'ip' => $req->getClient('ip'),
                 'browser' => $agent['browser'],
                 'system' => $agent['system'],
                 'country' => $req->getClient('country'),
                 'created_on' => Date::today(),
                 'created_at' => Date::now(),
                 'visitor_id' => $visitor_id);

    if (S('ctx')->_user['id'] > 0) {
      $row['user_id'] = (int) S('ctx')->_user['id'];
    }

    if ($cookie->actual > 0) {
      $row['span'] = ceil(($this->ts - $cookie->getAttribute('actual')) / (24 * 3600));
    }

    $visit_id = $this->dbo->insert(Visit::TABLE, $row, array('HIGH_PRIORITY'));
    $this->trace();

    if ($visit_id < 1) {
      S('log')->error_id('invalid visit_id', __METHOD__);
      throw new Exception();
    }

    if ($visitor_id > 0) {
      $ret = $this->dbo->exec('UPDATE '.self::TABLE_VISITOR
                              . ' SET ip='.$this->req->getClient('ip').','
                              .     ' crc='.$this->getCrc().','
                              .     ' visit_id='.$visit_id.','
                              .     ' created_at=NOW(),'
                              .     ' counter=counter+1'
                              .' WHERE visitor_id='.$visitor_id
                              .' LIMIT 1');
      $this->trace();
      $this->trace($ret, 'MATCHED ('.$this->dbo->matchedRows().')');
      if ($ret < 1) {
        $this->trackVisitor(array('visitor_id' => $visitor_id,
                                  'visit_id' => $visit_id));
      }
    }
    else {
      $visitor_id = $this->trackVisitor(array('visit_id' => $visit_id));
      if ($visitor_id < 1) {
        S('log')->error_id('invalid visitor_id', __METHOD__);
        throw new Exception();
      }
      $this->dbo->exec('UPDATE '.Visit::TABLE
                       . ' SET visitor_id='.$visitor_id
                       .' WHERE id='.$visit_id
                       .' LIMIT 1');
      $this->trace();
    }

    $this->trace($req->getClient(), __METHOD__);
    $this->trace($cookie->getAttributes(), __METHOD__);

    $this->setCookieAttributes(array('visit_id' => $visit_id,
                                     'visitor_id' => $visitor_id));
  }

  private function trackVisitor($fields) {
    $fields += array('crc' => $this->getCrc(),
                     'ip' => $this->req->getClient('ip'));
    $visitor_id = $this->dbo->insert(self::TABLE_VISITOR, $fields,
                                     array('HIGH_PRIORITY'));
    $this->trace();
    return $fields['visitor_id'] ?: $visitor_id;
  }

  private function getDb($create=false) {
    $h = $this->dbo->fetchHash('SELECT visitor_id, visit_id,'
                               .     ' UNIX_TIMESTAMP(created_at) as ts'
                               .' FROM '.self::TABLE_VISITOR
                               .' WHERE ip='.$this->req->getClient('ip')
                               .  ' AND crc='.$this->getCrc()
                               .' ORDER BY created_at DESC'
                               .' LIMIT 1');
    if (empty($h)) return array();
    $h['visit_id'] = (int) $h['visit_id'];
    $h['visitor_id'] = (int) $h['visitor_id'];
    $h['ts'] = (int) $h['ts'];
    if (($this->ts - $h['ts']) > $this->ttl) {
      $h['visit_id'] = 0;
    }
    if ($h['visit_id'] > 0) {
      $this->dbo->exec('UPDATE '.self::TABLE_VISITOR
                       . ' SET created_at=NOW()'
                       .' WHERE visitor_id='.$h['visitor_id']
                       .' LIMIT 1');
      $this->setCookieAttributes(array('visit_id' => $h['visit_id'],
                                       'visitor_id' => $h['visitor_id']));
    }
    return $h;
  }

  private function isBot() {

    $req = $this->req;
    $addr = $req->getClient('address');

    $is_bot = false;

    if ($req->getParameter('client_is_proxied') == true) {
      // on detecte le pays .. si pas fr, be ... on refuse ET on logge
    }

    $agent = $req->getClient('agent');
    $host = $req->getClient('host');
    list ($chunk, ) = explode('.', $host);
    $chunk = $agent.$chunk;

    if (strlen($agent) < 32 ||
        strpos($agent, 'http://') !== false ||
        strpos($agent, '@') !== false ||
        strpos($chunk, 'google') !== false ||
        strpos($chunk, 'bot') !== false ||
        strpos($chunk, 'crawler') !== false ||
        strpos($chunk, 'spider') !== false ||
        strpos($host, 'amazonaws.com') !== false ||
        !(strpos($agent, 'mozilla/') === 0 || strpos($agent, 'opera/') === 0)) {
      $this->dbo->insert(self::TABLE_ROBOT,
                         array('uri' => $req->getUri(),
                               'address' => $addr,
                               'robot' => $agent));
      $is_bot = true;
    }
    else {
      $ranges = array('150.70.', '65.52.', '216.104.15.', '199.19.249.');
      foreach ($ranges as $range) {
        if (strpos($addr, $range) === 0) {
          $is_bot = true;
          break ;
        }
      }
    }

    $req->setParameter('is_bot', $is_bot);
    if ($is_bot === true) {
      S('log')->disable();
      self::$disabled = true;
    }
    return $is_bot;
  }

  public function getCrc() {
    if ($this->crc !== null) return $this->crc;
    /*    $keys = array('HTTP_CLIENT_IP', 'HTTP_X_FORWARDED_FOR',
                  'HTTP_USER_AGENT', 'HTTP_ACCEPT', 'HTTP_ACCEPT_LANGUAGE',
                  'HTTP_X_CLUSTER_CLIENT_IP');
                  $crc = '';*/
    $crc = $this->req->getClient('address');
    // 'HTTP_ACCEPT_ENCODING'
    $keys = array('HTTP_USER_AGENT', 'HTTP_ACCEPT', 'HTTP_ACCEPT_LANGUAGE');
    foreach ($keys as $key) {
      $crc .= $_SERVER[$key];
    }
    $this->crc = String::crc32($crc);
    return $this->crc;
  }

  public function track($action, $category) {
    $visit_id = (int) $this->cookie->getAttribute('visit_id');
    if ($visit_id < 1) return false;
    if (Extension::exists('performance')) {
      foreach (Goal::asHash() as $id => $regexp) {
        $user_id = (int) S('ctx')->_user['id'];
        $model_id = Model::id('goal');
        if (preg_match($regexp, $action.'.'.$category) > 0) {
          Conversion::add(array('model_id' => $model_id,
                                'record_id' => $id),
                          array('visit_id' => $visit_id,
                                'user_id' => $user_id,
                                'unique' => true));
        }
      }
    }
    $ret = $this->dbo->insert(self::TABLE_TMP,
                              array('visit_id' => $visit_id,
                                    'action' => $action,
                                    'category' => $category));
    if ($ret === false) {
      S('log')->error($action, __METHOD__);
    }
  }

  private function trace($input=null, $prefix=null) {
    return ;
//    if (!is_ip('192.168.0.46')) return ;
    if ($input === null) {
      $this->dbo->debug();
      return ;
    }
    S('log')->debug($input, $prefix);
  }

  public static function getReferer($http_referer, $query) {
    $engines = array('google' => 'google|aol|conduit', 'bing' => 'bing|msn|live', 'yahoo!' => 'yahoo',
                     'orange' => 'voila|lemoteur', 'sfr' => 'sfr', 'free' => 'search\.free\.fr',
                     'lo.st' => 'lo.st', 'ask' => 'ask', 'yandex' => 'yandex',
                     'aliceadsl' => 'aliceadsl\.fr',
                     'hotbot' => 'hotbot', 'lycos' => 'lycos', 'about' => 'about',
                     'baidu' => 'baidu', 'alltheweb' => 'alltheweb', 'bluewin' => 'bluewin',
                     'toile' => 'toile',  'alexa' => 'alexa', 'exalead' => 'exalead', 
                     'ixquick' => 'ixquick', 'babylon' => 'babylon\.com');

    $tags = array('q', 'query', 'rdata', 'x_query', 'qs', 'encquery', 'qt', 'kw', 'text', 'terms', 'wd', 'as_q', 'as_epq');

    $mail_regex = 'mail|laposte|courrier|courriel|messagerie|pop|smtp|imp|horde|groups';
    $social_regex = 'facebook|twitter|identi.ca|linkedin|viadeo|friendfeed|friendster|jaiku|myspace|ning|netlog';
    $rss_regex = 'netvibes';

    $url_parts = parse_url($http_referer);

    $query['knxm'] = strtolower($query['knxm']);

    $medium = self::MEDIUM_DIRECT;
    $source = trim($query['knxs'], ' |');
    $term = $query['knxt'];
    $campaign = $query['knxc'];

    if ($query['knxsid'] >= 1) {
      $medium = self::MEDIUM_USER;
      $source = '|user|'.intval($query['knxsid']);
    }
    elseif (empty($http_referer) ||
            (preg_match(P('app.regex'), $url_parts['host']) > 0 && empty($query['knxm']))) {
      $medium = self::MEDIUM_DIRECT;
      $source = 'browser';
    }
    elseif ($query['knxm'] == self::MEDIUM_CPC ||
            $query['knxm'] == 'cpc' ||
            isset($query['gclid']) || isset($query['ovchn'])) {
      $medium = self::MEDIUM_CPC;
      if (!empty($query['knxs'])) $source = $query['knxs'];
      elseif (array_key_exists('gclid', $query)) $source = 'google adwords';
      elseif (array_key_exists('ovchn', $query)) $source = 'yahoo sponsored search';
    }
    elseif ($query['knxm'] == self::MEDIUM_CPM ||
            $query['knxm'] == 'cpm') {
      $medium = self::MEDIUM_CPM;
    }
    elseif ($query['knxm'] == self::MEDIUM_RSS ||
            $query['knxm'] == 'rss' ||
            preg_match('/('.$rss_regex.')/', $url_parts['host']) ||
            strpos($url_parts['path'], 'reader/view') > 0) {
      $medium = self::MEDIUM_RSS;
    }
    elseif ($query['knxm'] == self::MEDIUM_AFFILIATE ||
            $query['affiliate_id'] >= 1 ||
            $query['knxaid'] >= 1) {
      $medium = self::MEDIUM_AFFILIATE;
      $source = '|affiliate|'.intval($query['knxaid']?:$query['affiliate_id']);
//      error_log($source);
    }
    elseif (($query['knxcid'] >= 1 && $query['eid'] >= 1) ||
            preg_match('/('.$mail_regex.')/', $url_parts['host']) ||
	    $query['knxm'] == self::MEDIUM_CAMPAIGN ||
            $query['knxm'] == self::MEDIUM_MAIL ||
            $query['knxm'] == 'mail') {
      if ($query['cid'] >= 1 || $query['knxm'] == self::MEDIUM_CAMPAIGN) {
        $medium = self::MEDIUM_CAMPAIGN;
        $source = '|campaign|'.intval($query['knxcid']);
      }
      else {
        $medium = self::MEDIUM_MAIL;
      }
    }
    elseif (strlen($url_parts['path']) > 1 &&
            preg_match('/('.join('|', $engines).')/', $url_parts['host'])) {
      $medium = self::MEDIUM_SEARCH;
      $source = $url_parts['host'];
      foreach ($engines as $k => $regex) {
	if (preg_match('/('.$regex.')/', $url_parts['host'])) {
	  $source = $k;
	  break ;
	}
      }
      if (!empty($url_parts['query'])) {
	$referer_query = array();
	parse_str($url_parts['query'], $referer_query);
	$referer_query = array_change_key_case($referer_query, CASE_LOWER);
        if (isset($referer_query['q'])) {
          $term = $referer_query['q'];
        }
	elseif (strpos($source, 'yahoo') !== false) {
          $term = $referer_query['p'];
        }
	else {
	  foreach ($tags as $tag) {
	    if (array_key_exists($tag, $referer_query)) {
              $term = $referer_query[$tag];
              if (!empty($term)) break ;
            }
	  }
	}
        if (empty($term)) {
          if ($source == 'google' && !empty($referer_query['prev'])) {
            $source .= $url_parts['path'] == '/imgres' ? '-image' : '-translate';
            $prev = urldecode($referer_query['prev']);
            if ($prev[0] === '/') {
              $prev = 'http://localhost'.$prev;
            }
            $sub = array();
            parse_str(parse_url($prev, PHP_URL_QUERY), $sub);
            if (!empty($sub['q'])) {
              $term = $sub['q'];
            }
          }
        }
        $term = trim($term);
        if (!empty($term)) {
          S('ctx')->setAttribute('_search_query', $term);
          $ignored = (array) P('extension.tracker.ignore');
          if (in_array($term, $ignored)) {
            $medium = self::MEDIUM_DIRECT;
          }
	}
        else {
          error_log('EMPTY SEARCH : '.$http_referer);
          error_log('M='.$medium.' - S='.$source.' - T='.$term);
        }
      }
    }
    else {
      if (strpos($http_referer, 'http://') === 0 || strpos($http_referer, 'https://') === 0) {
	$medium = self::MEDIUM_LINK;
        if (empty($source)) {
          $source = $url_parts['host'];
          if (empty($source)) {
            S('log')->debug($url_parts, __METHOD__);
            $source = 'unknown';
          }
          elseif (substr($source, 0, 4) === 'www.') {
            $source = substr($url_parts['host'], 4);
            if (preg_match('/('.$social_regex.')/', $source)) {
              $medium = self::MEDIUM_SOCIAL;
            }
          }
        }
      }
      else {
        $medium = self::MEDIUM_DIRECT;
        $source = 'urlbar';
      }
    }

    $source = String::clean($source, array('strict' => true));
    $term = String::clean($term, array('strict' => true));
    $campaign = String::clean($campaign, array('strict' => true));

    $referer['medium']   = $medium;
    $referer['source']   = self::str2id($source, self::STR_SOURCE);
    $referer['term']     = self::str2id($term, self::STR_TERM);
    $referer['campaign'] = self::str2id($campaign, self::STR_CAMPAIGN);

    // error_log('URL : '.$http_referer); 
    // error_log('MEDIUM '.$medium.' - '.$source.' - '.$term);

    return $referer;
  }

  public static function getInstance() {
    if (Platform::hasSingleton('tracker')) {
      return S('tracker');
    }
    return new Tracker();
  }

  public static function str2id($str, $type, $create=true) {
    $str = (string) $str;
    if (strlen($str) < 1) return 0;
    $str = substr($str, 0, 128);
    $type = (int) $type;
    $id = (int) S('dbo')->fetchValue('SELECT id'
                                     .' FROM '.self::TABLE_STRING
                                     .' WHERE type='.$type
                                     .  ' AND name=:name:',
                                     array(':name:' => $str));
    if ($id < 1 && $create == true) {
      $id = S('dbo')->insert(self::TABLE_STRING,
                             array('type' => $type,
                                   'name' => $str));
    }
    return $id;
  }

}

