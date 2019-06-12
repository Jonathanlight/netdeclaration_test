<?php

class Letter extends ActiveRecord 
{
  protected function onBeforeCommit(&$attrs) {
    if (isset($attrs['subject']) && strlen($attrs['subject']) < 2) {
      throw new ActiveRecordException('subject required');
    }
    if (isset($attrs['body']) && strlen($attrs['body']) >= 3) {
      $attrs['body'] = String::tidy($attrs['body']);
    }
    if (isset($attrs['code'])) {
      $attrs['name'] = $attrs['code'];
    }
  }

  private function deliver($recipient, $bindings=null, $opts=array()) {
    $mail = new Mail();
    $mail->addRecipient($recipient);
    if (!empty($opts['rcpt'])) {
      $mail->addHeader('X-Kwo-Rcpt', $opts['rcpt']);
    }
    $locale = $opts['locale'];
    $body = $this->getProperty('body', $locale); 
    $subject = $this->getProperty('subject', $locale);
    if (is_array($bindings)) {
      $keys = array(); 
      foreach ($bindings as $key => &$value) {
        if ($key === 'url' || ($key === 'link' && $value[0] != '<')) {
          if ($value[0] === '/') {
            if (S('req')->isCLI()) {
              $value = H::url($value);
            }
            else {
              $value = 'http://'.S('req')->getServer('host').$value;
            }
          }
          $value = '<a href="'.$value.'">'.$value.'</a>';
        }
        /*        if ($key === 'link' && $value[0] != '<') {
          if ($value[0] === '/') {
            $value = S('req')->isCLI()
                   ? 'http://'.P('app.domain').$value
                   : 'http://'.S('req')->getHostname().$value;
          }
          $value = '<a href="'.$value.'">'.$value.'</a>';
          }*/
        //        $keys[] = '(('.$key.'))';
        $keys[] = $key;
        
      }
      //      $body = str_replace($keys, $bindings, $body);
      $body = String::bind2($body, $bindings); 
      //      $subject = str_replace($keys, $bindings, $subject);
      $subject = String::bind2($subject, $bindings); 
    }

    if (empty($subject)) {
      throw new Exception('empty subject ['.$this->code.']');
    }
    $mail->setSubject($subject);
    if (isset($opts['from'])) { 
      if (is_array($opts['from'])) {
      $mail->setFrom($opts['from']['email'], 
                     $opts['from']['name']);
      }
      else {
        $mail->setFrom($opts['from'], '');
      }
    }
    if (isset($opts['reply-to'])) { 
      if (is_array($opts['reply-to'])) {
        $mail->setReplyTo($opts['reply-to']['email'], 
                          $opts['reply-to']['name']);
      }
      else {
        $mail->setReplyTo($opts['reply-to'], '');
      }
    }
    elseif (strlen($this->from_name) > 1 && strlen($this->from_email) > 6) {
      $mail->setFrom($this->from_email, $this->from_name);
    }
    if (strlen($this->cc_set) > 6) {
      $mail->addCc($this->cc_set);
    }
    if (strlen($this->bcc_set) > 6) {
      $mail->addBcc($this->bcc_set);
    }
    $h = P('app.domain');
    $body = str_replace(array("='/".DOC_PATH,
                              '="/'.DOC_PATH, 
                              "='/".APP_PATH,
                              '="/'.APP_PATH,
                              ' href="/'),
                        array("='http://".$h."/".DOC_PATH,
                              '="http://'.$h.'/'.DOC_PATH, 
                              "='http://".$h."/".APP_PATH,
                              '="http://'.$h.'/'.APP_PATH,
                              ' href="http://'.$h.'/'),
                        $body);
    if (strpos($body, '((footer))') !== false) {
      $body = str_replace('((footer))', $this->footer($locale), $body);
    } 
    $mail->setBody($body);
    return $mail->send();
  }

  private static $footers = array();

  private function footer($locale) {
    if (!isset(self::$footers[$locale])) {
      self::$footers[$locale] = '';
      try {
        $snippet = Snippet::getInstance('letter.footer',
                                        array('ignore' => true));
        self::$footers[$locale] = $snippet->getProperty('content', $locale);
      }
      catch (Exception $e) {  }
    }
    return self::$footers[$locale];
  }

  public static function extensions() {
    $rs = S('dbo')->query('SELECT DISTINCT extension_id FROM '.T('letter'));
    $hash = array();
    foreach ($rs as $row) {
      $extension_id = $row['extension_id'];
      $hash[$extension_id] = Extension::name($extension_id);
    }
    asort($hash);
    return $hash;
  }

  private static $registry = array();

  public static function send($code, $recipient, $bindings=null, $opts=array()) {
    if ($recipient instanceof User) {
      if ($recipient->status < 1) return ;
      $opts['locale'] = $opts['locale'] >= 1 ? $opts['locale'] : $recipient->locale;
      $opts['rcpt'] = $recipient->getId();
      $recipient = $recipient->email;
    }
    elseif ($recipient instanceof Email) {
      if ($recipient->status < 1) return ;
      $recipient = $recipient->email;
    }
    elseif (is_numeric($recipient)) {
      $recipient = Email::getInstance($recipient)->email;
    }
    $opts['locale'] = $opts['locale'] >= 1 
                    ? $opts['locale']
                    : S('res')->getLocale();
    try {
      $letter = $registry[$code] ?: Letter::getInstance($code, array('ignore' => true));
      if (!$letter->isOnline()) {
        return ;
      }
      $registry[$code] = $letter;
      $letter->deliver($recipient, $bindings, $opts);
    }
    catch (Exception $e) {
      if ($opts['ignore'] === true) {
        S('log')->warn('letter ['.$code.'] unknown', __METHOD__);
      }
    }
  }



}