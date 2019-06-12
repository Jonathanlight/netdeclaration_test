<?php

class Tarif extends ActiveRecord {

  const PRICE_TYPE_FORFAIT = 1;
  const PRICE_TYPE_UNITAIRE = 2;
  const PRICE_TYPE_SIRET = 3;
  const PRICE_TYPE_LOYER = 4;
  const PRICE_TYPE_NO_FISCAL = 5;
  const PRICE_TYPE_SIREN = 6;
  const PRICE_TYPE_GREFFE = 7;

  const ADHERENT_LEVEL_BOTH = 0;
  const ADHERENT_LEVEL_PRIMARY = 1;
  const ADHERENT_LEVEL_SECONDARY = 2;

  public static $price_types = array(
    self::PRICE_TYPE_FORFAIT => 'Prix forfaitaire',
    self::PRICE_TYPE_UNITAIRE => 'Prix unitaire',
    self::PRICE_TYPE_SIRET => 'Prix par SIRET',
    self::PRICE_TYPE_SIREN => 'Prix par SIREN',
    self::PRICE_TYPE_LOYER => 'Prix par Loyer déclaré',
    self::PRICE_TYPE_NO_FISCAL => 'Prix par Numéro fiscal',
    self::PRICE_TYPE_GREFFE => 'Prix par Dépôt de greffe',
  );

  public static $adherent_levels = array(
    self::ADHERENT_LEVEL_BOTH => 'Les deux',
    self::ADHERENT_LEVEL_PRIMARY => 'Adhérent primaire',
    self::ADHERENT_LEVEL_SECONDARY => 'Adhérent secondaire',
  );


  /* ----- asMethods ----- */
  public function asFinderHash($hash) {
    $hash['adherent_types'] = implode('<br />', array_map(function($type) {
      return Adherent::$types[$type];
    }, $this->adherent_types));
    $hash['adherent_level'] = self::$adherent_levels[$hash['adherent_level']];    
    return $hash;
  }

  public function asUrl() {
    if (S('req')->isAccount()) {
      return '/account/ntd/account.tarif/-/id/' . $this->getId();
    }
    return parent::asUrl();
  }

  public function getPrice() {
    return $this->price;
  }

  protected function onBeforeCommit(&$attrs) {
    $name = "";
    $service = Service::getInstance(isset($attrs['service_id']) ? $attrs['service_id'] : $this->service_id);
    $name .= $service->name . ' [' . Service::$types[$service->type] . '] - ';
    if ($attrs['price_type'] == self::PRICE_TYPE_UNITAIRE) {
      $name .= "Tarif unitaire [" . $attrs['qty_min'] . '-' . $attrs['qty_max'] . "] : " . H::amount($attrs['price']);
    }
    elseif ($attrs['price_type'] == self::PRICE_TYPE_SIRET) {
      $name .= "Tarif SIRET : " . H::amount($attrs['price']);
    }
    elseif ($attrs['price_type'] == self::PRICE_TYPE_SIREN) {
      $name .= "Tarif SIREN : " . H::amount($attrs['price']);
    }
    elseif ($attrs['price_type'] == self::PRICE_TYPE_NO_FISCAL) {
      $name .= "Tarif N° Fiscal : " . H::amount($attrs['price']);
    }
    elseif ($attrs['price_type'] == self::PRICE_TYPE_LOYER) {
      $name .= "Tarif Loyer : " . H::amount($attrs['price']);
    }
    else {
      $name .= "Tarif forfait : " . H::amount($attrs['price']);
    }
    $attrs['name'] = $name;
  }

}