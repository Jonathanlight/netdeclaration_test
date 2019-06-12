<?php

class Partenaire extends ActiveRecord {

  const STATUS_OFFLINE = 0;
  const STATUS_ONLINE = 1;

  public static $statuses = array(self::STATUS_OFFLINE => 'hors ligne',
                                  self::STATUS_ONLINE => 'en ligne');

  public function hasService($service_id) {
    $opts = array('filters' => array('id' => $service_id,
                                     'status' => Service::STATUS_ONLINE));
    $services = $this->getServices($opts);
    if ($services->count() < 1) return false;
    return true;
  }

  /* ----- INTERFACE hooks ----- */
  public function onRelationCreate($item)
  {
    if ($item instanceof Service) {
      $adherentsId = Adherent::collect(array('filters' => array('partenaire_id' => $this->getId())))->asSet('id');
      $souscriptions = Souscription::collect(array('filters' => array('|IN|adherent_id' => $adherentsId, 'service_id' => $item->getId())));
      foreach ($souscriptions as $souscription) {
        $attr['partenaire_id'] = $this->getId();
        $attr['commission'] = $souscription->price * (float)$this->commission / 100;
        $souscription->commit($attr);
      }
    }
  }

  /* ----- INTERFACE hooks ----- */
  public function onRelationDestroy($item)
  {
    if ($item instanceof Service) {
      $adherentsId = Adherent::collect(array('filters' => array('partenaire_id' => $this->getId())))->asSet('id');
      $souscriptions = Souscription::collect(array('filters' => array('|IN|adherent_id' => $adherentsId, 'service_id' => $item->getId())));
      foreach ($souscriptions as $souscription) {
        $attr['partenaire_id'] = 0;
        $attr['commission'] = 0;
        $souscription->commit($attr);
      }
    }
  }
}
