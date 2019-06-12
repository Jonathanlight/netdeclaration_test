<?php

/*
- (pouvoir arrêter l'envoi)
*/

class Sender
{
  const TABLE_QUEUE = 'psh_queue';
  const SIG = 'eid=((email_id))&knxcid=((campaign_id))&hash=((hash))';

  private $bases = array();
  private $is_bat = false;
  private $bounce_domain = 'kwm.fr';
  private $campaign = null;
  private $content_html = null;
  private $content_text = null;
  private $dbo = null;
  private $from_email = null;
  private $from_name = null;
  private $hostname = null;
  private $queue_id = null;
  private $reply_to = null;
  private $subject = null;
  private $substitutions = array();

  public function __construct($campaign, $bases=null) {

    $this->dbo = S('dbo');

    try {
      $this->subject = $campaign->subject;
      if ($bases === null) {
        if ($campaign->status != Campaign::STATUS_SCHEDULED) {
          throw new Exception('campaign is not in SCHEDULED status');
        }
        $this->bases = $campaign->bases;
      }
      else {
        $this->subject = '[BAT] '.$campaign->subject;
        $this->bases = (array) $bases;
        $this->is_bat = true;
      }
      if (count($this->bases) < 1) {
        throw new Exception('no base selected');
      }
      $this->campaign = $campaign;
      $this->start();
      $this->loadContent();
      //$this->debug();
      $this->loadQueue();
      $this->processQueue();
      $this->end();
      S('app')->hook('onBeforeCampaignSend',
               array('sender' => $this));
    }
    catch (Exception $e) {
      S('log')->error('campaign ('.$campaign->getId().') : '.$e->getMessage(),
                      __METHOD__);
      throw new Exception('campaign ('.$campaign->getId().')');
    }
  }

  private function loadContent() {

    $this->content_html = $this->campaign->getHtmlContent();
    $this->replaceHtmlLinks();

    $this->content_text = $this->campaign->getTextContent();
    $this->replaceTextLinks();


    $from = array('((remove))', '((link))', '((open))', '((sig))');

    $click_here_view = $this->campaign->locale == I18N::LOCALE_FR ? 'cliquez ici pour visualisez ce message dans un navigateur web' : 'click here';
    $click_here_remove = $this->campaign->locale == I18N::LOCALE_FR ? 'cliquez ici pour vous désinscrire' : 'click here';

    $to = array('<a href="'.$this->campaign->getUrl().'/remove?'.self::SIG.'">'.$click_here_remove.'</a>',
                '<a href="'.$this->campaign->getUrl().'/view?'.self::SIG.'">'.$click_here_view.'</a>',
                '<img src="'.$this->campaign->getUrl().'/ping?'.self::SIG.'" border="0" />',
                self::SIG);

    $this->content_html = str_ireplace($from, $to, $this->content_html);

    $to = array($this->campaign->getUrl().'/remove?'.self::SIG,
                $this->campaign->getUrl().'/view?'.self::SIG,
                $this->campaign->getUrl().'/ping?'.self::SIG,
                self::SIG);
    $this->content_text = str_ireplace($from, $to, $this->content_text);

    $substitutions = String::extractTags($this->content_html.$this->subject, '((', '))');
    foreach ($substitutions as $value) {
      $this->substitutions[$value] = '(('.$value.'))';
    }
    //    error_log($this->content);
  }

  private function replaceHtmlLinks() {
    $doc = new DOMDocument();
    $doc->formatOutput = true;
    $doc->preserveWhiteSpace = true;
    $html = $this->content_html;
    if (stripos($html, '<?xml ') === false) {
      $html = '<?xml encoding="UTF-8">' . "\n\n" . $html;
    }
    if (stripos($html, 'http-equiv="content-type"') === false) {
      $html = str_ireplace('<head>',
                           '<head>'."\n".'<meta http-equiv="content-type" content="text/html; charset=utf-8">',
                           $html);
    }
    @$doc->loadHTML($html);
    $doc->encoding = 'UTF-8';
    $nodes = $doc->getElementsByTagName('a');
    if ($nodes->length < 1) return ;
    foreach ($nodes as $node) {
      $link = $node->getAttribute('href');
      if (strpos($link, '://') === false) {
        $link = H::url($link);
      }
      if (strpos($link, '/push/') !== false) {
        continue;
      }
      $suffix = '';
      if (stripos($link, P('app.domain')) === false) {
        /* do not track */
        $suffix .= '&dnt=1';
      }
      $link_id = Url::asId($link);
      $href = $this->campaign->getUrl().'/proxy?uid='.$link_id.'&'.self::SIG.$suffix;
      $node->setAttribute('href', $href);
      //S('log')->trace($link.' -> '.$href, __METHOD__);
    }
    $out = $doc->saveHTML();
    $out = preg_replace('/<meta http.+?>/i', '', $out);
    $out = preg_replace('/^<!DOCTYPE.+?>/i', '', $out);
    $out = preg_replace('/<\?xml encoding.+?>/i', '', $out);
    $out = trim($out);
    $this->content_html = $out;
  }

  private function replaceTextLinks() {
    $res = array();
    $url_regex = '#([\w]+://[\w\d.\-_]+/?[\S]*)#e';
    preg_match_all($url_regex, $this->content_text, $res);
    if (count($res) < 2) {
      return;
    }
    array_unique($res[1]);
    $bindings = array();
    foreach ($res[1] as $link) {
      if (strpos($link, '://') === false) {
        $link = H::url($link);
      }
      if (strpos($link, '/push/') !== false) {
        continue;
      }
      $link_id = Url::asId($link);
      $bindings[$link] = $this->campaign->getUrl().'/proxy?uid='.$link_id.'&'.self::SIG;
    }
    $this->content_text = str_replace(array_keys($bindings),
                                   array_values($bindings),
                                   $this->content_text);
  }

  private function loadQueue() {
    if (count($this->bases) < 1) {
      throw new Exception('no base selected');
    }
    $dbo = $this->dbo;
    $campaign = $this->campaign;
    $this->queue_id = time() + $campaign->getId();
    $bases = join(',', $this->bases);
    $ret = $dbo->exec('INSERT INTO '.self::TABLE_QUEUE.' (id, email_id)'
                      .' SELECT '.$this->queue_id.' AS queue_id, e.id'
                      .  ' FROM '.T('email').' AS e'
                      .  ' JOIN '.Base::TABLE_EMAIL.' AS b'
                      .    ' ON (b.email_id=e.id'
                      .   ' AND  b.base_id IN ('.$bases.')'
                      .   ' AND  b.status > 0)'
                      .  ' LEFT JOIN '.Act::TABLE.' AS a'
                      .         ' ON (a.email_id=e.id'
                      .        ' AND  a.campaign_id='.$campaign->getId()
                      .        ' AND  a.type='.Act::TYPE_SENDING.')'
                      .' WHERE a.email_id IS NULL'
                      .  ' AND e.status>0'
                      .' GROUP BY e.id');
    if ($ret === false) {
      $this->dbo->debug(__METHOD__);
      throw new Exception('queue loading failure');
    }
    $n = $dbo->exec('DELETE FROM '.self::TABLE_QUEUE
                    .' WHERE id='.$this->queue_id
                    .  ' AND email_id IN (SELECT email_id'
                    .                     ' FROM '.Act::TABLE
                    .                    ' WHERE (type='.Act::TYPE_REMOVE
                    .                      ' AND value='.$campaign->newsletter_id.')'
                    .                       ' OR type='.Act::TYPE_BLACKLIST.')');
    if ($n > 0) {
      S('log')->trace('('.$n.') recipients deleted', __METHOD__);
    }
  }

  private function processQueue() {

    $rs = $this->dbo->query('SELECT q.email_id, e.email, e.hashtable'
                            .' FROM '.self::TABLE_QUEUE.' AS q,'
                            .    ' '.T('email').' AS e'
                            .' WHERE q.email_id=e.id'
                            .  ' AND e.status>0'
                            .  ' AND q.id='.$this->queue_id);

    if ($rs === false || ($num_rows = $rs->numRows()) < 1) {
      $this->dbo->debug(__METHOD__);
      throw new Exception('queue ('.$this->queue_id.') is empty ('.$num_rows.')');
    }

    $campaign = $this->campaign;
    $campaign_id = $campaign->getId();
    $bounce_suffix = $campaign_id.'.'.intval(!$this->is_bat).'+'.P('app.domain').'@'.$this->bounce_domain;

    $act = array('campaign_id' => $campaign->getId(),
                 'type' => Act::TYPE_SENDING);
    $i = 0;
    $failure_count = 0;
    $url_prefix = $campaign->getUrl();

    $smtp = P('mail.smtp.push');

    while ($row = $rs->getNext()) {

      $row['campaign_id'] = $campaign_id;

      if ($this->is_bat === false) {
        $act['email_id'] = $row['email_id'];
        if (Act::add($act) < 1) {
          if ($failure_count >= 5) {
            throw new Exception('act insertion pb');
          }
          $failure_count++;
          S('log')->warn('campaign ('.$campaign_id.') : ('.$failure_count.') failures',
                         __METHOD__);
          sleep(10);
        }
      }

      $row['hash'] = String::crypt($campaign_id.$row['email_id']);

      if (!empty($row['hashtable'])) {
        $hashtable = (array) unserialize($row['hashtable']);
        foreach ($this->substitutions as $key => $value) {
          $row[$key] = $value;
        }
      }

      $bindings = array();
      foreach ($this->substitutions as $key => $value) {
        $bindings[] = $row[$key];
      }

      $subject = $this->subject;
      $content_html = $this->content_html;
      $content_text = $this->content_text;

      if (!empty($this->substitutions)) {
        $subject = str_ireplace($this->substitutions, $bindings, $subject);
        $content_html = str_ireplace($this->substitutions, $bindings, $content_html);
        $content_text = str_ireplace($this->substitutions, $bindings, $content_text);
      }

      $mail = new Mail();
      $mail->setBounce($row['email_id'].'.'.$bounce_suffix);
      $mail->setFrom($campaign->from_email, $campaign->from_name);
      $mail->addHeader('Precedence', 'bulk');
      $mail->addRecipient($row['email']);
      $mail->setReplyTo($campaign->reply_email);
      $mail->setSubject($subject);
      $mail->setBodyText($content_text);
      $mail->setBodyHtml($content_html);
      $mail->send($smtp);
      $i++;
      if (($i % 50) === 0 && $this->is_bat === false) {
        $progress  = round((($i / $num_rows) * 100), 1).'%';
        $progesss .= ' ['.$i.' / '.$num_rows.']';
        $this->campaign->commit(array('progress' => $i.' / '.$num_rows));
      }
    }
  }

  private function start() {
    if ($this->is_bat === true) return ;
    $this->campaign->commit(array('status' => Campaign::STATUS_PROCESSING,
                                  'scheduled_at' => Date::now()));
  }

  private function end() {
    if ($this->is_bat === true) return ;
    $this->campaign->commit(array('status' => Campaign::STATUS_DELIVERED,
                                  'delivered_at' => Date::now(),
                                  'progress' => ''));
  }

  private function debug() {
    S('log')->debug(array('content' => $this->content_html,
                          'substitutions' => $this->substitutions));
  }

}
