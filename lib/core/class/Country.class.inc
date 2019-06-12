<?php

class Country extends ActiveRecord 
{
  const FR = 250;
  const ES = 724;

  const FLAG_EUROPEAN = 1;
  const FLAG_TAXABLE = 2;
  const FLAG_SHIPPING = 4;
  const FLAG_DOM = 8;
  const FLAG_TOM = 16;

  public static $flags = array(self::FLAG_EUROPEAN => 'européen',
                               self::FLAG_TAXABLE => 'soumis à la TVA',
//                               self::FLAG_SHIPPING => 'livraison',
                               self::FLAG_DOM => 'DOM',
                               self::FLAG_TOM => 'TOM');

  const STATUS_OFFLINE = 0;
  const STATUS_ONLINE = 1;

  protected function onBeforeCommit(&$hash) {
    if (!empty($hash['name_fr'])) {
      $hash['name'] = $hash['name_fr'];
    }
  }

  public function destroy() { return true; }

  public function isTaxable() {
    return $this->hasFlag(self::FLAG_TAXABLE);
  }

  public function getShippingCost($shipping_id) {
    $rs = $this->dbo->query('SELECT z.cost'
                            .' FROM shp_country_zone AS cz'
                            .' JOIN '.T('zone').' AS z'
                            .  ' ON z.id=zone_id'
                            . ' AND z.shipping_id='.intval($shipping_id)
                            .' WHERE cz.country_id='.$this->getId()); 
    if ($rs === false || $rs->numRows() < 1) {
      $this->log->error('invalid shipping_id ('.$shipping_id.')', __METHOD__);
      throw new ActiveRecordException('invalid shipping');
    }
    return $rs->fetchValue();
  }

  public static function code($id) {
    if ($id == self::FR) return 'FR';
   return S('dbo')->fetchValue('SELECT code'
                               .' FROM '.T('country')
                               .' WHERE id='.intval($id));
  } 

}