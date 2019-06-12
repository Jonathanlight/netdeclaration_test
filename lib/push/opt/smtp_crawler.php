<?php

//" */15 * * * * root /usr/local/bin/php /etc/kernix/bin/smtp_crawler.php "

error_reporting(0);

define('FILE_READ_ERROR', 1);
define('DB_CREATE_ERROR', 2);
define('BLOCKER', '/tmp/smtp_crawler.lock');
define('LOG_FILE', '/var/log/smtp');

try {
  if (!file_exists(LOG_FILE)) {
    echo "Ajouter la ligne ci-dessous dans /etc/syslog.conf :\n";
    echo "---------------------------------------------------\n";
    echo "mail.*  /var/log/smtp\n";
    echo "---------------------------------------------------\n";
    echo "ATTENTION : utiliser des tabulations\n\n";
    return ;
  }
  if (file_exists(BLOCKER)) {
    throw new Exception(BLOCKER.' exists !');
  }
  touch(BLOCKER);
  $log = new SmtpCrawler();
  if (file_exists(BLOCKER) && strlen(BLOCKER) >= 5) {
    unlink(BLOCKER);
  }
}
catch (Exception $e) {
  print($e->getMessage()."\n");
  if ($e->getCode() == DB_CREATE_ERROR) {
    print('creating /var/lib/sqlite'."\n");
    mkdir('/var/lib/sqlite', 0700, true);
    if (file_exists(BLOCKER) && strlen(BLOCKER) >= 5) {
      unlink(BLOCKER);
    }
  }
}

class SmtpCrawler {
  
  private $db;
  private $path = '/var/tmp/smtp';
  private $handle;
  private $sender = '@kwm.fr';
  private $monthes = array('Jan' => '01','Feb' => '02','Mar' => '03','Apr' => '04','May' => '05','Jun' => '06',
                           'Jul' => '07','Aug' => '08','Sep' => '09','Oct' => '10','Nov' => '11','Dec' => '12');

  private $replace = array('', '', '');

  private $from2 = array('relay=', '. [', '[', ']');
  private $to2 = array('', ' ', '', '');

  private $from1 = array('to=', '<', '>');
  private $to1 = array('', '', '');
  
  public function __construct () {
    $this->timestamp = mktime();
    $fp = fopen(LOG_FILE, 'r+');
    flock($fp, LOCK_EX);
    copy(LOG_FILE,
         $this->path.'.'.$this->timestamp);
    ftruncate($fp, 0);
    fclose($fp);
    $this->db = new SQLite('/var/lib/sqlite/maillog.sqlite');
    if (!$this->db->table_exists('maillog')) {
      $sql  = 'CREATE TABLE maillog (';
      $sql .= '  smtp_key VARCHAR (16) NOT NULL PRIMARY KEY,';
      $sql .= '  email VARCHAR (255) NULL,';
      $sql .= '  contact_id INT (10) NULL,';
      $sql .= '  campaign_id SMALLINT (5) NULL,';
      $sql .= '  sending_id SMALLINT (5) NULL,';
      $sql .= '  sender_url VARCHAR (255) NULL,';
      $sql .= '  relay_host VARCHAR (255) NULL,';
      $sql .= '  relay_ip VARCHAR (16) NULL,';
      $sql .= '  stat VARCHAR (255) NULL,';
      $sql .= '  dsn VARCHAR (5) NULL,';
      $sql .= '  from_time DATETIME NULL,';
      $sql .= '  to_time DATETIME NULL';
      $sql .= ');';
      $sql .= 'CREATE INDEX maillog_contact_id ON maillog (contact_id);';
      $sql .= 'CREATE INDEX maillog_campaign_id ON maillog (campaign_id);';
      $sql .= 'CREATE INDEX maillog_sending_id ON maillog (sending_id);';
      $sql .= 'CREATE INDEX maillog_dsn ON maillog (dsn);';
      $sql .= 'CREATE INDEX maillog_from_time ON maillog (from_time);';
      $this->db->exec($sql);
    }
    if (!$this->db->table_exists('error')) {
      $sql  = 'CREATE TABLE error (';
      $sql .= '  url VARCHAR (255) NOT NULL PRIMARY KEY';
      $sql .= ');';
      $this->db->exec($sql);
    }
    $this->handle = @fopen($this->path.'.'.$this->timestamp, 'r');
    if ($this->handle === false) {
      throw new Exception('open failure ['.$this->path.'.'.$this->timestamp.']',
                          FILE_READ_ERROR);
    }
    $this->parse();
  }
  
  public function __destruct () {
    //unlink("/var/tmp/maillog.".$this->timestamp);
    system('find /var/tmp/ -maxdepth 1 -type f -mtime +1 -exec rm {} \;');
  }
  
  private function parse() {
    while ($buffer = fgets($this->handle)) {
      if (!(preg_match('/ from=/', $buffer) && preg_match('/'.$this->sender.'/', $buffer)) && 
          !preg_match('/ to=/', $buffer)) continue;
      list ($smtp_date, $smtp_key, $smtp_data) = explode(': ', $buffer, 3);
      if (empty($smtp_date) || empty($smtp_key) || empty($smtp_data)) continue;
      $smtp_key = trim($smtp_key);
      $smtp_date = $this->clean_date(preg_split('/(\s)+/', trim($smtp_date)));
      $smtp_data = trim($smtp_data);
      if (preg_match('/ from=</',$buffer) && preg_match('/'.$this->sender.'/',$buffer)) {
        $smtp_data = str_replace(array('from=', $this->sender, '<', '>'), 
                                 $this->replace, 
                                 $smtp_data);
        $smtp_data = substr($smtp_data, 0, strpos($smtp_data, ','));
        list ($campaign_infos, $sender_url) = explode('+', $smtp_data);
        list ($contact_id, $campaign_id, $sending_id) = explode('.', $campaign_infos);
        $contact_id = intval($contact_id);
        $campaign_id = intval($campaign_id);
        $sending_id = intval($sending_id);
        if (empty($contact_id) || empty($campaign_id)) continue;
        $this->insert($smtp_key, $contact_id, $campaign_id, $sending_id, $sender_url, $smtp_date);
      }
      elseif (preg_match('/ to=</',$buffer)) {
        $smtp_data = str_replace($this->from1, $this->to1, $smtp_data);
        list ($email,,,,,$hostip, $dsn, $stat) = explode(',', $smtp_data);
        if (empty($hostip) || empty($dsn) || empty($stat)) continue;
        list ($host, $ip) = explode(' ', str_replace($this->from2, $this->to2, trim($hostip)));
        if (empty($host) || empty($ip)) continue;
        $dsn = trim(str_replace('dsn=', '', $dsn));
        if ($dsn == '2.0.1' || $dsn == '2.0.2') $dsn = '2.0.0';
        $stat = trim(str_replace('stat=', '', $stat));
        $this->update($email, $smtp_key, $smtp_date, $host, $ip, $dsn, $stat, $smtp_data);
      }
    }
    $this->db->exec('DELETE FROM maillog WHERE dsn="2.0.0"');
    //$this->db->exec('DELETE FROM maillog WHERE dsn LIKE "_._._" AND from_time < "'.date('Y-m-d H:i:s',mktime(date('H'),date('m'),date('s'),date('m'),(date('d')-3),date('Y'))).'"');
    $this->db->exec('DELETE FROM maillog WHERE dsn LIKE "_._._"');
  }
  
  private function insert($smtp_key, $contact_id, $campaign_id, $sending_id, $sender_url, $smtp_date) {
    $this->db->query('SELECT * FROM maillog WHERE smtp_key="'.$this->db->protect($smtp_key).'";');
    if ($this->db->num_rows() != 0) return;
    $this->db->exec('INSERT INTO maillog (smtp_key,contact_id,campaign_id,sending_id,sender_url,from_time) '.
                    'VALUES ("'.$this->db->protect($smtp_key).'",'.$contact_id.','.$campaign_id.','.$sending_id.',"'.$this->db->protect($sender_url).'","'.$this->db->protect($smtp_date).'");');
  }
  
  private function update($email, $smtp_key, $smtp_date, $host, $ip, $dsn, $stat, $smtp_data) {
    $this->db->query('SELECT * FROM maillog WHERE smtp_key="'.$this->db->protect($smtp_key).'";');
    if ($this->db->num_rows() != 1) return;
    $this->db->exec('UPDATE maillog SET '.
                    'email="'.$this->db->protect($email).'", '.
                    'relay_host="'.$this->db->protect($host).'", '.
                    'relay_ip="'.$this->db->protect($ip).'", '.
                    'dsn="'.$this->db->protect($dsn).'", '.
                    'stat="'.$this->db->protect($stat).'", '.
                    'to_time="'.$this->db->protect($smtp_date).'" '.
                    'WHERE smtp_key="'.$this->db->protect($smtp_key).'";');
    
    $this->db->query('SELECT * FROM maillog WHERE smtp_key="'.$this->db->protect($smtp_key).'";');
    $obj = $this->db->object();
    $obj->proof = !$obj->sending_id;
    $obj->email_id = $obj->contact_id;
    $url = 'http://'.$obj->sender_url.'/push/smtp?'.http_build_query($obj);
    echo $url;
    if (intval(@file_get_contents($url)) != 1) {
      $this->db->exec('INSERT INTO error VALUES ("'.$this->db->protect($url).'")');
    }
  }
  
  private function clean_date($date_arr) {
    $day = str_pad($date_arr[1], 2, '00', STR_PAD_LEFT);
    $month = $this->monthes[$date_arr[0]];
    $time = $date_arr[2];
    $year = date('Y');
    if (date('m') < $day && date('d') < $month) {
      $year--;
    }
    return $year.'-'.$month.'-'.$day.' '.$time;
  }
}

class SQLite {
  private $db_path;
  private $db_conn;
  private $result;
  
  public function __construct($path) {
    $this->db_path = $path;
    $this->db_conn = sqlite_open($this->db_path, 0660, $error);
    if (!file_exists($this->db_path)) {
      throw new Exception('open failure ['.$this->db_path.']',
                          DB_CREATE_ERROR);
    }
  }
  
  public function table_exists($table) {
    $this->query('SELECT * FROM sqlite_master WHERE type="table" AND name="'.$table.'"');
    return $this->num_rows() >= 1;
  }
  
  public function query($sql) {
    $this->result = sqlite_query($this->db_conn, $sql, SQLITE_ASSOC, $error);
  }
  
  public function exec($sql) {
    $this->result = sqlite_exec($this->db_conn, $sql, $error);
  }
  
  public function object() {
    return sqlite_fetch_object($this->result);
  }
  
  public function num_rows() {
    return sqlite_num_rows($this->result);
  }
  
  public function protect($str) {
    return sqlite_escape_string($str);
  }
}
