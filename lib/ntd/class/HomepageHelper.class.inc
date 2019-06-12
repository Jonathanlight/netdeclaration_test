<?php

class HomepageHelper {

  const SNIPPET_INTRODUCTION_CODE = 'homepage.introduction';
  const SNIPPET_PAIEMENT_CODE = 'homepage.box.paiement';
  const SNIPPET_PARTENAIRES_CODE = 'homepage.box.partenaires';
  const SNIPPET_SERVICES_CODE = 'homepage.box.services';
  const SNIPPET_FORWHO_CODE = 'homepage.box.pourqui';


  public static function getServiceTypes() {
    return Servicetype::collect(array('order' => array('position' => 'asc'),
                                      'filters' => array('status' => 1)));
  }

  public static function getServices() {
    return Service::collect(array(
                              'include' => array('servicetype'),
                              'order' => array('position' => 'asc'),
                              'filters' => array('|>|status' => 0,
                                                 'type' => array(Service::TYPE_FORMULAIRE,
                                                                 Service::TYPE_EDI))));
  }

  public static function getForWhoPages() {
    return Page::collect(array('filters' => array('heading_id' => Heading::exists(array('code' => 'ntd.carousels'))),
                               'order' => array('code')));
  }

}