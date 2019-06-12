<?php

class Visit
{
  protected $dbo = null;
  protected $log = null;
  protected $attributes = null;

  const TABLE = 'tkr_visit';
  const TABLE_VISITOR = 'tkr_visitor';

  const FLAG_CONVERSION = 1;
  const FLAG_INTENT = 2;
  const FLAG_PROXIED = 4;

  public function __construct($id) {
    if ($id < 1) {
      throw new Exception('invalid visit id');
    }
    $this->dbo = S('dbo');
    $this->log = S('log');
    $this->attributes = $this->dbo->fetchHash('SELECT *'
                                              .' FROM '.Visit::TABLE
                                              .' WHERE id='.intval($id));
  }

  public function getSummary() {
    $hash = $this->attributes; 
    $hash['country_code'] = Country::code($this->country);
    $hash['country'] = ucfirst(Country::name($this->country));
    $hash['ip'] = Net::num2ip($this->ip); 
    $hash['host'] = gethostbyaddr($hash['ip']);
    $hash['path'] = $this->getPath();
    $hash['system'] = Report::$browsers[$this->browser].' / '.Report::$systems[$this->system];
    $hash['referer'] = $this->origin();
    if ($this->user_id >= 1) {
      try {
        $user = $this->getUser();
        $hash['user']  = '<div style="float:right; margin-top:2px;">'.$user->avatar().'</div>';
        $hash['user'] .= $user->name.' ('.$user->id.')<br/>';
        $hash['user'] .= $user->email.'<br/>';
        $hash['user'] .= $user->getMeta('created_at');
        try {
          $hash['user'] .= '<br/>'.$user->getVisit()->origin();
        }
        catch (Exception $e) {}
      }
      catch (Exception $e) { $hash['user'] = 'user unknown ('.$this->user_id.')'; }
    }
    return $hash;
  }

  private function origin() {
    $mediums = $this->dbo->asHash('SELECT id, name'
                                  .' FROM '.Tracker::TABLE_STRING
                                  .' WHERE id IN (:key:,:tag:)',
                                  array(':key:' => $this->source, 
                                        ':tag:' => $this->term));
    if (Tracker::MEDIUM_DIRECT == $this->medium) {
      $referer = Tracker::$mediums[$this->medium];
    }
    else {
      $referer = 'type : '.Tracker::$mediums[$this->medium].'<br/>'; 
      if (!empty($mediums[$this->source])) {
        $referer .= 'nom : '.$mediums[$this->source].'<br/>'; 
      }
      if (!empty($mediums[$this->term])) {
        $referer .= 'tag : '.$mediums[$this->term];
      }
    }
    return $referer;
  }

  public function getUser() {
    return User::getInstance($this->user_id);
  }

  public function getId() {
    return $this->id;
  }

  public function getPath() {
    $rs = $this->dbo->query('SELECT *'
                            .' FROM '.Tracker::TABLE_HIT
                            .' WHERE visit_id='.$this->id
                            .' ORDER BY created_at'); 
    $events = $rs->asArray(); 
    if (count($events) < 1) return array();
    $ids = array();
    foreach ($events as $value) {
      $ids[$value['category_id']]++;
      $ids[$value['action_id']]++;
    }
    $names = $this->dbo->asHash('SELECT id, name'
                                .' FROM '.Tracker::TABLE_STRING
                                .' WHERE id IN ([ids])',
                                array('[ids]' => array_keys($ids)));
    reset($events);
    $hash = array();
    foreach ($events as $value) {
      list($date, $time) = explode(' ', $value['created_at']);
      $hash[$time] = $names[$value['action_id']].' / '.$names[$value['category_id']];
    }
    return $hash;
  }

  public function getModalLink() {
    return self::url($this->id);
  }

  public static function url($id, $label=null) {
    $label = $label ? $label : $id;
    return '<a href="javascript:void(0)" onclick="Kwo.Visit.onDisplay(this)" data-id="'.$id.'">'.$label.'</a>';
  }

  public function getAttribute($key) { 
    return $this->attributes[$key];
  }

  public function getAttributes() { 
    return $this->attributes;
  }

  public function setAttribute($key, $value) {
    $opts = array('filters' => array('id' => $this->getId()),
                  'limit' => 1);
    S('dbo')->update(self::TABLE,
                     array($key => $value), 
                     $opts);
    return $this;
  }

  public function increment($key) {
    $value = $this->getAttribute($key) + 1;
    $this->setAttribute($key, $value);
  }

  public function decrement($key) {
    $value = $this->getAttribute($key) - 1;
    $this->setAttribute($key, ($value >= 0 ? $value : 0));
  }

  public function getSiblings() {
    $columns = 'id, duration, conversions, medium, source, term, created_on, created_at';
    $rs = $this->dbo->query('SELECT '.$columns
                            .' FROM '.self::TABLE
                            .' WHERE visitor_id='.$this->visitor_id
                            .' ORDER BY id DESC'
                            .' LIMIT 200');
    $set = array();
    foreach ($rs as $row) {
      $set[$row['source']]++;
      $set[$row['term']]++;
    }
    $names = $this->dbo->asHash('SELECT id, name'
                                .' FROM '.Tracker::TABLE_STRING
                                .' WHERE id IN ([set])',
                                array('[set]' => array_keys($set)));
    $out = array();
    foreach ($rs as $row) {
      $tmp = $row;
      $tmp['source'] = $names[$row['source']];
      $tmp['term'] = $names[$row['term']];
      $out[] = $tmp;
    }
    return $out;
  }

  public function hasNext($check_association=true) {
    $t = time();
    $session = S('req')->getSession();
    if ($session->getAttribute('visit_max') < 1 || 
        ($t - $session->getAttribute('last_check')) > 600) {
      $n = S('dbo')->fetchValue('SELECT MAX(id) FROM '.self::TABLE);
      $session->setAttribute('visit_max', $n);
      $session->setAttribute('last_check', $t);
    }
    return $this->id < $session->getAttribute('visit_max');
  }

  public function __get($key) { return $this->attributes[$key]; }

  public static function getInstance($id) {
    return new Visit($id);
  }

}