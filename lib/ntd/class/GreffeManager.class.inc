<?php

class GreffeManager {

  const XML_VERSION_SCHEMA = 'V2015.02';

  const COMPTE_SOCIAUX   = 1;
  const COMPTE_CONSOLIDE = 2;

  const FJ_SARL      = 1;
  const FJ_SELARL    = 2;
  const FJ_EURL      = 3;
  const FJ_SNC       = 4;
  const FJ_SCS       = 5;
  const FJ_SA        = 7;
  const FJ_SELAFA    = 8;
  const FJ_SAS       = 9;
  const FJ_SELAS     = 10;
  const FJ_SCA       = 12;
  const FJ_SELCA     = 13;
  const FJ_ETRANGERE = 14;

  const DIRECTION_CONSEIL_ADMINISTRATION = 1;
  const DIRECTION_CONSEIL_SURVEILLANCE   = 2;

  const DOC_BILAN                         = 1;
  const DOC_COMPTABLE                     = 2;
  const DOC_COMPTE_RESULTAT               = 3;
  const DOC_ATTESTATION                   = 4;
  const DOC_RAPPORT_GROUPE                = 5;
  const DOC_ANNEXE                        = 6;
  const DOC_PV_ASSEMBLE                   = 7;
  const DOC_RAPPORT_GESTION               = 8;
  const DOC_RAPPORT_COMMISSAIRE           = 9;
  const DOC_RAPPORT_PRESIDENT_225_37      = 10;
  const DOC_RAPPORT_COMMISSAIRE_CONSOLIDE = 11;
  const DOC_INVENTAIRE                    = 12;
  const DOC_RAPPORT_SURVEILLANCE          = 13;
  const DOC_RAPPORT_PRESIDENT_225_68      = 14;
  const DOC_DECLARATION_CONFIDENTIALITE   = 15;
  const DOC_MANDAT_DEPOT                  = 100;
  const DOC_LIASSE                        = 101;

  const DOCUMENTS_PATH = 'amitel';
  const DOCUMENTS_REPONSE_PATH = 'greffes';
  const DOCUMENTS_SIZE_MAX = 2097152; // 2 Mo

  const AMITEL_DEMANDE_PATH = 'demande';
  const AMITEL_ACK_PATH     = 'accuse';
  const AMITEL_REPONSE_PATH = 'reponse';

  const PDF_PATH = 'greffes';


  public static $types_compte = array(self::COMPTE_SOCIAUX   => 'Compte sociaux',
                                      self::COMPTE_CONSOLIDE => 'Comptes consolidés');

  public static $formes_juridique = array(self::FJ_SARL      => 'SARL',
                                          self::FJ_SELARL    => 'SELARL',
                                          self::FJ_EURL      => 'EURL',
                                          self::FJ_SNC       => 'SNC',
                                          self::FJ_SCS       => 'SCS',
                                          self::FJ_SA        => 'SA',
                                          self::FJ_SELAFA    => 'SELAFA',
                                          self::FJ_SAS       => 'SAS',
                                          self::FJ_SELAS     => 'SELAS',
                                          self::FJ_SCA       => 'SCA',
                                          self::FJ_SELCA     => 'SELCA',
                                          self::FJ_ETRANGERE => 'Étrangère');

  public static $modes_direction = array(self::DIRECTION_CONSEIL_ADMINISTRATION => 'Conseil d’administration',
                                         self::DIRECTION_CONSEIL_SURVEILLANCE   => 'Directoire et Conseil de surveillance');

  public static $docs = array(self::DOC_BILAN                         => 'Bilan (actif, passif)',
                              self::DOC_COMPTABLE                     => 'Documents comptables établis contrôlés et publiés dans l\'Etat où est situé le siège',
                              self::DOC_COMPTE_RESULTAT               => 'Compte de résultat',
                              self::DOC_ATTESTATION                   => 'Attestation de conformité des documents comptables *',
                              self::DOC_RAPPORT_GROUPE                => 'Rapport de gestion du groupe',
                              self::DOC_ANNEXE                        => 'Annexes',
                              self::DOC_PV_ASSEMBLE                   => 'PV d\'assemblée (proposition et résolution d\'affectation votée)',
                              self::DOC_RAPPORT_GESTION               => 'Rapport de gestion',
                              self::DOC_RAPPORT_COMMISSAIRE           => 'Rapport des Commissaires aux Comptes',
                              self::DOC_RAPPORT_PRESIDENT_225_37      => 'Rapport du président du conseil prévu à l\'article L.225-37 du code de commerce',
                              self::DOC_RAPPORT_COMMISSAIRE_CONSOLIDE => 'Rapport des Commissaires aux Comptes sur les comptes consolidés',
                              self::DOC_INVENTAIRE                    => 'Inventaire',
                              self::DOC_RAPPORT_SURVEILLANCE          => 'Rapport du conseil de surveillance',
                              self::DOC_RAPPORT_PRESIDENT_225_68      => 'Rapport du président du conseil prévu à l\'article L.225-68 du code de commerce',
                              self::DOC_DECLARATION_CONFIDENTIALITE   => 'Déclaration de confidentialité',
                              self::DOC_MANDAT_DEPOT                  => 'Mandat de dépôt',
                              self::DOC_LIASSE                        => 'Liasse');

  public static $doc_names = array(self::DOC_BILAN                         => 'bilan_actif_pasif',
                                   self::DOC_COMPTABLE                     => 'documents_comptables',
                                   self::DOC_COMPTE_RESULTAT               => 'compte_résultat',
                                   self::DOC_ATTESTATION                   => 'attestation_de_conformité_des_documents_comptables',
                                   self::DOC_RAPPORT_GROUPE                => 'rapport_de_gestion_du_groupe',
                                   self::DOC_ANNEXE                        => 'annexes',
                                   self::DOC_PV_ASSEMBLE                   => 'pv_assemblee',
                                   self::DOC_RAPPORT_GESTION               => 'rapport_de_gestion',
                                   self::DOC_RAPPORT_COMMISSAIRE           => 'rapport_des_commissaires_aux_comptes',
                                   self::DOC_RAPPORT_PRESIDENT_225_37      => 'rapport_du_président_du_conseil_article_l_225-37',
                                   self::DOC_RAPPORT_COMMISSAIRE_CONSOLIDE => 'rapport_des_commissaires_aux_comptes_sur_les_comptes_consolides',
                                   self::DOC_INVENTAIRE                    => 'inventaire',
                                   self::DOC_RAPPORT_SURVEILLANCE          => 'rapport_du_conseil_de_surveillance',
                                   self::DOC_RAPPORT_PRESIDENT_225_68      => 'rapport_du_président_du_conseil_article_l_225-68',
                                   self::DOC_DECLARATION_CONFIDENTIALITE   => 'déclaration_de_confidentialité',
                                   self::DOC_MANDAT_DEPOT                  => 'mandat_depot',
                                   self::DOC_LIASSE                        => 'liasse');

  public static $concat_doc_names = array(self::COMPTE_SOCIAUX   => array(self::DOC_BILAN,
                                                                          self::DOC_COMPTE_RESULTAT,
                                                                          self::DOC_ANNEXE,
                                                                          self::DOC_RAPPORT_GESTION,
                                                                          self::DOC_RAPPORT_SURVEILLANCE,
                                                                          self::DOC_RAPPORT_COMMISSAIRE,
                                                                          self::DOC_INVENTAIRE,
                                                                          self::DOC_PV_ASSEMBLE,
                                                                          self::DOC_RAPPORT_PRESIDENT_225_37,
                                                                          self::DOC_RAPPORT_PRESIDENT_225_68),
                                          self::COMPTE_CONSOLIDE => array(self::DOC_COMPTABLE,
                                                                          self::DOC_RAPPORT_GROUPE,
                                                                          self::DOC_RAPPORT_COMMISSAIRE_CONSOLIDE,
                                                                          self::DOC_RAPPORT_SURVEILLANCE));

  public static $authorized_doc_formats = array('pdf');
  public static $authorized_mandat_formats = array('pdf');
  public static $authorized_liasse_formats = array('pdf');

  public static $liasse_formulaires = array(
    // BIC RS
    'IS RS' => array('2033A', '2033B'),
    'IR RS' => array('2033A', '2033B'),
    'IS SE' => array('2033A', '2033B'),
    'IR SE' => array('2033A', '2033B'),
    // BIC RN
    'IS RN' => array('2050', '2051', '2052'),
    'IR RN' => array('2050', '2051', '2052'),
    'IS NE' => array('2050', '2051', '2052'),
    'IR NE' => array('2050', '2051', '2052'),
    // BA RS
    'BS'    => array('2139A', '2139B'),
    // BA RN
    'BN'    => array('2144', '2145', '2146', '2146BIS')
  );


  /** Service **/

  public static function getService() {
    $code = 'GREFFE';
    return Service::getInstance(array('code' => $code));
  }

  public static function getAvaillableSouscription(Adherent $adherent) {
    $service = self::getService();
    $souscription_opts = array('filters' => array('adherent_id'   => $adherent->getId(),
                                                  'service_id'    => $service->getId(),
                                                  '|!&|flags'     => Souscription::FLAG_CONSUMED,
                                                  '|<=|start_at'  => Date::today(),
                                                  '|>=|finish_at' => Date::today(),
                                                  'status'        => Souscription::STATUS_ACTIVE));

    $souscriptions = Souscription::collect($souscription_opts);
    return count($souscriptions) > 0 ? $souscriptions->first() : null;
  }

  public static function isAdherentAllowed(Adherent $adherent) {
    return count(self::getAvaillableSouscription($adherent)) > 0;
  }

  public static function getAvaillableUnpaidSubscription(Adherent $adherent) {
    $service = self::getService();
    $souscription_opts = array('filters' => array('adherent_id'   => $adherent->getId(),
                                                  'service_id'    => $service->getId(),
                                                  '|!&|flags'     => Souscription::FLAG_CONSUMED,
                                                  'status'        => Souscription::STATUS_WAITING_PAIEMENT));

    $souscriptions = Souscription::collect($souscription_opts);
    return count($souscriptions) > 0 ? $souscriptions->first() : null;
  }

  public static function hasAvaillableUnpaidSubscription(Adherent $adherent) {
    return !is_null(self::getAvaillableUnpaidSubscription($adherent));
  }

  public static function getUnpaidFacture(Adherent $adherent) {
    if (self::hasAvaillableUnpaidSubscription($adherent)) {
      $opts = array('filters' => array('|IN|status' => array(Facture::STATUS_NON_PAYE, Facture::STATUS_PENDING)));
      $factures = self::getAvaillableUnpaidSubscription($adherent)->getFactures($opts);
      return count($factures) > 0 ? $factures->first() : null;
    }
    return null;
  }

  public static function redirectToPurchaseService() {
    $service = self::getService();
    S('res')->sendRedirect('/middle/services.purchasables.validation', array('form[service_id]' => $service->getId()));
    return null;
  }

  /** Dossier **/

  public static function hasCurrentDossier() {
    return !is_null(self::getCurrentDossier());
  }

  public static function getCurrentDossier() {
    $adherent = NetDeclaration::getCurrentAdherent();
    $filters = array('adherent_id' => $adherent->getId(),
                     'status'      => Greffedossier::STATUS_PENDING);
    if (Greffedossier::exists($filters)) {
      return Greffedossier::getInstance($filters);
    }
    return null;
  }

  public static function canRegisterGreffe(Greffedossier $dossier) {
    if ($dossier->status == Greffedossier::STATUS_CLOSED) {
      return false;
    }

    $greffes = $dossier->getGreffes();
    if (count($greffes) == 0) {
      return true;
    }

    $args = array('filters' => array(),
                  'metas'   => array('created_at'),
                  'order'   => array('created_at' => 'desc'),
                  'limit'   => 1);
    $greffes = $dossier->getGreffes($args);
    if (count($greffes) > 0) {
      if ($greffes->first()->status == Greffe::STATUS_REFUSED) {
        return true;
      }
    }

    return false;
  }

  public static function getSouscriptionQuantityForDossier(Greffedossier $dossier) {
    return count($dossier->getGreffes()) +1;
  }

  public static function getSouscriptionQuantityForCurrentDossier() {
    return self::getSouscriptionQuantityForDossier(self::getCurrentDossier());
  }

  public static function isFirstSouscriptionCondition(Greffedossier $dossier) {
    return count($dossier->getGreffes()) == 0;
  }

  public static function isFirstSouscriptionConditionForCurrentDossier() {
    return self::isFirstSouscriptionCondition(self::getCurrentDossier());
  }

  /** Amitel **/

  public static function getRequiredDocs($type_compte, $forme_juridique, $is_gerant, $mode_direction, $compte_public) {
    $docs = array();

    if ($type_compte == self::COMPTE_SOCIAUX) {
      switch ($forme_juridique) {
        case self::FJ_EURL:
          $docs[] = self::DOC_BILAN;
          $docs[] = self::DOC_COMPTE_RESULTAT;
          $docs[] = self::DOC_ANNEXE;
          $docs[] = self::DOC_PV_ASSEMBLE;
          $docs[] = self::DOC_RAPPORT_COMMISSAIRE;
          if ($is_gerant) {
            $docs[] = self::DOC_INVENTAIRE;
          }
          $docs[] = self::DOC_ATTESTATION;
          break;
        case self::FJ_SARL:
        case self::FJ_SELARL:
        case self::FJ_SNC:
        case self::FJ_SCS:
          $docs[] = self::DOC_BILAN;
          $docs[] = self::DOC_COMPTE_RESULTAT;
          $docs[] = self::DOC_ANNEXE;
          $docs[] = self::DOC_PV_ASSEMBLE;
          $docs[] = self::DOC_RAPPORT_COMMISSAIRE;
          $docs[] = self::DOC_ATTESTATION;
          break;
        case self::FJ_SA:
          $docs[] = self::DOC_BILAN;
          $docs[] = self::DOC_COMPTE_RESULTAT;
          $docs[] = self::DOC_ANNEXE;
          $docs[] = self::DOC_RAPPORT_GESTION;
          if ($mode_direction == self::DIRECTION_CONSEIL_ADMINISTRATION) {
            $docs[] = self::DOC_RAPPORT_PRESIDENT_225_37;
          }
          $docs[] = self::DOC_PV_ASSEMBLE;
          $docs[] = self::DOC_RAPPORT_COMMISSAIRE;
          if ($mode_direction == self::DIRECTION_CONSEIL_SURVEILLANCE) {
            $docs[] = self::DOC_RAPPORT_SURVEILLANCE;
          }
          $docs[] = self::DOC_ATTESTATION;
          if ($mode_direction == self::DIRECTION_CONSEIL_SURVEILLANCE) {
            $docs[] = self::DOC_RAPPORT_PRESIDENT_225_68;
          }

          break;
        case self::FJ_SELAFA:
          $docs[] = self::DOC_BILAN;
          $docs[] = self::DOC_COMPTE_RESULTAT;
          $docs[] = self::DOC_ANNEXE;
          $docs[] = self::DOC_RAPPORT_GESTION;
          $docs[] = self::DOC_PV_ASSEMBLE;
          $docs[] = self::DOC_RAPPORT_COMMISSAIRE;
          if ($mode_direction == self::DIRECTION_CONSEIL_SURVEILLANCE) {
            $docs[] = self::DOC_RAPPORT_SURVEILLANCE;
          }
          $docs[] = self::DOC_ATTESTATION;
          break;
        case self::FJ_SAS:
        case self::FJ_SELAS:
          $docs[] = self::DOC_BILAN;
          $docs[] = self::DOC_COMPTE_RESULTAT;
          $docs[] = self::DOC_ANNEXE;
          $docs[] = self::DOC_RAPPORT_GESTION;
          $docs[] = self::DOC_PV_ASSEMBLE;
          $docs[] = self::DOC_RAPPORT_COMMISSAIRE;
          $docs[] = self::DOC_ATTESTATION;
          break;
        case self::FJ_SCA:
        case self::FJ_SELCA:
          $docs[] = self::DOC_BILAN;
          $docs[] = self::DOC_COMPTE_RESULTAT;
          $docs[] = self::DOC_ANNEXE;
          $docs[] = self::DOC_RAPPORT_GESTION;
          $docs[] = self::DOC_PV_ASSEMBLE;
          $docs[] = self::DOC_RAPPORT_COMMISSAIRE;
          $docs[] = self::DOC_RAPPORT_SURVEILLANCE;
          $docs[] = self::DOC_ATTESTATION;
          break;
        case self::FJ_ETRANGERE:
          $docs[] = self::DOC_COMPTABLE;
          $docs[] = self::DOC_ATTESTATION;
          break;
      }
    }
    else {
      switch ($forme_juridique) {
        case self::FJ_SARL:
        case self::FJ_SELARL:
        case self::FJ_EURL:
        case self::FJ_SA:
        case self::FJ_SELAFA:
        case self::FJ_SCA:
        case self::FJ_SELCA:
        case self::FJ_SAS:
        case self::FJ_SELAS:
        case self::FJ_SNC:
        case self::FJ_SCS:
          $docs[] = self::DOC_BILAN;
          $docs[] = self::DOC_COMPTE_RESULTAT;
          $docs[] = self::DOC_ANNEXE;
          $docs[] = self::DOC_RAPPORT_GROUPE;
          $docs[] = self::DOC_RAPPORT_COMMISSAIRE_CONSOLIDE;
          $docs[] = self::DOC_ATTESTATION;
          break;
        case self::FJ_ETRANGERE:
          $docs[] = self::DOC_COMPTABLE;
          $docs[] = self::DOC_RAPPORT_GROUPE;
          $docs[] = self::DOC_ATTESTATION;
          break;
      }
    }

    if (!$compte_public) {
      $docs[] = self::DOC_DECLARATION_CONFIDENTIALITE;
    }

    return $docs;
  }

  public static function isValidDocument($files, $key, $formats, &$errors_msg) {
    $valid = $files['error'][$key] == UPLOAD_ERR_OK;
    if (!$valid)
        $errors_msg[] = $files['name'][$key].': Une erreur est survenue pendant le téléchargement';
    if ($valid) {
      $path_parts = pathinfo($files['name'][$key]);
      $ext = strtolower($path_parts['extension']);
      $valid = in_array($ext, $formats);
      if (!$valid)
        $errors_msg[] = $files['name'][$key].': L\'extension n\'est pas supporté';
    }
    if ($valid) {
      if ($files['size'][$key] > self::DOCUMENTS_SIZE_MAX) {
        $size = self::DOCUMENTS_SIZE_MAX/pow(1024, 2);
        $errors_msg[] = $files['name'][$key].': La taille des fichiers est limité à '.$size.' Mo';
        return false;
      }
    }
    return $valid;
  }

  public static function moveDocument($greffe, $files, $key) {
    $path_parts = pathinfo($files["name"][$key]);
    $ext = strtolower($path_parts['extension']);
    $tmp_name = $files["tmp_name"][$key];
    $name = $greffe->getId() . '_' . self::$doc_names[$key] .'.'. $ext;
    $path = $greffe->getDocumentPath();
    $base_path = self::getDocumentPath();
    $internal_path = self::getInternalDocumentPath();
    if (!file_exists($base_path)) {
      mkdir($base_path);
    }
    if (!file_exists($internal_path)) {
      mkdir($internal_path);
    }
    if (!file_exists($path)) {
      mkdir($path);
    }
    move_uploaded_file($tmp_name, $path . '/' . $name);
    return $path . '/' . $name;
  }

  public static function getDocumentPath() {
    return DOC_PATH . '/' . self::DOCUMENTS_PATH;
  }

  public static function getInternalDocumentPath() {
    return self::getDocumentPath() . '/.greffes';
  }

  public static function getResponseDocumentPath() {
    return DOC_PATH . '/' . self::DOCUMENTS_REPONSE_PATH;
  }

  public static function getPdfPath() {
    return DOC_PATH . '/' . self::PDF_PATH;
  }

  public static function getDeclarations($greffe) {
    $adherent = $greffe->getAdherent();

    $today = Date::toDb(Date::now());
    $filters = array('|<=|start_at' => $today,
                     '|>=|end_at'   => $today,
                     'status'       => 1);
    $millesimes = Millesime::collect(array('filters' => $filters,
                                           'limit'   => 1));

    if ($millesimes->count() == 0) {
      return array();
    }

    $millesime = $millesimes->first();
    foreach (self::$liasse_formulaires as $key => $values) {
      $filters = array('|IN|'.T('formulairetype').'.code'         => $values,
                       '|have|'.T('formulairetype').'.millesimes' => $millesime->id,
                       T('declaration').'.adherent_id'            => $adherent->id,
                       '|>=|'.T('declaration').'.status'          => Declaration::STATUS_READY_TO_SEND,
                       'status'                                   => Formulaire::STATUS_ACTIF);

      $includes = array('formulairetype',
                        'declaration');

      $formulaires = Formulaire::collect(array('filters' => $filters,
                                               'include' => $includes));


      $filters = array('|IN|id'                     => $formulaires->asSet('declaration_id'),
                       T('dectype').'.millesime_id' => $millesime->id,
                       T('dectype').'.code'         => $key);

      $includes = array('dectype');

      $declarations[$key] = Declaration::collect(array('filters' => $filters,
                                                       'include' => $includes));
    }
    return $declarations;
  }

  public static function hasLiasse($greffe) {
    $declarations = self::getDeclarations($greffe);
    foreach ($declarations as $_declarations) {
      if (count($_declarations) > 0)
        return true;
    }
    return false;
  }

  public static function getLiasse($greffe) {
    $declarations = self::getDeclarations($greffe);
    foreach ($declarations as $_declarations) {
      if (count($_declarations) > 0)
        return $_declarations->first();
    }
    return null;
  }

  public static function hasServiceLiasse($greffe) {
    return self::hasLiasse($greffe); // TODO
  }

  public static function generateLiassePDF($greffe) {
    $declarations = self::getDeclarations($greffe);
    $path_targets = array();

    foreach ($declarations as $dectype_code => $_declarations) {
      foreach ($_declarations as $declaration) {
        $dectype = Dectype::getInstance(array('code' => $dectype_code));
        $path_target  = $greffe->getDocumentPath() . '/liasse-' . String::urlify($dectype->name) . '-' . time() . '.pdf';
        $path_source  = str_replace('.pdf', '.html', $path_target);

        $content = H::get('/declaration.pdf.content', array('key'              => $declaration->getKey(),
                                                            'formulaire_codes' => self::$liasse_formulaires[$dectype_code]));
        $header = H::url('/declaration.pdf.header?key='.$declaration->getKey());
        $footer = H::url('/declaration.pdf.footer?key='.$declaration->getKey());

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
                         '--margin-top'     => '15',
                         '--margin-left'    => '10',
                         '--margin-right'   => '10',
                         '--margin-bottom ' => '5',
                         '--header-spacing' => '5',
                         '--footer-spacing' => '0',
                         '--outline-depth'  => '0');

        system('/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf '.NetDeclaration::asShellParams($options).' \''.$path_source.'\' \''.$path_target.'\'"');
        unlink($path_source);

        if (!isset($path_targets[$dectype_code]))
          $path_targets[$dectype_code] = array();
        $path_targets[$dectype_code][] = $path_target;
      }
    }
    return $path_targets;
  }

  public static function generatePackage($greffe) {
    self::checkAmitelDirs();

    $xml_path = $greffe->getDocumentPath() . '/' . $greffe->getId() . '_demande.xml';
    $xml_content = $greffe->asXml();
    file_put_contents($xml_path, $xml_content);

    $zip_path = self::getAmitelPath(self::AMITEL_DEMANDE_PATH) . '/'.$greffe->getId().'_demande.zip';
    if (file_exists($zip_path)) {
      unlink($zip_path);
    }

    $zip = new ZipArchive();
    $zip->open($zip_path, ZipArchive::CREATE);
    $zip->addFile($xml_path, basename($xml_path));

    // ----

    $registered_docs = $greffe->getDocuments();

    $file = self::concatenateBilanDocument($greffe);
    $filename = $greffe->getId() . '_bilan.pdf';
    $filename = iconv('UTF-8', 'IBM850', $filename);
    $zip->addFile($file, $filename);

    if (isset($registered_docs[self::DOC_ATTESTATION])) {
      $file = $registered_docs[self::DOC_ATTESTATION]['path'];
      $filename = $greffe->getId() . '_conformité.pdf';
      $filename = iconv('UTF-8', 'IBM850', $filename);
      $zip->addFile($file, $filename);
    }

    if (isset($registered_docs[self::DOC_DECLARATION_CONFIDENTIALITE])) {
      $file = $registered_docs[self::DOC_DECLARATION_CONFIDENTIALITE]['path'];
      $filename = $greffe->getId() . '_confidentialité.pdf';
      $filename = iconv('UTF-8', 'IBM850', $filename);
      $zip->addFile($file, $filename);
    }

    $zip->close();
  }

  public static function concatenateBilanDocument(Greffe $greffe) {
    $type_compte = $greffe->compte_type;
    $forme_juridique = $greffe->forme_juridique;
    $is_gerant = $greffe->is_gerant;
    $mode_direction = $greffe->mode_direction;
    $compte_public = $greffe->is_public;

    $registered_docs = $greffe->getDocuments();
    $required_docs = self::getRequiredDocs($type_compte, $forme_juridique, $is_gerant, $mode_direction, $compte_public);
    $required_concatenate_docs = self::$concat_doc_names[$greffe->compte_type];
    $documents = array();
    foreach ($registered_docs as $type => $doc) {
      if (in_array($type, $required_docs) && in_array($type, $required_concatenate_docs)) {
        $documents[$doc['type']] = $doc['path'];
      }
    }
    $documents = self::sortDocuments($documents, $required_concatenate_docs);

    if (isset($registered_docs[self::DOC_MANDAT_DEPOT])) {
      $documents[self::DOC_MANDAT_DEPOT] = $registered_docs[self::DOC_MANDAT_DEPOT]['path'];
    }

    if (self::hasServiceLiasse($greffe) && self::hasLiasse($greffe)) {
      if ($greffe->link_liasse_declaration) {
        foreach (self::generateLiassePDF($greffe) as $dectype_code => $files) {
          foreach ($files as $i => $file) {
            $documents[self::DOC_LIASSE.'_'.$dectype_code.'_'.$i] = $file;
          }
        }
      }
      else if (isset($registered_docs[self::DOC_LIASSE])) {
        $documents[self::DOC_LIASSE] = $registered_docs[self::DOC_LIASSE]['path'];
      }
    }


    if (empty($documents)) {
      throw new Exception('Aucun document à ajouter au bilan');
    }

    $filename = $greffe->getDocumentPath() . '/bilan_'.time().'.pdf';
    $cmd = 'gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -dPDFSETTINGS=/prepress -sOutputFile=' . $filename . ' ' . implode(' ', $documents);
    shell_exec($cmd);

    return $filename;
  }

  private static function sortDocuments($documents, $sorts) {
    $out = array();
    foreach ($sorts as $sort) {
      if (isset($documents[$sort])) {
        $out[$sort] = $documents[$sort];
      }
    }
    return $out;
  }

  public static function getAmitelPath($dir_name) {
    $base_path = self::getDocumentPath();
    return $base_path . '/' . $dir_name;
  }

  private static function checkAmitelDirs() {
    $paths = array(self::AMITEL_DEMANDE_PATH, self::AMITEL_ACK_PATH, self::AMITEL_REPONSE_PATH);
    foreach ($paths as $path) {
      $path = self::getAmitelPath($path);
      if (!file_exists($path)) {
        mkdir($path);
      }
    }
  }

  public static function getCodesInsee($zipcode, $labelize=false) {
    $filters = array('zipcode' => $zipcode);
    $label = $labelize ? 'CONCAT(code_insee, " (", name, " ", zipcode, ")")' : 'code_insee';
    $communes = Greffecommune::collect(array('filters' => $filters,
                                             'cols'    => array($label => 'code')));
    return $communes->asHash('id', 'code');
  }

  public static function generatePdfGreffe(Greffe $greffe) {
    $base_path = $greffe->getPdfPath();
    if (!file_exists($base_path)) {
      mkdir($base_path, 0777, true);
    }

    $adherent = $greffe->getAdherent();

    $path_target  = $base_path . '/depot-' . $adherent->getId() . '-' . $greffe->getId() . '.pdf';
    $path_source  = str_replace('.pdf', '.html', $path_target);

    $user = $adherent->getUser();
    $is_domtom = $user->hasFlag(User::FLAG_NTD_DOMTOM);

    $url_greffe_args = array(
      'id'    => $greffe->getId(),
      'print' => 1
    );
    $url_args = array(
      'domtom' => $is_domtom ? 1 : 0,
      'title'  => 'Dépot de greffe',
      'page'   => 0,
      'topage' => 0
    );

    $content = H::get('/middle/greffe.edit', $url_greffe_args);
    $header = H::url('/skeleton.pdf.header', $url_args);
    $footer = H::url('/skeleton.pdf.footer', $url_args);

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
                     '--margin-top'     => '15',
                     '--margin-left'    => '10',
                     '--margin-right'   => '10',
                     '--margin-bottom ' => '5',
                     '--header-spacing' => '5',
                     '--footer-spacing' => '0',
                     '--outline-depth'  => '0');

    system('/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf '.NetDeclaration::asShellParams($options).' \''.$path_source.'\' \''.$path_target.'\'"');
    unlink($path_source);

    return $path_target;
  }

  public static function getCodesInseeOnline($zipcode, $labelize=false) {
    $filters = array('zipcode' => $zipcode,
                     'status'  => Greffecommune::STATUS_ONLINE);
    $label = $labelize ? 'CONCAT(code_insee, " (", name, " ", zipcode, ")")' : 'code_insee';
    $communes = Greffecommune::collect(array('filters' => $filters,
                                             'cols'    => array($label => 'code')));
    return $communes->asHash('id', 'code');
  }
}
