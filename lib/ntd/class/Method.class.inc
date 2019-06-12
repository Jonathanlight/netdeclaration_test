<?php

/***
PSP = Payment Service Provider
***/

class Method extends ActiveRecord
{
  const TYPE_GIFTCARD = 9;

  const FLAG_INSTALLEMENT = 1;

  public static $flags = array(self::FLAG_INSTALLEMENT => 'multiple');

  public static $types = array(1 => 'amex',
                               2 => 'credittransfer',
                               3 => 'creditcard',
                               4 => 'check',
                               5 => 'digitalwallet',
                               6 => 'prepaidcard',
                               7 => 'mobilepayment',
                               8 => 'voucher',
                               self::TYPE_GIFTCARD => 'giftcard',
                               10 => 'phone');

  public function request($facture, $amount=null) {
    $amount = $amount ?: $facture->price_ttc;
    if ($facture->status == Facture::STATUS_PAYE) {
      S('log')->error('facture ('.$facture->getId().') already paid '.
                      '[status='.$facture->status.']',
                      __METHOD__);
      throw new Exception('facture ('.$facture->getId().') already paid');
    }

    $payment = Payment::getInstance();
    $payment->commit(array('facture_id' => $facture->getId(),
                           'method_id' => $this->getId(),
                           'amount' => $amount));
    $payment->addFacture($facture, array('amount' => $amount));
    $payment->setVisit(S('req'));
    $class = self::loadClass($this->getPsp()->getName());
    $html = call_user_func(array($class, 'request'), $payment);
    //$payment->sendLetter();
    return $html;
  }

  public function asFinderHash($h) {
    $h['type'] = self::$types[$this->type];
    return $h;
  }

  public static function loadClass($name) {
    $name = (string) $name;
    $class = ucfirst($name);
    require LIB_PATH.'/ntd/class/psp/'.$class.'.class.inc';
    return $class;
  }

  public static function callback() {
    $req = S('req');
    if ($req->hasAttribute('psp')) {
      $class = $req->getAttribute('psp');
    }
    elseif ($req->hasAttribute('ips')) {
      S('log')->trace('ips param is deprecated', __METHOD__);
      $class = $req->getAttribute('ips');
    }
    else {
      throw new Exception('unknown psp');
    }
    $class = self::loadClass($class);
    call_user_func(array($class, 'callback'));
  }

  public function getType() {
    return self::$types[$this->type];
  }

  public static function label($id) {
    $hash = self::names();
    return $hash[$id];
  }

  public static $names = null;

  public static function names() {
    if (!is_array(self::$names)) {
      self::$names = S('dbo')->asHash('SELECT id, name'
                                      .' FROM '.T('payment')
                                      .' WHERE status=1');
    }
    return self::$names;
  }

}