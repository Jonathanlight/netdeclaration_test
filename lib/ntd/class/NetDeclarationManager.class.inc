<?php

class NetDeclarationManager {

  const PRIVILEGE_ADHERENT_MIDDLE = 12;

  const SERVICE_ADHESION_MAIN_PROFILE = 5;
  const SERVICE_ADHESION_PROFILE_SECONDAIRE = 6;
  const SERVICE_ACCES_EDI = 32;

  const COOKIE_DOMTOM_USER = 'domtom_user';

  public static function onAppStart() {
    if (P('app.offline')) {
      S('log')->trace(S('req')->getClient('address'), 'Redirect offline');
      S('res')->sendRedirect('/doc/offline.html');
      return;
    }
  }

  public static function onActionStart() {
    $req = S('req');
    $action = S('req')->action();
    $cookie = S('req')->getCookie();
    if (strpos($action, 'form.') !== false && !S('req')->isBack()) {
      S('res')->useTemplates(array(null, 'skeleton.formulaire'));
    }
    if ($req->isAuthenticated()) {
      S('ctx')->_current_adherent = NetDeclaration::getCurrentAdherent();
      S('ctx')->_current_primary_adherent = Adherent::getCurrentPrimaryAdherent();

      if (S('ctx')->_current_adherent->cgu_sign_infos) {
        $cguSignInfos = unserialize(S('ctx')->_current_adherent->cgu_sign_infos);
        $currentCguVersion = $cguSignInfos['cgu_version'];
      } else {
          $currentCguVersion = null;
      }

      if($req->isMiddle() && P('cgu.version') != $currentCguVersion && $req->action() != 'conditions' && $req->action() != 'bulletin' && $req->action() != 'bulletin.validate' && $req->action() != 'captcha' && $req->extension() != 'file') {
        S('res')->sendRedirect('/middle/conditions');
        return;
      }
    }
    if ($req->isFront() && $req->action() != 'home') {
      if ($req->getLocale() != I18N::LOCALE_FR) {
        S('res')->addMeta('robots', 'NOINDEX');
      }
    }
    // DOMTOM detection
    if ($req->isAuthenticated()) {
      $is_domtom = (int) $req->getUser()->hasFlag(User::FLAG_NTD_DOMTOM);
      S('ctx')->_domtom_user = $is_domtom;
      if (!$cookie->hasAttribute(self::COOKIE_DOMTOM_USER) || $cookie->getAttribute(self::COOKIE_DOMTOM_USER) != $is_domtom) {
        $cookie->setAttribute(self::COOKIE_DOMTOM_USER, $is_domtom);
      }
    }
    elseif (!$cookie->hasAttribute(self::COOKIE_DOMTOM_USER)) {
      $is_domtom = (int) (!NetDeclaration::isMetropoleIP($req->getClient('ip')));
      $cookie->setAttribute(self::COOKIE_DOMTOM_USER, $is_domtom);
      S('ctx')->_domtom_user = $is_domtom;
    }
    else {
      S('ctx')->_domtom_user = $cookie->getAttribute(self::COOKIE_DOMTOM_USER);
    }
    // -- middle
    if ($req->isMiddle()) {
      NtdMiddleManager::onMiddleStart();
    }
  }

  public static function onAfterCommit($args) {
    $item = $args['item'];
    try {
      if (Model::exists('checksum')) {
        if (in_array($item->getModel(), DecBdd::$models)) {
          S('log')->debug('store', __METHOD__);
          Checksum::store($item);
        }
      }
    }
    catch (Exception $e) {
      S('log')->error($e, __METHOD__);
    }

  }

  public static function onUserLogout() {
    S('req')->getCookie()->removeAttribute(NetDeclarationManager::COOKIE_DOMTOM_USER);
  }

  public static function onUserAuth($hash) {
    $user = $hash['user'];
    $req = S('req');
    try {
      NetDeclaration::getCurrentAdherent();
      if ($req->isFront() || $req->isAccount() || $req->isMiddle()) {
        $domtom = $req->getUser()->hasFlag(User::FLAG_NTD_DOMTOM);
        S('req')->getCookie()->setAttribute(self::COOKIE_DOMTOM_USER, $domtom);
      }
    }
    catch (UnknownRecordException $e) {
      if ($req->hasSession()) {
        $session = $req->getSession();
        $session->logout();
        if ($session->isEmpty()) {
          $session->invalidate();
        }
        $req->track();
      }
      $req->getCookie()->removeAttribute('user_secret');
      S('log')->error('no adherent found for user [ID:' . $user->getId() . ']');
      S('res')->sendRedirect('/');
      $mail = new Mail();
      $mail->setSubject('[NTD][Error] user problem');
      $mail->setBody('no adherent found for user [ID:' . $user->getId() . ']');
      //$mail->addRecipient(NetDeclaration::getMailAdmin());
      $mail->addRecipient('npinchon@kernix.com');
      $mail->send();
    }
  }

  public static function onUserValidate() {
    $adherent = S('req')->adherent;
    //$iban = S('req')->iban;

    Adherent::validateAdherent($adherent);
    /*if ($adherent['billing_payment_mode'] == Adherent::BILLING_PAYMENT_MODE_PREVELEMENT) {
      Iban::validateIban($iban);
    }*/
  }

  public static function onUserCreate($hash) {
    $user = $hash['user'];
    if (!(S('req')->action() == 'user.signup' && S('req')->hasAttribute('adherent'))) return false;
    $user->addPrivilege(self::PRIVILEGE_ADHERENT_MIDDLE);


    $record = (array) S('req')->adherent;
    $record['status'] = Adherent::STATUS_SUBSCRIPTION_PENDING;
    $record['level'] = Tarif::ADHERENT_LEVEL_PRIMARY;
    $record['cec_flags'] = array_sum( (array)$record['cec_flags'] );
    $record['is_free_membership'] = 1;

    if ($record['partenaire_code']) {
      if (Partenaire::exists(array('code' => $record['partenaire_code']))) {
        $record['partenaire_id'] = Partenaire::id(array('code' => $record['partenaire_code']));
      }
    }

    $adherent = $user->setProfile($record);

    /*if ($adherent->billing_payment_mode == Adherent::BILLING_PAYMENT_MODE_PREVELEMENT) {
      $iban = (array) S('req')->iban;
      $iban['type'] = Iban::TYPE_PRIMARY;
      $iban = $adherent->addIban($iban);
    }*/

    $service_adhesion = Service::getInstance(NetDeclarationManager::SERVICE_ADHESION_MAIN_PROFILE);
    $tarif = $service_adhesion->getTarifs(array('filters' => array('adherent_types' => $adherent->type)))->first();

    $attributes = array(
      'adherent_id' => $adherent->getId(),
      'service_id' => $service_adhesion->getId(),
      'price' => $tarif->price,
      'context' => array('prix_forfait' => $tarif->price), // TODO : vérifier le fonctionnement
      'sign_at' => Date::now(),
      'status' => Souscription::STATUS_WAITING_PAIEMENT
    );

    $souscription = Souscription::getInstance();
    $souscription->commit($attributes);

    if (isset($hash['adherentAttrs'])) {
        $adherent->commit($hash['adherentAttrs']);
    }

    // Facture
    $facture = Facture::getInstance();
    $facture->setAdherent($adherent);
    $facture->addTarif($tarif, 1);
    if ($facture->calculate() > 0) {
      $facture->commit(array('status' => Facture::STATUS_NON_PAYE,
                             'method_id' => Facture::getOldMethodID($adherent)));
      $facture->addSouscription($souscription);
    }
    else {
      $souscription->setStatus(Souscription::STATUS_ACTIVE);
    }

    Letter::send('user.signup.user.confirm', $user->email, array('adherent.first_name' => $adherent->first_name,
                                                                 'adherent.last_name' => $adherent->last_name,
                                                                 'footer' => NetDeclaration::getMailFooter()));

    Letter::send('user.signup.ntd.confirm', NetDeclaration::getMailAdmin(), array('adherent.first_name' => $adherent->first_name,
                                                                                  'adherent.last_name' => $adherent->last_name,
                                                                                  'adherent.id' => $adherent->getId(),
                                                                                  'footer' => NetDeclaration::getMailFooter()));


  }

  public static function isDomtom() {
    return false;
  }

  public static $ip_addresses = array(
    '192.168.3.184', // Kernix : bbechade (108)
    '192.168.0.111', // Kernix : npinchon
    '192.168.3.111', // Kernix : npinchon (108)
    '92.103.81.138', // Kernix : 15 rue cels
    '212.198.161.75', // Kernix : 108 Avenue Maine
    '87.231.13.224', // Kernix : 108 Avenue Maine
    '85.158.120.97', // Mr MAISON : TradeXpress (prod et test)
    '82.127.47.211', // Mr MAISON : Mon réseau (dev)
  );

  public static function manageWebServiceAccess() {
    if (P('app.domain') == 'dev.ntd-dev.li.kernix.net') return true;
    if (!in_array(long2ip(S('req')->getClient('ip')), self::$ip_addresses)) {
      throw new Exception('no access found');
    }
  }

  public static function sitemap($type = 'fr') {
    $set = array();

    $locale = I18N::lang($type);


    $urls = array();
    foreach (NetDeclaration::getTreeContent() as $node) {
      if ($node['node']['code'] == 'services') continue;
      if (!isset($node['item']['key'])) continue;
      $item = Item::getInstanceByKey($node['item']['key']);
      $urls[$node['item']['url']] = array('updated_at' => $item->getMeta('updated_at'),
                                          'url' => $node['item']['url']);

      foreach ((array) $node['children'] as $child) {
        if (!isset($child['item']['key'])) continue;
        $item = Item::getInstanceByKey($child['item']['key']);
        $urls[$child['item']['url']] = array('updated_at' => $item->getMeta('updated_at'),
                                             'url' => $child['item']['url']);
      }
    }
    foreach (NetDeclaration::getTreeFooter() as $root_node) {
      if (!isset($root_node['item']['key'])) continue;
      $item = Item::getInstanceByKey($root_node['item']['key']);
      $urls[$root_node['item']['url']] = array('updated_at' => $item->getMeta('updated_at'),
                                               'url' => $root_node['item']['url']);
      foreach ((array) $root_node['children'] as $node) {
        if (!isset($node['item']['key'])) continue;
        $item = Item::getInstanceByKey($node['item']['key']);
        $urls[$node['item']['url']] = array('updated_at' => $item->getMeta('updated_at'),
                                            'url' => $node['item']['url']);
      }
    }
    $set[] = $urls;

    $headings_fronts = array(
      //303, // ntd.front.actions
      300, // ntd.carousels
      //297, // ntd.pages
    );
    $set[] = Page::collect(array('filters' => array('|IN|heading_id' => $headings_fronts)));

    $urls = array();
    foreach (Servicetype::collect(array('filters' => array('status' => 1))) as $_servicetype) {
      $urls[] = $_servicetype;
      foreach ($_servicetype->getServices(array('|>|status' => 0,
                                                'order' => array('type' => 'ASC'))) as $service) {
        $urls[] = $service;
      }
    }

    $set[] = $urls;


    /*$opts = array('filters' => array('locale' => $locale));
    $set[] = Page::collect($opts);*/

    $opts = array('filters' => array('|>|status' => 0,
                                     'locale' => $locale),
                  'order' => array('published_at' => 'desc'),
                  'limit' => 10);
    $set[] = Article::collect($opts);

    $sitemap_opts = array('type' => $type,
                          'priority' => 0.5,
                          'changefreq' => Sitemap::FREQ_WEEKLY);
    $sitemap = Sitemap::getInstance($set, $sitemap_opts);
    return $sitemap;
  }

  public static function sitemaps() {
    return array(array('url' => '/sitemap-fr.xml'),
                 //array('url' => '/sitemap-de.xml'),
                 //array('url' => '/sitemap-es.xml'),
                 //array('url' => '/sitemap-en.xml'),
    );
  }

  public static function getNtdPrivileges() {
    $out = array();
    $privileges = array(B(self::PRIVILEGE_ADHERENT_MIDDLE));
    foreach (Model::asBits('privilege') as $key => $value) {
      if (in_array($key, $privileges)) {
        $out[$key] = $value;
      }
    }
    return $out;
  }

  public static function url($args, $locale_id = null) {
    if (isset($args['item'])) {
      $item = $args['item'];
      if ($item instanceof Service && $item->servicetype_id > 0) {
        $servicetype = $item->getServicetype();
        return $servicetype->asUrl($locale_id) . '/' . String::urlify($item->getProperty('title', $locale_id)) . '-s' . $item->getId();
      }
      if ($item instanceof Servicetype) {
        return '/servicetype-' . String::urlify($item->getProperty('title', $locale_id)) . '-st' . $item->getId();
      }
    }
  }

  /*public static function breadcrumb($action) {
    $breadcrumb = array();
    if ($action == 'servicetype') {
      $breadcrumb[]
    }
    return $breadcrumb;
  }*/

}
