<?php

class Payment extends ActiveRecord {

  const FLAG_EMAIL_SENT = 1;
  const FLAG_EBP_EXPORTED = 8;

  public static $flags = array(self::FLAG_EMAIL_SENT => 'email envoyé',
                               self::FLAG_EBP_EXPORTED => 'Exporté pour EBP');

  const STATUS_RECEIVED = 10;
  const STATUS_PENDING = 0;
  const STATUS_CANCELED = -50;
  const STATUS_ERROR = -100;

  public static $statuses = array(self::STATUS_RECEIVED => 'reçu',
                                  self::STATUS_PENDING => 'en attente',
                                  self::STATUS_CANCELED => 'annulé',
                                  self::STATUS_ERROR => 'erreur');

  public function sendLetter() {
    return;
    /*try {
      $method = $this->getMethod();
      $code = null;
      if ($this->status == Payment::STATUS_RECEIVED) {
        $code = $method->letter_received;
      }
      elseif ($this->status == Payment::STATUS_PENDING) {
        $code = $method->letter_pending;
      }
      if (strlen($code) < 2) return ;
      $facture = $this->getOrder();
      $user = $facture->getAdherent()->getUser();
      $bindings = $facture->getAttributes();
      $bindings['details'] = H::get('/shop/order.details',
                                    array('id' => $facture->id));
      $bindings['payment_amount'] = H::amount($this->amount);
      Letter::send($code, $user, $bindings);
    }
    catch (Exception $e) { } */
  }

  protected function onBeforeCommit(&$attrs) {
    if (is_array($attrs['datas'])) {
      $attrs['datas'] = serialize($attrs['datas']);
    }
  }

  protected function onAfterCommit($attrs) {
    if (empty($this->name)) {
      if ($this->method_id == 1) {
        $name = 'PAYBOX N°' . $this->datas['pbxs'];
      }
      else {
        $name = $this->getName();
      }
      $this->setAttribute('name', $name);
    }
    if (Date::isNull($this->placed_at)) {
      $this->setAttribute('placed_at', Date::now());
    }
    if ($this->status == self::STATUS_RECEIVED && $this->_changes['status'] != self::STATUS_RECEIVED) {
      $factures = $this->getFactures();

      if ($this->method_id > 0 && Date::isNull($this->paid_at)) {
        $method = $this->getMethod();
        if ($method->code == 'prelevement') {
          if ($factures->count > 0) {
            $this->setAttribute('paid_at', $factures->first()->getAttribute('start_at'));
          }
        }
        elseif ($method->code == 'virement') {
          $this->setAttribute('paid_at', Date::today());
        }
        elseif ($method->code == 'cb') {
          $this->setAttribute('paid_at', Date::today());
        }
      }

    }
    if ($this->status == self::STATUS_RECEIVED) {
      foreach ($factures as $facture) {
        $facture->commit(array('status' => Facture::STATUS_PAYE));
      }
    }

  }

  public function isReceived() {
    return $this->status == self::STATUS_RECEIVED;
  }

  public function asEditHash() {
    $h = array('datas' => array());
    $h['show_datas'] = false;
    if (strlen($this->datas) > 3) {
      $h['datas'] = unserialize($this->datas);
      $h['show_datas'] = true;
    }
    return $h;
  }

  public function isLast() {
    if ($this->status != self::STATUS_RECEIVED) return false;
    $facture = Facture::getInstance((int) $this->facture_id);
    $s = S('dbo')->fetchValue('SELECT SUM(amount)'
        . ' FROM ' . T('payment')
        . ' WHERE status=' . self::STATUS_RECEIVED
        . ' AND facture_id=' . $facture->getId());
    return ceil($s) >= ceil($facture->price_ttc);
  }

  public function getName($locale = null) {
    $method = $this->getMethod();
    $name = $method->getName();        
    return $name;
  }

  public function asListHash() {
    $opts = array('callback' => 'reload');
    $h = array('type' => Item::edit($this, $opts),
               'statut' => self::$statuses[$this->status],
               'montant' => $this->amount,
               'création' => $this->placed_at);
    if (!DH::isNull($this->paid_at)) {
      $h['paiement'] = $this->paid_at;
    }
    if (!empty($this->code)) {
      $h['uid'] = $this->code;
    }
    if (!empty($this->description)) {
      $h['infos'] = $this->description;
    }
    return $h;
  }

  public function asRelationRow($relation, $row) {
    if ($relation instanceof Facture) {
      return '[montant : ' . $row['amount'] . '][' . Facture::$statuses[$relation->status] . '] ' . $relation->name;      
    }
    return $relation->getName();
  }

}
