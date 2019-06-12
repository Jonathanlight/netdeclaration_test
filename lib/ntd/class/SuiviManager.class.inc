<?php

class SuiviManager {

  const URL = '/middle/suivi';
  const PATH_EDIMESSAGE_PDF = 'doc/edimessage';


  public static function getDestinatairesOpts($form, $adherent) {

    $opts = array('include' => array('suivi'),
                  'filters' => array(),
                  'order' => array(T('destinataire') . '.suivi_date_depot' => 'DESC',
                                   T('destinataire') . '.suivi_id' => 'DESC',
                                   T('destinataire') . '.id' => 'DESC'));

    if (!empty($form['date_depot_from'])) {
      $opts['filters']['|>=|' . T('suivi') . '.date_depot'] = Date::toDb($form['date_depot_from']) . ' 00:00:00';
    }
    if (!empty($form['date_depot_to'])) {
      $opts['filters']['|<=|' . T('suivi') . '.date_depot'] = Date::toDb($form['date_depot_to']) . ' 23:59:59';
    }
    if (!empty($form['periode_from'])) {
      $opts['filters']['|>=|' . T('suivi') . '.debut_periode'] = Date::toDb($form['periode_from']);
    }
    if (!empty($form['periode_to'])) {
      $opts['filters']['|<=|' . T('suivi') . '.fin_periode'] = Date::toDb($form['periode_to']);
    }
    if (!empty($form['type_doc'])) {
      $opts['filters'][T('suivi') . '.type_doc'] = $form['type_doc'];
    }
    if (!empty($form['siret_declarant'])) {
      $opts['filters'][T('suivi') . '.siret_decl'] = $form['siret_declarant'];
    }
    if (!empty($form['siret_emetteur'])) {
      $opts['filters'][T('suivi') . '.siret_emetteur'] = $form['siret_emetteur'];
    }
    if (!empty($form['status'])) {
      $opts['filters'][T('destinataire') . '.status'] = $form['status'];
    }
    if (!empty($form['type_doc'])) {
      $opts['filters'][T('suivi') . '.type_doc'] = $form['type_doc'];
    }
    if (!empty($form['type_decl'])) {
      $opts['filters'][T('suivi') . '.type_decl'] = $form['type_decl'];
    }
    if (!empty($form['type_dest'])) {
      $opts['filters'][T('destinataire') . '.type_dest'] = $form['type_dest'];
    }
    if (!empty($form['declarant_name'])) {
      $opts['filters']['|%%|'.T('suivi') . '.nom_decl'] = $form['declarant_name'];
    }


    $adherent_ids = self::adherentIds($adherent);
    $adherent_emetteur_id_filter = array('|IN|' . T('destinataire') . '.adherent_emetteur_id' => $adherent_ids);
    $adherent_declarant_id_filter = array('|IN|' . T('destinataire') . '.adherent_declarant_id' => $adherent_ids);
    $adherent_destinataire_id_filter = array('|IN|' . T('destinataire') . '.adherent_destinataire_id' => $adherent_ids);
    if ($form['sens'] == Destinataire::SENS_RECEPTION) {
      $opts['filters'][] = array($adherent_destinataire_id_filter);
    }
    elseif ($form['sens'] == Destinataire::SENS_EMISSION) {
      $opts['filters'][] = array(array($adherent_declarant_id_filter),
                                 array('OR' => $adherent_emetteur_id_filter));
    }
    else {
      $opts['filters'][] = array(array($adherent_declarant_id_filter),
                                 array('OR' => $adherent_emetteur_id_filter),
                                 array('OR' => $adherent_destinataire_id_filter));
    }

    return $opts;
  }

  public static function adherentIds($adherent) {
    $adherent_ids = array($adherent->getId());
    if ($adherent->isMainAdherent()) {
      $adherent_ids = array_merge($adherent_ids, Adherent::getAllAdherent($adherent->getUser()->getId())->asSet('id'));
    }
    if (false && self::admin()) {
      $adherent_ids = Adherent::collect(array('filters' => array(
        //'siret' => '33171849400015'
        'id' => '1043'
      )))->asSet('id');
      //$adherent_ids = array(2);
    }
    return $adherent_ids;
  }

  public static function admin() {
    return P('app.state') == 'dev';
  }

  public static function url($opts = array()){
    $url = self::URL;

    if($opts['service_id'] > 0) {

      //$params['type_doc']
    }

    return $url;
  }

  public static function generateEdiMessagePdf($edimessage) {
    if (is_numeric($edimessage)) {
      $edimessage = Edimessage::getInstance((int)$edimessage);
    }
    if (!Folder::exists(self::PATH_EDIMESSAGE_PDF)) {
      Folder::create(self::PATH_EDIMESSAGE_PDF, true);
    }

    $path_target  = self::PATH_EDIMESSAGE_PDF.'/'.$edimessage->getId().'.pdf';
    $path_source  = str_replace('.pdf', '.html', $path_target);

    $content = H::get('/middle/suivi.edimessage', array('id'    => $edimessage->getId(),
                                                        'print' => 1));

    $header = H::url('/skeleton.pdf.header', array('domtom'     => 0, //$user->hasFlag(User::FLAG_NTD_DOMTOM),
                                                   'head_title' => base64_encode('Message EDI ' . $edimessage->ref_message)));
    $footer = H::url('/skeleton.pdf.footer', array('domtom'     => 0)); //$user->hasFlag(User::FLAG_NTD_DOMTOM)));

    $fp = fopen($path_source, 'w');
    fwrite($fp, $content);
    fclose($fp);

    if (P('auth.login') && P('auth.password')) {
      $username = P('auth.login');
      $password = P('auth.password');
    } else {
      $username = null;
      $password = null;
    }

    $options = array('--header-html'    => '\''.$header.'\'',
                     '--footer-html'    => '\''.$footer.'\'',
                     '--username'       => $username,
                     '--password'       => $password,
                     '--page-size'      => 'A4',
                     '--margin-top'     => '34',
                     '--margin-left'    => '0',
                     '--margin-right'   => '0',
                     '--margin-bottom ' => '20',
                     '--header-spacing' => '0',
                     '--footer-spacing' => '0',
                     '--outline-depth'  => '0');

    system('/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf '.NetDeclaration::asShellParams($options).' \''.$path_source.'\' \''.$path_target.'\'"');
    unlink($path_source);

    return $path_target;
  }

} 